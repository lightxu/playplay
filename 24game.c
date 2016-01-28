#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARD_SIZE 4
#define MAX_CARD 13
#define EXPR_SIZE 20
#define GOAL 24
#define OPERATOR_SIZE 4

const int operators[OPERATOR_SIZE] = {'+', '-', '*', '/'};

struct Frac {
    int son;
    int ma;
};
typedef struct Frac Frac;

struct Node {
    char expr[EXPR_SIZE];
    Frac value;
};
typedef struct Node Node;

Node tree[CARD_SIZE];
char solution[EXPR_SIZE];

void Initialize();
void FindSolution();

int
main()
{
    while (1) {
        Initialize();
        FindSolution();
        printf("Press any key to see if there is any solution.\n");
        getchar();getchar();
        puts(solution);
        printf("--------------------------------------------\n");
        printf("Press Ctrl + C to quit, or replay otherwise.\n");
        getchar();
    }
    return 0;
}

#include <time.h>

void
Initialize()
{
    printf("Card Number Is: %d. Goal to achieve Is: %d.\n", CARD_SIZE, GOAL);
    printf("You can choose the mode by press the number of it.\n0: The card is randomly selected by computer.\n1: The card is given by you.\n");
    int mode;
    int i;
    int cards[CARD_SIZE];
    scanf("%d", &mode);
    if (mode == 0) {
        srand(time(NULL));
        for (i = 0; i < CARD_SIZE; i++) {
            cards[i] = rand() % MAX_CARD + 1;
            printf("%d%c", cards[i], i == CARD_SIZE - 1 ? '\n' : ' ');
        }
    }
    else
        for (i = 0; i < CARD_SIZE; i++)
            scanf("%d", &cards[i]);
    for (i = 0; i < CARD_SIZE; i++) {
        tree[i].value = (Frac) {cards[i], 1};
        sprintf(tree[i].expr, "%d", cards[i]);
    }
}

int flag[CARD_SIZE];

int DFS(int now);

void 
FindSolution()
{
    memset(flag, 0, sizeof(flag));
    if (!DFS(CARD_SIZE))
        sprintf(solution, "No solution."); 
}

int Calculate(Node *goal, Node x, Node y, char operator);
int Gcd(int x, int y);
int Equal(Frac x, int y);
void Simplify(Frac *goal, Frac mess);
void AddOrMinus(Frac *goal, Frac x, Frac y, int type);
void MultiplyOrDivide(Frac *goal, Frac x, Frac y, int type);

int 
DFS(int now)
{
    if (now == 1) {
        int i;
        for (i = 0; i < CARD_SIZE; i++)
            if (!flag[i])
                break;
        if (Equal(tree[i].value, 24)) {
            sprintf(solution, tree[i].expr);
            return 1;
        }
        return 0;
    }
#ifdef DEBUG
    int ii;
    for (ii = 0; ii < CARD_SIZE; ii++)
        if (!flag[ii])
            printf("%s    %d/%d\n", tree[ii].expr, tree[ii].value.son, tree[ii].value.ma);
#endif
    int i, j;
    for (i = 0; i < CARD_SIZE; i++)
        for (j = 0; j < CARD_SIZE; j++) 
            if (i != j && !flag[i] && !flag[j]) {
                Node tmp = tree[j];
                int op;
                flag[i] = 1;
                for (op = 0; op < OPERATOR_SIZE; op++)
                    if (Calculate(&tree[j], tree[i], tmp, operators[op]))
                        if (DFS(now - 1))
                            return 1;
                flag[i] = 0;
                tree[j] = tmp;
            }
    return 0;
}

#define ADD 1
#define MINUS -1
#define MULTIPLY 0
#define DIVIDE 1
int
Calculate(Node *goal, Node x, Node y, char operator)
{
    switch (operator) {
    case '+': AddOrMinus(&goal->value, x.value, y.value, ADD); break;
    case '-': AddOrMinus(&goal->value, x.value, y.value, MINUS); break;
    case '*': MultiplyOrDivide(&goal->value, x.value, y.value, MULTIPLY); break;
    case '/': 
        if (Equal(y.value, 0)) return 0; 
        MultiplyOrDivide(&goal->value, x.value, y.value, DIVIDE);
    }
    sprintf(goal->expr, "(%s%c%s)", x.expr, operator, y.expr);
    return 1;
}


int 
Gcd(int x, int y)
{
    int z = x % y;
    while (z != 0) {
        x = y;
        y = z;
        z = x % y;
    }
    return y;
}

int 
Equal(Frac x, int y)
{
    if (x.son % x.ma == 0 && x.son / x.ma == y)
        return 1;
    return 0;
}

void 
Simplify(Frac *goal, Frac tmp)
{   
    if (Equal(tmp, 0)) {
        (*goal).son = 0;
        (*goal).ma = 1;
        return ;
    }
    else {
        int gcd = Gcd(tmp.son, tmp.ma);
        (*goal).son = tmp.son / gcd;
        (*goal).ma = tmp.ma / gcd;
    }
}

void 
AddOrMinus(Frac *goal, Frac x, Frac y, int type)
{
    Frac tmp;
    tmp.son = x.son * y.ma + type * x.ma * y.son;
    tmp.ma = x.ma * y.ma;
    Simplify(goal, tmp);
}

void 
MultiplyOrDivide(Frac *goal, Frac x, Frac y, int type)
{
    Frac tmp;
    tmp.son = x.son * (type == DIVIDE ? y.ma : y.son);
    tmp.ma  = x.ma  * (type == DIVIDE ? y.son : y.ma);
    Simplify(goal, tmp);
}