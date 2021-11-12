// #include "objects.cpp"
#include <fstream>
#include "util.cpp"


int main(){
    
    vector<float> xlim{-20,30};
    vector<float> ylim{-20,30};
    float goal_threshold = 5;
    int loop_count = 2000;
    float max_segment_length = 2;

    float neighborhood_radius = 5;

    string filename = "../data.py";

    Node* start_node = new Node(-10, -10, 0.0);
    Node* goal_node = new Node(17, 17);

    Obstacle o1 = Obstacle(vector<Point>{{-15,5},{-10,2},{-2,3},{-5,15},{-8,10}});
    Obstacle o2 = Obstacle(vector<Point>{{5,-1},{5,-10},{18,-9},{20,3},{10,-5}});
    Obstacle o3 = Obstacle(vector<Point>{{15,15},{25,15},{25,10},{10,10},{10,25},{15,25}});

    vector<Obstacle*> obstacles = {&o1, &o2, &o3} ;                        

    
    ConfigurationSpace map = ConfigurationSpace(xlim,ylim);
    
    // --------------------------------------ADDING OBSTACLE in MAP---------------------------------------------------------
    for(auto obs : obstacles){
        map.addObstacle(obs);
    }

    Graph graph = Graph();
    graph.addNode(start_node);
    // graph.addNode(goal_node);

    cout<<"start_node: ("<<start_node->getPos().x<<","<<start_node->getPos().y<<")"<<endl;
    cout<<"goal_node: ("<<goal_node->getPos().x<<","<<goal_node->getPos().y<<")"<<endl;

    bool isPath = false;
    int i = 0;
    while (i<=loop_count){
        i+=1;
        print({"i: ",to_string(i-1)});
        Node* new_node = sampleNode(xlim,ylim);
        // cout<<"new_node: ("<<new_node.getPos().x<<","<<new_node.getPos().y<<")"<<endl;
        if(isNodeInObstacle(new_node, &map)){
            continue;
        }
        Node* nearest_node = nearestNode(graph, new_node);
        // cout<<"("<<nearest_node->getPos().x<<","<<nearest_node->getPos().y<<")"<<endl;
        if(isLineOnObstacle(new_node, nearest_node, &map)){
            continue;
        }
        Node* node_within_lim = getNodeOnLine(nearest_node, new_node, max_segment_length);
        // --------------------------------------------
        vector<Node*> sorted_neighbor_nodes = getNeighborNodes(node_within_lim, &graph, neighborhood_radius);
        updateNeighbors(node_within_lim, sorted_neighbor_nodes, &map);
        graph.addNode(node_within_lim);
        // --------------------------------------------
        

        // cout<<"node_within_lim: ("<<node_within_lim.getPos().x<<","<<node_within_lim.getPos().y<<")"<<endl;
        // cout<<"ptr_nwl: ("<<ptr_nwl->getPos().x<<","<<ptr_nwl->getPos().y<<")"<<endl;
        if(isGoalReached(node_within_lim, goal_node, &map, goal_threshold) && (!isPath)){
            goal_node->setParent(node_within_lim);
            goal_node->setCost(calculateCost(node_within_lim, goal_node));
            graph.addNode(goal_node);
            isPath = true;
        }
    }
    if ( ! isPath){
        print("can not find the path");
    }
    else{
        print("path found");
        print("saving path to file: data.py");

        string start = "start_node = (" + to_string(start_node->getPos().x)+", " + to_string(start_node->getPos().y) + ")";
        string goal = "\ngoal_node = (" + to_string(goal_node->getPos().x)+", " + to_string(goal_node->getPos().y) + ")";
        string obstacle_s;
        string graph_s;
        string path_s;


        obstacle_s = "\nobstacles = [";
        for(auto obs : map.getObstacles()){
            obstacle_s += "[";
            for(auto p : obs->getVertices()){
                obstacle_s += "("+to_string(p.x)+", "+to_string(p.y)+"), ";
            }
            obstacle_s += "],";
        }
        obstacle_s+="]";

        int i=0;
        Node* cn = goal_node;
        path_s = "\npath = [";
        while (cn != start_node){
            cout<<i<<": ("<<cn->getPos().x<<", "<<cn->getPos().y<<")"<<endl;
            path_s += "("+to_string(cn->getPos().x)+", "+to_string(cn->getPos().y)+"), ";
            // cout<<"addr cn: "<<cn<<endl;
            // cout<<"addr sn: "<<ptr_sn<<endl;
            cn = cn->getParent();
            i+=1;
        }
        cout<<i<<": ("<<cn->getPos().x<<", "<<cn->getPos().y<<")"<<endl;
        path_s += "("+to_string(cn->getPos().x)+", "+to_string(cn->getPos().y)+"), ";
        path_s += "]";


        graph_s = "\ngraph = [";
        for(auto n : graph.getNodes()){
            if(! n->getParent()){
                continue;
            }
            Node* np = n->getParent();
            graph_s += "[("+to_string(n->getPos().x)+", "+to_string(n->getPos().y)+"), ("+to_string(np->getPos().x)+", "+to_string(np->getPos().y)+")], ";
        }
        graph_s += "]";
        
        
        ofstream fout;
        fout.open(filename);
        fout<<start<<goal<<obstacle_s<<graph_s<<path_s;
        fout.close();
    }    
}
