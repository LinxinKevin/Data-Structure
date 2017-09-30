#include<stdio.h>
#include<stdlib.h>
struct snode;
typedef struct snode* PtrTnode;
struct snode{
    int Data;
    PtrTnode Next;
};
typedef PtrTnode Stack;

Stack Creat(int Maxsize){
    Stack S;
    S = (Stack)malloc(sizeof(struct snode));
    S->Data = Maxsize;
    S->Next = NULL;
    return S;
}

int Push(Stack S,int e){
    if(S->Data==0){
        return 0;
    }
    PtrTnode nodecell;
    nodecell = (PtrTnode)malloc(sizeof(struct snode));
    nodecell->Data = e;
    nodecell->Next = S->Next;
    S->Next = nodecell;
    S->Data--;
    return 1;
}

int Pop(Stack S){
    if(S->Next){
        S->Data++;
        PtrTnode nodecell;
        nodecell = (PtrTnode)malloc(sizeof(struct snode));
        nodecell = S->Next;
        S->Next = S->Next->Next;
        int a = nodecell->Data;
        free(nodecell);
        return a;
    }
    else{
        return 0;
    }
}

void Print(Stack S){
    S = S->Next;
    while(S){
        printf("%d ",S->Next );
        S = S->Next;
    }
    printf("\n");
}

int main(){
    int M,N,K;
    scanf("%d%d%d",&M,&N,&K );
    while(K--){
        int num[1005];
        int i,j;
        Stack S;
        S = Creat(M);
        for(i=1;i<=N;i++){
            scanf("%d",&num[i] );
        }
        j = i =1;
        int flag = 1;
        while(i<=N){
            if(j<=num[i]){
                if (!Push(S,j)) {flag = 0;break;}
                if(j==num[i]){Pop(S);i++;}
                j++;
                }
                else if(j>num[i]){
                    if(Pop(S)!=num[i]) {flag = 0;break;}
                    i++;
            }
        }
        if(flag) printf("YES\n");
        else printf("NO\n");

    }
}
