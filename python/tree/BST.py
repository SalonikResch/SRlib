class Node():
    def __init__(self, val, parent=None):
        self.val = val
        self.parent = parent
        self.right = None
        self.left = None

# In order traversla of BST
def inOrder(node):
    if node.left is not None:
        inOrder(node.left)
    print(node.val)
    if node.right is not None:
        inOrder(node.right)

def minimum(node):
    while node.left is not None:
        node = node.left
    return node


def maximum(node):
    while node.right is not None:
        node = node.right
    return node


# Right rotation 
def rightRotation(a, parent):
    b = a.left
    a.left = b.right
    b.right = a
    if parent.left == a:
        parent.left = b
    else:
        parent.right = b

# Left Rotation
def leftRotation(a, parent):
    b = a.right
    a.right = b.left
    b.left = a
    if parent.left == a:
        parent.left = b
    else:
        parent.right = b


def transplant(root, u, v):
    if u.parent is None:
        root = v
    elif u == u.parent.left:
        u.parent.left = v
    else:
        u.parent.right = v
    if v is not None:
        v.parent = u.parent


def delete(root, node):
    if node.left is None:
        transplant(root, node, node.right)
    elif node.right is None:
        transplant(root, node, node.left)
    else:
        y = minimum(node.right)
        if y.parent != node:
            transplant(root, y, y.right)
            y.right = node.right
            y.right.parent = y
        transplant(T, node, y)
        y.left = node.left
        y.left.p = y

inOrder(testGraph1())