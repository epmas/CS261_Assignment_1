#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct Node {
    int data;
    struct Node* link;
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
        head = head->link;
        free(temp);
    }
}


void _insert1(struct Node* curr) {
    if (head == NULL) {
		curr->link = NULL;
		head = tail = curr;
	}
	else {
		curr->link = head;
		head = curr;
	}
}


void _insert2(struct Node* curr, struct Node* pred) {
    if (pred->link == NULL) {
		curr->link = NULL;
		pred->link = curr;
		tail = curr;
	}
	else {
		curr->link = pred->link;
		pred->link = curr;
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
	if (curr->link == NULL) {
		head = tail = NULL;
	}
	else {
		head = curr->link;
	}
	free(curr);
}


void _delete2(struct Node* curr, struct Node* pred) {
    pred->link = curr->link;
    free(curr);
}


void _delete3(struct Node* curr, struct Node* pred) {
    pred->link = NULL;
	tail = pred;
	free(curr);
}


void delete(struct Node* curr, struct Node* pred) {
    if (pred == NULL) {
		_delete1();
	}
	else if (curr->link == NULL) {
		_delete3(curr, pred);
	}
	else {
		_delete2(curr, pred);
	}
}


void disp() {
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d\t", curr->data);
        curr = curr->link;
    }
    printf("\n");
}


void test() {
    struct Node* n1 = malloc(sizeof(struct Node));
    n1->data = 10; n1->link = NULL; insert(n1, NULL); disp();
    struct Node* n2 = malloc(sizeof(struct Node));
    n2->data = 20; n2->link = NULL; insert(n2, n1); disp();
    struct Node* n3 = malloc(sizeof(struct Node));
    n3->data = 30; n3->link = NULL; insert(n3, n2); disp();
    struct Node* n4 = malloc(sizeof(struct Node));
    n4->data = 25; n4->link = NULL; insert(n4, n2); disp();
    struct Node* n5 = malloc(sizeof(struct Node));
    n5->data = 40; n5->link = NULL; insert(n5, n3); disp();
    delete(n1, NULL); disp();
    n1 = malloc(sizeof(struct Node));
    n1->data = 10; n1->link = NULL; insert(n1, NULL); disp();
    delete(n2, n1); disp();
    n2 = malloc(sizeof(struct Node));
    n2->data = 20; n2->link = NULL; insert(n2, n1); disp();
    delete(n5, n3); disp();
}

