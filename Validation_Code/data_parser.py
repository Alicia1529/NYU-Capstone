import numpy as np
import pickle
main_dir = "External_hij/data/"
dtype = "complex128"

def data_parser(nbp, nmax):

    dimt = 2 * nmax * (nmax + 2)

    matrices = ["H", "J"]

    for matrix in matrices:
        # sub_path = matrix + "_Matrix/"
        mt = np.ones((nbp, nbp, dimt, dimt), dtype=dtype)
        for row in range(1, nbp + 1):
            for col in range(1, nbp + 1):
                if row == col:
                    continue
                file = matrix + "(" + str(row) + "," + str(col) + ")_" + ".txt"
                fullpath = main_dir + file
                fp = open(fullpath, "r")
                content = fp.read().strip().split("\n")[4:]
                idx = 0
                for line in content:
                    # not sure about the order of sub_row and sub_col
                    sub_row = idx // dimt
                    sub_col = idx % dimt
                    each = line.split()[1:]
                    # print(row, col, sub_row, sub_col, each)
                    re, im = eval(each[0]), eval(each[1])
                    mt[row - 1, col - 1, sub_row, sub_col] = re + im*1.j
                    idx += 1
        output = open(main_dir + matrix + '.npy', 'wb')
        pickle.dump(mt, output)
        output.close()

if __name__ == "__main__":
    nmax = 3
    nbp = 9
    data_parser(nbp, nmax)