#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;  
	struct Node* link;  //다음 노드의 주소를 가리킬 자기참조 구조체 포인터 변수 선언
} listNode;

typedef struct Head { 
	struct Node* first;  //headnode구조체에서 struct node의 자료형을 가지는 first 포인터 선언
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);  
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode *headnode=NULL;  //매개변수 역할으로 headnode 포인터 선언,

	printf("[----- [HanSeungheon] [%d\n] -----\n]", 2020023057);

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));  
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;  //listNode 선언과 (*h).first 값 대입
	listNode* prev = NULL;  //이전 노드에 대한 포인터 null로 초기화
	while(p != NULL) {  //p가 null이 아니면
		prev = p;  
		p = p->link;  //p에 다음 link가 가리키느 주소 대입
		free(prev);
	}
	free(h);  //메모리 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //메모리 동적할당을 통해 노드 생성, 자기참조 구조체 포인터형으로 형변환
	node->key = key;    
	node->link = NULL;  //널 값으로 초기화해야 된다.

	if (h->first == NULL)  // 가리키는 첫번째 노드 == NULL
	{
		h->first = node;  
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;  //끝 노드 포인터 생성

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {  
				h->first = node;  //first 변수에 노드 대입
				node->link = n;  //노드링크는 n을 가르키게 수정
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;
				trail->link = node;  
			}
			return 0;
		}

		trail = n;
		n = n->link;  //n에 link가 가리키는 주소 대입
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //메모리 동적 할당
	node->key = key;
	node->link = NULL;  //NULL값으로 초기화

	if (h->first == NULL)    
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //메모리 할당
	node->key = key;  

	node->link = h->first;
	h->first = node;  

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");  //프리컨디션 조사
		return 0;
	}

	listNode* n = h->first;  
	listNode* trail = NULL;  //포인터 선언 및 초기화

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n);  //메모리 해제
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)  //fisrt 노드에 접근 -> NULL
	{
		printf("nothing to delete.\n");  //삭제할 게 없음
		return 0;
	}

	listNode* n = h->first;  
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;  
	free(n);  //메모리 해제

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");  //NULL인지 프리컨디션 조사 
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;  //삭제하고 가리키는 주소 옮기기
	free(n);  //메모리 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) {  //프리컨디션 조사
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}


void printList(headNode* h) {  //리스트 출력 함수
	int i = 0;  //item, 인덱스 수
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {  //마지막 다음은 NULL값, NULL값 전까지
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}