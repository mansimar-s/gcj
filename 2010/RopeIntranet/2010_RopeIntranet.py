from operator import itemgetter


def solve(rope_list):
    """ Solves the given problem"
    returns number of intersections visible : int"""

    rope_list.sort(key=itemgetter(0))
    count = 0

    for pair in rope_list:
        i = rope_list.index(pair)
        if i == len(rope_list) - 1:
            break

        for n in range(i + 1, len(rope_list)):
            #print "checking between: ", rope_list[i], rope_list[n]

            if rope_list[i][1] > rope_list[n][1]:
                #print "intersection found: ", rope_list[i], rope_list[n]
                count += 1
            else:
                continue

    return count

def main():
    """ Reads the input file and creates the output file"""

    fin = open("A-large-practice.in","r")
    fout = open("output_large.txt", "w")

    lines = fin.readlines()
    n = 1
    case = 1

    #for n in range(1, len(lines), (wires + 1)):
    while True:
        rope_list = []

        wires = int(lines[n])

        first_wireIndex = n + 1

        for wire in range(first_wireIndex, first_wireIndex + wires):

            wire_list = lines[wire].split()
            int_wire_list = []
            for e in wire_list:
                int_wire_list.append(int(e))
            rope_list.append(int_wire_list)
        output = solve(rope_list)
        result = "Case #{0}: {1}\n".format(case, output)
        fout.write(result)

        n += (wires + 1)
        if n == len(lines):
            break
        case += 1







main()