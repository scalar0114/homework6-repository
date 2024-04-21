/**
 * circularQ.c
 *
 * School of Computer Science,
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct
{
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element *item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	printf("[----- [hyunseung] [2023041001] -----]\n");

	QueueType *cQ = createQueue();
	element data;
	char command;

	do
	{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'i':
		case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd':
		case 'D':
			deQueue(cQ, &data);
			break;
		case 'p':
		case 'P':
			printQ(cQ);
			break;
		case 'b':
		case 'B':
			debugQ(cQ);
			break;
		case 'q':
		case 'Q':
			freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
	if (cQ == NULL)
		return 1;
	free(cQ);
	return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

/* complete the function */
int isEmpty(QueueType *cQ) // front와 rear가 같으면 비어있는 상태
{
	return (cQ->front == cQ->rear);
}

/* complete the function */
int isFull(QueueType *cQ) // front와 rear가 한칸 차이나면 꽉 찬 상태
{
	return ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front);
}

/* complete the function */
void enQueue(QueueType *cQ, element item) // rear를 한칸 뒤로 옮기고 그 자리에 item을 넣는다.
{
	if (isFull(cQ)) // isFull함수를 통해 꽉 찼는지 확인
	{
		printf("Queue is full. Cannot enqueue.\n");
		return;
	}
	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear를 한칸 뒤로 옮김
	cQ->queue[cQ->rear] = item;					// rear에 item을 넣음
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) // front를 한칸 뒤로 옮기고 그 자리에 있는 값을 item에 넣는다.
{
	if (isEmpty(cQ)) // isEmpty함수를 통해 비어있는지 확인
	{
		printf("Queue is empty. Cannot dequeue.\n");
		return;
	}
	cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; // front를 한칸 뒤로 옮김
	*item = cQ->queue[cQ->front];				  // front에 있는 값을 item에 넣음
}

void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while (i != last)
	{
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;
	}
	printf(" ]\n");
}

void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front)
		{
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}