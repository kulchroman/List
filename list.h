#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <setjmp.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_PRIORITY 4          //Пріоритети
#define MIN_PRIORITY 0          //
#define MAX_MSG_SZ 120          //Максимальна довжина повідомлення
#define MAX_NODES MAX_PRIORITY  //Максимум повідомлень(нехай = пріоритетам)

#define TRY do { jmp_buf ex_buf__; switch( setjmp(ex_buf__) ) { case 0: while(1) {
#define CATCH(x) break; case x:
#define FINALLY break; } default: {
#define ETRY break; } } }while(0)
#define THROW(x) longjmp(ex_buf__, x)

#define BAD_ALLOC (1)
#define BAD_INPUT (2)

typedef struct Node
{
    int rate;
    char* msg;
    struct Node* next;
}node_t;
unsigned short count;
unsigned int rate;
node_t* head;
node_t* cur;

bool isempty();
bool isfull();
void print(node_t* const first);
void push(node_t **head, node_t *new_node);
void beg_del(node_t** head);
node_t* NewNode (int rate, char* msg);


#endif // LIST_H
