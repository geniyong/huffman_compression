#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

// 허프만 binary tree 구조체
struct node {
	int count=0;
	char alpha;
	struct node *left=NULL, *right=NULL;//바이너리트리에서사용노드
	char code[16];
	struct node *before; //큐에서 사용노드(리스트관리)
	struct node *next;//큐에서 사용노드
};
typedef struct node Node;

struct huffnode {
	struct node left;
	struct node right;
};

char code[16];


typedef node* nptr;
typedef struct queue {
	int count;
	nptr front;
	nptr rear;
}qu;


Node frequency[27];
Node minheapA[28];
Node sortarray[27];
Node huffarray[27];


qu* create_queu()
{
	qu* new_qu = (qu*)malloc(sizeof(qu));
	new_qu->count = 0;
	new_qu->front = NULL;
	new_qu->rear = NULL;
	return new_qu;
}

void insert_rear(qu* qptr, int count, char alpha)
{
	nptr new_node = (nptr)malloc(sizeof(node));
	new_node->count = count;
	new_node->alpha = alpha;
	new_node->before = NULL;
	new_node->next = NULL;

	if (qptr->count == 0) {
		qptr->front = new_node;
		qptr->rear = new_node;
	}

	else {
		qptr->rear->next = new_node;
		new_node->before = qptr->rear;
		qptr->rear = new_node;
		
	}
	qptr->count++;
}

nptr insert_node()
{
	nptr new_node = (nptr)malloc(sizeof(node));

	return new_node;
}

node delete_front(qu* qptr)
{
	if (qptr->count == 0) {
		printf("ERROR:큐가비어있습니다");
		return;
	}
	else {
		nptr tmp = qptr->front;
		qptr->front = tmp->next;
		node tmp_count = *tmp;
		free(tmp);
		qptr->count--;
		return tmp_count;
	}
}

void destroy_queue(qu* qptr)
{
	while (qptr->count != 0) {
		delete_front(qptr);
	}
	free(qptr);
	printf("우선순위큐가 제거되었습니다\n");
}

/*void givecode(int k)
{
	int i = 0;
	int j = 0;
	int c = 0;

	//왼쪽트리먼저 할당
	while (huffarray[k].left!=NULL)
	{
		if (huffarray[k].left->alpha != 0)
		{
			BC[i].alpha = huffarray[k].left->alpha;
			while (j <= c)
			{
				BC[i].Bcode[j] = 0;
				j++;
			}
			k--;
			i++;
		}
		else
		{
			c++;
		}
	}

	huffarray[k].right;
}*/

void givecode(Node *node, int depth) 
{
	int i;
	if (node->left || node->right)
	{ 
		code[depth] = '0';
		if (node->left)
			givecode(node->left, depth + 1);

		code[depth] = '1';
		if (node->right)
			givecode(node->right, depth + 1);
	}
	else if (node)
	{ 
		code[depth] = NULL;
		for (i = 0; i < depth; i++)
		{
			node->code[i] = code[i];
		}
		
	}
}

void huffmancode(int exist)
{
	int i = 0;
	int k = 0;
	qu* priqu = create_queu(); // 우선순위 큐 생성
	qu* sumqu = create_queu(); // 두 알파벳 합한 노드 저장 큐
	huffnode hn[27];
	Node tmp_qu1;
	Node tmp_qu2;
	nptr new_node;

	for (i = 0; i < exist; i++)
	{
		insert_rear(priqu, sortarray[i].count, sortarray[i].alpha);	
	}
	
	while (priqu->count > 0)
	{
		if (sumqu->front == NULL)
		{
			tmp_qu1 = delete_front(priqu);
			tmp_qu2 = delete_front(priqu);
			insert_rear(sumqu, tmp_qu1.count + tmp_qu2.count, NULL);
			hn[k].left = tmp_qu2;
			hn[k].right = tmp_qu1;
			k++;
		}
	
		else
		{
			tmp_qu1 = delete_front(sumqu);
			tmp_qu2 = *priqu->front;
			while (tmp_qu2.next != NULL;)
			{
				if (tmp_qu1.count < tmp_qu2.count)
				{
					new_node = insert_node();
					*new_node = tmp_qu1;

					if (tmp_qu2.next == priqu->front->next)
						priqu->front = new_node;

					tmp_qu2.before->next->before = new_node;
					new_node->next = tmp_qu2.before->next;
					tmp_qu2.before->next = new_node;

				}
				else
				{
					tmp_qu2 = *tmp_qu2.next;
				}
			}

			if (tmp_qu2.next == NULL)
			{
				if (tmp_qu1.count < tmp_qu2.count)
				{
					new_node = insert_node();
					*new_node = tmp_qu1;

					if (tmp_qu2.next == priqu->front->next)
						priqu->front = new_node;

					tmp_qu2.before->next->before = new_node;
					new_node->next = tmp_qu2.before->next;
					tmp_qu2.before->next = new_node;

				}
			}
		}
	}


	//노가다코드

	int j = 1;
	int k = 0;
	int p = 0;

	if (sortarray[i].count != 0)
	{
		if (sortarray[j].count == 0)
		{
			huffarray[k] = sortarray[i];
			huffarray[k].right = &sortarray[i];
			givecode(&huffarray[k], 0);
			return;
		}
		else
		{
			huffarray[k].count = sortarray[i].count + sortarray[j].count;
			huffarray[k].right = &sortarray[i];
			huffarray[k].left = &sortarray[j];
			i += 2;
			j += 2;
			k++;
		}
	}
	else
	{
		printf("Not Exist Any Letter");
		return;
	}

	while (sortarray[i].count != 0 && sortarray[j].count != 0)
	{
		if (p < 27)
		{
			if (huffarray[p].count != 0)
			{
				if (huffarray[p + 1].count != 0 && huffarray[p + 1].count < sortarray[i].count)
				{
					huffarray[k].count = huffarray[p].count + huffarray[p + 1].count;
					huffarray[k].right = &huffarray[p];
					huffarray[k].left = &huffarray[p + 1];
					k++;
					p += 2;
				}
				else
				{
					if (huffarray[p].count <= sortarray[i].count)
					{
						huffarray[k].count = sortarray[i].count + huffarray[p].count;
						huffarray[k].right = &huffarray[p];
						huffarray[k].left = &sortarray[i];
						p++;
						k++;
						i++;
						j++;
					}

					else if (huffarray[p].count <= sortarray[j].count)
					{
						huffarray[k].count = sortarray[i].count + huffarray[p].count;
						huffarray[k].right = &sortarray[i];
						huffarray[k].left = &huffarray[p];
						p++;
						k++;
						i++;
						j++;
					}

					else
					{
						huffarray[k].count = sortarray[i].count + sortarray[j].count;
						huffarray[k].right = &sortarray[i];
						huffarray[k].left = &sortarray[j];
						i += 2;
						j += 2;
						k++;
					}
				}
			}

			else
			{
				huffarray[k].count = sortarray[i].count + sortarray[j].count;
				huffarray[k].right = &sortarray[i];
				huffarray[k].left = &sortarray[j];
				i += 2;
				j += 2;
				k++;
			}
		}
	}

	while (sortarray[i].count != 0 && sortarray[j].count == 0)
	{
		if (p < 27)
		{
			if (huffarray[p + 1].count != 0 && huffarray[p + 1].count < sortarray[i].count)
			{
				huffarray[k].count = huffarray[p].count + huffarray[p + 1].count;
				huffarray[k].right = &huffarray[p];
				huffarray[k].left = &huffarray[p + 1];
				k++;
				p += 2;
			}
			else
			{
				if (huffarray[p].count <= sortarray[i].count)
				{
					huffarray[k].count = sortarray[i].count + huffarray[p].count;
					huffarray[k].right = &huffarray[p];
					huffarray[k].left = &sortarray[i];
					p++;
					k++;
					i++;
				}
				else
				{
					huffarray[k].count = sortarray[i].count + huffarray[p].count;
					huffarray[k].right = &sortarray[i];
					huffarray[k].left = &huffarray[p];
					p++;
					k++;
					i++;
				}
			}
		}
	}

	while (sortarray[i].count == 0)
	{
		if (p < 27)
		{
			if (huffarray[p].count == 0)
			{
				k--;
				givecode(&huffarray[k], 0);
				return;
			}
			if (huffarray[p + 1].count != 0)
			{
				huffarray[k].count = huffarray[p].count + huffarray[p + 1].count;
				huffarray[k].right = &huffarray[p];
				huffarray[k].left = &huffarray[p + 1];
				p+=2;
				k++;
			}
			else
			{
				k--;
				givecode(&huffarray[k], 0);
				return;
			}
		}
	}
}
void heapify(int head)//insert or delete 후 히피파이
{
	int leftchild = head * 2, rightchild = head * 2 + 1;

	if (minheapA[rightchild].count != NULL)
	{
		if (minheapA[leftchild].count < minheapA[rightchild].count)
		{
			minheapA[27] = minheapA[head];
			minheapA[head] = minheapA[leftchild];
			minheapA[leftchild] = minheapA[27];
			heapify(leftchild);
		}
		else
		{
			minheapA[27] = minheapA[head];
			minheapA[head] = minheapA[rightchild];
			minheapA[rightchild] = minheapA[27];
			heapify(rightchild);
		}
	}

	else if (minheapA[leftchild].count != NULL)
	{
		if (minheapA[leftchild].count < minheapA[head].count)
		{
			minheapA[27] = minheapA[head];
			minheapA[head] = minheapA[leftchild];
			minheapA[leftchild] = minheapA[27];
			heapify(leftchild);
		}
	}
	else
		return;

}
void deletemin(int tail)
{
	minheapA[1] = minheapA[tail];
	minheapA[tail].count = NULL;
	heapify(1);
}
void heapsort(int exist)
{
	int i = 0;
	while (exist)
	{
		sortarray[i] = minheapA[1];
		deletemin(exist);
		exist--;
		i++;
	}
}

void arraysetting() //알파벳 구조체 배열 세팅(0번방부터 'a'부터 시작)
{
	int i;
	char start = 'a';
	for (i = 0; i < 26; i++)
	{
		frequency[i].alpha = start;
		start++;
	}

	/*
	for (i = 0; i < 26; i++)
	{
	printf("%c\n", frequency[i].alpha);
	}*/

}

void countalpha(FILE *input)
{
	int i;
	char letter;
	while (1) // 반복문을 시작합니다.
	{
		if (feof(input) != 0) // 파일을 끝까지 읽었는지 체크합니다. 
			break;

		letter = fgetc(input);
		printf("%c", letter); // 읽은 문자를 출력
		char start = 'a';
		for (i = 0; i < 26; i++)
		{
			if (letter == start)
			{
				frequency[i].count += 1;
				break;
			}
			else
				start++;
		}
	}

	printf("\n");

	for (i = 0; i < 26; i++)
	{
		if (frequency[i].count != 0)
		{
			printf("count %c : %d\n", frequency[i].alpha, frequency[i].count);
		}
	}
	system("pause");
}

void minheap(int exist, int half)
{
	int i,j;
	int child = 0;
	int leftchild;
	int rightchild;

	//printf("exist 중간점검 : %d\n", exist);

	leftchild = half * 2;
	rightchild = half * 2 + 1;
	
	/*printf("half 중간점검 : %d\n", half);
	printf("leftchild : %d\n", leftchild);
	printf("rightchild : %d\n", rightchild);*/

	if (half == exist / 2)
	{
		if (exist % 2 == 0)
			child = 1;
		else
			child = 2;
	}
	else
		child = 2;

	if (child == 2) //자식 둘을 우선비교
	{
		if (minheapA[leftchild].count < minheapA[rightchild].count)
		{
			if (minheapA[leftchild].count < minheapA[half].count)
			{
				minheapA[27] = minheapA[leftchild];
				minheapA[leftchild] = minheapA[half];
				minheapA[half] = minheapA[27];

				if (leftchild * 2 <= exist)
				{
					minheap(exist, leftchild);
				}
			}
		}
		else
		{
			if (minheapA[rightchild].count < minheapA[half].count)
			{
				minheapA[27] = minheapA[rightchild];
				minheapA[rightchild] = minheapA[half];
				minheapA[half] = minheapA[27];

				if (rightchild * 2 <= exist)
				{
					minheap(exist, rightchild);
				}
			}
		}

	}
	else //자식혼자라서 부모랑 바로 비교
	{
		if (minheapA[leftchild].count < minheapA[half].count)
		{
			minheapA[27] = minheapA[leftchild];
			minheapA[leftchild] = minheapA[half];
			minheapA[half] = minheapA[27];

			if (leftchild * 2 <= exist)
			{
				minheap(exist, leftchild);
			}

		}
	}

}

void comrate()
{

}

void main()
{
	int type = 0; // compressing or decompressing
	int exist=1, half=0;
	int i, j;
	char filename[30];
	FILE *input;

	//compress or decompress select
	arraysetting();

	// 압축할 텍스트파일 이름 입력받기
	printf("Text File Name For Compressing : ");
	scanf("%s", filename);

	// 입력받은 텍스트파일 오픈
	input = fopen(filename, "r");

	// 파일 오픈 체크 
	if (input == NULL)
	{
		printf("file open error!\n");
		system("pause");
		return;
	}
	countalpha(input);

	//하나이상 있는 알파벳들만 따로 array에 저장
	for (i = 0; i < 26; i++)
	{
		if (frequency[i].count != 0)
		{
			minheapA[exist] = frequency[i];
			exist++;
		}
	}
	j = exist;
	while (j < 27)
	{
		minheapA[j].count = NULL;
		j++;
	}

	//min heapify진행
	exist -= 1; // for문에서 exist는 실제 데이터개수보다 1만큼 더 많은 상태에서 종료
	half = exist / 2;
	j = half;

	for (i = 0; i < half; i++)
	{
		minheap(exist, j);
		j--;
	}

	printf("The initial min heap : ");

	for (i = 1; i<exist + 1; i++)
	{
		printf("%d ", minheapA[i].count);
	}
	system("pause");
		
	//힙정렬로 minimum 부터 정렬 - sortarray[] 에 저장
	heapsort(exist);

	printf("\nsortedarray : ");
	for (i = 0; i < exist; i++)
	{
		printf("%d ", sortarray[i].count);
	}
	printf("\nsortedletter : ");
	for (i = 0; i < exist; i++)
	{
		printf("%c ", sortarray[i].alpha);
	}
	system("pause");

	//huffman binary tree 생성
	huffmancode(exist);

	for (i = 0; i < exist; i++)
	{
		printf("%c : ", sortarray[i].alpha);
		for (j = 0; j < 16; j++)
		{
			printf("%c", sortarray[i].code[j]);
		}
		printf("\n");
	}
	system("pause");

}