#include<stdio.h>
#include<stdlib.h>
int F_data[100005];
int F_next[100005];
struct snode;
typedef struct snode* PtrTode;
struct snode{
	int Data;
	PtrTode Next;
};
typedef PtrTode Stack;

Stack Creat(){
	Stack S;
	S = (Stack)malloc(sizeof(struct snode));
	S->Next = NULL;
	return S;
}

Insert(Stack S,int d){
	PtrTode nodecell;
	nodecell = (PtrTode)malloc(sizeof(struct snode));
	nodecell->Data = d;
	nodecell->Next = S->Next;
	S->Next = nodecell;
}

void Print(Stack S){
	S = S->Next;
	while(S->Next){
		printf("%05d %d %05d\n",S->Data,F_data[S->Data],S->Next->Data);
		S = S->Next;
	}
	printf("%05d %d -1\n",S->Data,F_data[S->Data]);
}

void reversed(Stack S){
	PtrTode s,t,e;
	s = t= e= (PtrTode)malloc(sizeof(struct snode));
	if(!S->Next) return;
	s = S->Next;
	e = NULL;
	while(s->Next){
		t = s->Next;
		s->Next = e;
		e = s;
		s = t;
  		t = t->Next;
	}
	s->Next = e;
	S->Next = s;
}

int main()
{
	Stack S,TMP;
	S = Creat();
	TMP = Creat();
	PtrTode t,q;
	t = q= (PtrTode)malloc(sizeof(struct snode));
	t = TMP;
	int start_add,num,rev_len;
    int cur_add,value,next_add;
    scanf("%d%d%d",&start_add,&num,&rev_len );
    while(num--){
        scanf("%d%d%d",&cur_add,&value,&next_add );
        F_data[cur_add] = value;
        F_next[cur_add] = next_add;
    }
    while(start_add!=-1){
        Insert(S,start_add);
        start_add = F_next[start_add];
    }
	// Print(S);
	reversed(S);
	// Print(S);
	q = S;
	while(rev_len--){
		Insert(TMP,q->Next->Data);
		q = q->Next;
	}


	t  = TMP;
	while(t->Next){
		t = t->Next;
	}
	t->Next = q->Next;
	Print(TMP);
}
