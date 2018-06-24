#include <stdio.h>
#include <stdlib.h>
typedef char Elemtype;
typedef struct Tree Tree;
struct Tree
{
    Elemtype data;
    Tree *left, *right;
    int Height;
};
int Max(int a,int b){
    return a>b? a:b;
}
int GetHeight(Tree* root){
    int cnt1=0,cnt2=0;
    Tree *T1 = root;
    Tree *T2 = root;
    if(root==NULL) return -1;
    else{
    	while(T1->left){
        cnt1++;
        T1 = T1->left;
    }
    while (T2->right)
    {
        cnt2++;
        T2 = T2->right;
    }
	}
    return cnt1 > cnt2 ? cnt1 : cnt2;
}
Tree *SingleLeftRotation(Tree* A){
    Tree *B = A->left;
    A->left = B->right;
    B->right = A;
    A->Height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->Height = Max(GetHeight(B->left), A->Height) + 1;
    return B;
}
Tree *SingleRightRotation(Tree* A){
    Tree *B = A->right;
    A->right = B->left;
    B->left = A;
    A->Height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->Height = Max(GetHeight(B->left), A->Height) + 1;
    return B;
}
Tree *DoubleLeftRightRotation(Tree* A){
    A->left = SingleRightRotation(A->left);
    return SingleLeftRotation(A);
}
Tree *DoubleRightLeftRotation(Tree *A){
    A->right = SingleLeftRotation(A->right);
    return SingleRightRotation(A);
}
Tree* Insert(Tree* T,Elemtype x){
    if(!T){
        T = malloc(sizeof(Tree));
        T->data = x;
        T->Height = 0;
        T->left = T->right = NULL;
    }else if(x<T->data){
        T->left = Insert(T->left, x);
        if (GetHeight(T->left) - GetHeight(T->right) == 2){
            if (x < T->left->data)
                T = SingleLeftRotation(T);
            else
                T = DoubleLeftRightRotation(T);
        }
    }
    else if(x>T->data){
        T->right = Insert(T->right, x);
        if (GetHeight(T->left) - GetHeight(T->right) == -2){
            if (x > T->right->data)
                T = SingleRightRotation(T);
            else
                T = DoubleRightLeftRotation(T);
        }
    }
    T->Height = Max(GetHeight(T->left), GetHeight(T->right)) + 1;
    return T;
}
void PreTree(Tree *ROOT)
{
    if (ROOT == NULL)
    {
        return;
    }
    else
    {
        printf("%c", ROOT->data);
        PreTree(ROOT->left);
        PreTree(ROOT->right);
    }
}
Tree *PreBuildTree()
{
    Elemtype x;
    scanf("%c", &x);
    Tree *Node;
    if (x == ' ')
    {
        Node = NULL;
    }
    else
    {
        Node = (Tree *)malloc(sizeof(Tree));
        Node->data = x;
        Node->left = PreBuildTree();
        Node->right = PreBuildTree();
    }
    return Node;
}
int main(){
    Elemtype x;
    Tree *root = PreBuildTree();
    printf("The formar Tree:\n");
    PreTree(root);
    printf("\nInput the element want to insert:");
    fflush(stdin);
    scanf("%c", &x);
    root=Insert(root, x);
    printf("\nThe current Tree:\n");
    PreTree(root);
}
