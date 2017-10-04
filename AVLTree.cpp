typedef struct AVLNode *Position;
typedef Position AVLTree;
struct AVLNode{
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
}

AVLTree SingleLeftRotation(AVLTree A){
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A ;
    A->Height = max(GetHeight(A->Left),GetHeight(A->Right))+1;
    B->Height = max(A->Height,GetHeight(B->Left))+1;
    return B;
}

AVLTree SingleRightRotation(AVLTree A){
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Right = A;
    A->Height = max(GetHeight(A->Left),GetHeight(A->Right))+1;
    B->Height = max(A->Height,GetHeight(B->Right));
    return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A){
    A->Left = SingleRightRotation(A->Left);
    return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A){
    A->Right = SingleLeftRotation(A->Right);
    return SingleRightRotation(A);
}

AVLTree Insert(AVLTree A,ElementType data){
    if(!AVLTree){
        AVLTree A;
        A = (AVLTree)malloc(sizeof(struct AVLNode));
        A->Data = data;
        A->Height = 0;
        A->Left = A->Right = NULL;
    }
    else{
        if(data>A->Data){
            A->Right = Insert(A->Right,data);
            if(GetHeight(A->Left)-GetHeight(A->Right)==-2){
                if (data>A->Right->Data)
                    A = SingleRightRotation(A);
                else
                    A = DoubleRightLeftRotation(A);
            }

        }
        else{
            A->Left = Insert(A->Left,data);
            if(GetHeight(A->Right)-GetHeight(A->Left)==-2){
                if(data<A->Left->Data)
                    A = SingleLeftRotation(A);
                else
                    A = DoubleLeftRightRotation(A);
            }
        }

    }
    A->Height = max(GetHeight(A->Left),GetHeight(A->Right))+1; // 更新树的高度
    return A;
}
