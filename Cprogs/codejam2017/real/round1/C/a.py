#!/usr/bin/python

import sys
import math

def main(argv):
    inputFile = argv[0];
    f = open(inputFile, 'r')
    T = int(f.readline())
    for i in range(1, T+1):
        line = f.readline()[:-1]
        N, K = [int(j) for j in line.split(' ')]
        cyl = []
        for k in range(1, N+1):
            line = f.readline()[:-1]
            R, H = [int(j) for j in line.split(' ')]
            cyl.append([R, H, 2*R*H])
        cyl.sort(key=lambda x: x[0])
        cyl = cyl[::-1]
        print("Case #%r: %.8f" % (i, solve(cyl, N, K)))

def solve(cyl, N, K):
    resultat = 0
    if N == K:
        resultat = cyl[0][0]**2
        for i in range(0, N):
            resultat += cyl[i][2]
        return resultat*math.pi

    for i in range(0, N-K+1):
        basis = cyl[i]
        temp = cyl[i][0]**2 + cyl[i][2] + best_heights(cyl, i+1, K-1)
        #print temp
        if temp > resultat:
            resultat = temp
    print math.pi
    return resultat*math.pi

def best_heights(cyl, i, K):
    resultat = 0
    sub_cyl = cyl[i::]
    sub_cyl.sort(key=lambda x: x[2])
    sub_cyl = sub_cyl[::-1]
    for j in range(0, K):
        resultat += sub_cyl[j][2]
    return resultat

if __name__ == '__main__':
    main(sys.argv[1:])

