import csv
import sys


def main():

    # TODO: Check for command-line usage
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable, database is now a list where each element
    # is a list of each row's contents.
    with open(sys.argv[1], "r") as dfile:
        dreader = csv.reader(dfile)  # a collection of lists
        database = list(dreader)

    # TODO: Read DNA sequence file into a variable, sreader is now a string of the entire
    # DNA sequence.
    with open(sys.argv[2], "r") as sfile:
        sreader = sfile.read()

    # TODO: Find longest match of each STR in DNA sequence. str_chains is a list of the
    # int values of the longest chain of each DNA sequence. The length and ordering of the
    # list is based on the length of the first row in the database, starting from 1,
    # ignoring the name. The for-loop iterates for each DNA sequence (e.g AGAT) & appends
    # the longest chain (int) of the DNA sequence to str_chains in same order as the first
    # row of the database csv.
    str_chains = []

    first_row_length = len(database[0])
    for i in range(1, first_row_length):
        str_chains.append(longest_match(sreader, database[0][i]))

    # TODO: Check database for matching profiles. The variables outcome & matches_found are the
    # outcome of comparing against the database & number of matches for a single person respectively.
    # The nested for-loop goes through each row of database (len(database) is the int value of the number
    # of rows) & compares the values of each DNA sequence (j+1 to exclude name) to the str_chains
    # list. If the current index of str_chains and the current index of the list in the database list
    # are the same, means there is a match of the current STR chain and matches_found is increased by
    # 1. If the matches_found equals the length str_chains, meaning all STRs have a match for the,
    # current individual, database[i][j=0], it is this person's DNA, and the nested-loop is broken.
    # If not, the matches_found is set back to zero for the next individual, for the next row of the
    # database. If after iterating through each list in the database list & a full match is not found,
    # the outcome remains as "No Match".
    matches_found = 0

    for i in range(1, len(database)):
        for j in range(len(str_chains)):

            if int(database[i][j+1]) == str_chains[j]:
                matches_found += 1

        if matches_found == len(str_chains):
            print(str(database[i][0]))
            sys.exit(0)

        else:
            matches_found = 0

    print("No Match")
    sys.exit(0)


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

            # Adjust substring start and end
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