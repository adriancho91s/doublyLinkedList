#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct node {
    struct node *prev;
    int id;
    char name[30];
    struct node *next;
};

typedef struct {
    int id;
    char name[30];
} FileNode;

void addNodeToPosition(struct node **first, int position, int id, char name[30]);

struct node *findNodeAtPosition(struct node **first, int position);

struct node *findNodeById(struct node **first, int id);

void insertAfterId(struct node **first, int referenceId, int id, char name[30]);

void deleteNodeAfterId(struct node **first, int id);

void deleteNodeAtPosition(struct node **first, int position);

int checkIfIdExists(struct node **first, int id);

void print(struct node **first, int order);

void clearScreen();

void delay();

int counterNodes(struct node **first);

int main() {
    struct node *first = NULL;

    char *options[] = {
            "Print the whole list",
            "Add a new node at position",
            "Add a new node after a given id",
            "Delete a node by position",
            "Delete a node after a given id",
            "Exit"
    };
    int numOptions = sizeof(options) / sizeof(options[0]);

    //Menu for the user
    int option;
    do {
        clearScreen();
        printf("\tWelcome to the linked list program\n\n");
        for (int i = 0; i < numOptions; i++) {
            printf("%d. %s\n", i + 1, options[i]);
        }
        fflush(stdin);
        printf("\nChoose an option: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                clearScreen();
                if (NULL == first) {
                    printf("The list is empty\n");
                    delay();
                    break;
                }
                int order;
                printf("Choose the order to print the list (0 ASC / 1 DESC): ");
                scanf("%d", &order);
                printf("\tHere's the whole list\n\n");
                print(&first, order);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 2:
                clearScreen();
                printf("\tYou're about to add a new node to a position\n");
                int position = 1;
                int id;
                char name[30];

                if (NULL != first) {
                    print(&first, 0);
                    printf("Choose a position to add the new node: ");
                    fflush(stdin);
                    scanf("%d", &position);
                    if (position < 1) {
                        printf("Invalid position\n");
                        break;
                    }
                }

                if(findNodeAtPosition(&first, position) == NULL && position != 1){
                    printf("The given position does not exist\n");
                    break;
                }

                printf("Write the id of the new node: ");
                scanf("%d", &id);
                getc(stdin);

                if (checkIfIdExists(&first, id)) {
                    printf("The given id already exists\n");
                    clearScreen();
                    break;
                }

                printf("Write the name of the new node: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                fflush(stdin);

                addNodeToPosition(&first, position - 1, id, name);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 3:
                clearScreen();
                printf("\tYou're about to add a new node after a given id\n");
                print(&first, 0);
                int referenceId;
                printf("Choose the id of the node after which you want to add a new node: ");
                scanf("%d", &referenceId);
                int idToAdd;
                printf("Write the id of the new node: ");
                scanf("%d", &idToAdd);
                printf("Write the name of the new node: ");
                char nameToAdd[30];
                getc(stdin);
                fgets(nameToAdd, sizeof(nameToAdd), stdin);
                nameToAdd[strcspn(nameToAdd, "\n")] = '\0';
                insertAfterId(&first, referenceId, idToAdd, nameToAdd);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 4:
                clearScreen();
                printf("\t\x1b[31mYou're about to delete a node in a given position\x1b[0m\n");
                print(&first, 0);
                int positionToDelete = 0;
                printf("Choose a position to delete the node: ");
                scanf("%d", &positionToDelete);
                if (positionToDelete < 1) {
                    printf("Invalid position\n");
                    break;
                }
                deleteNodeAtPosition(&first, positionToDelete);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 5:
                clearScreen();
                printf("\t\x1b[31mYou're about to delete a node after a given id\x1b[0m\n");
                print(&first, 0);
                int idToDelete;
                printf("Choose the id of the node after which you want to delete a node: ");
                scanf("%d", &idToDelete);
                deleteNodeAfterId(&first, idToDelete);
                printf("Press enter to continue...");
                fgetc(stdin);
                break;
            case 6:
                clearScreen();
                printf("Goodbye\n");
                delay();
                break;
            default:
                clearScreen();
                printf("Invalid option\n");
                delay();
                clearScreen();
                break;
        }
    } while (option != numOptions);
    return 0;
}

/*
 * Delete the linked list
 * @return void
 * */
void deleteList(struct node **first) {
    struct node *current = *first;
    struct node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *first = NULL;
    free(*first);
}

/*
 * Print the linked list
 * @param first The pointer to the pointer of the first node in the linked list
 * @param to print the doubly linked list ASC or DESC if 0 ASC if 1 DESC
 * @return void
 * */
void print(struct node **first, int order) {
    //printf("║     Id    ║    Name  ╚╝   ║\n");
    int i = 1;
    struct node *temp = *first;
    printf("╔═══════════╦═══════════╦═══════════════════════════════╗\n");
    printf("║ Node(pos) ║    Id     ║           Name                ║\n");
    printf("╠═══════════╬═══════════╬═══════════════════════════════╣\n");

    //If order is 0 print the list in ASC order
    if (order == 0) {
        while (temp != NULL) {
            printf("║    %d      ║    %d      ║           %s                ║\n", i, temp->id, temp->name);
            temp = temp->next;
            i++;
        }
    } else {
        //If order is 1 print the list in DESC order
        int n = counterNodes(first);
        while (n > 0) {
            temp = findNodeAtPosition(first, n);
            printf("║    %d      ║    %d      ║           %s                ║\n", i, temp->id, temp->name);
            n--;
            i++;
        }
    }
    printf("╚═══════════╩═══════════╩═══════════════════════════════╝\n");
}

/*
 * Clear the screen
 * @return void
 * */
void clearScreen() {
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

/*
 * Delay the program
 * @return void
 * */
void delay() {
#ifdef WINDOWS
    system("timeout 2 > nul");
#else
    system("sleep 2");
#endif
}


/*
 * Add a new node at a given position in the doubly linked list
 * @param first The pointer to the pointer of the first node in the linked list
 * @param target The node with the given position
 * @param id The id of the new node
 * @param name The name of the new node
 * @return void
 * */
void addNodeToPosition(struct node **first, int position, int id, char name[30]) {
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*first == NULL) {
        *first = newNode;
        return;
    }

    if (position == 0) {
        newNode->next = *first;
        if (*first != NULL) {
            (*first)->prev = newNode;
        }
        *first = newNode;
        return;
    }

    struct node *target = findNodeAtPosition(first, position + 1);
    if (target == NULL) {
        struct node *lastNode = findNodeAtPosition(first, position);
        if (lastNode == NULL) {
            printf("The given position does not exist\n");
            return;
        }
        lastNode->next = newNode;
        newNode->prev = lastNode;
        return;
    }

    newNode->next = target;
    newNode->prev = target->prev;
    if (target->prev != NULL) {
        target->prev->next = newNode;
    }
    target->prev = newNode;
}

/*
 * Find a node at a given position in the linked list
 * @param position The position of the node to find
 * @return struct node* The node at the given position
 * */
struct node *findNodeAtPosition(struct node **first, int position) {
    if (position < 0) {
        printf("Invalid position\n");
        return NULL;
    }
    struct node *temp = *first;
    int i = 1;
    while (temp != NULL && i < position) {
        temp = temp->next;
        i++;
    }
    return temp;
}

/*
 * Find a node by its id in the linked list
 * @param id The id of the node to find
 * @return struct node* The node with the given id
 * */
struct node *findNodeById(struct node **first, int id) {
    struct node *temp = *first;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/*
 * Insert a new node after a given id in the doubly linked list
 * @param first The pointer to the pointer of the first node in the linked list
 * @param referenceId The id of the node after which the new node will be inserted
 * @param id The id of the new node
 * @param name The name of the new node
 * @return void
 * */
void insertAfterId(struct node **first, int referenceId, int id, char name[30]) {
    struct node *currentId = findNodeById(first, referenceId);
    if (currentId == NULL) {
        printf("The given id does not exist\n");
        return;
    }
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->next = currentId->next;
    newNode->prev = currentId;
    if (currentId->next != NULL) {
        currentId->next->prev = newNode;
    }
    currentId->next = newNode;
}

/*
 * Delete a node at a given position in the doubly linked list
 * @param first The pointer to the pointer of the first node in the doubly linked list
 * @param position The position of the node to delete
 * @return void
 * */
void deleteNodeAtPosition(struct node **first, int position) {
    if (position < 0) {
        printf("Invalid position\n");
        return;
    }

    if (position == 0) {
        struct node *temp = *first;
        *first = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = NULL;
        }
        free(temp);
        return;
    }

    //THis is the node to be deleted
    struct node *temp = findNodeAtPosition(first, position);
    if (temp == NULL) {
        printf("The given position does not exist\n");
        return;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    temp->prev->next = temp->next;
    free(temp);
}

/*
 * Count the number of nodes in the doubly linked list
 * @param first The pointer to the pointer of the first node in the linked list
 * @return int The number of nodes in the doubly linked list
 * */
int counterNodes(struct node **first) {
    int contador = 0;
    struct node *temp = *first;
    while (temp != NULL) {
        contador++;
        temp = temp->next;
    }
    return contador;
}

/*
 * Delete a node after a given id in the doubly linked list
 * @param first The pointer to the pointer of the first node in the linked list
 * @param id The id of the node after which the node will be deleted
 * @return void
 * */
void deleteNodeAfterId(struct node **first, int id) {
    //Give a name to a node that it's after the given id, take into account that we must to delete the node after this one
    struct node *prevNode = findNodeById(first, id);
    if (prevNode == NULL) {
        printf("The given previous node cannot be NULL");
        return;
    }
    struct node *temp = prevNode->next;
    if (temp == NULL) {
        return;
    }
    prevNode->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = prevNode;
    }
    free(temp);
}

/*
 * Check if a given id exists in the linked list
 * @param id The id to check
 * @return int 1 if the id exists, 0 otherwise
 * */
int checkIfIdExists(struct node **first, int id) {
    struct node *temp = *first;
    while (temp != NULL) {
        if (temp->id == id) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
