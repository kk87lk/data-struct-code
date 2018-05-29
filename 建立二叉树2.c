#include <stdio.h>
#include <stdlib.h>
typedef char Elemtype;
typedef struct TreeNode Tree;
#define Maxsize 20
struct TreeNode{
    Elemtype data;
    Tree *left, *right;
};
void PreOrder(Tree *root)
{
    if (!root)
        return;
    else
    {
        printf("%c", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}
Tree* CreateBTree(){
    Elemtype x;
    Tree *root,*v[Maxsize];
    int i,j;
    printf("Please input the Series Num and value:");
    fflush(stdin);
    scanf("%d%c", &i, &x);
    while (i!=0&&x!='0')
    {
        Tree* p = (Tree *)malloc(sizeof(Tree));
        p->data = x;
        p->left = NULL;
        p->right = NULL;
        v[i]=p;
        if(i==1)    root=p;
        else{
        	j=i/2;
            if(i%2==0){
            	 v[j]->left=p;
			}
            else{
            	v[j]->right=p;
			}
        }
        printf("Please input the Series Num and value:");
        fflush(stdin);
        scanf("%d%c", &i, &x);
    }
    return root;
}
int main(){
    Tree *root;
    root = CreateBTree();
    PreOrder(root);
}
