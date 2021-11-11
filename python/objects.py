class Node:
    def __init__(self,x,y,cost=float('inf')):
        self.pos = (x,y)
        self.cost = cost
        self.parent = None

    def getPos(self):
        return self.pos
    
    def getCost(self):
        return self.cost
    
    def setCost(self, cost):
        self.cost = cost
    
    def setParent(self,parent):
        self.parent = parent

    def getParent(self):
        return self.parent

class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = {}
    
    def addNode(self,node):
        self.nodes.append(node)
        self.edges.update({node:[]})
    
    def addEdge(self,n1, n2):
        """
            n1 = first Node
            n2 = second Node

            n1 is parent of n2
        """
        if not n1 in self.nodes:
            self.nodes.append(n1)
            self.edges.update({n1:[]})
        if not n2 in self.nodes:
            self.nodes.append(n2)
            self.edges.update({n2:[]})

        self.edges[n1].append(n2)
        n2.setParent(n1)

    def getNodes(self):
        return self.nodes
    def getEdges(self):
        return self.edges

class Obstacle:
    def __init__(self, vertices):
        """
        vertices -> list of tuples
        """
        self.vertices = vertices
    
    def getVertices(self):
        return self.vertices

class ConfigurationSpace:
    def __init__(self,xlim, ylim, obstacles=[]):
        """
        xlim -> tuple
        ylim -> tuple
        obstacles -> list of "Obstacle" object
        """
        self.xlim = xlim
        self.ylim = ylim
        self.obstacles = obstacles
    
    def addObstacle(self, obstacle):
        if not obstacle in self.obstacles:
            if self.isWithinLimit(obstacle):
                self.obstacles.append(obstacle)

    def isWithinLimit(self,obstacle):
        isWithinX = False
        isWithinY = False
        for xy in obstacle.vertices:
            x,y = xy
            if self.xlim[0] < x < self.xlim[1]:
                isWithinX = True
            if self.ylim[0] < y < self.ylim[1]:
                isWithinY = True
        if isWithinX and isWithinY:
            return True
        return False  

    def getLimit(self):
        return self.xlim, self.ylim

    def getObstacles(self):
        return self.obstacles

