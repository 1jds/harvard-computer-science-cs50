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

    # Read teams into memory from file
    teams = []
    csv_file = open(sys.argv[1], "r", encoding="utf8")
    my_csv_reader_dictionary = csv.DictReader(csv_file)
    for row in my_csv_reader_dictionary:
        row["rating"] = int(row["rating"])
        teams.append(row)
    csv_file.close()

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    round = 0
    while round < N:
        winning_team = simulate_tournament(teams)
        # print(winning_team)
        if winning_team in counts:
            counts[winning_team] += 1
        else:
            counts[winning_team] = 1
        round += 1
    print(len(counts))

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
    how_many_rounds = 0
    teams_playing = len(teams)
    while teams_playing > 1:
        teams_playing = teams_playing / 2
        how_many_rounds += 1

    round_count = 0
    winners = teams
    while round_count < how_many_rounds:
        winners = simulate_round(winners)
        round_count += 1
    return winners[0]["team"]


if __name__ == "__main__":
    main()
