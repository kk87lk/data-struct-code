#include <stdio.h>
#include <stdlib.h>
typedef int Elemtype;
typedef struct TreeNode Tree;
struct TreeNode{
    Elemtype data;
    Tree*left,*right;
};
Tree* InsertNode(Tree* root,Elemtype x){
    if(!root){
        root = (Tree *)malloc(sizeof(Tree));
        root->data = x;
        root->left = root->right = NULL;
    }else{
        if(x<root->data)
            root->left = InsertNode(root->left, x);
        else if(x>root->data)
            root->right = InsertNode(root->right, x);
    }
    return root;
}
int JudgeTree(Tree* root1,Tree *root2){
    int cnt1 = 0, cnt2 = 0;
    Tree *p1 = root1;
    Tree *p2 = root2;
    while (p1 && p2)
    {
        if (p1->data != p2->data)
            return 0;
        cnt1++;
        p1 = p1->left;
        p2 = p2->left;
   }
   p1 = root1;
   p2 = root2;
   while (p1&&p2)
   {
       if (p1->data != p2->data)
           return 0;
       cnt2++;
       p1 = p1->right;
       p2 = p2->right;
   }
   if(cnt1&&cnt2)
   return 1;
   else return 0;
}
int main(){
    int N, L,i,x,j,k,cnt=0,vertex=0;
    int judge[100];
    scanf("%d", &N);
    while(N){
        scanf("%d", &L);
        Tree *root1 = NULL;
        for (i = 0; i < N;i++){
            scanf("%d", &x);
            root1=InsertNode(root1, x);
        }
        for (j = 0; j < L;j++){
            Tree *root2 = NULL;
            for (k = 0; k < N;k++){
                scanf("%d", &x);
                root2=InsertNode(root2, x);
            }
            cnt = JudgeTree(root1, root2);
            if(cnt!=0)
                judge[vertex] = 1;
            else
                judge[vertex] = 0;
            vertex++;
        }
        scanf("%d", &N);
    }
    for (i = 0; i < vertex;i++){
        if(judge[i]==1)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
