#include<stdio.h>
#include<stdlib.h>

typedef struct Node {		//���� ����Ʈ�� ��带 �����ϴ� ����ü Node ����
	int key;				//data field�� �ش��ϴ� ������ ����
	struct Node* link;		//link field�� �ش��ϴ� ����ü ������ ����
} listNode;					//struct Node�� listNode��� ������ ����

typedef struct Head {		//���� ����Ʈ�� ù��° ��带 ����ų ����ü Head ����
	struct Node* first;		//struct Node�� ����Ű�� ����ü ������ ���� first
}headNode;					//struct Head�� headNode��� ������ ����


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);		//���� ����Ʈ�� �ʱ�ȭ�ϴ� initialize �Լ� ���� ����
int freeList(headNode* h);				//���� ����Ʈ�� �Ҵ�Ǿ��� ������ �ʱ�ȭ�ϴ� freeList �Լ� ���� ����

int insertFirst(headNode* h, int key);	//���� ����Ʈ�� ù��° ��� �տ� ���ο� ��带 �����ϴ� insertFirst �Լ� ���� ����
int insertNode(headNode* h, int key);	//����� data field���� ���Ͽ� key������ ū data�� ���� ��� �տ� �����ϴ� insertNode �Լ� ���� ����
int insertLast(headNode* h, int key);	//���� ����Ʈ�� ���� ���ο� ��带 �����ϴ� insertLast �Լ� ���� ����

int deleteFirst(headNode* h);			//���� ����Ʈ�� ù��° ��带 �����ϴ� deleteFirst �Լ� ���� ����
int deleteNode(headNode* h, int key);	//��� �߿��� key���� ������ data field�� ������ ��带 �����ϴ� deleteNode �Լ� ���� ����
int deleteLast(headNode* h);			//���� ����Ʈ�� ������ ��带 �����ϴ� deleteLast �Լ� ���� ����
int invertList(headNode* h);			//���� ����Ʈ�� �������� �ٲ��ִ� invertList �Լ� ���� ����

void printList(headNode* h);			//���� ����Ʈ�� ����� ������ data field���� ����ϴ� printList �Լ� ���� ����

int main()
{
	char command;						//����ڰ� �Է��� �޴� ���ڸ� ������ ������ ���� ����
	int key;							//����� data field�� �� �� �Ǵ� ���� ���� �����ϴ� ������ ���� ����
	headNode* headnode = NULL;			//���� ����Ʈ�� ù��° ��带 ����ų ������ ������ ���� ���� �� NULL�� �ʱ�ȭ

	printf("[----- [������] [2019038006] -----]\n");
	do {
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
		scanf(" %c", &command);					//�����ϱ� ���ϴ� �޴� �Է� �� command�� ����

		switch (command) {						//command�� ���� case���� ���Ͽ� �ش��ϴ� case�� ��, �ش� �޴��� ����
		case 'z': case 'Z':						//command�� Initialize �޴��� �����Ű�� z or Z�� ���
			headnode = initialize(headnode);	//intialize �Լ��� ȣ���Ͽ� ����Ʈ�� �ʱ�ȭ��Ű�� ���� �޸��� �ּҸ� headnode�� ����
			break;								//switch�� Ż��
		case 'p': case 'P':						//command�� Print �޴��� �����Ű�� p or P�� ���
			printList(headnode);				//���� ����Ʈ�� ��ü ����� data field���� ����ϴ� printList �Լ� ȣ��
			break;								//switch�� Ż��
		case 'i': case 'I':						//command�� Insert Node �޴��� �����Ű�� i or I�� ���
			printf("Your Key = ");
			scanf("%d", &key);					//������ ����� data field�� �Է� �� key�� ����
			insertNode(headnode, key);			//insertNode �Լ��� ȣ���Ͽ� ������������ ���ο� ��� ����
			break;								//switch�� Ż��
		case 'd': case 'D':						//command�� Delete Node �޴��� �����Ű�� d or D�� ���
			printf("Your Key = ");
			scanf("%d", &key);					//�����ϰ��� ����� data field�� �Է� �� key�� ����
			deleteNode(headnode, key);			//deleteNode �Լ��� ȣ���Ͽ� key�� ���� data field�� ���� ��带 ����
			break;								//switch�� Ż��
		case 'n': case 'N':						//command�� Insert Last �޴��� �����Ű�� n or N�� ���
			printf("Your Key = ");	
			scanf("%d", &key);					//���� ����Ʈ�� �������� ������ ����� data field���� �Է� �� key�� ����
			insertLast(headnode, key);			//insertLast �Լ��� ȣ���Ͽ� ���� ����Ʈ�� �������� key���� ���� ���ο� ��� ����
			break;								//switch�� Ż��
		case 'e': case 'E':						//command�� Delete Last �޴��� �����Ű�� e or E�� ���
			deleteLast(headnode);				//deleteLast �Լ��� ȣ���Ͽ� ���� ����Ʈ�� ������ ��带 ����
			break;								//switch�� Ż��
		case 'f': case 'F':						//command�� Insert First �޴��� �����Ű�� f or F�� ���
			printf("Your Key = ");
			scanf("%d", &key);					//���� ����Ʈ�� ù��° ���� ������ data field�� ���� �Է� �� key�� ����
			insertFirst(headnode, key);			//insertFirst �Լ��� ȣ���Ͽ� ���� ����Ʈ�� ù��° ��� �տ� key���� ���� ���ο� ��� ����
			break;								//switch�� Ż��
		case 't': case 'T':						//command�� Delete First �޴��� �����Ű�� t or T�� ���
			deleteFirst(headnode);				//deleteFirst �Լ��� ȣ���Ͽ� ���� ����Ʈ�� ù��° ��带 ����
			break;								//switch�� Ż��
		case 'r': case 'R':						//command�� Invert List �޴��� �����Ű�� r or R�� ���
			invertList(headnode);				//invertList �Լ��� ȣ���Ͽ� ���� ����Ʈ�� �������� ����
			break;								//switch�� Ż��
		case 'q': case 'Q':						//command�� Quit �޴��� �����Ű�� q or Q�� ���
			freeList(headnode);					//freeList �Լ��� ȣ���Ͽ� ���� ����Ʈ�� ����
			break;								//switch�� Ż��
		default:								//command�� ���� ��� �̿��� ���ڸ� �Է����� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");	//ERROR message ���
			break;								//switch�� Ż��
		}

	} while (command != 'q' && command != 'Q');	//����ڰ� q or Q�� �Է��ϱ� ������ do-while�� ��� ����

	return 1;
}
headNode* initialize(headNode* h) {								//���� ����Ʈ�� head�� ����Ű�� ����ü ������ ������ �̿��Ͽ� ���� ����Ʈ�� �ʱ�ȭ�ϴ� �Լ� ����
	if (h != NULL)												//���� h�� ���� ����Ʈ�� head�� ����Ű�� �ִٸ�
		freeList(h);											// freeList �Լ� ȣ���Ͽ� �ʱ�ȭ ����

	headNode* temp = (headNode*)malloc(sizeof(headNode));		//���� ����Ʈ�� head�� �ּҸ� ����ų �� �ִ� ���� �޸��� �ּҸ� temp�� ����
	temp->first = NULL;											//temp�� NULL�� �����Ͽ� ���� �ƹ��͵� pointing�ϰ� ���� ����

	return temp;												//temp�� ����� �ּҸ� ��ȯ
}
int freeList(headNode* h) {										//���� ����Ʈ�� head�� ����Ű�� ����ü ������ ������ �̿��Ͽ� ������ ����� �޸� ����
	listNode* p = h->first;										//���� ����Ʈ�� head�� ��� �ּҸ� p�� ����

	listNode* prev = NULL;										//�޸� ������ ����� �ּҸ� �����ϴ� ����ü ������ ���� �� NULL�� �ʱ�ȭ
	while (p != NULL) {											//���� ����Ʈ�� ������ ��忡 �����ϱ� ������
		prev = p;												//prev�� p�� �ּҸ� �����Ͽ� ���� ����Ʈ�� head ��带 point
		p = p->link;											//������ ����� ���� ����� �ּҸ� p�� ����
		free(prev);												//prev�� �ּҿ� �ش��ϴ� ����� ���� �޸� ����
	}
	free(h);													//���� ����Ʈ�� head�� ����Ű�� �ִ� ����ü ������ ����

	return 0;
}
int insertFirst(headNode* h, int key) {							//���� ����Ʈ�� head�� ������ key���� �̿��� ���ο� ��带 ù��° ���� �����ϴ� �Լ� ����
	listNode* node = (listNode*)malloc(sizeof(listNode));		//listNode ũ�⸸ŭ�� ���� �޸��� �ּҸ� �޾Ƽ� ���ο� ���� ���

	if (h == NULL) {											//���� ����Ʈ�� �ʱ�ȭ�� �Ͼ�� �ʾ� head�� �ּҰ� NULL�̶��
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message ���
		return -1;
	}
	node->key = key;											//���ο� ����� data field�� key�� ����
	node->link = h->first;										//���ο� ��尡 ���� ����Ʈ�� head ���� ���� if. head ��尡 ���ٸ� NULL ����
	h->first = node;											//���� ����Ʈ�� ù��° ��尡 �ٲ�����Ƿ� head ��带 ���ο� ���� ����

	return 0;
}
int insertNode(headNode* h, int key) {								//���� ����Ʈ�� head�� ������ key���� �̿��Ͽ� key������ ū data�� ���� ��� �տ� �����ϴ� �Լ� ����
	listNode *search = (listNode *)malloc(sizeof(listNode));		//listNode ũ�⸸ŭ�� ���� �޸𸮸� �Ҵ�޾� ���ο� ���� ���
	listNode *previous = NULL;										//���� ����� ���� ���� ����� �������� ���� NULL�� �ʱ�ȭ
	listNode *now = NULL;											//head ������ ���� ����Ű�� �ִ� ��带 ǥ���ϱ� ���� ������ ���� �� �ʱ�ȭ
	search->key = key;												//������ ����� data field�� key���� ����

	if (h == NULL) {												//���� ����Ʈ�� �ʱ�ȭ�� �Ͼ�� �ʾ� head�� �ּҰ� NULL�̶��
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message ���
		return -1;
	}
	else if (h->first == NULL) {									//���� head ����� �ּҰ� NULL ��, ���� ����Ʈ�� ��尡 �������� �ʴٸ�
		search->link = NULL;										//ó������ ������ ����̹Ƿ� ������ ��带 �������� ����ų ��尡 �����Ƿ� NULL ����
		h->first = search;											//search�� ù��° ��尡 �Ǿ����Ƿ� head ��带 search�� ����

		return key;													//key�� ��ȯ
	}
	else {															//���� ����Ʈ�� ��尡 �ϳ� �̻��� ���� ���
		now = h->first;												//head ������ ���� ����Ű�� �ִ� ��带 ǥ���ϱ� ���� haed ����� �ּ� ����
		for (; now != NULL; previous = now, now = now->link) {		//���� ����Ű�� �ִ� ��ġ�� ������ ��带 ����� ������ ��� ���� ��带 ����Ű�� ���� for��
			if (now == h->first && key <= now->key) {				//���� ��ġ�� head ���� ���� �����ϰ��� �ϴ� key���� head ����� data���� �۴ٸ�
				search->link = now;									//������ ��忡 ���� ����� �ּҸ� �����Ͽ� head ��带 ����Ű���� ��
				h->first = search;									//head ��忡 ������ ����� �ּҸ� �����Ͽ� �� ��带 ����Ű���� �Ͽ� ���� ����Ʈ�� ����

				return key;											//key�� ��ȯ
			}
			else if (key <= now->key) {								//���� ����� data���� �����ϰ��� �ϴ� key�� �� ���� ���
				search->link = now;									//������ ��尡 ���� ����� �տ� ��ġ�ؾ� �ϹǷ� ������ ��尡 ���� ����� �ּҸ� �����Ͽ� pointing
				previous->link = search;							//���� ����� ���� ���� ������ ��带 �����Ѿ� �ϹǷ� search�� �ּ� ����

				return key;											//key�� ��ȯ
			}
		}
		if (previous->key <= key) {									//�Լ��� return���� �ʰ� for���� Ż���ߴٴ� ���� key���� ��� ����� data���� Ŭ ��쿡 �ش��ϴ� ���ǹ�
			search->link = now;										//������ ��尡 ���� ����Ʈ�� �������� ���ԵǾ� �ϹǷ� ���� NULL���� now�� �ּҸ� ����
			previous->link = search;								//���� ����� ���� ���� ������ ��带 �����Ѿ� �ϹǷ� search�� �ּ� ����

			return key;												//key�� ��ȯ
		}
	}
}int insertLast(headNode* h, int key) {								//���� ����Ʈ�� head�� ������ key���� �̿��� ���ο� ��带 ������ ��� �ڿ� ������ �Լ� ����
	listNode *input = (listNode *)malloc(sizeof(listNode));			//listNode ũ�⸸ŭ�� ���� �޸��� �ּҸ� �޾Ƽ� ���ο� ���� ���
	listNode *now = NULL;											//head ������ ���� ����Ű�� �ִ� ��带 ǥ���ϱ� ���� ������ ���� �� �ʱ�ȭ
				
	input->key = key;												//������ ����� data field�� ������ key ����

	if (h == NULL) {												//���� ����Ʈ�� �ʱ�ȭ�� �Ͼ�� �ʾ� head�� �ּҰ� NULL�̶��
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message ���
		return -1;
	}
	else if (h->first == NULL) {									//���� head ����� �ּҰ� NULL ��, ���� ����Ʈ�� ��尡 �������� �ʴٸ�
		input->link = NULL;											//ó������ ������ ����̹Ƿ� ������ ��带 �������� ����ų ��尡 �����Ƿ� NULL ����
		h->first = input;											//search�� ù��° ��尡 �Ǿ����Ƿ� head ��带 search�� ����

		return key;													//key�� ��ȯ
	}
	now = h->first;													//���� ����Ʈ�� head ����� �ּҸ� �����Ͽ� ù��° ������ �����ϵ��� ��
	for (; now->link != NULL; now = now->link);						//���� ��ġ�� ������ ��尡 �Ǳ� ������ ���� ����� ��ġ�� �̵��ϸ� ������ ��忡 �����ϱ� ���� for��
	input->link = now->link;										//������ ��尡 ���� ����� �ּҸ� �����Ͽ� pointing
	now->link = input;												//���� ��ġ�� ��尡 ������ ��带 ������ ���� ����Ʈ�� ������ �� �ֵ��� ���ο� ����� �ּ� ����

	return key;														//key�� ��ȯ
}
int deleteFirst(headNode* h) {										//���� ����Ʈ�� head�� �̿��Ͽ� ù��° ��带 �����ϴ� �Լ� ����
	listNode *temp = (listNode *)malloc(sizeof(listNode));			//������ ����� �ּҸ� ������ ������ ��带 listNode ũ�⸸ŭ�� ���� �޸� �Ҵ�

	if (h == NULL) {												//���� ����Ʈ�� �ʱ�ȭ�� �Ͼ�� �ʾ� head�� �ּҰ� NULL�̶��
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message ���
		return -1;
	}
	else if (h->first == NULL) {									//���� head ����� �ּҰ� NULL ��, ���� ����Ʈ�� ��尡 �������� �ʴٸ�
		printf(">>> This Linked List have not node!! <<<\n");		//head�� �ּҴ� ������ ���� node�� ������ ���� �ʾƼ� ERROR message ���

		return -1;
	}
	temp = h->first;												//���� ����Ʈ�� ù��° ����� head ����� �ּҸ� ������ ��忡 ����
	h->first = temp->link;											//head ��尡 ����Ű�� ��尡 ���ο� head ��尡 �Ǳ� ������ �ش� ����� �ּҸ� head ��带 ����Ű�� �����Ϳ� ����
	free(temp);														//���� ����Ʈ�� ù��° ����� ������ head ����� �޸𸮸� �������� ����
	printf("Delete First node\n");

	return 0;
}
int deleteNode(headNode* h, int key) {							//���� ����Ʈ�� head�� ������ key���� �̿��� key�� ���� data field�� ���� ��带 �����ϴ� �Լ� ����
	listNode *temp = (listNode *)malloc(sizeof(listNode));		//listNode ũ�⸸ŭ�� ���� �޸��� �ּҸ� �Ҵ�޾� ������ ���� ���
	listNode *previous = NULL;									//���� ����� ���� ��带 ����Ű��, ������ ��� ��, ���� ��带 �̾��ֱ� ���� �ʿ��� �����͸� NULL�� �ʱ�ȭ
	listNode *now = NULL;										//head ������ ���� ����Ű�� �ִ� ��带 ǥ���ϱ� ���� ������ ���� �� �ʱ�ȭ
		
	if (h == NULL) {											//���� ����Ʈ�� �ʱ�ȭ�� �Ͼ�� �ʾ� head�� �ּҰ� NULL�̶��
		printf(">>> This Linked List is not initialized! <<<\n");//ERROR message ���
		return -1;
	}
	else if (h->first == NULL) {								//���� head ����� �ּҰ� NULL ��, ���� ����Ʈ�� ��尡 �������� �ʴٸ�
		printf(">>> This Linked List have not node!! <<<\n");	//head�� �ּҴ� ������ ���� node�� ������ ���� �ʾƼ� ERROR message ���

		return -1;
	}
	now = h->first;												//���� ��ġ ��, ������ ����� �ּҸ� ������ �����͸� head ����� �ּҷ� �ʱ�ȭ
	for (; now != NULL; previous = now, now = now->link) {		//���� ��ġ�� ������ ��带 ����� ������ ���� ���� ���� ��带 ���� ���� ���� �̵��ϸ� ���� ���ϱ� ���� for��
		if (now == h->first && key == now->key) {				//���� ���� ��ġ�� head ����̰� �� ��尡 �����ϰ��� �ϴ� key���� �����ϴٸ�
			temp = now;											//������ ��忡 ��ġ�� ����� �ּҸ� ����
			h->first = now->link;								//head ��忡 ���� ����� ���� ����� �ּҸ� �����Ͽ� ���� ����Ʈ�� ������ �ʵ��� ��
			free(temp);											//������ ����� �ּҰ� ��� ������ ��带 �����Ͽ� key���� ����� ��� ����
			printf("Delete %d\n", key);
			return 0;
		}
		else if (now->key == key) {								//���� ��ġ�� data���� �����ϰ��� �ϴ� key�� ������ head ��尡 �ƴ϶��
			temp = now;											//������ ��忡 ��ġ�� ���� ����� �ּҸ� ����
			previous->link = now->link;							//���� ��尡 ���� ����� ���� ��带 ������ ��尡 �����Ǵ��� ���� ����Ʈ�� ������ �ʵ��� ��
			free(temp);											//������ ��带 ����Ű�� ������ ��带 �������� key���� ������ data field�� ���� ��� ����
			printf("Delete %d\n", key);
			return 0;
		}
	}
	printf(">>> Not found %d <<<\n", key);						//���� ����Ʈ�� ������ ������ Ž�������� ������ key���� ã�� ���ߴٸ� ERROR message ���
	return -1;
}
int deleteLast(headNode* h) {										//���� ����Ʈ�� head�� �̿��Ͽ� ������ ��带 �����ϴ� �Լ� ����
	listNode *previous = NULL;										//���� ����� ���� ��带 ����Ű��, ������ ����� ��, �ڸ� �̾��ֱ� ���� ������ ���� �� NULL�� �ʱ�ȭ
	listNode *now = NULL;											//head ������ ���� ����Ű�� �ִ� ��带 ǥ���ϱ� ���� ������ ���� �� �ʱ�ȭ

	if (h == NULL) {												//���� ����Ʈ�� �ʱ�ȭ�� �Ͼ�� �ʾ� head�� �ּҰ� NULL�̶��
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message ���
		return -1;
	}
	else if (h->first == NULL) {									//���� head ����� �ּҰ� NULL ��, ���� ����Ʈ�� ��尡 �������� �ʴٸ�
		printf(">>> This Linked List have not node!! <<<\n");		//head�� �ּҴ� ������ ���� node�� ������ ���� �ʾƼ� ERROR message ���

		return -1;
	}
	now = h->first;													//������ ����� �ּҸ� ������ �����͸� head ����� �ּҷ� �ʱ�ȭ
	for (; now->link != NULL; previous = now, now = now->link);		//���� ��ġ�� ������ ��忡 �����ϱ� ������ ���� ���� ���� ��带 ���� ���� ���� �̵��ϱ� ���� for��
	if (previous != NULL)											//���� ����� ���� ��尡 NULL�� �ƴ� ��� ��, ù��° ��尡 �ƴ� ���
		previous->link = now->link;									//������ ��� ������ ��尡 ������ ��尡 ����Ű�� NULL�� pointing �ϵ��� �ϱ� ���� ���� ��尡 ����Ű�� �ּ� ����
	else															//���� ����� ���� ��尡 NULL ��, ���� ��尡 ���� ����Ʈ�� ù��° ����� ���
		h->first = NULL;											//previous ���� ����Ű�� �ִ� ��尡 �����Ƿ� head ��带 ���� ��尡 ����Ű�� �ּ� ��, NULL�� ����
	free(now);														//������ ��忡 ��ġ���ִ� ���� ��带 ���������� ������ ��� ����
	printf("Delete Last node\n");

	return 0;
}
int invertList(headNode* h) {										//���� ����Ʈ�� head�� �̿��Ͽ� ���� ����Ʈ�� �������� �ٲٴ� �Լ� ����
	listNode *end, *mid = NULL, *now = NULL;						//���� ����Ʈ�� �������� ������ �� �������� ���� �����ϱ� ���� 3���� ����ü ������ ���� �� �ʱ�ȭ
	if (h == NULL) {												//���� ����Ʈ�� �ʱ�ȭ�� �Ͼ�� �ʾ� head�� �ּҰ� NULL�̶��
		printf(">>> This Linked List is not initialized! <<<\n");	//ERROR message ���
		return -1;
	}
	else if (h->first == NULL) {									//���� head ����� �ּҰ� NULL ��, ���� ����Ʈ�� ��尡 �������� �ʴٸ�
		printf(">>> This Linked List have not node!! <<<\n");		//head�� �ּҴ� ������ ���� node�� ������ ���� �ʾƼ� ERROR message ���

		return -1;	
	}
	else {															//���� ����Ʈ�� �ϳ� �̻��� ��尡 ����Ǿ� �ִٸ�
		now = h->first;												//���� ����Ʈ�� ù��° ������ �����ϱ� ���� ù��° ����� �ּ� ����
		for (; now != NULL;) {										//���� ��ġ�� ��尡 ������ ��带 ����� ������ ���� ����Ʈ�� �������� �ձ� ���� for��
			end = mid;												//������ ����Ʈ���� �����ؾ� �� ���� ����ϱ� ���� ���� ���� ��ġ�� ������ ����� �ּҸ� ����
			mid = now;												//���� ����Ʈ�� ������ �ڽ��� ���� ��带 ����Ű���� �ϱ� ���� �ϴ� ���� ����� �ּ� ����
			now = now->link;										//�������� ����� �� mid�� ���� ����� �ּҸ� �Ҿ���� �� �����Ƿ� ���� ��带 ���� ����� �ּҸ� �����Ͽ� �̵�
			mid->link = end;										//mid ������ ����� �ּҸ� ������ end�� �ּҸ� �����Ͽ� ���� ����Ʈ�� �������� ����
		}	
		h->first = mid;												//�����Ǳ� ������ ���� ����Ʈ�� head ��带 ������ ����Ʈ�� head ��带 ����Ű�� ����� �ּҸ� �����Ͽ� head ����

		return 0;
	}
}
void printList(headNode* h) {					//���� ����Ʈ�� head�� �̿��Ͽ� ���� ����Ʈ�� �� ������ data field���� ����ϴ� �Լ� ����
	int i = 0;									//���� ����Ʈ�� index ��ȣ�� ǥ���ϱ� ���� ������ ���� ���� �� 0���� �ʱ�ȭ
	listNode* p;								//���� ����Ʈ�� head ����� �ּҸ� ������ ����ü ������ ���� ����

	printf("\n---PRINT\n");

	if (h == NULL) {							//���� ����Ʈ�� head�� NULL ��, � ���� ����Ʈ�� ����Ű�� ���� �ʴٸ�
		printf("Nothing to print....\n");		//ERROR message ���
		return;
	}

	p = h->first;								//���� ����Ʈ�� head ����� �ּҸ� �����Ͽ� ù��° ������ ���� ����

	while (p != NULL) {							//���� ����� ��ġ�� ������ ����� ��ġ�� ����� ������ �� ����� data field���� ����ϱ� ���� for��
		printf("[ [%d]=%d ] ", i, p->key);		//ù��° ������ ������ �������� data field���� index��ȣ�� �Բ� ���
		p = p->link;							//���� ��ġ���� ���� ����� �ּҸ� �����Ͽ� ���� ���� �̵�
		i++;									//�̿� �Բ� index ��ȣ�� ����
	}

	printf("  items = %d\n", i);				//���� ����Ʈ�� ����ִ� ����� �� ���
}
