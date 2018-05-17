#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct studentInformation{      //Student's Basic Information
    int num;
    char name[30];
    char sex[4];
    int room;
    long int phone;
    struct studentInformation *next;
} Basic;

typedef struct gardeInformation{        //Student's Grade Information
    int num;
    char classnum[5];
    char classname[30];
    int credit;
    float daily;
    float experiment;
    float test;
    float Comprehension;
    float truecredit;
    struct gardeInformation *next;
} Grade;

void printmenu()
{
    printf("**********Student Manage System****************");
    printf("\n***********************************************\n");
    printf("                   Menu Items \n");
    printf("***********************************************\n");
    printf("*      1__Data Sort                           *\n");
    printf("*      2__Data Loading                        *\n");
    printf("*      3__Query Students Information          *\n");
    printf("*      4__Edit Students Information           *\n");
    printf("*      0__Exit System                         *\n");
    printf("***********************************************\n");
}
void Editmenu()
{
    printf("-----------------------------------------------\n");
    printf("                   Edit  Sub_Meun\n");
    printf("-----------------------------------------------\n");
    printf("                1__Delect Record\n");
    printf("                2__Return\n");
    printf("-----------------------------------------------\n");
}

void Querymenu()
{
    printf("-----------------------------------------------\n");
    printf("                   Query Sub_Meun\n");
    printf("                1__Query Grades by No\n");
    printf("                2__Query Basic Information by No\n");
    printf("                3__Query Basic Information by Name\n");
    printf("                4__Query Basic Information by Room\n");
    printf("                5__Return\n");
    printf("-----------------------------------------------\n");
}

void Sortmenu()
{
    printf("-----------------------------------------------\n");
    printf("                   Sort Sub_Meun\n");
    printf("                1__Ascending   by Comprehension\n");
    printf("                2__Descending  by Comprehension\n");
    printf("                3__Ascending   by TrueCredits\n");
    printf("                4__Descending  by TrueCredits\n");
    printf("                5__Return\n");
    printf("-----------------------------------------------\n");
}

int judge(char *x,char a[],char b[]){                                         //guarantee input right
    return (strlen(x) != 1 || (strcmp(x, a) > 0) || (strcmp(x, b) < 0));
}

int caculate(Grade*p){
    if(!p)
        return 0;
    if (p->experiment == -1)
    {
        p->Comprehension = (p->daily) * 0.30 + (p->test) * 0.70;
        if (p->Comprehension <= 100 || p->Comprehension >= 90)
            p->truecredit = p->credit * 1.00;
        else if (p->Comprehension < 90 || p->Comprehension >= 80)
            p->truecredit = p->credit * 0.80;
        else if (p->Comprehension < 80 || p->Comprehension >= 70)
            p->truecredit = p->credit * 0.75;
        else if (p->Comprehension < 70 || p->Comprehension >= 60)
            p->truecredit = p->credit * 0.60;
        else if (p->Comprehension < 60)
            p->truecredit = p->credit * 0.00;
    }
    else
    {
        p->Comprehension = (p->daily) * 0.15 + (p->experiment) * 0.15 + (p->test) * 0.70;
        if (p->Comprehension <= 100 || p->Comprehension >= 90)
            p->truecredit = p->credit * 1.00;
        else if (p->Comprehension < 90 || p->Comprehension >= 80)
            p->truecredit = p->credit * 0.80;
        else if (p->Comprehension < 80 || p->Comprehension >= 70)
            p->truecredit = p->credit * 0.75;
        else if (p->Comprehension < 70 || p->Comprehension >= 60)
            p->truecredit = p->credit * 0.60;
        else if (p->Comprehension < 60)
            p->truecredit = p->credit * 0.00;
    }
    return 1;
}

int DataLoding(char *file,Grade* head){             //DataLoading
    int ret;
	if(!head)   return 0;
    FILE *FP = NULL;
    Grade *p = NULL;
    Grade *point = (Grade *)malloc(sizeof(Grade));
    point = head;
    FP = fopen(file, "r+");
    if(!FP){
        printf("Open File:'%s' fail!\n", file);
        return 0;
    }
    while(!(feof(FP))){
        Grade *Node = (Grade *)malloc(sizeof(Grade));
        ret=fscanf(FP, "%d%s%s%d%f%f%f", &Node->num, Node->classnum, Node->classname, &Node->credit, &Node->daily, &Node->experiment, &Node->test);
        if(ret!=EOF&&ret!=0){
        point->next = Node;
        Node->next = NULL;
        point = Node;
        }else{
            return 0;
        }
    }
    p = head->next;
    if(point==head){
        printf("There is no data in file:'%s'\n", file);
    }else{
        printf("Below is the data in the file'%s':\n", file);
        while (p != NULL)
        {
            caculate(p);
            printf("%d  %-4s %4s %-4d %-.2f %-.2f %-.2f %-.2f %-.2f\n", p->num, p->classnum, p->classname, p->credit, p->daily, p->experiment, p->test,p->Comprehension,p->truecredit);
            p = p->next;
        }
    }
    fclose(FP);
    return 1;
}

Grade* QueryGrade(char* file,Grade* head){              //Take Grade Information to memory
    int ret;
	if(!head)   return NULL;
    FILE *FP = NULL;
    Grade *point = (Grade *)malloc(sizeof(Grade));
    point = head;
    FP = fopen(file, "r+");
    if(!FP){
        printf("Open File:'%s' fail!\n", file);
        return head;
    }
    while (!(feof(FP)))
    {
        Grade *Node = (Grade *)malloc(sizeof(Grade));
        ret=fscanf(FP, "%d%s%s%d%f%f%f", &Node->num, Node->classnum, Node->classname, &Node->credit, &Node->daily, &Node->experiment, &Node->test);
        if(ret!=EOF&&ret!=0){
        point->next = Node;
        Node->next = NULL;
        point = Node;
        }else{
            return NULL;
        }
    }
    if (point == head)
    {
        printf("There is no data in file:'%s'\n", file);
        fclose(FP);
        return NULL;
    }else{
        fclose(FP);
        return head;
    }
}

Basic* QueryBasic(char* file,Basic* head){              //Take Basic Information to memory
    int ret;
	if(!head)   return NULL;
    FILE *FP = NULL;
    Basic *point = (Basic *)malloc(sizeof(Basic));
    point = head;
    FP = fopen(file, "r+");
    if(!FP){
        printf("Open File:'%s' fail!\n", file);
        return head;
    }
    while (!(feof(FP)))
    {
        Basic *Node = (Basic *)malloc(sizeof(Basic));
        ret=fscanf(FP, "%d%s%s%d%ld", &Node->num, Node->name, Node->sex, &Node->room, &Node->phone);
        if(ret!=EOF&&ret!=0){
        point->next = Node;
        Node->next = NULL;
        point = Node;
        }else{
            return NULL;
        }
    }
    if (point == head)
    {
        printf("There is no data in file:'%s'\n", file);
        fclose(FP);
        return NULL;
    }
    else
    {
        fclose(FP);
        return head;
    }
}

Grade* FindGrade(Grade*head,int num){                       //Find the Grade Information by num
    if(!head)   return NULL;
    Grade *pointer = head->next;
    if(!pointer)   return NULL;
    Grade *NewHead = (Grade *)malloc(sizeof(Grade));
    NewHead->next = NULL;
    Grade *Gpointer = NewHead;
    do
    {
        if (pointer->num != num)
        {
            pointer = pointer->next;
            continue;
        }
        else
        {
            Grade *Node = (Grade *)malloc(sizeof(Grade));
            Node->num = pointer->num;
            strcpy(Node->classnum, pointer->classnum);
            strcpy(Node->classname, pointer->classname);
            Node->credit = pointer->credit;
            Node->daily = pointer->daily;
            Node->experiment = pointer->experiment;
            Node->test = pointer->test;
            caculate(Node);
            Gpointer->next = Node;
            Node->next = NULL;
            Gpointer = Node;
            pointer = pointer->next;
        }
    } while (pointer);
    return NewHead;
}

Basic* FindBasicRoom(Basic*head,int room){              //Find the Basic Information by Room
    if(!head)   return NULL;
    Basic *pointer = head->next;
    if(!pointer)    return NULL;
    Basic *NewHead = (Basic *)malloc(sizeof(Basic));
    NewHead->next = NULL;
    Basic *Bpointer = NewHead;
    do
    {
    if (pointer->room!= room)
    {
        pointer = pointer->next;
        continue;
    }
    else
    {
        Basic *Node = (Basic *)malloc(sizeof(Basic));
        strcpy(Node->name, pointer->name);
        strcpy(Node->sex, pointer->sex);
        Node->num = pointer->num;
        Node->phone = pointer->phone;
        Node->room = pointer->room;
        Bpointer->next = Node;
        Node->next = NULL;
        Bpointer = Node;
        pointer = pointer->next;
    }
}while (pointer);

return NewHead;
}

Basic* FindBasicName(Basic*head,char name[]){           //Find the Basic Information by name
    if(!head)   return NULL;
    Basic *pointer = head->next;
    if(!pointer)    return NULL;
    Basic *NewHead = (Basic *)malloc(sizeof(Basic));
    NewHead->next = NULL;
    Basic *Bpointer = NewHead;
    do{
        if(strcmp(pointer->name,name)){
            pointer=pointer->next;
            continue;
        }else{
            Basic *Node = (Basic *)malloc(sizeof(Basic));
            strcpy(Node->name, pointer->name);
            strcpy(Node->sex, pointer->sex);
            Node->num = pointer->num;
            Node->phone = pointer->phone;
            Node->room = pointer->room;
            Bpointer->next = Node;
            Node->next = NULL;
            Bpointer = Node;
            pointer = pointer->next;
        }
    } while (pointer);
    return NewHead;
}

Basic* FindBasic(Basic*head,int num){           //Find the Basic Information by num
    if(!head)	return NULL;
	Basic *pointer = head->next;
    if(!pointer)    return NULL;
    Basic *NewHead = (Basic *)malloc(sizeof(Basic));
    NewHead->next = NULL;
    Basic *Bpointer=NewHead;
    do
    {
        if(pointer->num != num){
            pointer = pointer->next;
            continue;
        }else{
            Basic *Node = (Basic *)malloc(sizeof(Basic));
            strcpy(Node->name, pointer->name);
            strcpy(Node->sex, pointer->sex);
            Node->num = pointer->num;
            Node->phone = pointer->phone;
            Node->room = pointer->room;
            Bpointer->next = Node;
            Node->next = NULL;
            Bpointer = Node;
            pointer = pointer->next;
        }
    } while (pointer);
    return NewHead;
}

void copy(Grade *Temp,Grade* Pointer){                  //Copy Pointer's Information to Temp's Information
    Temp->num = Pointer->num;
    strcpy(Temp->classnum, Pointer->classnum);
    strcpy(Temp->classname, Pointer->classname);
    Temp->credit = Pointer->credit;
    Temp->daily = Pointer->daily;
    Temp->experiment = Pointer->experiment;
    Temp->test = Pointer->test;
    Temp->Comprehension = Pointer->Comprehension;
    Temp->truecredit = Pointer->truecredit;
}

Grade*DescendbyTrueCredits(Grade* SortHead){           //Descending by True Credits
    if(!SortHead)   return NULL;
    if(!SortHead->next)     return NULL;
    Grade *CalPointer = SortHead->next;
    Grade *SortPointer = SortHead->next;
    Grade *SortPointer2 = NULL;
    Grade *TempNode = (Grade *)malloc(sizeof(Grade));
    int size = 0, i = 0, j = 0, k = 0;
    if (!CalPointer)
    { //No data
        return NULL;
    }
    while (CalPointer)
    {
        caculate(CalPointer);
        CalPointer = CalPointer->next;
        size++;
    }
    Grade Temp[size];
    for (i = 0; i < size; i++)
    {
        copy(&Temp[i], SortPointer);
        SortPointer = SortPointer->next;
    }
    for (j = 0; j < size - 1; j++)
    {
        for (k = 0; k < size - 1 - j; k++)
        {
            if ((Temp[k].truecredit) < (Temp[k + 1].truecredit))
            {
                copy(TempNode, &Temp[k + 1]);
                copy(&Temp[k + 1], &Temp[k]);
                copy(&Temp[k], TempNode);
            }
        }
    }
    SortPointer2 = SortHead->next;
    for (i = 0; i < size; i++)
    {
        copy(SortPointer2, &Temp[i]);
        SortPointer2 = SortPointer2->next;
    }

    return SortHead;
}

Grade*DescendbyComprehension(Grade* SortHead){              //Descending by Comprehension
    if(!SortHead)   return NULL;
    if(!SortHead->next)     return NULL;
    Grade *CalPointer = SortHead->next;
    Grade *SortPointer = SortHead->next;
    Grade *SortPointer2 = NULL;
    Grade *TempNode = (Grade *)malloc(sizeof(Grade));
    int size = 0, i = 0, j = 0, k = 0;
    if (!CalPointer)
    { //No data
        return NULL;
    }
    while (CalPointer)
    {
        caculate(CalPointer);
        CalPointer = CalPointer->next;
        size++;
    }
    Grade Temp[size];
    for (i = 0; i < size; i++)
    {
        copy(&Temp[i], SortPointer);
        SortPointer = SortPointer->next;
    }
    for (j = 0; j < size - 1; j++)
    {
        for (k = 0; k < size - 1 - j; k++)
        {
            if ((Temp[k].Comprehension) < (Temp[k + 1].Comprehension))
            {
                copy(TempNode, &Temp[k + 1]);
                copy(&Temp[k + 1], &Temp[k]);
                copy(&Temp[k], TempNode);
            }
        }
    }
    SortPointer2 = SortHead->next;
    for (i = 0; i < size; i++)
    {
        copy(SortPointer2, &Temp[i]);
        SortPointer2 = SortPointer2->next;
    }

    return SortHead;
}

Grade*AscendbyComprehension(Grade* SortHead){           //Ascendint by Comprehension
    if(!SortHead)   return NULL;
    if(!SortHead->next)     return NULL;
    Grade *CalPointer = SortHead->next;
    Grade *SortPointer = SortHead->next;
    Grade *SortPointer2=NULL;
    Grade *TempNode = (Grade*)malloc(sizeof(Grade));
    int size = 0,i=0,j=0,k=0;
    if(!CalPointer){        //No data
        return NULL;
    }
    while (CalPointer)
    {
        caculate(CalPointer);
        CalPointer = CalPointer->next;
        size++;
    }
    Grade Temp[size];
    for (i = 0; i < size;i++){
        copy(&Temp[i], SortPointer);
        SortPointer = SortPointer->next;
    }
    for (j = 0; j < size -1;j++){
        for (k = 0; k < size -1 - j;k++){
            if((Temp[k].Comprehension)>(Temp[k+1].Comprehension)){
                copy(TempNode, &Temp[k+1]);
                copy(&Temp[k + 1], &Temp[k]);
                copy(&Temp[k], TempNode);
            }
        }
    }
    SortPointer2 = SortHead->next;
    for (i = 0; i < size;i++){
        copy(SortPointer2, &Temp[i]);
        SortPointer2 = SortPointer2->next;
    }
        return SortHead;
}

Grade* AscendbyTrueCredits(Grade* SortHead){            //Ascending by True Credits
    if(!SortHead)   return NULL;
    if(!SortHead->next)     return NULL;
    Grade *CalPointer = SortHead->next;
    Grade *SortPointer = SortHead->next;
    Grade *SortPointer2 = NULL;
    Grade *TempNode = (Grade *)malloc(sizeof(Grade));
    int size = 0, i = 0, j = 0, k = 0;
    if (!CalPointer)
    { //No data
        return NULL;
    }
    while (CalPointer)
    {
        caculate(CalPointer);
        CalPointer = CalPointer->next;
        size++;
    }
    Grade Temp[size];
    for (i = 0; i < size; i++)
    {
        copy(&Temp[i], SortPointer);
        SortPointer = SortPointer->next;
    }
    for (j = 0; j < size - 1; j++)
    {
        for (k = 0; k < size - 1 - j; k++)
        {
            if ((Temp[k].truecredit) > (Temp[k + 1].truecredit))
            {
                copy(TempNode, &Temp[k + 1]);
                copy(&Temp[k + 1], &Temp[k]);
                copy(&Temp[k], TempNode);
            }
        }
    }
    SortPointer2 = SortHead->next;
    for (i = 0; i < size; i++)
    {
        copy(SortPointer2, &Temp[i]);
        SortPointer2 = SortPointer2->next;
    }
    return SortHead;
}

int delete ()                           //Delete one Information
{   
    int del_student(FILE * f, FILE * fp);
    FILE *f, *fp;
    int ret=0;
    f = fopen("grade.txt", "r");
    fp = fopen("basic.txt", "r");
    if (fp == NULL || f == NULL)
    {
        return 0;
    }
    ret=del_student(f, fp);
    if(ret==-1){
        return -1;
    }else if(ret==0)	return 0;
    return 1;
}

int del_student(FILE *f, FILE *fp)       //Delete one Information
{	int ret=0;
    int Num=0;
    FILE *p, *q;
    Basic *head_1, *point_1;
    Grade *head_2, *point_2;
    head_1 = (Basic *)malloc(sizeof(Basic));
    head_2 = (Grade *)malloc(sizeof(Grade));
    head_1->next = NULL;
    head_2->next = NULL;
    head_1 = QueryBasic("basic.txt", head_1);
    head_2 = QueryGrade("grade.txt", head_2);
    if(head_1&&head_2){
    point_1 = head_1->next;
    point_2 = head_2->next;
flag5:	printf("\nPlease input the student's number you want to Delete:\n");
    ret=scanf("%d",&Num);
    if(!ret){
    	printf("Please check your input!\n");
    	fflush(stdin);
    	goto flag5;
	}
    if(!point_1&&!point_2){
    	printf("Open file error! Please check your path!\n");
        return 0;
    }else{
    if(point_1){
    p = fopen("c.txt", "a+");
    while (point_1)
    {
        if (point_1->num != Num)
        {
            if (point_1->next)
                fprintf(p, "%d %s %s %d %ld\n", point_1->num, point_1->name, point_1->sex, point_1->room, point_1->phone);
            else
                fprintf(p, "%d %s %s %d %ld", point_1->num, point_1->name, point_1->sex, point_1->room, point_1->phone);
        }
        point_1 = point_1->next;
    }
    fclose(fp);
    fclose(p);
    remove("basic.txt");
    rename("c.txt", "basic.txt");
    }
	if(point_2){
    q = fopen("d.txt", "a+");
    while (point_2)
    {
        if (point_2->num != Num)
        {
            if (point_2->next)
                fprintf(q, "%d %s %s %d %f %f %f\n", point_2->num, point_2->classnum, point_2->classname, point_2->credit, point_2->daily, point_2->experiment, point_2->test);
            else
                fprintf(q, "%d %s %s %d %f %f %f", point_2->num, point_2->classnum, point_2->classname, point_2->credit, point_2->daily, point_2->experiment, point_2->test);
        }
        point_2 = point_2->next;
    }
    fclose(f);
    fclose(q);
    remove("grade.txt");
    rename("d.txt", "grade.txt");
    }
   }
}else{
	if(!head_1&&!head_2){
		printf("There is no data in the file!\n");
		return -1;
	}else{
	if(head_1){
		point_1 = head_1->next;
		if(!point_1){
			printf("Open file error!\n");
			return 0;
		}
		p = fopen("c.txt", "a+");
    while (point_1)
    {
        if (point_1->num != Num)
        {
            if (point_1->next)
                fprintf(p, "%d %s %s %d %ld\n", point_1->num, point_1->name, point_1->sex, point_1->room, point_1->phone);
            else
                fprintf(p, "%d %s %s %d %ld", point_1->num, point_1->name, point_1->sex, point_1->room, point_1->phone);
        }
        point_1 = point_1->next;
    }
    fclose(fp);
    fclose(p);
    remove("basic.txt");
    rename("c.txt", "basic.txt");
	}	
	if(head_2){
		point_2 = head_2->next;
		if(!point_2){
			printf("Open file error!\n");
			return 0;
		}
		q = fopen("d.txt", "a+");
    while (point_2)
    {
        if (point_2->num != Num)
        {
            if (point_2->next)
                fprintf(q, "%d %s %s %d %f %f %f\n", point_2->num, point_2->classnum, point_2->classname, point_2->credit, point_2->daily, point_2->experiment, point_2->test);
            else
                fprintf(q, "%d %s %s %d %f %f %f", point_2->num, point_2->classnum, point_2->classname, point_2->credit, point_2->daily, point_2->experiment, point_2->test);
        }
        point_2 = point_2->next;
    }
    fclose(f);
    fclose(q);
    remove("grade.txt");
    rename("d.txt", "grade.txt");	
	}	
		}
			}
 return 1;
}

int main(){
    char X[3],X2[3],X3[3],x,x2,x3;
    char file[30],file2[30],Basicfile[30],SearchName[30],Sortfile[30];
    int Querynum,cnt=0,SearchRoom,ret,ret1=0,ret2=0,ret3=0;
    float truecredit=0;
    Grade *head = (Grade *)malloc(sizeof(Grade));
    head->next = NULL;
    Grade *head2 = (Grade *)malloc(sizeof(Grade));
    head2->next = NULL;
    Grade *SortHead = (Grade *)malloc(sizeof(Grade));
    SortHead->next = NULL;
    Basic *BasicHead = (Basic *)malloc(sizeof(Basic));
    BasicHead->next = NULL;
    Basic *BasicHead2 = (Basic *)malloc(sizeof(Basic));
    BasicHead2->next = NULL;
    Basic *BasicHead3 = (Basic *)malloc(sizeof(Basic));
    BasicHead3->next = NULL;
    Basic *BasicHead4 = (Basic *)malloc(sizeof(Basic));
    BasicHead4->next = NULL;
    Grade *pointer = NULL;
    Grade *pointer2 = NULL;
    Grade *AscendSort = NULL;
    Grade *DescendSort = NULL;
    Basic *Bpointer = NULL;
    Basic *BasicPointer = NULL;
    Basic *BasicPointer2 = NULL;
    Basic *BasicPointer3 = NULL;
    Basic *BasicPointer4 = NULL;
flag1:printmenu();
    printf("Please Select an Option(0-4):");
    fflush(stdin);
    scanf("%s", X);
    while (judge(X,"4","0"))
    {
        printf("Input Error! Please Input Again!\n");
        fflush(stdin);
        scanf("%s", X);
    }
    x = X[0];
    switch(x){
        case '1'://Sort
flag3:  Sortmenu();
        printf("Please Select an Option(1-5):");
        fflush(stdin);
        scanf("%s", X3);
        while (judge(X3, "5", "1"))
        {
            printf("Input Error! Please Input Again!\n");
            fflush(stdin);
            scanf("%s", X3);
        }
        x3 = X3[0];
        switch(x3){
        case '1':       //Ascending  by Comprehension
        printf("Please input the file path!\n");
        fflush(stdin);
        scanf("%s", Sortfile);
        SortHead = QueryGrade(Sortfile, SortHead);
        if(!SortHead){
            printf("There is No data in the file\n");
            goto flag3;
        }
        SortHead=AscendbyComprehension(SortHead);
        if(!SortHead){
            printf("There is No data in the file\n");
            goto flag3;
        }
       AscendSort = SortHead->next;
       while (AscendSort)
       {
           printf("%d  %-4s %4s %-4d %-.2f %-.2f %-.2f %-.2f %-.2f\n", AscendSort->num, AscendSort->classnum, AscendSort->classname, AscendSort->credit, AscendSort->daily, AscendSort->experiment, AscendSort->test, AscendSort->Comprehension, AscendSort->truecredit);
           AscendSort = AscendSort->next;
       }
       goto flag3;
       break;

        case '2':
        printf("Please input the file path!\n");
        fflush(stdin);
        scanf("%s", Sortfile);
        SortHead = QueryGrade(Sortfile, SortHead);
        if(!SortHead){
            printf("There is No data in the file\n");
            goto flag3;
        }
        if (!SortHead)
        {
            printf("There is No data in the file\n");
            goto flag3;
        }
        SortHead = DescendbyComprehension(SortHead);
        if(!SortHead){
            printf("There is No data in the file\n");
            goto flag3;
        }
        DescendSort = SortHead->next;
        while (DescendSort)
        {
            printf("%d  %-4s %4s %-4d %-.2f %-.2f %-.2f %-.2f %-.2f\n", DescendSort->num, DescendSort->classnum, DescendSort->classname, DescendSort->credit, DescendSort->daily, DescendSort->experiment, DescendSort->test, DescendSort->Comprehension, DescendSort->truecredit);
            DescendSort = DescendSort->next;
        }
        goto flag3;
        break;

        case'3':
        printf("Please input the file path!\n");
        fflush(stdin);
        scanf("%s", Sortfile);
        SortHead = QueryGrade(Sortfile, SortHead);
        if(!SortHead){
            printf("There is No data in the file\n");
            goto flag3;
        }
        SortHead = AscendbyTrueCredits(SortHead);
        if(!SortHead){
            printf("There is No data in the file\n");
            goto flag3;
        }
        AscendSort = SortHead->next;
        while (AscendSort)
        {
            printf("%d  %-4s %4s %-4d %-.2f %-.2f %-.2f %-.2f %-.2f\n", AscendSort->num, AscendSort->classnum, AscendSort->classname, AscendSort->credit, AscendSort->daily, AscendSort->experiment, AscendSort->test, AscendSort->Comprehension, AscendSort->truecredit);
            AscendSort = AscendSort->next;
        }
        goto flag3;
        break;
        case '4':
        printf("Please input the file path!\n");
        fflush(stdin);
        scanf("%s", Sortfile);
        SortHead = QueryGrade(Sortfile, SortHead);
        if(!SortHead){
            printf("There is No data in the file\n");
            goto flag3;
        }
        SortHead = DescendbyTrueCredits(SortHead);
        if(!SortHead){
            printf("There is No data in the file\n");
            goto flag3;
        }
        DescendSort = SortHead->next;
        while (DescendSort)
        {
            printf("%d  %-4s %4s %-4d %-.2f %-.2f %-.2f %-.2f %-.2f\n", DescendSort->num, DescendSort->classnum, DescendSort->classname, DescendSort->credit, DescendSort->daily, DescendSort->experiment, DescendSort->test, DescendSort->Comprehension, DescendSort->truecredit);
            DescendSort = DescendSort->next;
        }
        goto flag3;
        break;
        case '5':
        goto flag1;
        break;
        }
        break;

        case '2'://Data Loading
        printf("Please input the file path!\n");
        fflush(stdin);
        scanf("%s", file);
        if(!DataLoding(file,head)){
            printf("There is no data in the file!\n");
            goto flag1;
        }else{
        	goto flag1;
		}
        break;

        case '3'://Query
flag2:  Querymenu();
        printf("Please Select an Option(1-5):");
        fflush(stdin);
        scanf("%s", X2);
        while (judge(X2,"5","1"))
        {
            printf("Input Error! Please Input Again!\n");
            fflush(stdin);
            scanf("%s", X2);
        }
        x2 = X2[0];
        switch(x2){
            case '1':
            //search by num(Grade Information)
flag6:      printf("Please input the Number you want to search:");
            ret1=scanf("%d", &Querynum);
            while(!ret1){
            	printf("Please check you input!\n");
            	fflush(stdin);
            	goto flag6;
			}
            printf("Please input the file path!\n");
            fflush(stdin);
            scanf("%s", file2);
            strcpy(Basicfile, "basic.txt");
            head2=QueryGrade(file2,head2);
            BasicHead = QueryBasic(Basicfile, BasicHead);
            if(!head2||!BasicHead){
                printf("There is No data in the file\n");
                goto flag2;
            }
            pointer = FindGrade(head2, Querynum);
            BasicPointer=FindBasic(BasicHead, Querynum);
            if(!pointer||!BasicPointer){
                printf("Please check the File\n");
                goto flag2;
            }
            if(!(pointer->next)||!(BasicPointer->next)){
                printf("There is no such num in file\n");
                goto flag2;
            }else{
                printf("Student Num:%d  Student Name:%s\n", BasicPointer->next->num, BasicPointer->next->name);
                pointer2 = pointer->next;
                while(pointer2){
                    printf("ClassNum:%s  ClassName:%s  Comprehension:%.2f  TrueCredits:%.2f\n", pointer2->classnum, pointer2->classname, pointer2->Comprehension, pointer2->truecredit);
                    cnt++;
                    truecredit += pointer2->truecredit;
                    pointer2 = pointer2->next;
                }
                printf("Total Class:%d      Total Credits:%.2f\n", cnt, truecredit);
            }
              goto flag2;
              break;

            case'2':    //search by num(Basic Information)
flag7:          printf("Please input the Number you want to search:");
                ret2=scanf("%d", &Querynum);
                if(!ret2){
                	printf("Please check your input!\n");
                	fflush(stdin);
                	goto flag7;
				}
				strcpy(Basicfile, "basic.txt");
                BasicHead2=QueryBasic(Basicfile, BasicHead2);
                BasicPointer2 = FindBasic(BasicHead2, Querynum);
                if(!BasicHead2||!BasicPointer2){
                    printf("There is No data in the file\n");
                    goto flag2;
                }else{
                if(!(BasicPointer2->next)){
                    printf("There is no such num in file\n");
                    goto flag2;
                }else{
                    printf("Student's Num:%d     Student's Name:%s   Sex:%s  Room:%d   PhoneNumber:%ld\n", BasicPointer2->next->num, BasicPointer2->next->name, BasicPointer2->next->sex, BasicPointer2->next->room, BasicPointer2->next->phone);
                }
                    }
                goto flag2;
                break;

                case'3':    //search by name (Basic Information)
                printf("Please input Student's Name you want to search:");
                scanf("%s", SearchName);
                strcpy(Basicfile, "basic.txt");
                BasicHead3 = QueryBasic(Basicfile, BasicHead3);
                BasicPointer3 = FindBasicName(BasicHead3, SearchName);
                if (!(BasicHead3))
                {
                    printf("There is No data in the file\n");
                    goto flag2;
                }
                else
                {
                    if (!(BasicPointer3->next))
                    {
                        printf("There is no such Name in file\n");
                        goto flag2;
                    }
                    else
                    {
                        printf("Student's Num:%d     Student's Name:%s   Sex:%s  Room:%d   PhoneNumber:%ld\n", BasicPointer3->next->num, BasicPointer3->next->name, BasicPointer3->next->sex, BasicPointer3->next->room, BasicPointer3->next->phone);
                    }
                }
                goto flag2;
                break;
                case '4':       //search by room (Basic Information)
flag8:              printf("Please input The Room you want to search:");
                    ret3=scanf("%d", &SearchRoom);
                    if(!ret3){
                	printf("Please check your input!\n");
                	fflush(stdin);
                	goto flag8;
				}
                    strcpy(Basicfile, "basic.txt");
                    BasicHead4 = QueryBasic(Basicfile, BasicHead4);
                    BasicPointer4 = FindBasicRoom(BasicHead4, SearchRoom);
                    if(!BasicPointer4){
                        printf("There is no data in the file\n");
                        goto flag2;
                    }
                    Bpointer = BasicPointer4->next;
                    if(!Bpointer){
                        printf("There is no such Room in file\n");
                        goto flag2;
                    }else{
                        while (Bpointer)
                        {
                            printf("Student's Num:%d     Student's Name:%s   Sex:%s  Room:%d   PhoneNumber:%ld\n", Bpointer->num, Bpointer->name, Bpointer->sex, Bpointer->room, Bpointer->phone);
                            Bpointer = Bpointer->next;
                        }
                    }
                    goto flag2;
                    break;
                    case '5':
                    goto flag1;
                    break;
         }
        break;

        case '4'://Delete Information
flag4:  Editmenu();
    printf("Please Select an Option(1-2):");
    fflush(stdin);
    scanf("%s", X2);
    while (judge(X2, "2", "1"))
    {
        printf("Input Error! Please Input Again!\n");
        fflush(stdin);
        scanf("%s", X2);
    }
    x2 = X2[0];
    switch(x2){
        case '1':
        ret=delete();
        if(ret==0){
        	printf("No data in the file!\n");
            goto flag4;
        }else if(ret==-1){
            printf("There is no data in the file!\n");
            goto flag4;
        }else if(ret==1){
            printf("Delete Done!\n");
            goto flag4;
        }
        break;

        case '2':
        goto flag1;
        break;
    }
        case '0':
        printf("Thanks to use!\n");
        exit(1);
    }
}
