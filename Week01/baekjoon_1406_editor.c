#if 1
//백준 - 1406 에디터  https://www.acmicpc.net/problem/1406
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_N (100000+1)

/*구조체 및 전역변수 선언*/
typedef char DLL_Element;
typedef struct _dll_node {
	DLL_Element data;
	struct _dll_node* prev;
	struct _dll_node* next;
}DLL_Node;

char ary[MAX_N];
int N;
int M;
char action;
DLL_Node* Head = NULL;
DLL_Node* Tail = NULL;
DLL_Node* cursor = NULL;

/*함수 선언*/
void makebase_DLL(DLL_Node* Head, DLL_Node* Tail);
DLL_Node* Create_DLLNode(DLL_Element data);
DLL_Node* InsertNode_DLLNode(DLL_Element data, DLL_Node* prenode, DLL_Node* nextnode);
int Delete_DLLNode(DLL_Node* temp);
void print_DLLNode(DLL_Node* temp);
void scan_action_DLLNode();
void choice_action_DLLnode(char action);
void move_cursur_left();
void move_cursur_right();

/*함수 정의*/
void makebase_DLL(DLL_Node* Head, DLL_Node* Tail) {
	DLL_Node* temp = Head;
	for (int i = 0; i < N; ++i) {
		temp = InsertNode_DLLNode(ary[i], temp, temp->next);
		if (temp == NULL) exit(1);
	}
}

DLL_Node* Create_DLLNode(DLL_Element data) {
	DLL_Node* newnode = NULL;
	newnode = (DLL_Node*)calloc(1, sizeof(DLL_Node));
	if (newnode == NULL) exit(1);
	newnode->data = data;
	newnode->prev = 0;
	newnode->next = 0;
	return newnode;
}
DLL_Node* InsertNode_DLLNode(DLL_Element data, DLL_Node* prenode, DLL_Node* nextnode) {
	DLL_Node* newnode = Create_DLLNode(data);
	if (newnode == NULL) return NULL;
	newnode->prev = prenode;
	newnode->next = nextnode;
	prenode->next = newnode;
	nextnode->prev = newnode;
	return newnode;
}

void print_DLLNode(DLL_Node* temp) {
	DLL_Node* curr = NULL;
	for (curr = temp->next; curr->next != NULL; curr = curr->next) {
		printf("%c", curr->data);
	}
}
int Delete_DLLNode(DLL_Node* temp) {
	DLL_Node* delnode = (temp)->prev;
	if (delnode == Head) return 1;
	delnode->next->prev = delnode->prev;
	delnode->prev->next = delnode->next;

	delnode->prev = NULL;
	delnode->next = NULL;
	free(delnode);
	return 0;
}
void scan_action_DLLNode() {
	for (int i = 0; i < M; ++i) {
		(void)scanf(" %c", &action);
		choice_action_DLLnode(action);
	}
}
void choice_action_DLLnode(char action) {
	char temp;
	switch (action) {
	case 'L':
		move_cursur_left(cursor);
		break;
	case 'D':
		move_cursur_right(cursor);
		break;
	case 'B':
		Delete_DLLNode(cursor);
		break;
	case 'P':
		(void)scanf(" %c", &temp);
		InsertNode_DLLNode(temp, cursor->prev, cursor);
		break;
	}
}

void move_cursur_left() {
	if (cursor->prev != Head) {
		cursor = cursor->prev;
	}
}
void move_cursur_right() {
	if (cursor->next != NULL) {
		cursor = cursor->next;
	}
}

/*메인 함수*/
int main() {
	(void)scanf(" %s", ary);
	N = strlen(ary);
	(void)scanf(" %d", &M);
	Head = Create_DLLNode(0);
	Tail = Create_DLLNode(0);
	Head->next = Tail;
	Tail->prev = Head;

	/*초기 문자열 DLL 삽입 + cursor 맨 뒤에 삽입*/
	makebase_DLL(Head, Tail);

	cursor = Tail;
	scan_action_DLLNode();

	print_DLLNode(Head);
}
#endif // 0

////void move_cursor_left_DLLNode(DLL_Node* cursor) {
//	if (cursor == NULL) return;
//	if (cursor->prev == Head) return;
//	DLL_Node* prevnode = cursor->prev;
//	DLL_Node* nextnode = cursor->next;
//	prevnode->prev->next = cursor;
//	prevnode->next = nextnode;
//	cursor->prev = prevnode->prev;
//	prevnode->prev = cursor;
//	cursor->next = prevnode;
//	nextnode->prev = prevnode;
//}

	//DLL_Node* cursor = InsertNode_DLLNode('C', Tail->prev, Tail); 병신짓 했네 ㅇㅇ