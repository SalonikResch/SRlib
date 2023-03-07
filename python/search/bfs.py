import datetime


graph1 = {
    0: (5,29,4,7),
    1: (7,),
    2: (18,10),
    3: (9,7),
    4: (0,8),
    5: (0,9),
    6: (38,20),
    7: (0,3,1),
    8: (4,19,38),
    9: (5,22,21,3),
    10: (2,31,32,19),
    11: (26,12,13),
    12: (11,20),
    13: (11,28,27,14),
    14: (13,15),
    15: (14,),
    16: (21,26),
    17: (38,40,37),
    18: (30,2,22),
    19: (10,41,8),
    20: (6,12),
    21: (9,16),
    22: (18,9),
    23: (42,40),
    24: (27,46,33),
    25: (33,34),
    26: (16,11),
    27: (13,24),
    28: (13,),
    29: (0,),
    30: (47,31,18),
    31: (30,44,10),
    32: (44,10,41,45),
    33: (24,25),
    34: (25,36),
    35: (49,50),
    36: (39,34,51),
    37: (17,39),
    38: (8,17,6),
    39: (37,36),
    40: (23,17),
    41: (32,19,45,42),
    42: (41,23),
    43: (46,49),
    44: (47,31,48,32),
    45: (48,32,41),
    46: (24,43),
    47: (30,44),
    48: (44,45),
    49: (43,35),
    50: (35,51),
    51: (50,36)
}

class BFS():
    def __init__(self, graph):
        # A graph is a dict with {node: (neighbors,)}
        self.graph = graph

    def search(self, start, stop):
        if start == stop:
            return 0

        # Leading edge nodes
        active = [start]
        # Nodes that have already been visited
        visited = [start]
        # Record how many iterations it takes
        n_iterations = 0
        # Record how many nodes searched
        n_nodes = 0
        # Keep searching till it's found
        while True:
            n_iterations += 1
            # Get neighbors of active nodes
            neighbors = []
            for a in active:
                # For each of their neighbors
                for n in self.graph[a]:
                    if (n not in active) and (n not in visited) and (n not in neighbors):
                        neighbors.append(n)
                        n_nodes += 1
            # Check if it was found
            if stop in neighbors:
                return n_iterations, n_nodes
            # Set new neighbors to new active and add old active to visited
            for a in active:
                visited.append(a)
            active = neighbors
            
bfs = BFS(graph1)
start = datetime.datetime.now()
n_iterations, n_nodes = bfs.search(0, 15)
stop = datetime.datetime.now()

latency = stop - start
print("Search took",n_iterations,"iterations")
print('Search took',latency.microseconds,'us')