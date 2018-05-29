#include <stdio.h>
#include <stdlib.h>
typedef char Elemtype;
typedef struct Tree Tree;
struct Tree
{
    Elemtype data;
    Tree *left, *right;
};

Tree* PreInOrder(char Preorder[],char Inorder[],int i,int j,int k,int h){
    Tree *T = (Tree *)malloc(sizeof(Tree));
    int m;
    T->data = Preorder[i];
    m = k;
    while (Preorder[i]!=Inorder[m])
    {
        m++;
    }
    if(m==k)
        T->left = NULL;
    else
        T->left = PreInOrder(Preorder, Inorder, i + 1, i + m - k, k, m-1);              //m-k:Inorder中根结点前面的结点数(即偏移个数)
    if(m==h)                                                                            //m-1:Inorder中根结点前一个
        T->right = NULL;
    else
        T->right = PreInOrder(Preorder, Inorder, i + m - k + 1, j, m + 1, h);
    return T;
}
Tree *Build(char Preorder[], char Inorder[],int n){             //统一接口
    Tree *root;
    if(n<=0)
        root = NULL;
    else
        root = PreInOrder(Preorder, Inorder, 0, n - 1, 0, n - 1);
    return root;
}
void Preorder(Tree *root)
{
    if (!root)
        return;
    else
    {
        printf("%c", root->data);
        Preorder(root->left);
        Preorder(root->right);
    }
}
int main(){
    char PreOrder[] = "ABDC";
    char InOrder[] = "BDAC";
    Tree *root = Build(PreOrder, InOrder, 4);
    Preorder(root);
}