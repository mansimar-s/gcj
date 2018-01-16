
def solve(s, fs):

    start = 0
    count = 0
    while True:
        try:
            beg = s.index("-")
            """

            Latest Change was adding the following if

            """
            #if beg > len(fs) - 1:
                #return "IMPOSSIBLE"
        except:
            return count

        count += 1

        for k in range(beg,beg+fs):
            if s[k] == "-":
                s[k] = "+"
            else:
                s[k] = "-"
            start = beg+1
        print(s)
        print(start)
        if start > len(s) - fs +1:
            if "-" in s:
                return "IMPOSSIBLE"
            else:
                return count





with open("sample.txt","r") as fin:
    with open("solved.txt","w") as fout:
        cases = int(fin.readline())
        case = 0
        for line in fin:
            case += 1
            list_array = line.rstrip().split()
            fout.write("Case #{}: {}\n".format(case, solve(list(list_array[0]),
                                                         int(list_array[1]))))





