import csv
from cs50 import SQL

# main() access assigns the database, newroster.db to the variable db. Then, the students.csv
# file is read and each line (a list of values) is stored into reader which is a collection
# of these lists. Then, for each list in reader the respective values of each index of the list
# is added to the respective tables in the database newroster.db.
def main():
    db = SQL("sqlite:///newroster.db")
    with open("students.csv", "r") as file:
        reader = csv.reader(file)
        next(reader)

        for list in reader:
            db.execute("INSERT INTO only_students (id, student_name) VALUES (?, ?);", int(list[0]), list[1])
            db.execute("INSERT INTO only_houses (id, house) VALUES (?, ?);", int(list[0]), list[2])
            db.execute("INSERT INTO house_assigments (id, student_name, assigned_house) VALUES (?, ?, ?);", int(list[0]), list[1], list[2])


if __name__ == "__main__":
    main()