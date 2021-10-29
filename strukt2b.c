#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct _Person{
    char name[20];
    char surname[30];
    int birthYear;
    struct _Person* next;
}person;

int PrependList(person* head);
int AppendList(person* head);
person* CreatePerson();
int insertAfter(person* position, person* newPerson);
person* FindLast(person* head);
int freeList(person* head);
int PrintList(person* head);
int PrintMember(person* head, int num);
person* FindViaSurname(person* head);
int FindViaSurnameAndPrint(person* head);
int DeleteMember(person* head);
void clearScreen();
person* FindViaSurname(person* head);

int main(int argc, char** argv)
{
    int check=0;
    char znak[10];
    person head={.name={0}, .surname={0}, .birthYear=0, .next=NULL};

    while(1){
        printf("\n-------------------------------------------------"
             "\nTo prepend:\t\t\t-\n"
             "To append:\t\t\t+\n"
             "To exit:\t\t\tSTOP\n"
             "To print the whole list:\tPRINT\n"
             "To find a member by surname:\tFIND\n"
             "To delete by surname:\t\tDELETE\n");
        printf("-------------------------------------------------\n");
        printf("User input:\t");
        scanf(" %s", znak);

        if(strcmp(znak, "-")==0){
            check=PrependList(&head);
            if(check==-1){
                freeList(&head);
                return -1;
            }
        }
        else if (strcmp(znak, "+")==0){
            check=AppendList(&head);
            if(check==-1){
                freeList(&head);
                return -1;
            }
        }
        else if(strcmp(znak, "stop")==0 || strcmp(znak, "STOP")==0){
                return freeList(&head);

        }
        else if(strcmp(znak, "print")==0 || strcmp(znak, "PRINT")==0) {
            check=PrintList(&head);
            if(check!=0){
                continue;
            }

        }
        else if(strcmp(znak, "find")==0 || strcmp(znak, "FIND")==0) {
            check=FindViaSurnameAndPrint(&head); //ovdje mislim da bi bilo logicnije da FindViaSurname vraca void
            if(check!=0){
                continue;
            }
        }
        else if(strcmp(znak, "delete")==0 || strcmp(znak, "DELETE")==0) {
            check=DeleteMember(&head); //ovdje mislim da bi bilo logicnije da DeleteMember vraca void
            if(check!=0){
                continue;
            }
        }
        else{
            clearScreen();
            puts("\nWRONG INPUT! TRY AGAIN...");
        }

    }

    return 0;

}
int DeleteMember(person* head) //deletes a member by surname, returns -1 if FindViaSurname returns -1, if all is good returns 0
{
    person* temp=NULL;
    person* before=head;


    temp=FindViaSurname(head);
    if(temp==NULL){
        return -1;
    }

    //Finding the one before:
    //(before starts from the head and looks for a member before the one that we want to delete)
    while(before->next!=temp){
        before=before->next;
    }

    before->next=temp->next;
    free(temp);

    return 0;

}
person* FindViaSurname(person* head) //returns -1 if the list is empty, or if there is no such surname
{
    person* temp=head;
    person* last=FindLast(head);
    char sur[30]={0};

    if(last==head){
        clearScreen();
        printf("\nList is empty!\n");
        return NULL;
    }

    printf("\nEnter a surname:\t");
    scanf(" %s", sur);


    while((strcmp(temp->surname, sur)!=0)){
        temp=temp->next;
        if((temp==last) && (strcmp(temp->surname, sur)!=0)){
                clearScreen();
                printf("\nNo such surname in this list\n");
                return NULL;
        }
    }
    return temp;
}
int FindViaSurnameAndPrint(person* head) //returns -1 if the list is empty, or if there is no such surname
{
    int check=0;
    int num=0;
    person* temp=head;
    person* last=FindLast(head);
    char sur[30]={0};

    if(last==head){
        clearScreen();
        printf("\nList is empty!\n");
        return -1;
    }

    printf("\nEnter a surname:\t");
    scanf(" %s", sur);


    while((strcmp(temp->surname, sur)!=0)){
        temp=temp->next;
        num++;
        if((temp==last) && (strcmp(temp->surname, sur)!=0)){
            clearScreen();
            printf("\nNo such surname stored in this list\n");
            return -1;
        }
    }

    check=PrintMember(temp, num);
    if(check!=0){
            printf("ERROR");
            return -1;
    }
    return 0;
}
int PrintList(person* head) //prints the whole list, returns -1 if the list is empty
{
    clearScreen();
    int br=0;
    person* temp=head;
    person* last=FindLast(head);

    if(last==head){
        clearScreen();
        printf("\nList is empty!\n");
        return -1;
    }
    printf("\n-------------------------------------------------");
    while(temp->next){
            temp=temp->next;
            printf("\nNum.%d\n"
                   "Name:\t\t%s\n"
                   "Surname:\t%s\n"
                   "Birth year:\t%d\n", br+1, temp->name, temp->surname, temp->birthYear);
            br++;
    }
    printf("-------------------------------------------------\n");
    return 0;
}
int PrintMember(person* member, int num) //prints out a member
{
    clearScreen();
    printf("\n-------------------------------------------------");
    printf("\nNum.%d\n"
            "Name:\t\t%s\n"
            "Surname:\t%s\n"
            "Birth year:\t%d\n", num, member->name, member->surname, member->birthYear);
    printf("-------------------------------------------------\n");
    return 0;
}
int PrependList(person* head)//adds a new member to the end of a list
{
    person* newPerson;

    newPerson=CreatePerson();
    if(newPerson==NULL){
        return -1;
    }
    if(insertAfter(head, newPerson)!=0)
        return -1;

    return 0;
}

int AppendList(person* head) //adds a new member to the beginning of a list
{
    person* newPerson=NULL;
    person* last=NULL;

    newPerson=CreatePerson();
    if(newPerson==NULL){
        return -1;
    }

    last=FindLast(head);
    if(last==NULL){
        return -1;
    }

    if(insertAfter(last, newPerson)!=0){
        return -1;
    }
    return 0;
}
person* FindLast(person* head) // finds returns last node of a linked list
{
    person* temp=head;
    while(temp->next){
        temp=temp->next;
    }
    return temp;
}
person* CreatePerson() //returns (person*) NewPerson, writes an error message and returns NULL if it was unable to access memory
{
    person* NewPerson=NULL;
    NewPerson=(person*)malloc(sizeof(person));
    if(NewPerson==NULL)
    {
        puts("Unable to access memory!\n");
        return NULL;
    }
    printf("Input name, surname and year of birth:\t");
    scanf(" %s %s %d", NewPerson->name, NewPerson->surname, &NewPerson->birthYear);
    return NewPerson;

}
int insertAfter(person* position, person* newPerson)
{
    newPerson->next=position->next;
    position->next=newPerson;
    return 0;
}

int freeList(person* head)
{
    person* temp=NULL;
    head=head->next;
    while (head)
    {
       temp = head;
       head=head->next;
       free(temp);
    }
    return 0;
}
void clearScreen() // source: https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c/36253316
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}
