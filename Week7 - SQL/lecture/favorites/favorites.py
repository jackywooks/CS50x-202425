import csv

# # Pythonic Way to read through file
# with open("favorites.csv","r") as file:
#     reader = csv.reader(file)
#     # Skip the first row of metadata
#     next(reader)
#     for row in reader:
#         favorite = row[1]
#         print(favorite)

# # Use dict Reader
# with open("favorites.csv","r") as file:
#     reader = csv.DictReader(file)
#     scratch, c, python = 0, 0, 0
#     for row in reader:
#         favorite = row["language"]
#         if favorite == "Scratch":
#             scratch += 1
#         elif favorite == "C":
#             c += 1
#         elif favorite == "Python":
#             python += 1

#     print(f"Scratch: {scratch}")
#     print(f"C: {c}")
#     print(f"Python: {python}")

# # use empty dict for count
# with open("favorites.csv", "r") as file:
#     reader = csv.DictReader(file)
#     counts = {}
#     for row in reader:
#         favorite = row["language"]
#         if favorite in counts:
#             counts[favorite] += 1
#         else:
#             counts[favorite] = 1

# use collection Counter to count
from collections import Counter
with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = Counter()
    for row in reader:
        favorite = row["problem"]
        counts[favorite] += 1

# # sort dict by key
# for favorite in sorted(counts):
#     print(f"{favorite}: {counts[favorite]}")

# # sort dict by value, descendingly
# for favorite in sorted(counts, key=counts.get, reverse=True):
#     print(f"{favorite}: {counts[favorite]}")


# sort dict by build in Counter() function
# Counter() is a counter object
# most_common() returned a list of tuple
# for favorite, count in counts.most_common():
#     print(f"{favorite}: {count}")


favorite = input("Favorite: ")
print(f"{favorite}: {counts[favorite]}")
