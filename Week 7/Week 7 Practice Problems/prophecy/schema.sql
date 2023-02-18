CREATE TABLE only_students(id INTEGER, student_name TEXT, PRIMARY KEY(id));
CREATE TABLE only_houses(id INTEGER, house TEXT, PRIMARY KEY(id));
CREATE TABLE house_assigments(id INTEGER, student_name TEXT, assigned_house TEXT, PRIMARY KEY(id));