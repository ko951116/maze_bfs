#include "maze.h"
#include "heap.h"

State* popMin(State** array, int size)
{
	State* min;

	min = array[0];
	array[0] = array[size - 1];
	heapify(array, 0, size - 1);

	return min;
}

void addAtLast(State** array, State*node, int size) //�߰��� ��ġ�� ��̰� �հ�, ���Ӱ� �߰��� ��尡 �ְ�, ���� ���� ��� ���ִ����� size
	//�ǵڿ� �ٰ� �߰� �ϰ� ���� ���� ������ ��.
{
	array[size] = node;
	reverseHeapify(array, size);
}

void reverseHeapify(State** array, int index)
{
	State *temp;
	int parent = (index - 1) / 2;

	if (index > 0 && (array[parent]->len + array[parent]->guessing) > (array[index]->len + array[index]->guessing))
	{
		temp = array[index];
		array[index] = array[parent];
		array[parent] = temp;
		reverseHeapify(array, parent);
	}
}

void heapify(State** array, int index, int size)
{
	State *temp;
	int less = index * 2 + 1;

	if (less >= size)
		return;

	if (index * 2 + 2 < size && (array[index * 2 + 1]->len + array[index * 2 + 1]->guessing) > (array[index * 2 + 2]->len + array[index * 2 + 2]->guessing))
		less = index * 2 + 2;

	if ((array[index]->len + array[index]->guessing) > (array[less]->len + array[less]->guessing))
	{
		temp = array[index];
		array[index] = array[less];
		array[less] = temp;
		heapify(array, less, size);
	}
}

void buildHeap(State** array, int size)
{
	int i;
	for (i = size - 1; i >= 0; i--)
		heapify(array, i, size);
}