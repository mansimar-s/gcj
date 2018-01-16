

def solve(n):
    for e in range(n,1,-1):
        listed = [int(d) for d in str(e)]
        if sorted(listed) == listed:
            return str(e)


def main():
    with open("sample.txt","r") as fin:
        with open("solved.txt", "w") as fout:
            lines = fin.readlines()
            cases = lines[0]
            for i in range(1,int(cases)+1):
                fout.write("Case #{}: {}\n".format(i,solve(int(lines[i]))))

main()
