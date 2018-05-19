#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXTABLESIZE 1000
typedef int Index,Elemtype;
typedef Index Position;
typedef enum{Leitimate, Empty, Deleted} Entrytype;
typedef struct node{
    Elemtype data;
    Entrytype info;
} cell;

typedef struct {
    int size;
    cell *cells;
} HashTable;

int NextPrime( int N )
{ /* 返回大于N且不超过MAXTABLESIZE的最小素数 */
    int i, p = (N%2)? N+2 : N+1; /*从大于N的下一个奇数开始 */
 
    while( p <= MAXTABLESIZE ) {
        for( i=(int)sqrt(p); i>2; i-- )
            if ( !(p%i) ) break; /* p不是素数 */
        if ( i==2 ) break; /* for正常结束，说明p是素数 */
        else  p += 2; /* 否则试探下一个奇数 */
    }
    return p;
}
HashTable* CreateTable(int TableSize){
    HashTable *H;
    int i;
    H = (HashTable *)malloc(sizeof(HashTable));
    H->size = NextPrime(TableSize);
    H->cells = (cell *)malloc(sizeof(cell));
    for (i = 0; i < H->size;i++){
        H->cells[i].info = Empty;
    }
    return H;
}
int Hash(Elemtype x,int TableSize){
    return x % TableSize;                               //取模求哈希位值
}

Position Find(Elemtype key,HashTable* H){
    Position Newpos, Currentpos;
    int CNum = 0;
    Newpos = Currentpos = Hash(key, H->size);
    while(H->cells[Newpos].info!=Empty&&H->cells[Newpos].data!=key){
        if(++CNum%2){
            Newpos = Currentpos + (CNum + 1) * (CNum + 1) / 4;
            while (Newpos>=H->size)
            {
                Newpos -= H->size;
            }
        }else{
            Newpos = Currentpos + CNum * CNum / 4;
            while (Newpos<0)
            {
                Newpos += H->size;
            }
        }
    }
    return Newpos;
}
void Insert(Elemtype key,HashTable *H){
    Position pos;
    pos = Find(key, H);
    if(H->cells[pos].info!=Leitimate){
        H->cells[pos].data = key;
        H->cells[pos].info = Leitimate;
    }
}