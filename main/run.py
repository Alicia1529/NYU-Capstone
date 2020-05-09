import sys, os
path2add = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__))))

if (not (path2add in sys.path)) :
    sys.path.append(path2add)


import time
import pickle
import os
from OAEC import oaec
from parameter_parser import parameter_parser
from data_parser import data_parser

test_num = 1
config_num = {1: 9, 2: 14, 3:10, 4: 9, 5: 13, 6:3}
num = config_num[test_num]
nmax_list = range(12, 13)
parallel = True

if parallel:
    import ray
    print("#"*50)
    print(sys.argv)
    redis_password = sys.argv[1]
    num_workers = int(sys.argv[2])
    # os.environ["ip_head"] = "10.214.97.24:6379"
    ray.init(address=os.environ["ip_head"], redis_password=redis_password)

    print("Nodes in the Ray cluster:")
    print(ray.nodes())

    from RCTMA_parallel import rctma
else:
    num_workers = 1 # decoration
    from RCTMA_sequential import rctma

IN_FILE = "InputDataC{}.txt".format(str(test_num))

num_iter = 10


for nmax in nmax_list:
    time1 = time.time()
    lbd, n0, particles = parameter_parser(nmax, IN_FILE)

    # os.system("module load cmake")
    # os.system("cmake external/CMakeLists.txt")
    # os.system("(cd external && make)") 
    # os.system("./external/external_hij")  
    # data_parser(num, nmax)

    time2 = time.time()
    print("Time for preparing Hij is:", time2 - time1)

    time_taken = []
    for i in range(num_iter):
        rctma_start = time.time()
        T = rctma(num, nmax, lbd, n0, particles, num_workers)
        rctma_end = time.time()
        interval = rctma_end - rctma_start
        time_taken.append(interval )
        print("i {}, interval {}".format(str(i), str(interval )))
    print("Average Time for computing vscatter and rcmta matrices is:", sum(time_taken[1:])/(num_iter - 1))

    J = pickle.load(open("external/data/J.npy", "rb"))
    time3 = time.time()
    Cext = oaec(lbd, n0, T, J)
    time4 = time.time()
    print("Time for reading Jij and computing OAEC is :", time4 - time3)
    print("Cext:", Cext)
