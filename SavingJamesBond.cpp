#include <iostream>
#include <memory.h>
using namespace std;

#define MAXNV 101;
typedef int Position;
struct CrocoNode;
struct Gnode{
    CrocoNode *CrocosPositon;
    int CrocodileNum;
    int CrocodileIndex;
    int MAXDistance;
};
typedef Gnode *MGraph;

struct CrocoNode{
    Position X;
    Position Y;
    bool checked;
};
typedef CrocoNode* Crocodile;

MGraph Create(int CrocodileNum,int MAXDistance){
    MGraph Grapth = (MGraph)malloc(sizeof(struct Gnode));
    Grapth->MAXDistance = MAXDistance;
    Grapth->CrocodileNum = CrocodileNum;
    Grapth->CrocodileIndex = 0;
    Grapth->CrocosPositon = (CrocoNode*)malloc(sizeof(struct CrocoNode)*CrocodileNum);
    return Grapth;
}
void InsertCroco(MGraph Grapth,Crocodile croco){
    if(Grapth->CrocodileIndex == Grapth->CrocodileNum) std::cout << "Too many crocos" << '\n';
    Grapth->CrocosPositon[Grapth->CrocodileIndex] = *croco;
    Grapth->CrocodileIndex++;
}

MGraph BuildGraph(){
    int CrocodileNum,MAXDistance;
    std::cin >> CrocodileNum>>MAXDistance;
    MGraph Grapth  = Create(CrocodileNum,MAXDistance);
    Crocodile croco = (Crocodile)malloc(sizeof(struct CrocoNode));
    while(CrocodileNum--){
        std::cin >> croco->X>>croco->Y;
        croco->checked = false;
        InsertCroco(Grapth,croco);
    }
    return Grapth;
}

bool Enable(CrocoNode start,CrocoNode end,int MAXDistance){
    int length = (end.X-start.X)*(end.X-start.X) + (end.Y-start.Y)*(end.Y-start.Y);
    return length <= MAXDistance*MAXDistance;
}

int abs(int a){
    return a>0?a:-a;
}

bool Escape(CrocoNode croco,int MAXDistance){
    // std::cout << croco.X<<croco.Y << '\n';
    if(abs(croco.X) + MAXDistance >=50 || abs(croco.Y)+MAXDistance>=50) return true;
    else return false;
}

bool CheckDFS(MGraph Grapth,int index){
    int flag = false;
    Grapth->CrocosPositon[index].checked = true;
    if(Escape(Grapth->CrocosPositon[index],Grapth->MAXDistance))
        return  true;
    for(int i =0;i<Grapth->CrocodileNum;i++){
        if(Grapth->CrocosPositon[i].checked == false && Enable(Grapth->CrocosPositon[index],Grapth->CrocosPositon[i],Grapth->MAXDistance)){
             flag = flag||CheckDFS(Grapth,i);
        }
    }
    return flag;
}

void DFS(MGraph Grapth){
    CrocoNode island;
    bool flag = false;
    island.X = island.Y = 0;
    if(Escape(island,Grapth->MAXDistance+15/2)) flag = true;
    else{
        for(int i=0;i<Grapth->CrocodileNum;i++){
            if(Enable(island,Grapth->CrocosPositon[i],Grapth->MAXDistance+15/2)){
                flag = CheckDFS(Grapth,i);
            }
            if(flag) break;
        }
    }
    if(flag) std::cout << "Yes" << '\n';
    else std::cout << "No" << '\n';
}

int main(){
    MGraph Grapth;
    Grapth = BuildGraph();
    DFS(Grapth);
}
