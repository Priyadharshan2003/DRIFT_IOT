from queue import PriorityQueue

def ShortestPathV2X(graph, source, destination):
    distances = [float("inf") for _ in range(len(graph))] # initialize all distances as infinite
    distances[source] = 0 # set source distance as 0
    visited = set() # set to keep track of visited nodes
    pq = PriorityQueue() # priority queue to store nodes
    pq.put((0, source)) # add source node with distance 0

    while not pq.empty():
        (dist, node) = pq.get()
        if node in visited:
            continue
        visited.add(node)

        for neighbor in graph[node]:
            # calculate tentative distance to the neighbor
            tentative_distance = dist + get_v2x_info(node, neighbor) 
            if tentative_distance < distances[neighbor]:
                distances[neighbor] = tentative_distance
                pq.put((tentative_distance, neighbor))
    
    return distances

def get_v2x_info(node, neighbor):
    # function to retrieve V2X communication information (such as traffic conditions, road conditions, etc.)
    return 1 # for simplicity, return 1 for now

graph = {
    0: [1, 2],
    1: [0, 2],
    2: [0, 1]
}

source = 0
destination = 2

print(ShortestPathV2X(graph, source, destination))
