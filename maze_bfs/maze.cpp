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
	int openCount = 0; //처음엔 비어있음
	int closedCount = 0; //처음엔 비어있음
	int i, len = 0;

	open[openCount++] = init; //open에게 최초값을 집어넣는다. 뒤에 ++이므로 init이 들어갈때는 0으로 들어가고 그다음 하나증가

	while (openCount > 0 && openCount < GMAX && closedCount < GMAX) 
	{
		cur = popMin(open, openCount--); //하나꺼냈으니까 open이 하나 줄어듬
		closed1[closedCount++] = cur; //꺼내온 애는 closed에 넣음

		if (cur->guessing == 0) //게싱이 0이란 얘기는 이것이 골이라는 얘기 
		{
			for (i = 0; i < cur->len; i++)
				seq[i] = cur->sequence[i];

			len = cur->len; //경로를 담는 과정
			break; 
		}
		else //최대 네개를 만들어서 open에 집어넣자
		{
			for (i = N; i <=E; i++) //4번 돌아
			{
				next = getNextState(cur, goal1, goal2, (Move)i); 

				if (next != NULL && !inClosed(closed1, closedCount, next)) 
					addAtLast(open, next, openCount++);
				else if (next != NULL) //널이 아닌데 클로즈에 있던 애야.그럼 free
					free(next); 
			}
		}
	}
	clean(open, openCount); //malloc으로 받아놓은 애들 free
	clean(closed1, closedCount);

	return len;
}

void clean(State **array, int len) //어레이를 받아서 그 길이만큼 free
{
	int i;
	for (i = 0; i < len; i++)
		free(array[i]);
}

