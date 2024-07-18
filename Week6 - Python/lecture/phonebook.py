# names = ["Carter", "David", "John"]

# name = input("Name: ")

# # for loop can have else
# # for n in names:
# #     if name == n:
# #         print("Found")
# #         break
# # else:
# #     print("Not Found")


# if name in names:
#     print("Found")
# else:
#     print("Not Found")


# Loop though a dictonary array
# people = [
#     {"name": "Carter", "number": "+1 23210333-3213"},
#     {"name": "David", "number": "+1 213-3213"},
#     {"name": "John", "number": "+1 213-3213"},
# ]

# name = input("Name: ")

# for person in people:
#     if person["name"] == name:
#         print(f"Found {person["number"]}")
#         break
# else:
#     print("Not Found")

people = {
    "Jacky":"123123",
    "Koey":"41244",
    "James":"53336"
}
name = input("Name: ")

if name in people:
    print(f"Found {people[name]}")
else:
    print("Not Found")
