

def solve():
    with open("A-small-practice.in","r") as fin:
        with open("solved_Small.txt","w") as fout:
            lines =fin.readlines()
            cases = int(lines[0])
            for n in range(1, cases+1):
                line = lines[n].strip().split()
                if int(line[1]) % 2 == 0:
                    fout.write("Case #{}: WHITE\n".format(n))
                elif int(line[1]) % 2 == 1:
                    fout.write("Case #{}: BLACK\n".format(n))


solve()

