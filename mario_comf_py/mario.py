def main():
    while (True):
        try:
            height = int(input("Height: "))
        except:
            print("Value error. The input must be a number.")
        else:
            if height >= 1 and height <= 8:
                break
            print("Incorrect assignment. Height must be between 1 and 8 (inclusive).")

    print_funct(height)


def print_funct(h):
    white_spaces = 0
    symbols = 0

    for y in range(0, h):
        white_spaces = h - y - 1
        symbols = y + 1
        print(" " * white_spaces, end="")
        print("#" * symbols, end="")
        print("  ", end="")
        print("#" * symbols)

    return


main()