#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

struct node
{
	int num;
	struct node* next;
};

typedef struct node Node;

Node* ReadFile(char* filename)
{
	FILE* f = fopen(filename, "r");
	Node* head = NULL, * tail = NULL, * newElement;
	int num;
	while (!feof(f))
	{
		fscanf(f, "%d", &num);
		if (head == NULL)
		{
			head = (Node*)malloc(sizeof(Node));
			head->num = num;
			head->next = NULL;
			tail = head;
		}
		else
		{
			newElement = (Node*)malloc(sizeof(Node));
			newElement->num = num;
			newElement->next = NULL;
			tail->next = newElement;
			tail = newElement;
		}
	}
	fclose(f);
	return head;
}

void WriteFile(Node* queue, char* filename)
{
	FILE* f = fopen(filename, "w");
	Node* tmp;
	tmp = queue;
	while (tmp != NULL)
	{
		fprintf(f, "%d\n", tmp->num);
		tmp = tmp->next;
	}
	fclose(f);
}

void FreeMemory(Node* queue)
{
	Node* tmp = queue, * next = queue;
	while (next)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

double GetAverage(Node* queue)
{
	Node* tmp;
	tmp = queue;
	int sum, count;
	sum = 0;
	count = 0;
	while (tmp)
	{
		sum = sum + tmp->num;
		tmp = tmp->next;
		count++;
	}
	return (double)sum / count;
}

Node* RemoveOverAverage(Node* queue)
{
	Node* tmp, * prev;
	double average = GetAverage(queue);
	tmp = prev = queue;
	while (tmp)
	{
		if (tmp->num > average)
		{
			if (tmp == queue)
			{
				tmp = tmp->next;
				free(queue);
				queue = tmp;
				prev = tmp;
			}
			else
			{
				prev->next = tmp->next;
				free(tmp);
				tmp = prev->next;
			}
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return queue;
}

void PlacingSort(Node* queue)
{
	int tmp;
	Node* i, * j;
	i = queue;
	while (i->next != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (i->num > j->num)
			{
				tmp = i->num;
				i->num = j->num;
				j->num = tmp;
			}
			j = j->next;
		}
		i = i->next;
	}
}

void SortAfterPositive(Node* queue)
{
	Node* tmp = queue;
	Node* start = NULL;
	while (tmp->next != NULL && start == NULL)
	{
		if (tmp->num > 0)
			start = tmp->next;
		tmp = tmp->next;
	}
	if (start != NULL)
		PlacingSort(start);
}

int main()
{
	Node* queue = ReadFile("input.txt");
	WriteFile(queue, "output1.txt");
	RemoveOverAverage(queue);
	WriteFile(queue, "output2.txt");
	SortAfterPositive(queue);
	WriteFile(queue, "output3.txt");
	FreeMemory(queue);
}