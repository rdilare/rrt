from objects import *
from util import NearestNode, getNeighborNodes, getNodeOnLine, isGoalReached, isLineOnObstacle, isNodeInObstacle, sampleNode, updateNeighbors
from visualization import Viz

import sys

xlim = (-20,30)
ylim = (-20,30)
goal_threshold = 5
loop_count = 1000
max_segment_length = 2

neighborhood_radius = 10

start_node = Node(-10,-10, cost=0)
goal_node = Node(17,17)

obstacles = [Obstacle([(-15,5),(-10,2),(-2,3),(-5,15),(-8,10)]),
             Obstacle([(0,0),(-1,8),(4,5),(3,-2),(-2,-5)]),
             Obstacle([(5,-1),(5,-10),(18,-9),(20,3),(10,-5)]),
             Obstacle([(15,15),(25,15),(25,10),(10,10),(10,25),(15,25)])]

map = ConfigurationSpace(xlim, ylim, obstacles)
graph = Graph()
graph.addNode(start_node)
graph.addNode(goal_node)

isPath = False
i = 0
while i<=loop_count:
    i+=1
    print(f"i: {i-1}")
    new_node = sampleNode(xlim, ylim)
    if isNodeInObstacle(new_node, map):
        continue
    
    nearest_node = NearestNode(graph, new_node)
    if isLineOnObstacle(new_node, nearest_node, map):
        continue
    
    node_within_lim = getNodeOnLine(nearest_node, new_node, max_distance=max_segment_length)
    # -------------------------------
    sorted_neighbor_nodes = getNeighborNodes(node_within_lim,graph,neighborhood_radius)
    graph.addNode(node_within_lim)
    updateNeighbors(node_within_lim, sorted_neighbor_nodes, map)

    # graph.addEdge(nearest_node, node_within_lim)
    # -------------------------------
    if isGoalReached(node_within_lim, goal_node, map, threshold=goal_threshold) and not isPath:
        # graph.addEdge(node_within_lim, goal_node)
        isPath = True
        # break

if not isPath:
    print("can not find the path")
    sys.exit(0)
else:
    print("saving path to file: data.py")


with open("data.py",'w') as f:
    sn = start_node.getPos()
    gn = goal_node.getPos()
    tree = []
    path = []
    obs = []
    for obstacle in map.getObstacles():
        obs.append(obstacle.getVertices())

    # for n1 in graph.getEdges().keys():
    #     for n2 in graph.getEdges()[n1]:
    #         tree.append([n1.getPos(),n2.getPos()])

    for n in graph.getNodes():
        if n.getParent():
            tree.append([n.getPos(),n.getParent().getPos()])
    
    cn = goal_node
    while not cn is start_node:
        path.append(cn.getPos())
        cn = cn.getParent()
        print(f"cn : {cn.getPos()}")
    path.append(cn.getPos())


    data = f"start_node = {start_node.getPos()} \
            \ngoal_node = {goal_node.getPos()} \
            \nobstacles = {obs}\
            \ngraph = {tree}\
            \npath = {path}\
    "
    f.write(data)


print("data saved")