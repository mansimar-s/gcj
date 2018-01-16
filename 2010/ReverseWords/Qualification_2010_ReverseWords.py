

#def reverse_list_str(word_list):

    #res_str = ""
    #reverse_list = word_list[-1::-1]
    #for word in reverse_list:
        #if reverse_list.index(word) == len(reverse_list) - 1:
            #res_str += word
        #else:

            #res_str += word
            #res_str += " "
    #return res_str

#print reverse_list_str(["abc", "def", "pqr"])

def reverse_list(word_list):

    res = ""

    reverse_list_words = word_list[-1::-1]
    for e in reverse_list_words:
        res += e
        res += " "
    return res
print reverse_list(["abc", "def", "pqr"])



def main():

    fin = open("B-large-practice.in", "r")
    fout = open("output_file_large.txt", "a")

    lines = fin.readlines()

    cases = int(lines[0])



    for n in range(1, cases + 1):

        res = reverse_list(lines[n].split())
        output = ("Case #{0}: " + res + "\n").format(n)
        fout.write(output)

    fin.close()
    fout.close()

main()


#