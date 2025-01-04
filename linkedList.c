#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* current;
} LinkedList;

LinkedList* createList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->current = NULL;
    return list;
}

void addElement(LinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void moveForward(LinkedList* list) {
    if (list->current != NULL) {
        list->current = list->current->next;
    }
}


int getFirstElement(LinkedList* list) {
    if (list->head != NULL) {
        list->current = list->head;
        return list->head->data;
    }
    return -1; // Assuming -1 indicates no elements
}

void removeCurrentElement(LinkedList* list) {
    if (list->head == NULL || list->current == NULL) {
        return;
    }

    if (list->head == list->current) {
        Node* temp = list->head;
        list->head = list->head->next;
        list->current = list->head;
        free(temp);
        return;
    }

    Node* prev = list->head;
    while (prev->next != list->current && prev->next != NULL) {
        prev = prev->next;
    }

    if (prev->next != NULL) {
        Node* toDelete = list->current;
        prev->next = toDelete->next;
        list->current = toDelete->next;
        free(toDelete);
    }
}

void printList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void removeElementsDivisibleBy(LinkedList* list, int N) {
    if (list->head == NULL) return;

    Node* temp = list->head;
    Node* prev = NULL;

    while (temp != NULL) {
        if (temp->data % N == 0) {
            if (prev == NULL) {
                // Removing head node
                list->head = temp->next;
                free(temp);
                temp = list->head;
            } else {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <max>\n", argv[0]);
        return 1;
    }

    int max = atoi(argv[1]);
    LinkedList* list = createList();
    LinkedList* primeList = createList();
    
    int firstItem;
    int primeCounter = 0;

    printf("Calculating primes up to %d...\n", max);
    printf("Adding elements to the list...\n");
    for (int i = 2; i < max; i++) {
        addElement(list, i);
    }
    printf("Done adding elements to the list.\n");
    // once elements are loaded, I can remove all following elements given that the first one is prime;
    printf("Calculating primes...\n");
    while (list->head != NULL) {
        firstItem = getFirstElement(list);
        removeElementsDivisibleBy(list, firstItem);
        primeCounter++;
        addElement(primeList, firstItem);
    }
    
    printf("Prime count: %d\n", primeCounter);
    // printList(primeList);

    free(list);
    free(primeList);
    return 0;
}
