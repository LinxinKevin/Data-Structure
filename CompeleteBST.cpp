#include<iostream>
#include<math.h>
#include<queue>
using namespace std;

int N ;
int flag = 1;
int num[1005];
int tmp[2005] = {0};
struct Tnode;
typedef Tnode *BSTree;
struct Tnode{
    int value;
    BSTree Left;
    BSTree Right;
};
BSTree BST = NULL;
queue<BSTree> q;
void Sort(){
    int i,j;
    j = 0;
    for(i=0;i<2005;i++){
        if(tmp[i]==1){
            num[j] = i;
            j++;
        }
    }
}

void Competele(int start,int end,BSTree &BST){
    if(end < start) BST = NULL  ;
    else{
        int OtherRoots = end-start;
        int LeftRoots,RightRoots;
        LeftRoots = RightRoots = 0;
        int level = 1;
        while( OtherRoots >= (int)pow(2,level) ){
            LeftRoots += (int)pow(2,level-1);
            RightRoots = LeftRoots;
            OtherRoots -= (int)pow(2,level);
            level += 1;
        }
        if(OtherRoots > (int)pow(2,level-1)){
            LeftRoots += (int)pow(2,level-1);
            RightRoots += OtherRoots-(int)pow(2,level-1);
        }
        else{
            LeftRoots += OtherRoots;
        }
        BST = (BSTree)malloc(sizeof(struct Tnode));
        BST->value = num[start+LeftRoots];
        BST->Left = BST->Right = NULL;
        // std::cout << num[start+LeftRoots] <<" " ;
        // std::cout << "LeftRoots:  " << LeftRoots<< '\n';
        // std::cout << "RightRoots  " << RightRoots<<'\n';
        Competele(start,start+LeftRoots-1,BST->Left);
        Competele(start+LeftRoots+1,end,BST->Right);
    }

}

void Print(BSTree BST){
    q.push(BST);
    while (!q.empty()) {
        if(flag) flag=0,std::cout << q.front()->value;
        else std::cout << " " << q.front()->value;
        if(q.front()->Left!=NULL) q.push(q.front()->Left);
        if(q.front()->Right!=NULL) q.push(q.front()->Right);
        q.pop();
    }
}

int main() {
    std::cin >> N;
    int i ;
    int value;
    for(i=0;i<N;i++) {
        std::cin >> value;
        tmp[value] = 1;
    }
    Sort();
    Competele(0,N-1,BST);
    // std::cout << BST->Left->Left->Right->value << '\n';
    Print(BST);
    return 0;
}
