#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// defining structs
struct student
{
    char name[20];
    int id;
};

struct node
{
    struct student st;
    struct node *pprev;
    struct node *pnext;
};
// global variables
struct node *phead;
struct node *ptail;
int count; // this var to know how nodes i have

// functions
struct student fillStudent();
struct node *createNode(struct student stu);

int addNode();
int insertNode();

struct student searchIDStu(int id);
struct node *searchIDPtr(int id);
struct student searchNameStu(char name[20]);
struct node *searchNamePtr(char name[20]);
struct student ReturnStudent(struct node *);

void deleteID(int id);
void deleteName(char name[20]);

void freeList();

void printStudent(struct student);
void printList();

int main()
{
    int choice;
    int id = 0;
    char name[20] = {0};
    int retval;
    struct student stu;
    stu.id = id;
    while (1)
    {
        system("cls");
        printf("\n--Student-Linked-List-Menu----------\n\n");
        printf("1: Add Node\n");
        printf("2: Insert Node\n");
        printf("3: Search by ID \n");
        printf("4: Search by Name\n");
        printf("5: Delete by ID\n");
        printf("6: Delete by name\n");
        printf("7: Free list\n");
        printf("8: Print list\n");
        printf("9: Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // add Node
            printf("You chose to add a node.\n");

            retval = addNode();

            if (retval == 1)
            {
                printf("Node added successfully");
            }
            break;
        case 2: // insert Node
            printf("You chose to insert a node.\n");
            retval = insertNode();
            if (retval == 1)
            {
                printf("Node added successfully");
            }
            break;
        case 3: // serach by id
            printf("You chose to search by ID.\n");
            printf("enter ID:\n");
            scanf("%d", &id);
            stu = searchIDStu(id);
            if (stu.id != 0)
            {
                printStudent(stu);
                printf("Press Enter to continue...\n");
                getchar();
                getchar();
            }
            else
            {
                printf("Student with ID '%d' not found.\n", id);
                printf("Press Enter to continue...\n");
                getchar();
                getchar();
            }

            break;
        case 4: // search by name
            printf("You chose to search by name.\n");
            printf("enter Name:\n");
            scanf("%s", name);
            stu = searchNameStu(name);
            if (stu.id != 0)
            {
                printStudent(stu);
                printf("Press Enter to continue...\n");
                getchar();
                getchar();
            }
            else
            {
                printf("Student with name '%s' not found.\n", name);
                printf("Press Enter to continue...\n");
                getchar();
                getchar();
            }
            break;
        case 5: // delete by id
            printf("You chose to delete by ID.\n");
            printf("enter ID:\n");
            scanf("%d", &id);
            deleteID(id);
            printf("Press Enter to continue...\n");
            getchar();
            getchar();
            break;
        case 6: // delete by name
            printf("You chose to delete by name.\n");
            printf("enter Name:\n");
            scanf("%s", name);
            deleteName(name);
            printf("Press Enter to continue...\n");
            getchar();
            getchar();
            break;
        case 7: // free list
            printf("You chose to free the list.\n");
            freeList();
            break;
        case 8: // print list
            printf("You chose to print the list.\n");
            printList();
            printf("Press Enter to continue...\n");
            getchar();
            getchar();
            break;
        case 9:
            printf("Exiting the program. Goodbye!\n");
            exit(0); // Exit the program
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

struct student fillStudent()
{
    struct student stu;
    system("cls");
    stu.id = 0;
    while (stu.id == 0)
    {
        printf("Enter Your ID (don't use 0)\n");
        scanf("%d", &stu.id);
    }
    printf("Enter Your Name\n");
    scanf("%s", stu.name);

    return stu;
}

struct node *createNode(struct student stu)
{
    struct node *pnode = NULL;
    pnode = (struct node *)malloc(sizeof(struct node));
    if (pnode)
    {
        pnode->st = stu;
        pnode->pnext = pnode->pprev = NULL;
    }
    return pnode;
}
int addNode()
{
    int retval = 0;
    struct student stu;
    struct node *ptr = NULL;
    stu = fillStudent();
    ptr = createNode(stu);
    if (ptr)
    {
        retval = 1;
        if (!phead)
        {
            phead = ptail = ptr;
        }
        else
        {
            ptail->pnext = ptr;
            ptr->pprev = ptail;
            ptail = ptr;
        }
        count++;
    }

    return retval;
}

int insertNode()
{
    int loc, retval = 0;
    printf("please enter the location of the node to insert\n");
    scanf("%d", &loc);
    struct student stu;
    struct node *ptr = NULL, *temp = NULL;
    stu = fillStudent();
    ptr = createNode(stu);
    if (ptr)
    {
        retval = 1;
        if (!phead)
        { // no list
            phead = ptail = ptr;
        }
        else if (loc <= 0)
        { // insert node in first location
            ptr->pnext = phead;
            phead->pprev = ptr;
            phead = ptr;
        }
        else if (loc >= count)
        {
            ptr->pprev = ptail;
            ptail->pnext = ptr;
            ptail = ptr;
        }
        else // in the middle
        {
            temp = phead; // we will start moving from start
            for (int i = 0; i < loc - 1; i++)
            {
                temp = temp->pnext;
            }
            ptr->pnext = temp->pnext;
            temp->pnext->pprev = ptr;
            ptr->pprev = temp;
            temp->pnext = ptr;
        }
        count++;
    }
    return retval;
}

struct student searchIDStu(int id)
{
    struct node *ptr;
    ptr = searchIDPtr(id);
    return ptr->st;
}

struct node *searchIDPtr(int id)
{
    struct node *ptr;
    ptr = phead;
    while (ptr->st.id != id && ptr != NULL)
    {
        ptr = ptr->pnext;
    }
    return ptr;
}

struct student searchNameStu(char name[20])
{
    struct node *ptr;
    ptr = searchNamePtr(name);
    return ptr->st;
}

struct node *searchNamePtr(char name[20])
{
    struct node *ptr;
    ptr = phead;
    while (ptr != NULL)
    {
        if (strcmp(ptr->st.name, name) == 0)
        {
            printStudent(ptr->st);
            return ptr;
        }
        ptr = ptr->pnext;
    }
    return NULL;
}
void deleteID(int id)
{
    struct node *ptr;
    ptr = NULL;
    ptr = searchIDPtr(id);
    if (ptr)
    { // first
        if (ptr->pprev == NULL)
        {
            phead = ptr->pnext;
        }
        else if (ptr->pprev == NULL) // last
        {
            ptail = ptr->pprev;
        }
        else // in the middle
        {
            // change pnext node pprev
            ptr->pnext->pprev = ptr->pprev;
            // change pprev node pnext
            ptr->pprev->pnext = ptr->pnext;
        }
        count--;
        free(ptr);
        printf("the Node is deleted");
    }
}

void deleteName(char name[20])
{
    struct node *ptr;
    ptr = NULL;
    ptr = searchNamePtr(name);
    if (ptr)
    { // first
        if (ptr->pprev == NULL)
        {
            phead = ptr->pnext;
        }
        else if (ptr->pprev == NULL) // last
        {
            ptail = ptr->pprev;
        }
        else // in the middle
        {
            // change pnext node pprev
            ptr->pnext->pprev = ptr->pprev;
            // change pprev node pnext
            ptr->pprev->pnext = ptr->pnext;
        }
        count--;
        free(ptr);
        printf("the Node is deleted\n");
    }
}

void freeList()
{
    struct node *ptr;
    while (phead)
    {
        ptr = phead;
        phead = phead->pnext;
        free(ptr);
    }
    ptail = NULL;
}

void printStudent(struct student stu)
{
    printf("the student ID : %d \n", stu.id);
    printf("the student Name : %s\n", stu.name);
}
void printList()
{
    struct node *ptr = NULL;
    ptr = phead;
    for (int i = 0; i < count; i++)
    {
        printStudent(ptr->st);
        printf("--------------------------------------------\n");
        ptr = ptr->pnext;
    }
}