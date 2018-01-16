def solve(list_a, list_b):

    list_a.sort()
    list_b.sort()

    i = 0
    j = len(list_b) - 1
    min_product = 0

    while True:

        min_product += list_a[i] * list_b[j]
        if i == len(list_a) - 1:
            break
        i += 1
        j -= 1

        continue
    return min_product


def main():

    fin = open("A-large-practice.in", "r")
    fout = open("large_out.txt", "a")

    lines = fin.readlines()
    count = 1

    for n in range(2, len(lines), 3):
        list1 = lines[n].split()
        int_list1 = []
        for e in list1:
            int_list1.append(int(e))
        list2 = lines[n + 1].split()
        int_list2 = []
        for e in list2:
            int_list2.append(int(e))

        print int_list1
        print int_list2

        result = solve(int_list1, int_list2)

        output = "Case #{0}: {1}\n".format(count, result)
        fout.write(output)

        count += 1

    fin.close()
    fout.close()

main()
