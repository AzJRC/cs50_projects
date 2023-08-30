import csv
import sys

filename = sys.argv[1]
print(f"The name of the file is: {filename}")

teams = []
with open(filename) as line:
    reader = csv.DictReader(line)
    for team in reader:
        team["rating"] = int(team["rating"])
        teams.append(team)
        print(team)

