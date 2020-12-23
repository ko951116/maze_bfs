#include <stdio.h>
#include <Windows.h>
#include "maze.h"

#define MAX_MAZE_X 100
#define MAX_MAZE_Y 100

void main()
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	double elapsedTime;

	State *init;
	State goal1, goal2;

	char colmaze[20][20];
	Move seq[MAX];
	int t=0, len;

	FILE *fr;
	int  i,j;

	int curx = 2, cury = 0;
	init = (State*)malloc(sizeof(State));

	if ( (fr = fopen("test.txt", "rt")) == NULL )
	{
		printf("\nfile open error!\n");
		return;
	}

	for ( i = 0; i < 12; i++ ){
		for ( j = 0; j < 13; j++ ){
			fscanf(fr,"%c", &init->maze[i][j]);
		}
	}
	fclose(fr);
	
	for (i = 0; i < 12; i++){
		for (j = 0; j <13; j++){
			colmaze[i][j] = init->maze[i][j];
		}
	}

	init->len = 0;
	init->curR = 2;//출발점row
	init->curC = 0;//출발점col

	goal1.curR = 4;//오른쪽에 있는 출구
	goal1.curC = 11;

	goal2.curR = 11;//왼쪽 아래에 있는 출구
	goal2.curC = 1;

	init->guessing = compare(init, &goal1, &goal2);//9
	
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);

	len = solvemaze(init, &goal1, &goal2, seq);

	for (t = 0; t < len; t++)
	{
		switch (seq[t])
		{
		case N :
			printf("N");
			curx--;
			break;
		case S:
			printf("S");
			curx++;
			break;
		case W:
			printf("W");
			cury--;
			break;
		case E:
			printf("E");
			cury++;
			break;
		}
		colmaze[curx][cury] = '*';
	}
	printf("\n");

	QueryPerformanceCounter(&t2);
	elapsedTime = ((double)t2.QuadPart - (double)t1.QuadPart) / frequency.QuadPart;

	printf("time : %.4f seconds\n\n", elapsedTime);
	printf("%d steps\n\n", len);

	colmaze[2][0] = '*';
	for (i = 0; i < 12; i++){
		for (j = 0; j <12; j++){
			printf(" %c ", colmaze[i][j]);
		}printf("\n");
	}
}