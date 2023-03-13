import numpy as np

def findFirstGreater(a, v, l, r):
    if l == r:
        return l

    m = int((l+r)/2)
    if a[m] <= v:
        l = m + 1
    else:
        r = m
    return findFirstGreater(a, v, l, r)

def insertInto(a, v):
    index = findFirstGreater(a=a, v=v, l=0, r=len(a))
    a = np.insert(arr=a,obj=index, values=v)
    return a

def checkIncreasing(a):
    for i in range(1,len(a)):
        if a[i] < a[i-1]:
            return False
    return True

for i in range(100):
    size = np.random.randint(low=1,high=13)
    v = np.random.randint(low=0,high=100)
    a = np.random.randint(low=0,high=100,size=size)
    a.sort()

    b = insertInto(a, v)

    assert len(b) == len(a) + 1
    assert checkIncreasing(b)

