from cs50 import get_int

while True:
    try:
       change = get_int("Change owed: ")
    except ValueError:
        continue

    if change < 0:
        continue

    break

coins = [25, 10, 5, 1]
total = 0

for coin in coins:
    total += change // coin
    change = change % coin

print(total)
