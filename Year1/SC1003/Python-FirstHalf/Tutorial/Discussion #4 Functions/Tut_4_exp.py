import math

#database, use dictionary, tuple as keys.
grades = {
    ("G1", 1): 45,
    ("G1", 2): 75,
    ("G1", 3): 85,
    ("G1", 4): 120,
    ("G2", 1): 75,
    ("G2", 2): 85,
    ("G2", 3): 100,
    ("G2", 4): 25
}

def inserrRecord(database,group,id,score):
    dataKey = (group.id)
    database[dataKey] = score

def query(database,group,id):
    try:
        dataKey = (group,id)
        return database[dataKey]
    except:
        return None

def listGrades(database,group):
    listOfScores = []
    for key, value in database.items():
        if key[0] == group:
            listofScores.append(value)
    return listOfScores

def maxGrade(database,group):
    scores = listGrades(database,group)
    return max(scores)
