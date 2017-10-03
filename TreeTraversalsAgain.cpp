#include <iostream>
#include <memory.h>
#include <string>
using namespace std;

struct TreeNode;
string Push = "Push";
string Pop = "Pop";
int N;
int flag = 1;
typedef TreeNode *TNodePtr;
struct TreeNode{
    int Data;
    TNodePtr Left;
    TNodePtr Right;
};
typedef TNodePtr BinTree;

void Creat(BinTree &BT){
    string Action;
    int n;
    if(N){
        std::cin >> Action;
        if(Action.compare(Push)==0){
            std::cin >> n;
            N--;
            BT = new TreeNode;
            BT->Data = n;
            Creat(BT->Left);
            Creat(BT->Right);
        }
        else if(Action.compare(Pop)==0){
            N--;
            BT = NULL;
        }
    }
}

void Print(BinTree BT){
    if(BT!=NULL){
        Print(BT->Left);
        Print(BT->Right);
        if(flag) flag =0 ,std::cout << BT->Data;
        else std::cout << " " <<BT->Data;
        // std::cout << BT->Data;
    }
}

int main(){
    std::cin >> N;
    N*=2;
    BinTree BT;
    Creat(BT);
    Print(BT);
    return 0;
}
