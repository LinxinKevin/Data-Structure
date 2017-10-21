#include <iostream>
#include <stdlib.h>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

struct Node{
    int weight;
    char letter;
};

struct Tnode;
typedef Tnode *HTree;
struct Tnode
{
    int weight;
    HTree Left;
    HTree Right;
};

int getIndex(Node* letterNodes,char letter,int size){
    int index = 0;
    while(index < size){
        if(letterNodes[index].letter == letter) return index;
        index ++;
    }
    return -1;
}

int TreeInsert(HTree T, string road)
{
    // std::cout << "/* message */" << '\n';
    HTree tmp = T;
    for (int i = 0; i < road.length(); i++)
    {
        if (road[i] == '1')
        {
            // std::cout << "right" << '\n';
            if (tmp->Right == NULL)
                tmp->Right = (HTree)malloc(sizeof(struct Tnode)), tmp->Right->Left = tmp->Right->Right = NULL;
            else
            {
                if (tmp->Right->weight == 1)
                    return 0;
            }
            tmp = tmp->Right;
        }
        else if (road[i] == '0')
        {
            // std::cout << "left" << '\n';
            if (tmp->Left == NULL)
                tmp->Left = (HTree)malloc(sizeof(struct Tnode)), tmp->Left->Left = tmp->Left->Right = NULL;
            else
            {
                if (tmp->Left->weight == 1)
                    return 0;
            }
            tmp = tmp->Left;
        }
    }
    tmp->weight = 1;
    return 1;
}

int travel(HTree T)
{
    if (T == NULL)
        return 1;
    if (T->Right == NULL && T->Left == NULL)
        return 1;
    if ((T->Left != NULL || T->Right != NULL) && T->weight == 1)
        return 0;
    else
        return travel(T->Left) && travel(T->Right);
}

int main(){
    int N;
    int index = 0;
    int tmpWeight;
    char tmpLetter;
    int WPL = 0;
    std::cin >> N;
    priority_queue<int,vector<int>,greater<int> >q;
    Node *letterNodes = (Node*)malloc(sizeof(struct Node)*N);
    while(index < N){
        std::cin >> tmpLetter >> tmpWeight;
        letterNodes[index].weight = tmpWeight;
        letterNodes[index].letter = tmpLetter;
        q.push(tmpWeight);
        index ++;
    }
    int weight1,weight2;
    while(!q.empty()){
        weight1 = q.top();
        q.pop();
        WPL += weight1;
        if(!q.empty()){
            weight2 = q.top();
            q.pop();
            q.push(weight1 + weight2);
            WPL += weight2;
        }else{
            WPL -= weight1;
        }
    }
    // std::cout << WPL << '\n';
    int M;
    std::cin >> M;
    while (M--) {
        int flag = 1;
        char letter;
        string road;
        int result = 0;
        HTree T = (HTree)malloc(sizeof(struct Tnode));
        T->Left = T->Right =NULL;
        T->weight = 0;
        for(int i =0;i<N;i++){
            std::cin >> letter>> road;
            if(flag){
                int index = getIndex(letterNodes,letter,N);
                flag = flag && (index>=0) ;
                if(flag){
                    result += road.length() * letterNodes[getIndex(letterNodes,letter,N)].weight;
                    flag = flag && (TreeInsert(T,road)==1);
                    // std::cout << TreeInsert(T,road);
                }
            }
        }
        flag = flag && travel(T);
        if(flag && result==WPL) std::cout << "Yes" << '\n';
        else std::cout << "No" << '\n';
    }
}
