def solve(total, price_list):

    sorted_price_list = price_list[:]
    sorted_price_list.sort()


    i = 0
    j = len(price_list) - 1
    res = []
    while True:


        if (sorted_price_list[i] + sorted_price_list[j]) > total:
            #print sorted_price_list[i], sorted_price_list[j], total
            j -= 1
            continue

        elif (sorted_price_list[i] + sorted_price_list[j]) < total:
            #print sorted_price_list[i], sorted_price_list[j], total

            i += 1
            continue

        if sorted_price_list[i] + sorted_price_list[j] == total:
            #print sorted_price_list[i], sorted_price_list[j], total
            res.append(price_list.index(sorted_price_list[i]) + 1)
            res.append(price_list.index(sorted_price_list[j]) + 1)
            res.sort()
            if res[0] == res[1]:
                res[1] = res[0] + 1
            #print res
            return res
            break
#print solve(100, [35, 25, 75])

def main():

    fin = open("A-large-practice.in", "r")
    fout = open("large_out.txt", "a")

    lines = fin.readlines()

    count = 1

    for n in range(1, len(lines), 3):

        c = int(lines[n])
        word_list = lines[n + 2].split()
        int_list = []
        for e in word_list:
            int_list.append(int(e))

        result = solve(c, int_list)

        output = "Case #{0}: {1} {2}\n".format(count, result[0], result[1])
        #print "writing : ", result[0], result[1]
        fout.write(output)

        count += 1

    fin.close()
    fout.close()

main()



