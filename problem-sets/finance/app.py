import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user id
    user_id = session["user_id"]

    # Get users stocks
    stocks = db.execute(
        "SELECT name, price, symbol, SUM(shares) FROM transactions WHERE user_id = ? GROUP BY symbol",
        user_id
    )

    # Get users cash total
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Get total
    total = cash
    for stock in stocks:
        curr_stock = lookup(stock["symbol"])
        total += curr_stock["price"] * stock["SUM(shares)"]

    return render_template("index.html", stocks=stocks, cash=cash, total=total, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Get stock symbol and convert to uppercase
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)

        # Check for valid symbol or empty submit
        if not symbol:
            return apology("Please Enter a Stock")

        # Check for valid stock
        elif not stock:
            return apology("Invalid Stock")

        # Check share is an integer
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Share must be a number")
            
        # Check that the share amount is a positive integer
        if shares <= 0:
            return apology("Share must be positive number")

        # Get user id
        user_id = session["user_id"]

        # Use user id to get cash value from db
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        stock_price = stock["price"]
        stock_name = stock["name"]
        total_sum = stock_price * shares

        # Check if user can afford that stock with their current cash
        if cash < total_sum:
            return apology("Insufficient funds for transaction")

        else:
            # Update db with new cash total after purchasing stock
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?",
                cash - total_sum,
                user_id
            )

            # Add transaction to transaction table
            db.execute(
                "INSERT INTO transactions (user_id, name, shares,price, type, symbol) VALUES (? ,? ,? ,? ,? ,?)",
                user_id,
                stock_name,
                shares,
                stock_price,
                "buy",
                symbol
            )
            
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?",
            request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Please enter a stock symbol")

        stock = lookup(symbol)

        if not stock:
            return apology("Invalid stock code")

        usd_price = usd(stock["price"])
        return render_template("quoted.html", stock=stock, usd_price=usd_price)

    elif request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check for valid entries for each value in form
        if not username:
            return apology("Please enter a username")

        elif not password:
            return apology("Please enter a password")

        elif not confirmation:
            return apology("Please confirm password")

        elif password != confirmation:
            return apology("Please ensure passwords match")

        # Generate hashed password
        hash = generate_password_hash(password)

        # Insert new user into database
        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                username,
                hash
            )

            # Login as current user
            current_user = db.execute(
                "SELECT id FROM users WHERE username = ?",
                request.form.get("username")
            )

            session["user_id"] = current_user[0]["id"]
            return redirect('/')

        except:
            return apology("Username already in use", 200)

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        # Get user id
        user_id = session["user_id"]

        # Get symbol
        symbol = request.form.get("symbol")

        # Get shares
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Share must be a number")

        # Check if they have shares
        if shares <= 0:
            return apology("Share must be positive number")
          
        # Get stock symbol and convert to uppercase
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
          
        # Check for valid symbol or empty submit
        if not symbol:
            return apology("Please Enter a Stock")
          
        # Check for valid stock
        elif not stock:
            return apology("Invalid Stock")

        # Get stock price
        stock_price = stock["price"]

        # Get stock name
        stock_name = stock["name"]

        # Get current amount of shares
        curr_shares = db.execute(
            "SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
            user_id,
            symbol
        )[0]["SUM(shares)"]

        # Check if user has enough shares to sell
        if curr_shares < shares:
            return apology("You don't have enough shares to sell")

        # Get current cash
        curr_cash = db.execute(
            "SELECT cash FROM users WHERE id = ?",
            user_id
        )[0]["cash"]

        # Update users cash
        price = shares * stock_price
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            curr_cash + price,
            user_id
        )

        db.execute(
            "INSERT INTO transactions (user_id, name, shares,price, type, symbol) VALUES (? ,? ,? ,? ,? ,?)",
            user_id,
            stock_name,
            -shares,
            stock_price,
            "sell",
            symbol
        )

        return redirect("/")

    else:
        # Get user id
        user_id = session["user_id"]

        # Get symbols
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol",
            user_id
        )

        return render_template("sell.html", symbols=symbols)