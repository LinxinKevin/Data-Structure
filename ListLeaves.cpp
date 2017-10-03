#include <iostream>
#include <memory.h>
#include<queue>
using namespace std;

struct TreeNode{
    int Left;
    int Right;
}Tree[10];
queue<int>  q;
int flag = 1;
int Creat(){
    int N,i,root;
    std::cin >> N;
    char left,right;
    int num[10];
    memset(num,0,sizeof(int)*10);
    for(i=0;i<N;i++){
        std::cin >>left >>right ;
        if(left=='-') Tree[i].Left=-1;
        else{
            Tree[i].Left = left-'0';
            num[left-'0'] = 1;
        }
        if(right=='-') Tree[i].Right=-1;
        else{
            Tree[i].Right = right-'0';
            num[right-'0'] = 1;
        }
    }
    root = -1;
    for(i=0;i<N;i++){
        if(!num[i]){
            root = i;
            break;
        }
    }
    return root;
 }

void OutLeves(int root){
    if(root != -1) q.push(root);
    while(!q.empty()){
        int tmp = q.front();
        q.pop();
        if(Tree[tmp].Left==-1 && Tree[tmp].Left==-1)
        {
            if(flag) flag=0,std::cout << tmp;
            else std::cout << " " <<tmp;
        }
        else{
            if(Tree[tmp].Left != -1) q.push(Tree[tmp].Left);
            if(Tree[tmp].Right != -1) q.push(Tree[tmp].Right);
        }
    }
}

int main(){
    int root = Creat();
    OutLeves(root);
}
