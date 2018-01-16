"""shyness"""

def solveProblem(Smax, distribution):
    print "Solving ",Smax, " ", distribution

    totalStanding = 0
    needed = 0
    totalNeeded = 0
    for people in distribution:
        moreNeeded = needed - totalStanding
        totalStanding += int(people)
        needed += 1
        if moreNeeded > 0:
            totalNeeded += moreNeeded
            totalStanding += moreNeeded

    return totalNeeded

def main():
    inputFile = open("test.in.txt", "r")

    N = int(inputFile.readline().strip())
    #print "Total cases = ", N, " N+1 = ", (N+1)

    for line in inputFile:
        simpleLine = line.strip()
        parts = simpleLine.split(' ')
        Smax = int(parts[0])
        dist = parts[1]
        result = solveProblem(Smax, dist)
        print "Result = ", result

main()
