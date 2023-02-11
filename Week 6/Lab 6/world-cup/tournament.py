# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    filename = sys.argv[1]

# This portion opens the file for section of statements below & closes it automatically.
    with open(filename, "r") as file:
        reader = csv.DictReader(file)  # creates a collection of dictionaries.

# goes through each dictionary in the collection
        for team_dict in reader:

            # edits the rating portion of the key value pair, ie the values & adds it to the list teams.
            team_dict["rating"] = int(team_dict["rating"])
            teams.append(team_dict)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):
        champion = simulate_tournament(teams)
        if champion not in counts:
            counts[champion] = 1

        else:
            counts[champion] += 1


# Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    while len(teams) != 1:
        teams = simulate_round(teams)

# returns the "team", ie key, stored in the dictionary at the first index, 0.
    return teams[0]["team"]


if __name__ == "__main__":
    main()
