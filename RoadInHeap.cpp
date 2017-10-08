#include <iostream>
using namespace std;
int MinNum = -10005;
struct HTnode;
typedef HTnode *Heap;
struct HTnode{
    int *Data;
    int Size;
    int Capacity;
};
typedef Heap MinHeap;
MinHeap MinHP;
int flag = 1;

MinHeap Create(int MaxSize)
{
    MinHeap MinP = (MinHeap)malloc(sizeof(struct HTnode));
    MinP->Data = (int*)malloc(sizeof(int)*(MaxSize+1));
    MinP->Size = 0;
    MinP->Capacity = MaxSize;
    MinP->Data[0] = MinNum;
    return MinP;
}

bool Insert(int data){
    int i = ++MinHP->Size;
    for(;MinHP->Data[i/2]>data;i/=2){
        MinHP->Data[i] = MinHP->Data[i/2];
    }
    MinHP->Data[i] = data;
    return true;
}

void Print(int index){
    while(index>0){
        if(flag) flag=0,std::cout << MinHP->Data[index];
        else std::cout << " " << MinHP->Data[index];
        index /=2;
    }
}

int main(){
    int N,M;
    std::cin >> N>>M ;
    MinHP = Create(N);
    int i ,value;
    for(i=0;i<N;i++){
        std::cin >> value;
        Insert(value);
    }
    int index;
    for(i=0;i<M;i++){
        std::cin >> index;
        Print(index);
        flag = 1;
        std::cout << '\n';
    }
}
