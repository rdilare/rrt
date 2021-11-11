from objects import Graph

import matplotlib.pyplot as plt

from data import *


class Viz:
    def __init__(self):
        self.nodes = []
        self.obstacles = []
        self.edges = []
        self.start_node = None
        self.goal_node = None
        self.path = []
    
    def addNode(self,node,nodeType="Normal"):
        if nodeType=="Start":
            self.start_node = node
        elif nodeType=="Goal":
            self.goal_node = node
        elif nodeType=="Path":
            self.path.append(node)
        else :
            self.nodes.append(node)
    
    def addEdge(self,edge):
        """
        edge -> list of two tuples
        """
        self.edges.append(edge)

    
    def addObstacle(self,obstacle):
        self.obstacles.append(obstacle)

    def plot(self):
        fig = plt.figure()

        self.plotGraph()

        x=[]
        y=[]
        for node in self.path:
            x.append(node[0])
            y.append(node[1])
        plt.plot(x,y,"-k",label="Path")
        x=[]
        y=[]
        for obstacle in self.obstacles:
            for xy in obstacle:
                x.append(xy[0])
                y.append(xy[1])
            x.append(x[0])
            y.append(y[0])
            plt.plot(x,y,"-r")
            x=[]
            y=[]

        plt.plot(*self.start_node,"go",label="Start Node")
        plt.plot(*self.goal_node,"ro",label="Goal Node")
        plt.legend(loc="lower left")
        plt.show()

    def plotGraph(self):
        for line in self.edges:
            plt.plot([line[0][0],line[1][0]],[line[0][1],line[1][1]], "-y.")


def main():
    viz = Viz()
    viz.addNode(start_node, nodeType="Start")
    viz.addNode(goal_node, nodeType="Goal")
    for node in path:
        viz.addNode(node, nodeType="Path")
    for obs in obstacles:
        viz.addObstacle(obs)
    for edge in graph:
        viz.addEdge(edge)
    viz.plot()

if __name__=="__main__":
    main()