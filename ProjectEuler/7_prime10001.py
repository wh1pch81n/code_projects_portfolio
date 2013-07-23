#!/usr/bin/python
from math import sqrt

def seiveArray(max=1000):
    seive = []
    filterSeive = []
    for I in range(0,max): #init seive with all nums set an prime
        #print "# %d" %(I)
        seive.append(True)
    s = int(sqrt(max))
    seive[0] = False
    seive[1] = False
    for I in range(0, s): #do some seive magic to disqualify non primes
        if(seive[I] == True):
            J = I*I
            jmul = 0
            while( (J+jmul) < max):
                seive[J+jmul] = False
                jmul += I
    for K in range(0, len(seive)): #make array of only primes
        pp = ""
        if seive[K] == True:
            pp = "prime"
            filterSeive.append(K)
        #print "%d:  %s" %(K, pp)

    return filterSeive
def seive10001():
    i = 2
    m = []
    while len(m) < 10001:
        m = seiveArray(i)
        i *= 2
        #print len(m)
    return m[10000]
if __name__ == "__main__":
    print ">>>>>>>\tew"
    print seive10001()
    #m = seiveArray(200000)
    #for I in range(0, len(m)):
        #print "%d: %d" % (I +1, m[I])
    #//print "%d: %d" % (len(m), m[len(m)-1])
    print ">>>>>>>\tdone"
