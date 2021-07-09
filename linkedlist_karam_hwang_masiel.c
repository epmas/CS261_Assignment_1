#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct Node {
    struct Node* prev;   		 /*changed node struct to allow for moving backwards through list */
    int data;
    struct Node* next;
};

struct Node* head;
struct Node* tail;


void insert(struct Node*, struct Node*);
void delete(struct Node*, struct Node*);
void _insert1(struct Node*);
void _insert2(struct Node*, struct Node*);
void _delete1();
void _delete2(struct Node*, struct Node*);
void _delete3(struct Node*, struct Node*);

void init();
void cleanup();

void disp();
void test();


int main() {
    init();
    test();
    cleanup();
    return 0;
}


void init() {
    head = tail = NULL;
}


void cleanup() {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


void _insert1(struct Node* curr) { 
    if (head == NULL) {
		curr->next = NULL;
		head = tail = curr;
	}
	else {
		curr->next = head;
		head = curr;
	}
}


void _insert2(struct Node* curr, struct Node* pred) {
    if (pred->next == NULL) {
		curr->next = NULL;
		pred->next = curr;
		tail = curr;
	}
	else {
		curr->next = pred->next;
		pred->next = curr;
	}
}


void insert(struct Node* curr, struct Node* pred) {
    if (pred == NULL) {
        _insert1(curr);
    }
    else {
        _insert2(curr, pred);
    }
}


void _delete1() {
    struct Node* curr = head;
	if (curr->next == NULL) {
		head = tail = NULL;
	}
	else {
		head = curr->next;
	}
	free(curr);
}


void _delete2(struct Node* curr, struct Node* pred) {
    pred->next = curr->next;
    free(curr);
}


void _delete3(struct Node* curr, struct Node* pred) {
    pred->next = NULL;
	tail = pred;
	free(curr);
}


void delete(struct Node* curr, struct Node* pred) { 		
    if (pred == NULL) {
		_delete1();
	}
	else if (curr->next == NULL) {
		_delete3(curr, pred);
	}
	else {
		_delete2(curr, pred);
	}
}

//prints all elements in linked list
void disp() { 							
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d\t", curr->data);
        curr = curr->next;
    }
    printf("\n");
}


void test() {
    struct Node* n1 = malloc(sizeof(struct Node));
    n1->data = 10; n1->next = NULL; insert(n1, NULL); disp();
    struct Node* n2 = malloc(sizeof(struct Node));
    n2->data = 20; n2->next = NULL; insert(n2, n1); disp();
    struct Node* n3 = malloc(sizeof(struct Node));
    n3->data = 30; n3->next = NULL; insert(n3, n2); disp();
    struct Node* n4 = malloc(sizeof(struct Node));
    n4->data = 25; n4->next = NULL; insert(n4, n2); disp();
    struct Node* n5 = malloc(sizeof(struct Node));
    n5->data = 40; n5->next = NULL; insert(n5, n3); disp();
    delete(n1, NULL); disp();
    n1 = malloc(sizeof(struct Node));
    n1->data = 10; n1->next = NULL; insert(n1, NULL); disp();
    delete(n2, n1); disp();
    n2 = malloc(sizeof(struct Node));
    n2->data = 20; n2->next = NULL; insert(n2, n1); disp();
    delete(n5, n3); disp();
}

