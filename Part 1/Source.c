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
	Node* head = NULL, *tail, *newElement;
	int num;
	while (fscanf(f, "%d", &num))
	{
		if (head == NULL)
		{
			head = (Node*)malloc(sizeof(Node));
			head->num = num;
			tail = head;
		}
		else
		{
			newElement = (Node*)malloc(sizeof(Node));
			newElement->num = num;
			newElement->next = NULL;
			tail->next = newElement;
			tail = newElement;
			tail->next = num;
		}
	}
	fclose(f);
	return head;
}

int main() 
{

}