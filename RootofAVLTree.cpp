#include<iostream>
using namespace std;
struct TreeNode;
typedef TreeNode *AVLTree;

struct TreeNode{
    int Height;
    AVLTree Left;
    AVLTree Right;
    int value;
};

int GetHeight(AVLTree T){
    if(T==NULL) return 0;
    // else if(T->Right==NULL && T->Left==NULL) T->Height = 1;
    else T->Height = max(GetHeight(T->Left),GetHeight(T->Right))+1;

    return T->Height;
}

AVLTree SingleLeftRotation(AVLTree T){
    AVLTree B = T->Left;
    T->Left = B->Right;
    B->Right = T;
    T->Height = GetHeight(T);
    B->Height = GetHeight(B);
    return B;
}
AVLTree SingleRightRotation(AVLTree T){
    AVLTree B = T->Right;
    T->Right = B->Left;
    B->Left = T;
    T->Height = GetHeight(T);
    B->Height = GetHeight(B);
    return B;
}

AVLTree DoubleRightLeftRotation(AVLTree T){
        T->Right = SingleLeftRotation(T->Right);
        return SingleRightRotation(T);
}

AVLTree DoubleLeftRightRotation(AVLTree T){
        T->Left = SingleRightRotation(T->Left);
        return SingleLeftRotation(T);
}

AVLTree Insert(AVLTree T,int data){
    if(T==NULL){
        T = (AVLTree)malloc(sizeof(TreeNode));
        T->value = data;
        T->Left = T->Right = NULL;
        T->Height = 1;
    }
    else{
        if(data<T->value){
            T->Left = Insert(T->Left,data);
            if(GetHeight(T->Left)-GetHeight(T->Right)==2){
                if(data<T->Left->value){
                    T = SingleLeftRotation(T);
                }else{
                    T = DoubleLeftRightRotation(T);
                }
            }
        }
        else if(data>T->value){
            T->Right = Insert(T->Right,data);
            if(GetHeight(T->Right)-GetHeight(T->Left)==2){
                if(data>T->Right->value){
                    T = SingleRightRotation(T);
                }else{
                    T = DoubleRightLeftRotation(T);
                }
            }

        }

    }
    T->Height = GetHeight(T);
    return T;
}

int main(){
    AVLTree T = NULL;
    int N,data;
    std::cin >> N;
    for(int i=0;i<N;i++){
        std::cin >>data ;
        T = Insert(T,data);
        // std::cout << "root -> value:  "<<T->value << '\n';
    }
    std::cout << T->value << '\n';
}
