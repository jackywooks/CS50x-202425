s = input("Do you agree? ").lower()

# if s == "Y" or s == "y":
#     print("Agreed")
# elif s == "N" or s == "n":
#     print("Not agreed")

if s in ["y", "yes"]:
    print("Agreed")
elif s in ["n", "no"]:
    print("Not Agreed")
