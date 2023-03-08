class Node():
    def __init__(self, val=None):
        self.val = val
        self.neighbors = []


def identical(root1, root2):

    def searchAndCheck(node1, node2):
        if node1 is None and node2 is None:
            return True
        if node1 is None or node2 is None:
            return False
        if node1.val != node2.val:
            return False
        left = searchAndCheck(node1.left, node2.left)
        right = searchAndCheck(node1.right, node2.right)
        return left and right

    searchAndCheck(root1, root2)

test()