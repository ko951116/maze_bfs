#define MAX 100
#define GMAX 1000

typedef enum move {
   N, S, W, E
} Move;

typedef struct state {
   char maze[12][12];
   int curR;
   int curC;
   Move sequence[MAX];
   int len;
   int guessing;
} State;

State* getNextState(State *curState, State *goal1, State *goal2, Move m);
State* cloneState(State *curState);
int compare(State *one, State *another1, State *another2);
int inClosed(State **closed1, int len, State *next);
int solvemaze(State *init, State *goal1, State *goal2, Move *seq);
void clean(State **array, int len);
int compare2 (State *next, State *closed);