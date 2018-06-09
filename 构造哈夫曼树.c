#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXBIT 10
#define MAXVALUE 1000
typedef struct{
    int weight;
    int parent,left,right;
}Hnode,*HTree;
typedef char* *HCode;
HTree HuffmanTree(int *w,int n){
    int m,m1,m2,x1,x2,i,j;
    HTree ht;
    Hnode *p;
    if(n<=1)    return NULL;
    m=2*n-1;
    ht=(Hnode*)malloc(sizeof(Hnode)*m);
    if(ht==NULL)    return ht;
    for(p=ht,i=0;i<n;++i,++p,++w){
        p->weight=*w;
        p->left=-1;
        p->right=-1;
        p->parent=-1;
    }
    for(i=n;i<m;++i){
        m1=m2=MAXVALUE;
        x1=x2=0;
        for(j=0;j<i;++j){
            if(ht[j].parent==-1&&ht[j].weight<m1){
                m2=m1;
                x2=x1;
                m1=ht[j].weight;
                x1=j;
            }else if(ht[j].parent==-1&&ht[j].weight<m2){
                m2=ht[j].weight;
                x2=j;
            }
        }
        ht[x1].parent=i;
        ht[x2].parent=i;
        ht[i].left=x1;
        ht[i].right=x2;
        ht[i].weight=m1+m2;
    }
    return ht;
}
HCode HuffmanCoding(HTree ht,int n){
    HCode HC;
    char *cd;
    int start,i,c,f;
    HC=(HCode)malloc(n*sizeof(char*));
    cd=(char*)malloc(sizeof(char)*n);
    cd[n-1]='\0';
    for(i=0;i<n;++i){
        start=n-1;
        for(c=i,f=ht[i].parent;f!=-1;c=f,f=ht[f].parent){
            if(ht[f].left==c)   cd[--start]='\0';
            else    cd[--start]='1';
        }
        HC[i]=(char*)malloc(sizeof(char)*(n-start));
        strcpy(HC[i],&cd[start]);
    }
    free(cd);
    return HC;
}
