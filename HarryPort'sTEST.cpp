#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;

int MAXNUM = 99999;
typedef int Vertex;
struct Gnode{
    int NumV;
    int NumE;
    int G[102][102];
};
typedef Gnode* MGrapth;

struct Enode{
    Vertex v1;
    Vertex v2;
    int weight;
};
typedef Enode* Edge;

MGrapth CreateGrapth(int NumV){
    MGrapth Grapth = (MGrapth)malloc(sizeof(struct Gnode));
    Grapth->NumV = NumV;
    for(Vertex v=0;v<=Grapth->NumV;v++){
        for(Vertex w=0;w<=Grapth->NumV;w++)
            Grapth->G[v][w] = 0;
    }
    return Grapth;
}

void InsertEdge(MGrapth Grapth,Edge E){
    Grapth->NumE++;
    Grapth->G[E->v1][E->v2] = E->weight;
    Grapth->NumE++;
    Grapth->G[E->v2][E->v1] = E->weight;
}

MGrapth BuildGraph(){
    int VertexNum;
    int EdgeNum;
    std::cin >> VertexNum>>EdgeNum;
    MGrapth Grapth = CreateGrapth(VertexNum);
    Edge E = (Edge)malloc(sizeof(struct Enode));
    while(EdgeNum--){
        std::cin >> E->v1>>E->v2>>E->weight;
        InsertEdge(Grapth,E);
    }
    return Grapth;
}

int BSF(MGrapth Grapth,Vertex V){
    int count = 0;
    // std::cout << V<<" : ";
    int *Distance = (int*)malloc(sizeof(int)*(Grapth->NumV+1));
    memset(Distance,0,sizeof(int)*(Grapth->NumV+1));
    std::queue<int> q;
    q.push(V);
    while(!q.empty()){
        Vertex v = q.front();
        q.pop();
        for(Vertex w =1;w<=Grapth->NumV;w++){
            if(Grapth->G[v][w]){
                if(Distance[w] > Distance[v]+Grapth->G[v][w] || (Distance[w] ==0 && w!=V)){
                    Distance[w] = Distance[v]+Grapth->G[v][w];
                    q.push(w);
                }
            }
        }
    }
    int maxnum = 0;
    for(Vertex v=1;v<=Grapth->NumV;v++){
        if(Distance[v]==0 && v!=V) return MAXNUM;
        maxnum = max(maxnum,Distance[v]);
    }
    // std::cout << maxnum << '\n';
    return maxnum;
}

void PrintBSF(MGrapth Grapth){
    int min = MAXNUM;
    int index = 0;
    for(Vertex v=1;v<=Grapth->NumV;v++){
        int tmp = BSF(Grapth,v);
        if(tmp < min) index = v,min = tmp;
    }
    if(index==0) std::cout << "0" << '\n';
    else std::cout << index <<" "<<min << '\n';
}

int main(){
    MGrapth Grapth = BuildGraph();
    PrintBSF(Grapth);
}
