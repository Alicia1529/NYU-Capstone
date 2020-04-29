import sys, os
path2add = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__))))

if (not (path2add in sys.path)) :
    sys.path.append(path2add)

import numpy as np 
import pickle
import re
import os

PATH = "Validation_Data/"

HIJ_PATH = "External_hij/input_data/"
HIJ_FILE = "hij_input.txt"

def parameter_parser(nmax, IN_FILE):
    # OUT_FILE = IN_FILE.split('.')[0] + '.npy'
    
    f = open(PATH+IN_FILE, "r")
    content = f.read().strip().split("\n")
    lbd = eval(content[0].strip())
    n0 =  eval(content[1].strip())

    particles = []
    for line in content[2:]:
        line = line.strip().strip("{|};").split(",")[1:]
        params = list(map(lambda x: eval(x.strip()), line))
        particles.append(params)
    
    particles = np.array(particles)
    # fw = open(PATH+OUT_FILE, 'wb')
    # pickle.dump(particles, fw)
    # fw.close()
    # f.close()

    # if not os.path.exists(HIJ_PATH+HIJ_FILE):
    f = open(HIJ_PATH+HIJ_FILE,"w+")
    f.write("%d\n" % nmax)
    f.write("%d\n" % particles.shape[0])
    f.write("{:.10}\n".format(lbd))
    f.write("{:.10}\n".format(n0))
    for i in range(particles.shape[0]):
        f.write("{:.10} {:.10} {:.10}".format(particles[i][0], particles[i][1], particles[i][2]))
        f.write("\n")
    # f.close()

    print("input: nmax {}, lbd {}, n0 {}\n".format(nmax, lbd, n0))
    print("particles: x, y, z, a, ren, imn")
    print(particles)
    return lbd, n0, particles


if __name__ == "__main__":
    nmax = 7
    IN_FILE = "InputDataC2.txt"
    lbd, n0, particles = parameter_parser(nmax, IN_FILE)
    # hij_input_parser(particles, lbd, n0, 3, particles.shape[0])


    

