
#include "bits/stdc++.h"
#include <iostream>
#include <map>
#include <math.h>
#include <random>
#include <string>
#include <vector>

#include "objects.cpp"

using namespace std;


void print(vector<string> sv){
    for(auto s : sv){
        cout<<s;
    }
    cout<<endl;
}
void print(string sv){
    cout<<sv;
    cout<<endl;
}


float getDistanceBetween(Node* n1, Node* n2){
    float x1 = n1->getPos().x;
    float y1 = n1->getPos().y;
    float x2 = n2->getPos().x;
    float y2 = n2->getPos().y;
    float dist;
    dist = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
    return dist;
}

Node getNodeOnLine(Node* p, Node* q, float max_distance=10){
    float dist = getDistanceBetween(p,q);
    if(dist <= max_distance){
        return *q;
    }
    float x1 = p->getPos().x;
    float y1 = p->getPos().y;
    float x2 = q->getPos().x;
    float y2 = q->getPos().y;
    float x,y;
    x = x1 + (x2-x1)*(max_distance/dist);
    y = y1 + (y2-y1)*(max_distance/dist);
    return Node(x,y);
}


float calculateCost(Node* n1, Node* n2){
    // calculate cost to reach n2 through n1 (include the cost of n1)

    // n1,n2 -> Node objects
    float dist = getDistanceBetween(n1,n2);
    float cost;
    cost = n1->getCost() + dist;
    return cost;
}


// --------------- Local Function start-----------------------
bool cmp(pair<Node*,float>& a, pair<Node*,float>& b){
    return a.second < b.second;
}

float genRandomNumber(float low, float high){
    random_device random_dev;
    mt19937 engine{random_dev()};
    uniform_real_distribution<float> dist(low, high);
    return dist(engine);
}
// --------------- Local Function end-----------------------

vector<Node*> getNeighborNodes(Node* node, Graph* graph, float neighbor_radius){
    vector<pair<Node*,float>> neighbor_nodes;
    float cost;
    vector<Node>* all_nodes = graph->getNodes();
    vector<Node>::iterator it = all_nodes->begin();
    // for(Node n : all_nodes){
    //     float dist = getDistanceBetween(node, &n);
    //     if(dist <= neighbor_radius){
    //         cost = n.getCost() + dist;
    //         neighbor_nodes.push_back(pair<Node*,float>(&n,cost));
    //     }
    // }

    for(it; it!=all_nodes->end();it++){
        float dist = getDistanceBetween(node, &(*it));
        if(dist <= neighbor_radius){
            cost = it->getCost() + dist;
            neighbor_nodes.push_back(pair<Node*,float>(&(*it),cost));
        }

    }


    //sorting neighbor_nodes
    
    sort(neighbor_nodes.begin(), neighbor_nodes.end(), cmp);

    vector<Node*> sorted_neighbor_nodes;
    for(auto elem : neighbor_nodes){
        sorted_neighbor_nodes.push_back(elem.first);
    }
    return sorted_neighbor_nodes;
}

int orientation(Point p, Point q, Point r){
    float val;
    val = (q.y-p.y)*(r.x-p.x) - (r.y-p.y)*(q.x-p.x);
    if (val==0){
        return 0;
    }
    else if(val<0){
        return -1;
    }
    else {
        return 1;
    }
}

bool doIntersect(Point p1,Point q1,Point p2,Point q2){
    int o1 = orientation(p1,q1,p2);
    int o2 = orientation(p1,q1,q2);
    int o3 = orientation(p2,q2,p1);
    int o4 = orientation(p2,q2,q1);

    if(o1 != o2 && o3 != o4){
        return true;
    }
    return false;
}

bool isPIP(Point p, vector<Point> polygon){
    int count = 0;
    Point q;
    q.x = 1e8;
    q.y = p.y;

    int l = polygon.size();
    for(int i=0; i<l; i++){
        Point p1,q1;
        p1 = polygon[i];
        q1 = polygon[(i+1)%l];
        if(doIntersect(p,q,p1,q1)){
            count+=1;
        }
    }
    if (count%2==0){
        return false;
    }
    else {
        return true;
    }
}

bool isLineOnPolygon(Point p, Point q, vector<Point> polygon){
    int l = polygon.size();
    for(int i=0; i<l; i++){
        Point p1,q1;
        p1 = polygon[i];
        q1 = polygon[(i+1)%l];
        if(doIntersect(p,q,p1,q1)){
            return true;
        }
    }
    return false;
}



Node sampleNode(vector<float> xlim, vector<float> ylim){
    float x = genRandomNumber(xlim[0], xlim[1]);
    float y = genRandomNumber(ylim[0], ylim[1]);
    return Node(x,y);
}

// Node* nearestNode(Graph& graph, Node* newNode){
//     vector<Node*> all_nodes = graph.getNodes();
//     float min_dist = inf;
//     Node* nearest_node;
//     for(Node* n: all_nodes){
//         float dist = getDistanceBetween(n,newNode);
//         if (dist<min_dist){
//             min_dist = dist;
//             nearest_node = n;
//         }
//     }
//     return nearest_node;
// }



Node* nearestNode(Graph& graph, Node* newNode){
    vector<Node>* all_nodes = graph.getNodes();
    float min_dist = inf;
    Node* nearest_node;
    vector<Node>::iterator it = all_nodes->begin();
    for(it; it!=all_nodes->end(); it++){
        float dist = getDistanceBetween(&(*it),newNode);
        if (dist<min_dist){
            min_dist = dist;
            nearest_node = &(*it);
        }
    }
    return nearest_node;
}




bool isNodeInObstacle(Node* node, ConfigurationSpace* space){
    for(auto obstacle : space->getObstacles()){
        if (isPIP(node->getPos(),obstacle->getVertices())){
            return true;
        }
    }
    return false;
}

bool isLineOnObstacle(Node* p, Node* q, ConfigurationSpace* space){
    for(auto obstacle : space->getObstacles()){
        if(isLineOnPolygon(p->getPos(), q->getPos(), obstacle->getVertices())){
            return true;
        }
    }
    return false;
}

void updateNeighbors(Node* node, vector<Node*> neighbor_nodes, ConfigurationSpace* space){
    bool is_added = false;
    for(auto n : neighbor_nodes){
        if (isLineOnObstacle(node, n, space)){
            continue;
        }
        else if(! is_added){
            node->setCost(calculateCost(n, node));
            node->setParent(n);
            is_added = true;
            continue;
        }
        float cost = calculateCost(node,n);
        if(cost <= n->getCost()){
            n->setCost(cost);
            n->setParent(node);
        }
    }
}

bool isGoalReached(Node* current_node, Node* goal_node, ConfigurationSpace* space, float threshold=2){
    float dist = getDistanceBetween(current_node, goal_node);
    if (dist > threshold){
        return false;
    }
    if (isLineOnObstacle(current_node, goal_node, space)){
        return false;
    }
    return true;
}
