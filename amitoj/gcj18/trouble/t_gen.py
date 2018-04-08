import random
N = 100000;

with open("large.in", "w") as out:
    out.write(str(N))
    out.write("\n")
    for i in range(N):
        out.write('100')
        out.write("\n")
        for n in range(100):
            out.write(str(random.randint(1,int(1e9))))
            out.write(" ")
        out.write("\n")
        
