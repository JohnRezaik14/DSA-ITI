#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables
struct Student
{
    char name[20];
    int id;
};

// functions for stack
int push();
struct Student pop();
void printStack();
void printStudent(struct Student);
// Global Variables for stack
struct Node *pbase;
struct Node *ptop;
struct Node
{
    struct Student st;
    struct Node *pprev;
};

// functions for queue
int EnQueue();
struct Student DeQueue();
void printQueue();
// array for students queue
struct Student *arr[10];
int LOQ = -1; // last element in queue array
// and -1 means no data added yet

// continue fns function
void continueFun()
{
    printf("\nPress Enter to continue...\n");
    getchar();
    getchar();
    system("cls");
}

int main()
{
    int choice = -1, subChoice = -1;
    while (1)
    {
        system("cls");
        printf("\n--lab-2-Menu--\n\n");
        printf("1: Use Stack\n");
        printf("2: Use Queue\n");
        printf("3: Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // use Stack
            system("cls");
            printf("You chose to use Stack.\n");
            while (1)
            {
                system("cls");
                printf("1: Push\n");
                printf("2: Pop\n");
                printf("3: print Stack\n");
                printf("4: Exit\n");
                printf("\nEnter your choice: ");
                scanf("%d", &subChoice);
                switch (subChoice)
                {
                case 1:
                    if (push())
                    {
                        printf("the Student is pushed to the stack\n");
                    }
                    continueFun();
                    break;
                case 2:
                    struct Student stu;
                    stu = pop();

                    printf("The student %s with id %d popped from the stack\n", stu.name, stu.id);
                    continueFun();
                    break;
                case 3:
                    printStack();
                    continueFun();
                    break;
                case 4:
                    exit(0);
                default:
                    printf("Invalid choice! Please try again.\n");
                    continueFun();
                }
            }

            break;
        case 2: // insert Node
            system("cls");
            printf("You chose to Queue.\n");
            while (1)
            {

                printf("1: EnQueue\n");
                printf("2: DeQueue\n");
                printf("3: print Queue\n");
                printf("4: Exit\n");
                printf("\nEnter your choice: ");
                scanf("%d", &subChoice);
                switch (subChoice)
                {
                case 1:
                    if (EnQueue())
                    {
                        printf("the Student is added to the queue\n");
                    }
                    else
                    {
                        printf("enQueue failed or reached the limit\n");
                    }
                    continueFun();
                    break;
                case 2:
                    struct Student st;
                    st = DeQueue();
                    if (st.id != -1)
                    {
                        printf("the student %s with id %d \nis removed from the queue \n", st.name, st.id);
                    }
                    else
                    {
                        printf("there is no student to deQueue\n");
                    }
                    continueFun();
                    break;
                case 3:
                    printQueue();
                    continueFun();
                    break;
                case 4:
                    exit(0);
                default:
                    printf("Invalid choice! Please try again.\n");
                    continueFun();
                }
            }
            break;
        case 3:
            printf("Exiting the program. Goodbye!\n");
            exit(0); // Exit the program
        default:
            printf("Invalid choice! Please try again.\n");
            continueFun();
        }
    }

    return 0;
}

int push()
{
    system("cls");
    int retval = 0;
    struct Node *ptr = NULL;
    ptr = (struct Node *)malloc(sizeof(struct Node));
    if (ptr)
    {
        retval = 1;
        ptr->st.id = -1;
        strcpy(ptr->st.name, "");

        printf("Enter Your ID \n");
        scanf("%d", &(ptr->st.id));

        printf("Enter Your Name\n");
        scanf("%s", ptr->st.name);

        if (!pbase)
        {
            ptr->pprev = NULL;
            pbase = ptop = ptr;
        }
        else
        {
            ptr->pprev = ptop;
            ptop = ptr;
        }
    }

    return retval;
}

struct Student pop()
{
    struct Student stu = {"", -1};
    struct Node *ptr;
    ptr = ptop;
    if (ptr != NULL)
    {
        stu = ptop->st;
        if (ptop->pprev != NULL) // hasn't reached the base yet that has pprev with Null
        {
            ptop = ptop->pprev;
        }
        else
        {
            ptop = NULL;
        }

        free(ptr);
    }
    return stu;
}

void printStack()
{
    struct Node *ptr;
    if (ptop)
    {
        ptr = ptop;
        for (; ptr != pbase; ptr = ptr->pprev)
        {
            printf("The student %s with id : %d\n", ptr->st.name, ptr->st.id);
        }
        // for the student in pbase
        printf("The student %s with id : %d\n", ptr->st.name, ptr->st.id);
    }
    else
    {
        printf("The stack is empty\n");
    }
}

// Queue Implemntation

int EnQueue()
{
    system("cls");
    int added = 0;
    struct Student *stu; // creat student to add to array
    if (LOQ < 9)
    {
        stu = (struct Student *)malloc(sizeof(struct Student));
        if (stu)
        {
            added = 1;
            LOQ++;
            arr[LOQ] = stu;
            printf("Enter Your ID \n");
            scanf("%d", &(stu->id));

            printf("Enter Your Name\n");
            scanf("%s", stu->name);
        }
    }
    return added;
}
struct Student DeQueue()
{
    system("cls");
    struct Student *stu, *arr2[10];
    stu = arr[0];
    if (stu)
    {
        int i, j;
        for (i = 0, j = 1; j <= LOQ; i++, j++)
        {
            arr2[i] = arr[j];
        }
        LOQ--;
        for (i = 0; i <= LOQ; i++)
        {
            arr[i] = arr2[i];
        }
    }
    else
    {
        stu->id = -1;
    }
    return *stu;
}
void printQueue()
{
    system("cls");
    if (LOQ >= 0)
    {
        for (int i = 0; i <= LOQ; i++)
        {
            printf("Student %s with id : %d \n", arr[i]->name, arr[i]->id);
        }
    }
    else
    {
        printf("The Queue is empty\n");
    }
}