#include <stdio.h>
#include <stdlib.h>
typedef int Elemtype;
typedef struct node List;
struct node{
    Elemtype data;
    List *next;
};
List* Tranvers(List* head){
    List *ph = head;
    List *p, *q;
    p = q = head->next;
    if(!p)
        return head;
    for (; ph->next->next;ph=ph->next){
        for (; p->next;p=p->next){
            q = p;
        }
        q->next = p->next;
        p->next = ph->next;
        ph->next = p;
    }
    return head;
}
void show(List* head){
    List *p = head->next;
    if(!p)
        return;
    for (; p;p=p->next){
        printf("%d ", p->data);
    }
}
int main(){
    List *head = (List *)malloc(sizeof(List));
    List *p1=head, *p2=NULL;
    Elemtype x;
    scanf("%d", &x);
    while (x)
    {
        p2 = (List *)malloc(sizeof(List));
        p2->next = NULL;
        p2->data = x;
        p1->next = p2;
        p1 = p1->next;
        scanf("%d", &x);
    }
    show(head);
    head=Tranvers(head);
    printf("\n");
    show(head);
}