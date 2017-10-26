#include <iostream>
#include <memory.h>
using namespace std;
typedef int City;
const int MAXCITYNUM = 500;
const int MAXNUM = 999999;

struct cityNode{
    int cost;
    int length;
};

struct Rnode{
    City Scity;
    City Ecity;
    int cost;
    int length;
};
typedef Rnode* Road;

struct Gnode{
    City startCity,endCity;
    cityNode *Cities;
    int cityNum;
    cityNode G[MAXCITYNUM][MAXCITYNUM];
};
typedef Gnode* MGrapth;

MGrapth Create(int cityNum,City startCity,City endCity){
    MGrapth Grapth = (MGrapth)malloc(sizeof(struct Gnode));
    Grapth->cityNum = cityNum;
    Grapth->Cities = (cityNode*)malloc(sizeof(struct cityNode)*cityNum);
    for(City c1 =0;c1<cityNum;c1++){
        for(City c2 =0;c2<cityNum;c2++){
             Grapth->G[c1][c2].cost = MAXNUM;
             Grapth->G[c1][c2].length = MAXNUM;
        }
    }
    for(City c1=0;c1<cityNum;c1++) Grapth->Cities[c1].cost = Grapth->Cities[c1].length = MAXNUM;
    Grapth->startCity = startCity;
    Grapth->endCity = endCity;
    return Grapth;
}

void InsertRoad(MGrapth Grapth,Road road){
    Grapth->G[road->Scity][road->Ecity].cost = road->cost;
    Grapth->G[road->Scity][road->Ecity].length = road->length;
    Grapth->G[road->Ecity][road->Scity].cost = road->cost;
    Grapth->G[road->Ecity][road->Scity].length = road->length;
}

MGrapth BuildGrapth(){
    int cityNum,roadNum;
    City startCity,endCity;
    std::cin >> cityNum>>roadNum>>startCity>>endCity;
    MGrapth Grapth = Create(cityNum,startCity,endCity);
    Road road = (Road)malloc(sizeof(struct Rnode));
    while(roadNum--){
        std::cin >> road->Scity>>road->Ecity>>road->length>>road->cost;
        InsertRoad(Grapth,road);
    }
    return Grapth;
}

City FindMinDis(MGrapth Grapth,bool * collected){
    City index = -1;
    for(City c=0;c<Grapth->cityNum;c++){
        if(collected[c]==false&&Grapth->Cities[c].length < MAXNUM){
            if(index == -1) index = c;
            else{
                if((Grapth->Cities[index].length > Grapth->Cities[c].length)||(Grapth->Cities[index].length==Grapth->Cities[c].length&&Grapth->Cities[index].cost>Grapth->Cities[c].cost))
                    index = c;
            }
        }
    }
    return index;
};

bool Dijkstra(MGrapth Grapth){
    bool collected[Grapth->cityNum];
    memset(collected,false,sizeof(collected));
    // collected[MGrapth->startCity] = true;
    Grapth->Cities[Grapth->startCity].cost = 0;
    Grapth->Cities[Grapth->startCity].length = 0;
    int index;
    while(1){
        index = FindMinDis(Grapth,collected);
        if(index == -1) break;
        collected[index] = true;
        for(City c =0;c<Grapth->cityNum;c++){
            if(collected[c] == false && Grapth->G[index][c].length<MAXNUM){
                if(Grapth->Cities[index].length + Grapth->G[index][c].length <= Grapth->Cities[c].length){
                    if(Grapth->Cities[index].length + Grapth->G[index][c].length == Grapth->Cities[c].length && Grapth->Cities[index].cost + Grapth->G[index][c].cost > Grapth->Cities[c].cost);
                    else{
                        Grapth->Cities[c].length =Grapth->Cities[index].length + Grapth->G[index][c].length ;
                        Grapth->Cities[c].cost = Grapth->Cities[index].cost + Grapth->G[index][c].cost;
                    }
                }
            }
        }
    }
    return true;
}

void PrintLANDC(MGrapth Grapth){
    Dijkstra(Grapth);
    std::cout <<Grapth->Cities[Grapth->endCity].length<<" "<<Grapth->Cities[Grapth->endCity].cost << '\n';
}

int main(){
    MGrapth Grapth = BuildGrapth();
    PrintLANDC(Grapth);
}
