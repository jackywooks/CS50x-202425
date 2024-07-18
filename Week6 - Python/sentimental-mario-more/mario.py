from cs50 import get_int

def main():
    while (True):
        input = get_int("Please input a number: ")
        if (input > 0 and input < 9):
            break
    print_pyramid(input)

def print_pyramid(n):
    for i in range(1, n + 1):
        print(" " * (n - i), "#" * i, "  ", "#" * i, sep="")

main()
