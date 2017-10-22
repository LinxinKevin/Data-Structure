#include <iostream>
#include <memory.h>
#include <queue>
using namespace std;
#define MAXNV 11
typedef int Vertex;

struct Gnode{
    bool *VertexCheck;
    int NumV,NumE;
    int G[MAXNV][MAXNV];
};
typedef Gnode* MGraph;

struct Enode{
    Vertex v1;
    Vertex v2;
};
typedef Enode* Edge;

MGraph Create(int VertexNum){
    MGraph Grapth = (MGraph)malloc(sizeof(struct Gnode));
    Grapth->NumV = VertexNum;
    Grapth->NumE = 0;
    for(int i=0;i<VertexNum;i++){
        for(int j=0;j<VertexNum;j++){
            Grapth->G[i][j] = 0;
        }
    }
    Grapth->VertexCheck = (bool*)malloc(sizeof(bool)*VertexNum);
    memset(Grapth->VertexCheck,false,sizeof(bool)*VertexNum);
    return Grapth;
}

void InsertEdge(MGraph Grapth,Edge E){
    Grapth->G[E->v1][E->v2] = 1;
    Grapth->G[E->v2][E->v1] = 1;
    Grapth->NumE++;
}

MGraph BuildGraph(){
    int VertexNum;
    int EdgeNum;
    std::cin >> VertexNum>>EdgeNum;
    MGraph Grapth = Create(VertexNum);
    int v1,v2;
    Edge E = (Edge)malloc(sizeof(struct Enode));
    while(EdgeNum--){
        std::cin >> E->v1>>E->v2;
        InsertEdge(Grapth,E);
    }
    return Grapth;
}

void PrintDFS(MGraph Grapth,Vertex V){
    Grapth->VertexCheck[V] = true;
    std::cout << V << " ";
    for(Vertex w=0;w<Grapth->NumV;w++){
        if( Grapth->G[V][w]==1 && Grapth->VertexCheck[w]==false)
            PrintDFS(Grapth,w);
    }
}

void DFS(MGraph Grapth){
    for(Vertex v=0;v<Grapth->NumV;v++){
        if(!Grapth->VertexCheck[v]){
            std::cout << "{ " ;
            PrintDFS(Grapth,v);
            std::cout << "}" << '\n';
        }
    }
    memset(Grapth->VertexCheck,false,sizeof(bool)*Grapth->NumV);
}

void PrintBFS(MGraph Grapth,Vertex V){
    queue<int> q;
    q.push(V);
    while(!q.empty()){
        Vertex M = q.front();
        q.pop();
        Grapth->VertexCheck[M] = true;
        std::cout << M << " ";
        for(Vertex W=0;W<Grapth->NumV;W++){
            if(Grapth->G[M][W] == 1 && Grapth->VertexCheck[W]==false ){
                Grapth->VertexCheck[W] = true;
                q.push(W);
            }
        }
    }

}

void BFS(MGraph Grapth){
    for(Vertex v=0;v<Grapth->NumV;v++){
        if(!Grapth->VertexCheck[v]){
            std::cout << "{ " ;
            PrintBFS(Grapth,v);
            std::cout << "}" << '\n';
        }
    }
    memset(Grapth->VertexCheck,false,sizeof(bool)*Grapth->NumV);
}

int main(){
    MGraph Grapth = BuildGraph();
    // for(int i =0;i<Grapth->NumV;i++){
    //     for(int j=0;j<Grapth->NumV;j++){
    //         std::cout << Grapth->G[i][j] << " ";
    //     }
    //     std::cout << '\n';
    // }
    DFS(Grapth);

    BFS(Grapth);
}
