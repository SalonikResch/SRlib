
class BFS():
    def __init__(self, graph):
        # A graph is a dict with {node: (neighbors,)}
        self.graph = graph

    def search(start, stop):
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
                for n in self.graph[n]:
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
            

