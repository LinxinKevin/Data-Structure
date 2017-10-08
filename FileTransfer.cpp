#include <iostream>
using namespace std;
int *UTNodes;
int size;
void Create(int size){
    UTNodes = (int*)malloc(sizeof(int)*(size+1));
    for(int i=1;i<=size;i++) UTNodes[i] = -1;
}
void Insert(int a,int b){
    while(UTNodes[a]>0){
        a = UTNodes[a];
    }
    while(UTNodes[b]>0){
        b = UTNodes[b];
    }
    if(UTNodes[a] > UTNodes[b])
        UTNodes[a] = b ;
    else{
        if(UTNodes[a] == UTNodes[b]) UTNodes[a]--;
        UTNodes[b] = a;
    }
}
int Check(int c1,int c2){
    while(UTNodes[c1]>0) c1 = UTNodes[c1];
    while(UTNodes[c2]>0) c2 = UTNodes[c2];
    return c1==c2;
}
int Components(){
    int count,i;
    count = 0;
    for(i=1;i<=size;i++){
        if(UTNodes[i] < 0) count ++;
    }
    return count;
}

int main(){
    std::cin >> size;
    Create(size);
    char action;
    int c1,c2;
    while(1){
        std::cin >> action;
        if(action == 'I'){
            std::cin >> c1>>c2;
            if(c1!=c2)  Insert(c1,c2);
        }else if(action == 'C'){
            std::cin >> c1>>c2;
            if(Check(c1,c2)) std::cout << "yes" << '\n';
            else std::cout << "no" << '\n';
        }else if(action == 'S'){
            break;
        }
    }
    if(Components()==1) std::cout << "The network is connected." << '\n';
    else std::cout << "There are "<< Components()<<" components." << '\n';
    return 0;
}
