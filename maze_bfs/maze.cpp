#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "maze.h"
#include "heap.h"

State* getNextState(State *curState, State *goal1, State *goal2, Move m)
{	
	State *next;

	next = NULL;
	
	switch (m)
	{
	case N :
		if (curState->curR > 1 && curState->len < MAX && curState->maze[curState->curR-1][curState->curC] == '.')
		{
			next = cloneState(curState); 
			next->curR--;
			next->sequence[next->len++] = m;
			next->guessing = compare(next,goal1,goal2);
		}
		break;
	case S :
		if (curState->curR < 11 && curState->len < MAX && curState->maze[curState->curR+1][curState->curC] == '.')
		{
		
			next = cloneState(curState);
			next->curR++;
			next->sequence[next->len++] = m;
			next->guessing = compare(next,goal1,goal2);
		}
		break;
	case W :
		if (curState->curC > 1 && curState->len < MAX && curState->maze[curState->curR][curState->curC-1] == '.')
		{
			
			next = cloneState(curState);
			next->curC--;
			next->sequence[next->len++] = m;
			next->guessing = compare(next,goal1,goal2);
			
		}
		break;
	case E :
		if (curState->curC < 11 && curState->len < MAX && curState->maze[curState->curR][curState->curC+1] == '.')
		{
			next = cloneState(curState);
			next->curC++;
			next->sequence[next->len++] = m; 
			next->guessing = compare(next,goal1,goal2);
		}
		break;
	}
	return next;
}

int compare(State *one, State *another1, State *another2)
{
	int i,j;
	int dist1,dist2;

	dist1 = abs(one->curR - another2->curR); //2-11 = 9
	dist2 = abs(one->curC - another1->curC); //0-11 = 11

	if(dist1 < dist2)
		return dist1;
	else if(dist1 = dist2)
		return dist2;
	else
		return dist2;
}

int compare2 (State *next, State *closed)
{
	if ((next->curR == closed->curR) && (next->curC == closed->curC))
		return 0; 
	else
		return 1;
}

int inClosed(State **closed1, int len, State *next) 
{
	int i;
	for (i = 0; i < len; i++)
	{
		if (compare2(next, closed1[i]) == 0)
			return 1; 
	}

	return 0; 
}

State* cloneState(State *curState)
{
	int i, j;
	State *next;
	next = (State*)malloc(sizeof(State));

	for (i = 0; i < 12; i++)
		for (j = 0; j < 12; j++)
			next->maze[i][j] = curState->maze[i][j]; 

	next->curR = curState->curR;
	next->curC = curState->curC;
	next->len = curState->len; 

	for (i = 0; i < curState->len; i++)
		next->sequence[i] = curState->sequence[i]; 

	next->guessing = curState->guessing;

	return next;
}

int solvemaze(State *init, State *goal1, State *goal2, Move *seq)
{
	State *open[GMAX];
	State *closed1[GMAX];
	State *cur; //
	State *next; //
	int openCount = 0; //ó���� �������
	int closedCount = 0; //ó���� �������
	int i, len = 0;

	open[openCount++] = init; //open���� ���ʰ��� ����ִ´�. �ڿ� ++�̹Ƿ� init�� ������ 0���� ���� �״��� �ϳ�����

	while (openCount > 0 && openCount < GMAX && closedCount < GMAX) 
	{
		cur = popMin(open, openCount--); //�ϳ��������ϱ� open�� �ϳ� �پ��
		closed1[closedCount++] = cur; //������ �ִ� closed�� ����

		if (cur->guessing == 0) //�Խ��� 0�̶� ���� �̰��� ���̶�� ��� 
		{
			for (i = 0; i < cur->len; i++)
				seq[i] = cur->sequence[i];

			len = cur->len; //��θ� ��� ����
			break; 
		}
		else //�ִ� �װ��� ���� open�� �������
		{
			for (i = N; i <=E; i++) //4�� ����
			{
				next = getNextState(cur, goal1, goal2, (Move)i); 

				if (next != NULL && !inClosed(closed1, closedCount, next)) 
					addAtLast(open, next, openCount++);
				else if (next != NULL) //���� �ƴѵ� Ŭ��� �ִ� �־�.�׷� free
					free(next); 
			}
		}
	}
	clean(open, openCount); //malloc���� �޾Ƴ��� �ֵ� free
	clean(closed1, closedCount);

	return len;
}

void clean(State **array, int len) //��̸� �޾Ƽ� �� ���̸�ŭ free
{
	int i;
	for (i = 0; i < len; i++)
		free(array[i]);
}

