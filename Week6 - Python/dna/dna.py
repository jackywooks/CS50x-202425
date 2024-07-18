import csv
from sys import argv


def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("Command-line argument Incorrect, dna.py [database.csv] [sequence.txt]")

    # Read database file into a variable
    rows = []
    with open(argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)

    # Read DNA sequence file into a variable
    with open(argv[2]) as file:
        dnaSeq = file.read()

    # Find longest match of each STR in DNA sequence and store it in a dict
    subSeqList = reader.fieldnames[1::]
    dnaDict = {}
    for subSeq in subSeqList:
        dnaDict[subSeq] = longest_match(dnaSeq, subSeq)

    # Check database for matching profiles

    # Using a flag variable to check all of the DNA sub seq is correct
    # for row in rows:
    #   for index, subSeq in enumerate(subSeqList):
        # row["Flag"] = True
        # if int(row[subSeq]) != dnaDict[subSeq]:
        #     row["Flag"] = False
        #     break
        # if (row["Flag"] == True and index == len(subSeqList) -1):
        #    print(row["name"])

    # Using All function
    for row in rows:
        if all(int(row[subSeq]) == dnaDict[subSeq] for subSeq in subSeqList):
            print(row["name"])
            return

    print("No Match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)
    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0
        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and en
            start = i + count * subsequence_length
            end = start + subsequence_length
            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            # If there is no match in the substring
            else:
                break
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
