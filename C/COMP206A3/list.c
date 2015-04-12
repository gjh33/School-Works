#include <stdlib.h>
#include <stdio.h>

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

struct NODE{//this is a doubly linked list to make delete simple and O(n)
	int value;//value of this node
	struct NODE *next;//node after this one
};
struct LinkedList{
	struct NODE *head;//first node of the list
	struct NODE *tail;//last node of the list
	int size;//size of the list
} myList;

struct NODE *trailingPointer;

void add(int num) {
	if (myList.tail == NULL){
		struct NODE *tmp = (struct NODE *)malloc(sizeof(struct NODE));
		tmp->value = num;
		myList.head = tmp;
		myList.tail = tmp;
		myList.size = 1;
	}
	else {
		struct NODE *tmp = (struct NODE *)malloc(sizeof(struct NODE));
		tmp->value = num;
		myList.tail->next = tmp;
		myList.tail = tmp;
		myList.size = myList.size + 1;
	}
}

void prettyPrint() {
	int i = 0;//iterator
	struct NODE *cur;//the current node
	cur = myList.head;
	printf("====================================================\n====================================================\n");//some fancy border
	for(i=0; i<myList.size;i++){
		printf("%d\n", cur->value);
		cur = cur->next;
	}
	printf("====================================================\n====================================================\n");//some fancy border
}

struct NODE *find(int val){
	struct NODE *toRet = NULL;//the pointer to the returned node
	int i = 0;//iterator
	struct NODE *cur;//current node being searched
	trailingPointer = NULL;
	cur = myList.head;
	for(i=0; i<myList.size; i++){
		if(cur->value == val){
			toRet = cur;
			break;
		}
		trailingPointer = cur;
		cur = cur->next;
	}
	return toRet;
}

BOOLEAN delete(int val) {
	struct NODE *toDel = find(val);
	if(toDel == NULL){
		return FALSE;
	}
	else{
		if(toDel == myList.head){
			myList.head = myList.head->next;
		}
		else if(toDel == myList.tail){
			myList.tail = trailingPointer;
			myList.tail->next = NULL;
		}
		else{
			trailingPointer->next = toDel->next;
		}
		free(toDel);
		myList.size = myList.size - 1;
		return TRUE;
	}
}
