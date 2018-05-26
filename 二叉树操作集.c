#include <stdio.h>
#include <stdlib.h>
typedef char Elemtype;
int n0 = 0, n1 = 0, n2 = 0,cnt1 = 0,cnt2 = 0;
#define Maxsize 100
typedef struct Tree Tree;
struct Tree
{
    Elemtype data;
    Tree *left, *right;
    int flag;
};
typedef struct sNode
{
    Tree *Data[Maxsize];
    int top;
} Stack;
typedef struct queue
{
    Tree *Data[Maxsize];
    int front, rear;
} Queue;
int isemptyQueue(Queue *Q)
{
    return (Q->front == Q->rear);
}
void InsertQueue(Queue *Q, Tree *root)
{
    Q->Data[Q->rear] = root;
    Q->rear = (Q->rear + 1) % Maxsize;
}
Tree *Delete(Queue *Q)
{
    Tree *T;
    T = Q->Data[Q->front];
    Q->front = (Q->front + 1) % Maxsize;
    return T;
}
Queue *CreateQueue()
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->front = Q->rear = 0;
    return Q;
}
int push(Stack *S, Tree *root)
{
    S->Data[++(S->top)] = root;
    return 1;
}
Tree *pop(Stack *S)
{
    return S->Data[S->top--];
}
Stack *Create()
{
    Stack *S = (Stack *)malloc(sizeof(Stack));
    S->top = -1;
    return S;
}
int isempty(Stack *S)
{
    return (S->top == -1);
}
Tree* PreBuildTree(){
    Elemtype x;
    scanf("%c", &x);
    Tree *Node;
    if(x==' '){
        Node = NULL;
    }else
    {
        Node = (Tree *)malloc(sizeof(Tree));
        Node->data = x;
        Node->flag = 0;
        Node->left = PreBuildTree();
        Node->right = PreBuildTree();
    }
    return Node;
}
void PreOrder(Tree* root){
    if(!root)
        return;
    else{
        printf("%c", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}
void InOrder(Tree* root){
    if (!root)
        return;
    else
    {
        InOrder(root->left);
        printf("%c", root->data);
        InOrder(root->right);
    }
}
void PostOrder(Tree *root)
{
    if (!root)
        return;
    else
    {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%c", root->data);
    }
}
void PreorderTree(Tree* root){
    Tree* T=root;
    Stack *S = Create();
    while (T || !isempty(S))
    {
        while (T)
        {
            push(S, T);
            printf("%c", T->data);
            T = T->left;
        }
        if (!isempty(S))
        {
            T = pop(S);
            T = T->right;
        }
    }
}
void InorderTree(Tree *root)
{
    Tree *T = root;
    Stack *S = Create();
    while (T || !isempty(S))
    {
        while (T)
        {
            push(S, T);
            T = T->left;
        }
        if (!isempty(S))
        {
            T = pop(S);
            printf("%c", T->data);
            T = T->right;
        }
    }
}
void PostorderTree(Tree* root){
    Tree *T = root;
    Stack *S = Create();
    while (T || !isempty(S))
    {
        while (T && T->flag == 0)
        {
            push(S, T);
            T->flag++;
            T = T->left;
        }
        if (!isempty(S))
        {
            T = pop(S);
            if (T->right && T->right->flag == 0)
            {
                push(S, T);
            }
            else
            {
                printf("%c", T->data);
            }
            T = T->right;
        }
        else
        {
            return;
        }
    }
}
void Lineorder(Tree *root)
{
    Queue *Q = CreateQueue();
    Tree *T;
    if (!root)
        return;
    InsertQueue(Q, root);
    while (!isemptyQueue(Q))
    {
        T = Delete(Q);
        printf("%c", T->data);
        if (T->left)
            InsertQueue(Q, T->left);
        if (T->right)
            InsertQueue(Q, T->right);
    }
}
void CalculateTreeNode(Tree* T){
    if(T){
        if (T->left && T->right)
            n2++;
        if (!T->left && !T->right)
            n0++;
        if ((T->left && !T->right) || (!T->left && T->right))
            n1++;
        CalculateTreeNode(T->left);
        CalculateTreeNode(T->right);
    }
}
void GetHeight(Tree *root)
{
    if (root == NULL)
        return ;
    if(root->left)
        cnt1++;
    if(root->right)
        cnt2++;
    GetHeight(root->left);
    GetHeight(root->right);
}
int main(){
    int x = 0,mark=0;
    Tree *root;
    do{
        printf("1.Build Tree(Preorder)\n");
        printf("2.PreOrder  Tree(recursion)\n");
        printf("3.InOrder   Tree(recursion)\n");
        printf("4.PostOrder Tree(recursion)\n");
        printf("5.PreOrder  Tree\n");
        printf("6.InOrder   Tree\n");
        printf("7.PostOrder Tree\n");
        printf("8.LineOrder Tree\n");
        printf("9.Get Tree Nodes\n");
        printf("10.Get Tree Height\n");
        printf("0.Exit\n");
        printf("Please select an option:");
        scanf("%d", &x);
        switch(x){
            case 1:
                fflush(stdin);
                printf("Please input the nodes:");
                root = PreBuildTree();
                mark=1;
                break;
            case 2:
                if(mark){
                    printf("Below is the Preorder:\n");
                    PreOrder(root);
                    printf("\n");
                }else{
                    printf("There is no Tree in memory!\n");
                    continue;
                }
                break;
            case 3:
                if (mark)
                {
                    printf("Below is the Inorder:\n");
                    InOrder(root);
                    printf("\n");
                }
                else
                {
                    printf("There is no Tree in memory!\n");
                    continue;
                }
                break;
            case 4:
                if (mark)
                {
                    printf("Below is the Postorder:\n");
                    PostOrder(root);
                    printf("\n");
                }
                else
                {
                    printf("There is no Tree in memory!\n");
                    continue;
                }
                break;
            case 5:
                if (mark)
                {
                    printf("Below is the Preorder:\n");
                    PreorderTree(root);
                    printf("\n");
                }
                else
                {
                    printf("There is no Tree in memory!\n");
                    continue;
                }
                break;
            case 6:
                if (mark)
                {
                    printf("Below is the Inorder:\n");
                    InorderTree(root);
                    printf("\n");
                }
                else
                {
                    printf("There is no Tree in memory!\n");
                    continue;
                }
                break;
            case 7:
                if (mark)
                {
                    printf("Below is the Postorder:\n");
                    PostorderTree(root);
                    printf("\n");
                }
                else
                {
                    printf("There is no Tree in memory!\n");
                    continue;
                }
                break;
            case 8:
                if (mark)
                {
                    printf("Below is the Lineorder:\n");
                    Lineorder(root);
                    printf("\n");
                }
                else
                {
                    printf("There is no Tree in memory!\n");
                    continue;
                }
                break;
            case 9:
                if(mark){
                    CalculateTreeNode(root);
                    printf("There is %d nodes in the Tree!\nn0=%d\tn1=%d\tn2=%d\n",n0+n1+n2,n0,n1,n2);
                    n0 = n1 = n2 = 0;
                }else{
                    printf("There is no Tree in memory!\n");
                    continue;
                }
                break;
            case 10:
                if(mark){
                    GetHeight(root);
                    printf("The Height is %d!\n", (cnt1 > cnt2 ? cnt1 : cnt2) + 1);
                    cnt1 = cnt2 = 0;
                }else{
                    printf("There is no Tree in memory!\n");
                    continue;
                }
                break;
            case 0:
                printf("Thanks to use!\n");
                exit(1);
        }
    } while (1);
}