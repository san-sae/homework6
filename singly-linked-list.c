/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>

/* node에 대한 구조체*/
typedef struct Node {
	int key;           // 저장할 값
	struct Node* link; // 다음 노드를 가리키는 포인터
} listNode;

/* headnode에 대한 구조체 */ 
typedef struct Head {
	struct Node* first; // first node를 가리키는 포인터
}headNode;


/* prototype */
headNode* initialize(headNode* h);     // first node를 가리키는 헤드 생성
int freeList(headNode* h);             // linked list에 대한 동적 할당 해제

int insertFirst(headNode* h, int key); // linked list의 첫 번째 노드에 key 삽입
int insertNode(headNode* h, int key);  // linked list의 중간 노드에 key 삽입
int insertLast(headNode* h, int key);  // linked list의 마지막 노드에 key 삽입

int deleteFirst(headNode* h);          // linked list의 첫 번째 노드 제거
int deleteNode(headNode* h, int key);  // linked list에서 key의 값을 가진 노드 제거
int deleteLast(headNode* h);           // linked list의 마지막 노드 제거
int invertList(headNode* h);           // linked list를 역순으로 배열

void printList(headNode* h);           // linked list 출력

int main(){

	char command;            // 커맨드
	int key;                 // 노드에 저정할 값
	headNode* headnode=NULL; // first node를 가리키는 head를 NULL로 초기화

    printf("[----- [Choi Yoolim] [2020022001] -----]\n");

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
		scanf(" %c", &command); // 커맨드 입력

		switch(command) {
            case 'z': case 'Z':
                headnode = initialize(headnode); // linked list 초기화
                break;
            case 'p': case 'P':
                printList(headnode);             // linked list 출력
                break;
            case 'i': case 'I':
                printf("Your Key = ");
                scanf("%d", &key);               // 노드의 key값 입력
                insertNode(headnode, key);       // 입력 받은 key을 linked list의 중간에 삽입
                break;
            case 'd': case 'D':
                printf("Your Key = ");
                scanf("%d", &key);               // 노드의 key값 입력
                deleteNode(headnode, key);       // 입력 받은 key값을 가진 노드를 linked list에서 삭제
                break;
            case 'n': case 'N':
                printf("Your Key = ");
                scanf("%d", &key);               // 노드의 key값 입력
                insertLast(headnode, key);       // 입력 받은 key값을 linked list의 마지막에 삽입
                break;
            case 'e': case 'E':
                deleteLast(headnode);            // linked list의 마지막 노드 삭제
                break;
            case 'f': case 'F':
                printf("Your Key = ");
                scanf("%d", &key);               // 노드의 key값 입력
                insertFirst(headnode, key);      // 입력 받은 key을 linked list의 첫 번째에 삽입
                break;
            case 't': case 'T':
                deleteFirst(headnode);           // linked list의 첫번째 노드 삭제
                break;
            case 'r': case 'R':
                invertList(headnode);            // linked lis를 역순으로 배열
                break;
            case 'q': case 'Q':
                freeList(headnode);              // linked list의 동적 할당 해제
                break;
            default:                             // 그 이외의 경우에는 동작 없이 주의 메시지 출력
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
		}

	}while(command != 'q' && command != 'Q'); // 'q' 또는 'Q'를 입력하기 전까지 반복

	return 1;
}

headNode* initialize(headNode* h) { // headNode 초기화 함수

	/* headNode가 NULL이 아닐 경우, freeNode() 함수를 호출 */
	if(h != NULL)
		freeList(h);

	/* headNode가 NULL일 경우, 아래의 코드 실행 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode 크기만큼 동적할당된 메모리에 대한 headNode*를 temp에 저장
	temp->first = NULL;                                   // temp 포인터가 가리키는 headNode 구조체의 first 멤버 변수에 NULL 저장

	return temp;                                          // temp 포인터 반환
}

int freeList(headNode* h){  // linked list에 대한 동적 할당 메모리 해제 함수
	
    /* h는 listNode의 첫 번째 노드를 가리키는 포인터를 뜻하며,
	 * 이러한 headNode가 해제되는 함수
	 */
	listNode* p = h->first; // headNode 구조체 멤버 변수 first가 가리키는 구조체 listNode의 주소를 포인터 p에 저장

	listNode* prev = NULL;  // 현재 노드의 주소를 잠시 저장할 포인터 변수
	while(p != NULL) {      // p가 NULL이 아닐 때까지 반복(linked list의 끝까지 수행)
		prev = p;           // 현재 노드의 주소인 p를 이전 노드의 주소를 뜻하는 prev에 저장
		p = p->link;        // p에 새로운 현재 노드의 주소를 저장
		free(prev);         // 이전 노드에 대한 동적 할당 메모리 해제
	}
	free(h);                // headNode 구조체에 대한 동적 할당 메모리 해제
	return 0;               // 0 return
}


/* linked list에 새로운 node를 삽입하는 함수로서,
 * key는 삽입할 값을 의미한다
 */
int insertNode(headNode* h, int key) { 
    
    // 새로운 노드인 node 생성
	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode 크기만큼 동적할당된 메모리에 대한 listNode*를 node에 저장
	node->key = key;                                      // argument로 받은 key의 값을 node의 key의 값에 저장
	node->link = NULL;                                    // node의 link의 값은 NULL로 저장장

	if (h->first == NULL) {                               // linked list h가 비어 있는 경우
		h->first = node;                                  // 위에서 만든 node를 첫 번째 노드로 설정하기 위해 h의 first에 node의 주소값을 저장 
		return 0;                                         
	}

    // 아래부터는 linked list가 비어있지 않는 경우
	listNode* n = h->first;                               // firstNode를 가리키는 주소 값을 포인터 변수 n에 저장
	listNode* trail = h->first;                           // 

	while(n != NULL) {                                    // 현재 node인 n이 NULL이 아닐 때까지 반복(linked list의 끝까지 수행)
		if(n->key >= key) {                               // n의 key 값이 삽입할 key 값보다 크거나 같을 경우
			if(n == h->first) {                           // n이 첫 번째 node인 경우
				h->first = node;                          // node의 주소를 headNode로 설정
				node->link = n;                           // n의 주소를 node의 link 값으로 설정
			} else {                                      // n이 첫 번째 node가 아닌 경우
				node->link = n;                           // n의 주소를 node의 link 값으로 설정
				trail->link = node;                       // node의 주소를 trail의 link 값으로 설정
			}
			return 0;                                
		}

		trail = n;
		n = n->link;                                      // 현재 노드에 다음 노드의 주소 저장
	}

	trail->link = node;                                   // 새로운 노드를 연결 리스트의 끝에 추가
	return 0;
}

int insertLast(headNode* h, int key) { // 입력받은 key값을 linked list의 마지막 노드로 설정

    // 새로운 노드 생성
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) {            // linked list가 비어 있을 경우
		h->first = node;               // node를 첫 번째 노드로 설정
		return 0;
	}

    // linked list가 비어 있지 않는 경우
	listNode* n = h->first;
	while(n->link != NULL) {           // n이 NULL이 아닐 때 수행
		n = n->link;                   // n에 n의 다음 주소를 저장
	}
	n->link = node;                    // 새로운 노드를 n의 link값으로 설정

	return 0;
}

int insertFirst(headNode* h, int key) {                   // 입력받은 key의 값을 첫 번째 노드로 설정

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode 크기 만큼 동적 할당
	node->key = key;                                      // 입력받은 key값을 새로 만들어진 노드의 key값에 대입 

	node->link = h->first;                                // 기존에 headNode가 가리켰던 첫번째 노드의 주소값을 새로운 노드 연결
	h->first = node;                                      // 새로운 노드에 headNode의 값을 대입

	return 0;
}

int deleteNode(headNode* h, int key) { // 입력받은 key 값을 가진 노드 삭제

	if (h->first == NULL) {
		printf("nothing to delete.\n"); // 삭제할 노드가 없다는 메시지 출력
		return 0;
	}

	listNode* n = h->first;            // 현재 노드를 표시하는 포인터 n
	listNode* trail = NULL;            // 이전 노드를 표시하는 포인터 trail

	while(n != NULL) {                 // n이 NULL이 아닐 때 수행

		if(n->key == key) {            // 입력받은 key값과 같은 값을 가진 노드일 경우

			if(n == h->first) {        // 찾은 노드가 첫 번째 노드일 경우
				h->first = n->link;    // n의 link값을 헤드노드 값으로 변경
			}
            else {                     // 찾은 노드가 첫 번째 노드가 아닐 경우
				trail->link = n->link; // n의 link값을 trail의 link값으로 변경
			}
			free(n);                   // 노드 n에 대한 동적 할당 해제

			return 0;
		}

		trail = n;                     // 현재 노드를 trail로 설정
		n = n->link;                   // 다음 노드를 현재 노드로 설정
	}

	
	printf("cannot find the node for key = %d\n", key); // key값을 가진 노드가 없다는 메시지 출력
	return 0;

}

int deleteLast(headNode* h) {           // linked list에서 마지막 노드 삭제

    // linked list가 비어있는 경우
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

    
	listNode* n = h->first;             // n에 헤드노드 대입
	listNode* trail = NULL;             // trail에 NULL 대입

	if(n->link == NULL) {               // linked list에 노드가 하나인 경우
		h->first = NULL;                // 헤드노드에 들어 있는 주소 값을 NULL로 초기화
		free(n);                        // n에 대한 동적 할당 메모리 삭제
		return 0;
	}

    // linked list에 노드가 두 개 이상인 경우
	while(n->link != NULL) {            // 노드의 link 값이 NULL일 때 수행
		trail = n;                      // 현재 노드의 주소를 trail에 저장
		n = n->link;                    // 다음 노드의 주소를 현재 노드로 저장 
	}

	trail->link = NULL;                 // trail의 link 값을 NULL로 초기화
	free(n);                            // 현재 노드에 대한 동적 할당 메모리 삭제

	return 0;
}

int deleteFirst(headNode* h) {          // linked

    // linked list가 비어있는 경우
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;             // n에 헤드노드 저장

	h->first = n->link;                 // 다음 노드의 주소를 헤드노드에 저장
	free(n);                            // 노드 n 삭제

	return 0;
}

int invertList(headNode* h) { // linked list를 역순으로 배열

    // linked list가 비어있는 경우
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;    // n에 헤드노드 저장
	listNode *trail = NULL;    // n의 이전 노드
	listNode *middle = NULL;   // n의 다음 노드

	while(n != NULL){          // n이 NULL이 아닐 때 수행
        trail = middle;        // 다음 노드를 이전 노드로 설정
		middle = n;            // 현재 노드를 다음 노드로 설정
		n = n->link;           // n의 list값을 현재 노드로 설정
		middle->link = trail;  // 이전 노드를 다음 노드의 link값으로 설정
	}

	h->first = middle;         // liked list의 맨 마지막 노드를 헤드 노드로 설정

	return 0;
}

void printList(headNode* h) {              // linked list의 key값들을 출력
	
    int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

    // linked list가 비어있는 경우
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;                          // 인자로 받은 linked list의 헤드노드를 p에 저장

	while(p != NULL) {                     // p가 NULL이 아닐 때 수행
		printf("[ [%d]=%d ] ", i, p->key); // [ [i]=i번째 key값 ]의 형태로 출력
		p = p->link;                       // 다음 노드로 이동
		i++;                               // i+1번째 인덱스로 이동
	}

	printf("  items = %d\n", i);           // linked list의 노드 개수 출력
}
