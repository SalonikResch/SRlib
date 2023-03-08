class Node():
    def __init__(self, val=None):
        self.val = val
        self.neighbors = []


def searchAndClone(node, clone, visited):
    print('In node',node.val)
    # Indicate that this node has been visited
    visited[node] = clone
    # Set same value in clone
    clone.val = node.val
    # Check and possibly clone neighbors
    for neighbor in node.neighbors:
        if neighbor in visited:
            print("See existing neighbor",visited[neighbor].val)
            clone.neighbors.append(visited[neighbor])
        else:
            print("Creating new neighbor",neighbor.val)
            new_clone = Node()
            searchAndClone(neighbor,new_clone, visited)
            clone.neighbors.append(new_clone)

def cloneGraph(node):
    clone = Node()
    visited = {}
    searchAndClone(node, clone, visited)
    #return clone

def test():
    nodes = []
    for i in range(5):
        nodes.append(Node(i))
    nodes[0].neighbors = [nodes[2],nodes[3],nodes[4]]
    nodes[1].neighbors = [nodes[2]]
    nodes[2].neighbors = [nodes[0]]
    nodes[3].neighbors = [nodes[2]]
    nodes[4].neighbors = [nodes[0],nodes[1],nodes[3]]

    clone = cloneGraph(nodes[0])


test()