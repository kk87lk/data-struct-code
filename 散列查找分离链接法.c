#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Maxsize 15     //字符串最大长度假设15
#define MAXTABLESIZE 1000
typedef char Elemtype[Maxsize + 1];
typedef int Index;
typedef struct node LNode;
struct node{
    Elemtype data;
    LNode *next;
};
typedef LNode Position;
typedef LNode List;
typedef struct {
    int size;
    List *Heads;
} HashTable;
int NextPrime(int N)
{                                       /* 返回大于N且不超过MAXTABLESIZE的最小素数 */
    int i, p = (N % 2) ? N + 2 : N + 1; /*从大于N的下一个奇数开始 */

    while (p <= MAXTABLESIZE)
    {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i))
                break; /* p不是素数 */
        if (i == 2)
            break; /* for正常结束，说明p是素数 */
        else
            p += 2; /* 否则试探下一个奇数 */
    }
    return p;
}
HashTable* Create(int Tablesize){
    HashTable *H;
    int i;
    H = (HashTable *)sizeof(HashTable);
    H->size = NextPrime(Tablesize);
    H->Heads = (List *)malloc(H->size * sizeof(struct node));
    for(i = 0; i < H->size;i++){
        H->Heads[i].data[0] = '\0';
        H->Heads[i].next = NULL;
    }
    return H;
}
int Hash(Elemtype x, int TableSize)
{
    return (x[0] - 'a');
}
Position* Find(HashTable* H,Elemtype key){                  //key是字符串
    Position *P;
    Index Pos;
    Pos = Hash(key, H->size);
    P = H->Heads[Pos].next;
    while (P&&strcmp(P->data,key))
    {
        P = P->next;
    }
    return P;
}
void Insert(HashTable* H,Elemtype key){
    Position* P, *NewCell;
    Index pos;
    P = Find(H, key);
    if(!P){
        pos = Hash(key, H->size);
        NewCell = (Position *)malloc(sizeof(Position));
        strcpy(NewCell->data, key);
        NewCell->next = H->Heads[pos].next;
        H->Heads[pos].next = NewCell;
    }
}
void Destroy(HashTable* H){
    int i;
    Position *p, *temp;
    for (i = 0; i < H->size;i++){
        p = H->Heads[i].next;
        while (p)
        {
            temp = p->next;
            free(p);
            p = temp;
        }
        free(H->Heads);
        free(H);
    }
}