while True:
    try:
       change = float(input("Change owed: "))
    except ValueError:
        continue

    if change < 0:
        continue

    break

change = round(change * 100)

coins = [25, 10, 5, 1]
total = 0

for coin in coins:
    total += change // coin
    change = change % coin


print(total)
