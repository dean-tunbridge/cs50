while True:
    try:
        height = int(input("Height: "))
    except ValueError:
        continue

    if height < 1 or height > 8:
        continue

    break

for row in range(height):
    spaces = height - row - 1

    for i in range(spaces):
        print(" ", end="")

    for k in range(row + 1):
        print("#", end="")

    print("  ", end="")

    for j in range(row + 1):
        print("#", end="")

    print()
