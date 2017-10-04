#include<iostream>
#include<memory>
#include <stdlib.h>
using namespace std;

int N,L,i,value;
struct Tnode;
typedef Tnode *STree;
struct Tnode{
    int Data;
    STree Left;
    STree Right;
};

STree Insert(STree T,int data){
        if(T==NULL){
            // std::cout << "/* message */" << '\n';
            T = (STree)malloc(sizeof(struct Tnode));
            T->Data = data;
            T->Left = T->Right = NULL;
        }
        else{
            // std::cout << "/* message */" << '\n';
            if(data<T->Data){
                T->Left = Insert(T->Left,data);
            }
            else if(data>T->Data){
                T->Right = Insert(T->Right,data);
            }
        }
        return T;
}

int compare(STree A,STree B){
    // A = B = NULL   The leaves   return true
    if(A == NULL && B== NULL) return 1;
    // A or B is NULL   one is leave one is not  return false
    if((A == NULL && B!=NULL) || (A != NULL && B==NULL)) return 0;
    // BOTH A AND B aren't leaces
    else{
        if(A->Data == B->Data) return compare(A->Left,B->Left)&&compare(A->Right,B->Right);
        else return 0;
    }

}

int main(){
    while(1){
        // std::cout << "/* message */" << '\n';
        std::cin >> N;
        if(!N) break;
        std::cin >> L;
        STree OrigTree = NULL;
        for(i=0;i<N;i++){
            std::cin >>value ;
            OrigTree = Insert(OrigTree,value);
        }
        // std::cout << OrigTree->Data <<OrigTree->Left->Data<< '\n';
        while(L--){
            STree TmpTree =NULL;
            for(i=0;i<N;i++){
                std::cin >>value ;
                TmpTree = Insert(TmpTree,value);
            }
            // std::cout << TmpTree->Data <<TmpTree->Left->Data<< '\n';

            if (compare(OrigTree,TmpTree)) std::cout << "Yes" << '\n';
            else std::cout << "No" << '\n';
        }
    }
    return 0;
}
