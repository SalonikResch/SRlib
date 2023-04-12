
import numpy as np
import math

# Left child = 2*p+1
# Right child = 2*p+2
# parent = math.floor((c-1)/2)

def parentIndex(c):
    return math.floor((c-1)/2)

class Heap():
    def __init__(self):
        self.values = []

    def insert(self, val):
        # Increase size and add value
        self.values.append(val)

        # Push the value up the heap until its parent is bigger or it has no parent
        index = len(self.values)-1
        while index > 0 and parentIndex(index) >= 0 and self.values[parentIndex(index)] < self.values[index]:
            # Swap with parent
            t = self.values[parentIndex(index)]
            self.values[parentIndex(index)] = self.values[index]
            self.values[index] = t
            index = parentIndex(index)

    def heapify(self, index):
        l = 2*index + 1 # left child
        r = 2*index + 2 # right child

        largest = index
        if l < len(self.values) and self.values[l] > self.values[largest]:
            largest = l
        if r < len(self.values) and self.values[r] > self.values[largest]:
            largest = r

        # If parent is not the largest
        if largest != index:
            t = self.values[index]
            self.values[index] = self.values[largest]
            self.values[largest] = t
            self.heapify(largest)

    def pop(self):
        # The root is largest value
        r = self.values[0]
        # Get last value and move to root
        self.values[0] = self.values[-1]
        # Remove last value
        self.values = self.values[:-1]
        # Heapify
        self.heapify(0)
        # Return previous root
        return r

def test_heap()
    values = np.random.randint(low=0,high=1000,size=30)
    h = Heap()
    for v in values:
        h.insert(v)

    print('All values')
    print(values)
    print('The largest 10 are')
    l = [h.pop() for _ in range(10)]
    print(l)
