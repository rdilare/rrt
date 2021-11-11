
#include <iostream>
#include <vector>
#include <utility>

#define inf 1.0e8

using namespace std;


struct Point{
    float x;
    float y;
};


class Node{
    public:
    struct Point pos;
    float cost;
    Node* parent = NULL;

    Node(float x, float y, float cost=inf){
        pos.x = x;
        pos.y = y;
        cost = cost;
    }
    struct Point getPos(){
        return this->pos;
    }
    float getCost(){
        return this->cost;
    }
    Node* getParent(){
        return this->parent;
    }
    void setCost(float cost){
        this->cost = cost;
    }
    void setParent(Node* p){
        this->parent = p;
    }
};

class Obstacle{
    public:
    vector<Point> vertices;

    Obstacle(vector<Point> v){
        this->vertices = v;
    }
    vector<Point>& getVertices(){
        return this->vertices;
    }
};


class Graph{
    public:
    vector<Node> nodes;

    Node* addNode(Node node){
        this->nodes.push_back(node);
        return &(*(nodes.end()-1));
    }
    vector<Node>* getNodes(){
        // vector<Node*> Ns;
        // for(Node n : this->nodes){
        //     Ns.push_back(&n);
        // }
        return &this->nodes;
    }
};

class ConfigurationSpace{
    public:
    vector<float> xlim;
    vector<float> ylim;
    vector<Obstacle*> obstacles;

    ConfigurationSpace(vector<float> xlm, vector<float> ylm){
        this->xlim = xlm;
        this->ylim = ylm;
    }
    void addObstacle(Obstacle *obs){
        if (this->isWithinLimit(obs)){
            this->obstacles.push_back(obs);
        }
    }
    bool isWithinLimit(Obstacle* obs){
        bool isWithinX = false;
        bool isWithinY = false;
        for(auto xy: obs->getVertices()){
            float x=xy.x;
            float y=xy.y;
            if(xlim[0]<x && x<xlim[1] ){
                isWithinX = true;
            }
            if(ylim[0]<y && y<ylim[1]){
                isWithinY = true;
            }
        }
        if(isWithinX && isWithinY){
            return true;
        }
        return false;
    }
    vector<Obstacle*> getObstacles(){
        return this->obstacles;
    }
};