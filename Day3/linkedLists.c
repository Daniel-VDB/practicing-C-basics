#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX 7

typedef struct node{
    int body;
    struct node *next;
} node;

node *create_list(int num);
void print_list(node *head);
void reverse_list(node **head);
void free_list(node *head);

int main(void){
    srand(time(NULL));

    int num = abs(rand() % MAX);
    node *head = create_list(num);

    print_list(head);
    reverse_list(&head);
    print_list(head);

    free_list(head);
    return 0;
}

node *create_list(int num){
    // empty list
    if (num <= 0){
        return NULL;
    }

    // Create first node
    node *current = malloc(sizeof(node));
    if (current == NULL) {return NULL;}

    current->body = rand();
    current->next = NULL;

    // Store first node in header
    node *start = current;
    node *previous = NULL;
    
    // Create remaining nodes, setting current pointer to previouse nodes "next"
    for (int i = 1; i < num; i++){
        previous = current;

        current = malloc(sizeof(node));
        if (current == NULL){
            printf("Failed memory allocation");
            free_list(start);
            return NULL;
        }

        current->body = rand();
        current->next = NULL;

        previous->next = current;   
        
    }
    return start;
}

void print_list(node *head){
    while(head != NULL){
        printf("[%i]->", head->body);
        head = head->next;
    }
    printf("NULL\n");
}

void reverse_list(node **head){
    if (head == NULL) return;
    node *current = *head;
    node *last = NULL;
    node *next = NULL;
    while (current != NULL){
        next = current->next;
        current->next = last;
        last = current;
        current = next;
    }
    *head = last;
}

void free_list(node *head){
    if (head==NULL){return;}
    // Freeing all elements in the linked list
    node *last = NULL;
    while(head != NULL){
        last = head;
        head = head->next;
        free(last);
    }
}