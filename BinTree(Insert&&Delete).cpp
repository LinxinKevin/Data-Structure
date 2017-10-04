BinTree Insert(BinTree BST, ElementType X)
{
    if(BST==NULL){
        BST = (BinTree)malloc(sizeof(Tnode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else{
        if(X>BST->Data) return Insert(BST->Right,X);
        if(X<BST->Data) return Insert(BST->Left,X);
    }
    return BST;
}

BinTree Delete(BinTree BST,ElementType X){
    if(BST = NULL) std::cout << "can not  find the X" << '\n';
    else{
        if (X>BST->Data) return Delete(BST->Right,X);
        else if(X<BST->Data) return Delete(BST->Left,X);
        else{
            if(BST->Left && BST->Right){
                // Find the Min Ele in BST->Right
                TMP = FindMin(BST->Right);
                BST->Data = TMP->Data;
                Delete(BST->Right,BST->Data)

                // Find the Max Ele in BST->Left
                // TMP = FindMax(BST->Left);
                // BST->Data = TMP->Data;
                // Delete(BST->Left,BST->Data);
            }
            else{
                TMP = BST;
                // Only exits Right or No Childs
                if(!BST->Left)
                    BST = BST->Right;
                else
                    BST = BST->Left;
                free(TMP);
            }

        }
    }
    return BST;

}
