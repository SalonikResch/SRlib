import numpy as np

# Convert a matrix to CSR format
def toCSR(M):
    # Values array
    v = []
    # Col index
    c = []
    # Row start index
    r = []

    # Running count of non-zero elements
    count = 0

    # Go through and check for non-zero elements
    for i in range(M.shape[0]):
        for j in range(M.shape[1]):
            # If non-zero
            if M[i][j] != 0:
                v.append(M[i][j]) # Add to values
                c.append(j) # Record column
                count += 1 # Indicate a new non-zero element
        r.append(count)
    return v, c, r

# Expand from CSR to regular format
def fromCSR(n, m, v, c, r):
    # Create zero matrix
    M = np.zeros(shape=(n, m))

    # Running count of non-zero elements
    count = 0

    # Go row by row
    for i in range(len(r)):
        # Find how many elements in row
        start = 0
        if i > 0:
            start = r[i-1]
        stop = r[i]

        # Iterate over elements in this row, if any
        for j in range(stop-start):
            M[i][c[count]] = v[count]
            count += 1
    return M



def multiplyCSR(V, Col_Index, Row_Index, a):
    r = np.zeros(len(a))
    for i in range(len(a)):
        s = 0
        for j in range(Row_Index[i],Row_Index[j]):
            s += V[j] * a[Col_Index[j]]
        r[i] = s
    return r


def test_CSR():
    testMatrix = np.array([[0,2,0,0,4], [0,6,0,0,8], [10,12,0,0,14], [0,16,0,0,18]])

    print('Test Matrix')
    print(testMatrix)

    v, c, r = toCSR(testMatrix)
    print('In CSR format')
    print('v:',v)
    print('c:',c)
    print('r:',r)

    n = testMatrix.shape[0]
    m = testMatrix.shape[1]
    reconstructedMatrix = fromCSR(n, m, v, c, r)
    print('Reconstructed Matrix')
    print(reconstructedMatrix)

    assert np.allclose(testMatrix, reconstructedMatrix)

test_CSR()