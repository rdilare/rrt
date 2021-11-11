import numpy as np

from objects import ConfigurationSpace
from objects import Node


def getNodeOnLine(p,q,max_distance=10):
    x1,y1 = p.getPos()
    x2,y2 = q.getPos()
    distance = ((x1-x2)**2 + (y1-y2)**2)**0.5
    if max_distance >= distance:
        return q
    
    dx = x2-x1
    dy = y2-y1

    x = x1 + dx*(max_distance/distance)
    y = y1 + dy*(max_distance/distance)
    return Node(x,y)


def calculateCost(n1, n2):
    """
    calculate cost to reach n2 through n1 (include the cost of n1)

    n1,n2 -> Node objects
    """
    x1,y1 = n1.getPos()
    x2,y2 = n2.getPos()
    dist = ((x1-x2)**2 + (y1-y2)**2)**0.5

    cost = n1.getCost() + dist
    return cost

# def getNeighborNodes(node, graph, neighbor_radius):
#     neighbor_nodes = []
#     min_cost = float('inf')
#     shortest_parent = None
#     for n in graph.getNodes():
#         x1,y1 = node.getPos()
#         x2,y2 = n.getPos()
#         dist = ((x1-x2)**2 + (y1-y2)**2)**0.5
#         if dist <= neighbor_radius:
#             neighbor_nodes.append(n)

#             cost = n.getCost() + dist
#             if cost <= min_cost:
#                 shortest_parent = n
#                 min_cost = cost
#     return neighbor_nodes, shortest_parent, min_cost


def getNeighborNodes(node, graph, neighbor_radius):
    neighbor_nodes = {}
    for n in graph.getNodes():
        x1,y1 = node.getPos()
        x2,y2 = n.getPos()
        dist = ((x1-x2)**2 + (y1-y2)**2)**0.5
        if dist <= neighbor_radius:
            cost = n.getCost() + dist
            neighbor_nodes.update({n:cost})
    sorted_neighbor_nodes = sorted(neighbor_nodes.keys(), key=lambda x:neighbor_nodes[x])
    return sorted_neighbor_nodes


def orientation(p,q,r):
    val = (q[1]-p[1])*(r[0]-p[0]) - (r[1]-p[1])*(q[0]-p[0])
    if val == 0:
        return 0
    elif val<0:
        return -1
    else:
        return 1

def doIntersect(p1,q1,p2,q2):
    o1 = orientation(p1,q1,p2)
    o2 = orientation(p1,q1,q2)
    o3 = orientation(p2,q2,p1)
    o4 = orientation(p2,q2,q1)

    if o1 != o2 and o3 != o4:
        return True
    return False

def isPIP(point, polygon):
    """
    checks if a Point is In Polygon.
    point -> tuple of Point's coordinate
    polygon -> list of Polygon's vertices
    """
    count = 0
    p = point
    q = (1000000000, p[1])

    l = len(polygon)
    for i in range(l):
        i1 = i
        i2 = (i+1)%l
        p1 = polygon[i1]
        q1 = polygon[i2]
        if doIntersect(p,q,p1,q1):
            count+=1

    if count%2 == 0:
        return False
    elif count%2 == 1:
        return True


def isLineOnPolygon(p,q,polygon):
    """
    p -> tuple
    q -> tuple
    polygon -> list of tuples
    """

    l = len(polygon)
    for i in range(l):
        i1 = i
        i2 = (i+1)%l
        p1 = polygon[i1]
        q1 = polygon[i2]
        if doIntersect(p,q,p1,q1):
            return True
    return False


def sampleNode(xlim,ylim):
    x = np.random.uniform(*xlim)
    y = np.random.uniform(*ylim)
    return Node(x,y)


def NearestNode(graph,newNode):
    nodes = graph.getNodes()
    minDist = float("inf")
    nearestNode = None
    for node in nodes:
        x1,y1 = newNode.getPos()
        x2,y2 = node.getPos()
        dist = ((x1-x2)**2 + (y1-y2)**2)**0.5
        if dist < minDist:
            minDist = dist
            nearestNode = node
    return nearestNode


def isNodeInObstacle(node, space):
    if not isinstance(space, ConfigurationSpace):
        raise TypeError("space must be of type: ConfigurationSpace")

    for obstacle in space.getObstacles():
        if isPIP(node.getPos(), obstacle.getVertices()):
            return True
    return False


def isLineOnObstacle(p, q, space):
    for obstacle in space.getObstacles():
        if isLineOnPolygon(p.getPos(), q.getPos(), obstacle.getVertices()):
            return True
    return False



def updateNeighbors(node, neighbor_nodes, space):
    is_added = False
    for n in neighbor_nodes:
        if isLineOnObstacle(node, n, space):
            continue
        elif not is_added:
            node.setCost(calculateCost(n,node))
            node.setParent(n)
            is_added = True
            continue

        x1,y1 = node.getPos()
        x2,y2 = n.getPos()
        dist = ((x1-x2)**2 + (y1-y2)**2)**0.5
        cost = node.getCost() + dist
        if cost <= n.getCost():
            n.setCost(cost)
            n.setParent(node)


def isGoalReached(current_node, goal_node, space, threshold=2):
    x1,y1 = current_node.getPos()
    x2,y2 = goal_node.getPos()
    dist = ((x1-x2)**2 + (y1-y2)**2)**0.5
    if dist > threshold:
        return False
    if isLineOnObstacle(current_node, goal_node, space):
        return False
    return True

