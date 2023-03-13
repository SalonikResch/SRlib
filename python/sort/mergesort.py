import numpy as np


def merge(a,b):
    r = np.zeros(len(a)+len(b))
    aIdx = 0
    bIdx = 0
    rIdx = 0
    while aIdx < len(a) and bIdx < len(b):
        # Take whichever is smaller
        if a[aIdx] > b[bIdx]:
            r[rIdx] = b[bIdx]
            bIdx += 1
        else:
            r[rIdx] = a[aIdx]
            aIdx += 1
        rIdx += 1

    # Fill in remaining values from one of the arrays
    for i in range(aIdx, len(a)):
        r[rIdx] = a[i]
        rIdx += 1
    for i in range(bIdx, len(b)):
        r[rIdx] = b[i]
        rIdx += 1

    return r

def mergesort(a):
    if len(a) == 2:
        if a[1] < a[0]:
            t = a[1]
            a[1] = a[0]
            a[0] = t
        return a
    if len(a) < 2:
        return a
    m = int(len(a)/2)
    l = mergesort(a[:m])
    r = mergesort(a[m:])

    a = merge(l,r)
    return a


a = np.random.randint(low=0,high=100,size=25)

print('Unsorted:',a)
b = mergesort(a)
print('Sorted:',b)