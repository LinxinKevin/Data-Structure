#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;
typedef int Vertex;

struct VNode{
    VNode *Next;
    Vertex V;
    // int Level;
};
typedef VNode *PtrVNode;

struct HNode{
    PtrVNode FirstEdge;
    bool checked;
};
struct Gnode{
    int NumV;
    int NumE;
    HNode *AdjList;
};
typedef Gnode* LGrapth;
struct Enode{
    Vertex v1,v2;
};
typedef Enode *Edge;
LGrapth Create(int VertexNum){
    LGrapth Grapth = (LGrapth)malloc(sizeof(struct Gnode));
    Grapth->NumE = 0;
    Grapth->NumV = VertexNum;
    Grapth->AdjList = (HNode*)malloc(sizeof(struct HNode)*(VertexNum+1));
    for(int v=1;v<=VertexNum;v++) Grapth->AdjList[v].FirstEdge = NULL,Grapth->AdjList[v].checked = false;
    return Grapth;
}
void InsertEdge(LGrapth Grapth,Edge E){
    Grapth->NumE ++;
    PtrVNode PV = (PtrVNode)malloc(sizeof(struct VNode));
    PV->V = E->v2;
    PV->Next = Grapth->AdjList[E->v1].FirstEdge;
    // PV->Level = 0;
    Grapth->AdjList[E->v1].FirstEdge = PV;
    PtrVNode PV2 = (PtrVNode)malloc(sizeof(struct VNode));
    PV2->V = E->v1;
    // PV2->Level = 0;
    PV2->Next = Grapth->AdjList[E->v2].FirstEdge;
    Grapth->AdjList[E->v2].FirstEdge = PV2;
}

LGrapth BuildGraph(){
    int VertexNum,EdgeNum;
    std::cin >> VertexNum>>EdgeNum;
    LGrapth Grapth = Create(VertexNum);
    Edge E = (Edge)malloc(sizeof(struct Enode));
    while(EdgeNum--){
        std::cin >> E->v1>>E->v2;
        InsertEdge(Grapth,E);
    }
    return Grapth;
}

void BFS(LGrapth Grapth, Vertex V){
    int count = 0;
    Vertex last = V;
    Vertex tail;
    int Level = 0;
    std::queue<int> q;
    q.push(V);
    PtrVNode TMP;
    std::cout << V << ": ";
    while(!q.empty()){
        V = q.front();
        q.pop();
        count++;
        Grapth->AdjList[V].checked = true;
        for(TMP=Grapth->AdjList[V].FirstEdge;TMP!=NULL;TMP=TMP->Next){
            if(!Grapth->AdjList[TMP->V].checked){
                q.push(TMP->V);
                Grapth->AdjList[TMP->V].checked = true;
                tail = TMP->V;
            }
        }
        if( V == last ){
            Level++;
            last = tail;
        }
        if(Level > 6) break;
    }
    for(Vertex v=1;v<=Grapth->NumV;v++) Grapth->AdjList[v].checked = false;
    std::cout << fixed<<showpoint<<setprecision(2)<<100*(double)count/Grapth->NumV <<"%"<< '\n';
}

void CollectBFS(LGrapth Grapth){
    for(Vertex V = 1;V<=Grapth->NumV;V++){
        BFS(Grapth,V);
    }
}

int main(){
    LGrapth Grapth = BuildGraph();
    CollectBFS(Grapth);
}
