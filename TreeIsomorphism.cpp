#include<iostream>
#include<stdio.h>
#include<memory.h>
using namespace std;

struct Tnode{
    char index;
    int Left;
    int Right;
};
Tnode T1[10];
Tnode T2[10];


int Creat(Tnode *T){
int N,cl,cr,i,num[10];
char Ele,left,right;
memset(num,0,sizeof(int)*10);

std::cin >> N;
for(i=0;i<N;i++){
    std::cin >> Ele>> left>> right;
    if(left=='-') cl = -1;
    else cl = left-'0';
    if(right=='-') cr = -1;
    else cr = right-'0';
    T[i].index = Ele;
    T[i].Left = cl;
    T[i].Right = cr;
    num[cr] = num[cl] = 1;
}
int root = -1;
for(i=0;i<N;i++){
    if(!num[i]){
        root = i;
        break;
    }
}
return root;
}

int isOmorphism(int ONE,int TWO){
    if(ONE == -1 && TWO==-1) return 1;
    if(ONE==-1 && TWO!=-1 ||ONE!=-1 && TWO==-1) return 0;
    if(T1[ONE].index != T2[TWO].index) return 0;
    if(T1[ONE].Left == -1 && T2[TWO].Left == -1) return isOmorphism(T1[ONE].Right,T2[TWO].Right);
    if(T1[ONE].Right == -1 && T2[TWO].Right == -1) return isOmorphism(T1[ONE].Right,T2[TWO].Right);
    if(T1[ONE].Left !=-1 && T2[TWO].Left != -1 && T1[T1[ONE].Left].index == T2[T2[TWO].Left].index) return isOmorphism(T1[ONE].Left,T2[TWO].Left) && isOmorphism(T1[ONE].Right,T2[TWO].Right);
    return isOmorphism(T1[ONE].Left,T2[TWO].Right) && isOmorphism(T1[ONE].Right,T2[TWO].Left);
}

int main(int argc, char const *argv[]) {

    int root1 = Creat(T1);
    int root2 = Creat(T2);
    if(isOmorphism(root1,root2)) std::cout << "Yes" << '\n';
    else std::cout << "No" << '\n';
    return 0;
}
