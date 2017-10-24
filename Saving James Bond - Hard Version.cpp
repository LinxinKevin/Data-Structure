#include <iostream>
#include <memory.h>
#include <queue>
#include <stack>
using namespace std;
#define MAXNUM 9999;
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
    bool Escaped;
    int countJumps;
    int Prev;
};
typedef CrocoNode* Crocodile;

int abs(int a){
    return a>0?a:-a;
}

MGraph Create(int CrocodileNum,int MAXDistance){
    MGraph Grapth = (MGraph)malloc(sizeof(struct Gnode));
    Grapth->MAXDistance = MAXDistance;
    Grapth->CrocodileNum = CrocodileNum;
    Grapth->CrocodileIndex = 1;
    Grapth->CrocosPositon = (CrocoNode*)malloc(sizeof(struct CrocoNode)*(CrocodileNum+1));
    CrocoNode island;
    island.X = island.Y = 0;
    island.Escaped = (island,Grapth->MAXDistance+15/2);
    island.Prev = 0;
    island.countJumps = 0;
    Grapth->CrocosPositon[0] = island;
    return Grapth;
}

bool Escape(CrocoNode croco,int MAXDistance){
    // std::cout << croco.X<<croco.Y << '\n';
    if(abs(croco.X) + MAXDistance >=50 || abs(croco.Y)+MAXDistance>=50) return true;
    else return false;
}

void InsertCroco(MGraph Grapth,CrocoNode croco){
    if(Grapth->CrocodileIndex > Grapth->CrocodileNum) std::cout << "Too many crocos" << '\n';
    Grapth->CrocosPositon[Grapth->CrocodileIndex] = croco;
    Grapth->CrocodileIndex++;
}

MGraph BuildGraph(){
    int CrocodileNum,MAXDistance;
    std::cin >> CrocodileNum>>MAXDistance;
    MGraph Grapth  = Create(CrocodileNum,MAXDistance);
    CrocoNode croco;
    while(CrocodileNum--){
        std::cin >> croco.X>>croco.Y;
        croco.Escaped = false;
        croco.countJumps = 0;
        croco.Prev = 0;
        InsertCroco(Grapth,croco);
    }
    return Grapth;
}

bool Enable(CrocoNode start,CrocoNode end,int MAXDistance){
    int length = (end.X-start.X)*(end.X-start.X) + (end.Y-start.Y)*(end.Y-start.Y);
    return length <= MAXDistance*MAXDistance;
}


void BFS(MGraph Grapth){
    std:queue<int>q;
    q.push(0);
    int INDEX;
    while(!q.empty()){
        INDEX = q.front();
        q.pop();
        if(INDEX==0) Grapth->CrocosPositon[INDEX].Escaped = Escape(Grapth->CrocosPositon[INDEX],Grapth->MAXDistance+15/2);
        else Grapth->CrocosPositon[INDEX].Escaped = Escape(Grapth->CrocosPositon[INDEX],Grapth->MAXDistance);
        for(int i=1;i<=Grapth->CrocodileNum;i++){
            if(INDEX == 0){
                if(Enable(Grapth->CrocosPositon[INDEX],Grapth->CrocosPositon[i],Grapth->MAXDistance+15/2)){
                    Grapth->CrocosPositon[i].Prev = INDEX;
                    Grapth->CrocosPositon[i].countJumps =1;
                    q.push(i);
                }
            }
            else if(Enable(Grapth->CrocosPositon[INDEX],Grapth->CrocosPositon[i],Grapth->MAXDistance)){
                if(Grapth->CrocosPositon[i].countJumps > Grapth->CrocosPositon[INDEX].countJumps+1||(Grapth->CrocosPositon[i].countJumps ==0 && i!=INDEX)){
                    Grapth->CrocosPositon[i].countJumps = Grapth->CrocosPositon[INDEX].countJumps+1;
                    Grapth->CrocosPositon[i].Prev = INDEX;
                    q.push(i);
                }
            }
        }
    }
}


void PrintBFS(MGraph Grapth){
    BFS(Grapth);
    int index =-1 ;
    int min = MAXNUM;
    for(int i=0;i<=Grapth->CrocodileNum;i++){
        // std::cout << i<<" : "<<" X :"<<Grapth->CrocosPositon[i].X <<" Y : "<<Grapth->CrocosPositon[i].Y<<" countJumps : "<<Grapth->CrocosPositon[i].countJumps<<" Escaped: "<<Grapth->CrocosPositon[i].Escaped<<endl;
        if(Grapth->CrocosPositon[i].Escaped == true){
            if(Grapth->CrocosPositon[i].countJumps < min){
                min = Grapth->CrocosPositon[i].countJumps;
                index = i;
            }
            else if(Grapth->CrocosPositon[i].countJumps == min){
                int tmp1 = index;
                int tmp2 = i;
                while(Grapth->CrocosPositon[tmp1].Prev!=0) tmp1 = Grapth->CrocosPositon[tmp1].Prev;
                while(Grapth->CrocosPositon[tmp2].Prev!=0) tmp2 = Grapth->CrocosPositon[tmp2].Prev;
                if(Grapth->CrocosPositon[tmp2].X*Grapth->CrocosPositon[tmp2].X + Grapth->CrocosPositon[tmp2].Y*Grapth->CrocosPositon[tmp2].Y - Grapth->CrocosPositon[tmp1].X*Grapth->CrocosPositon[tmp1].X - Grapth->CrocosPositon[tmp1].Y*Grapth->CrocosPositon[tmp1].Y <0 )
                {
                    index = i;
                }
            }
        }
    }
    if(index == -1) std::cout << 0 << '\n';
    else{
        // std::cout << "/* message */" << '\n';
        int INDEX = index;
        std:stack<int> road;
        while(INDEX!=0){
            road.push(INDEX);
            INDEX = Grapth->CrocosPositon[INDEX].Prev;
        }
        std::cout << min+1 << '\n';
        while(!road.empty()){
            std::cout << Grapth->CrocosPositon[road.top()].X<<" "<<Grapth->CrocosPositon[road.top()].Y << '\n';
            road.pop();
        }
    }

}

int main(){
    MGraph Grapth;
    Grapth = BuildGraph();
    PrintBFS(Grapth);
}
