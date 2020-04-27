import sys, os
path2add = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__))))

if (not (path2add in sys.path)) :
    sys.path.append(path2add)

import numpy as np 
import pickle
import re
import os

PATH = "Validation_Data/"
IN_FILE = "InputDataC1.txt"
OUT_FILE = IN_FILE.split('.')[0] + '.npy'

HIJ_PATH = "External_hij/input_data/"
HIJ_FILE = "hij_input.txt"

# NMAX = 3 
NBP = 9

def convert(l):
    nl = []
    for s in l:
        nl.append(float(s))
    return nl

def parameter_parser(nmax):
    f = open(PATH+IN_FILE, "r")
    content = f.read().strip().split("\n")
    lbd, n0 = re.findall(r"\d+[.]?\d+", content[1])
    lbd = float(lbd)
    n0 = float(n0)

    if os.path.exists(PATH+OUT_FILE):
        fr = open(PATH+OUT_FILE, "rb")
        particles = pickle.load(fr)
    else:
        particles = []
        for line in content[4:]:
            params = re.findall(r"[-]?\d+[.]?\d+[Ee]?[+-]?[\d+]?", line)
            params = [*params[3:], params[2], *params[0:2]]
            params = convert(params)
            particles.append(params)
        
        particles = np.array(particles)
        fw = open(PATH+OUT_FILE, 'wb')
        pickle.dump(particles, fw)
        fw.close()
    f.close()

    if not os.path.exists(HIJ_PATH+HIJ_FILE):
        f = open(HIJ_PATH+HIJ_FILE,"w+")
        f.write("%d\n" % nmax)
        f.write("%d\n" % particles.shape[0])
        f.write("{:.10}\n".format(lbd))
        f.write("{:.10}\n".format(n0))
        for i in range(particles.shape[0]):
            f.write("{:.10} {:.10} {:.10}".format(particles[i][0], particles[i][1], particles[i][2]))
            f.write("\n")
    f.close()

    print("input: lbd, n0, particles\n")
    print(lbd, n0)
    print(particles)
    return lbd, n0, particles


if __name__ == "__main__":
    lbd, n0, particles = parameter_parser(3)
    # hij_input_parser(particles, lbd, n0, 3, particles.shape[0])


    

