#include <iostream>
#include <string>
#include <vector>

using namespace std;

class A{
    public:
    string data;

    A(string s){
        this->data = s;
    }

    void print(){
        cout<<"A: I am "<<this->data<<endl;
    }
};

class Collection{
    public:
    vector<A*> C;

    void add(A* a){
        this->C.push_back(a);
    }

    vector<A*>* get(){
        return &C;
    }

    void print(){
        vector<A*>::iterator it = this->get()->begin();
        for(it ; it!=this->get()->end(); it++){
            (*it)->print();
        }
    }
};


A* create_A(string s){
    A* _a = new A(s);
    return _a;
}


int main(){
    A* a = new A("a");
    A* b = new A("b");
    A* d = create_A("d");
    Collection c = Collection();
    c.add(a);
    c.add(b);
    c.add(d);

    c.print();
}