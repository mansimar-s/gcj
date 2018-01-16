

def solve(n):

    p = 1

    while True:
        listed = [int(d) for d in str(n)]

        if sorted(listed) == listed or len(listed) == 1:
            return str(n)

        if n % 10 == 0:
            n -= 1
            continue
        else:
            n -= n % (10**p)
            p += 1



def main():
    with open("B-small-practice.in","r") as fin:
        with open("solved_small.txt", "w") as fout:
            lines = fin.readlines()
            cases = lines[0]
            for i in range(1,int(cases)+1):
                fout.write("Case #{}: {}\n".format(i,solve(int(lines[i]))))

main()
