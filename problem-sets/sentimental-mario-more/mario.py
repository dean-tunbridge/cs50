height = int(input("Height: "))

while height < 1 or height > 8:
    height = int(input("Height: "))

for row in range(height):
    spaces = height - row

    for i in range(spaces + 1):
        print(" ", end="")

    for k in range(row + 1):
        print("#", end="")

    print("  ", end="")

    for j in range(row + 1):
        print("#", end="")

    print()
