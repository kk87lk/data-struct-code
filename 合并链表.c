#include <stdio.h>
#include <stdlib.h>
typedef struct list List;
struct list
{
    int num;
    List *next;
};
List* Converge(List* HeadA,List* HeadB){
    List *PA = HeadA->next;
    List *PB = HeadB->next;
    List *temp = NULL;
    List *HeadC = (List *)malloc(sizeof(List));
    HeadC->next = NULL;
    List *PC = HeadC;
    while (PA&&PB)
    {
        if(PA->num>PB->num){
            temp = PA;
            PA = PA->next;
            temp->next = NULL;
            PC->next = temp;
            PC = PC->next;
        }else if(PA->num<PB->num){
            temp = PB;
            PB = PB->next;
            temp->next = NULL;
            PC->next = temp;
            PC = PC->next;
        }else{
            temp = PA;
            PA = PA->next;
            temp->next = NULL;
            PC->next = temp;
            PC = PC->next;
            temp = PB;
            PB = PB->next;
            temp->next = NULL;
            PC->next = temp;
            PC = PC->next;
        }
    }
    if(PA)
        PC->next = PA;
    if(PB)
        PC->next = PB;
    return HeadC;
}
void show(List *head)
{
    List *p = head->next;
    if (!p)
        return;
    for (; p; p = p->next)
    {
        printf("%d ", p->num);
    }
}
List* Create(){
    List *head = (List *)malloc(sizeof(List));
    head->next = NULL;
    int x;
    scanf("%d", &x);
    while (x)
    {
        List *new = (List *)malloc(sizeof(List));
        new->num = x;
        new->next = head->next;
        head->next = new;
        scanf("%d", &x);
    }
    return head;
}
int main(){
    List *HeadA = NULL, *HeadB = NULL,*HeadC=NULL;
    HeadA = Create();
    HeadB = Create();
    HeadC = Converge(HeadA, HeadB);
    show(HeadC);
}