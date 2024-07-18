# Addition
# x = int(input("x: "))
# y = int(input("y: "))

# print(x + y)

# Multiplication

# x = int(input("x: "))
# y = int(input("y: "))

# z = x / y
# print(f"{z:.50f}")

def get_int(prompt):
    while(True):
        try:
            return int(input(prompt))
        except ValueError:
            # print("Not an integer")
            pass # to pass the checking

def main():
    x = get_int("x: ")
    y = get_int("y: ")
    print(x + y)

main()
