#include <stdio.h>
#include <stdlib.h>
#define MAX_PRIORITY 8          //Пріоритети
#define MIN_PRIORITY 0          //
#define MAX_MSG_SZ 120          //Максимальна довжина повідомлення
#define MAX_NODES MAX_PRIORITY  //Максимум повідомлень(нехай = пріоритетам)
typedef struct Node
{
    int rate;
    char* msg;
    struct Node* next;
}node_t;

typedef struct
{
    int rate;
    char *msg;
}msg_t;

int isempty();
int isfull();
void push(const node_t *it,int i,const char *msg);
void print(node_t* const first);
void sort (const node_t * const it);
void insert(node_t *target, int rate, char *msg);
static unsigned short count=0;
static unsigned short is_sort_flag=0;

int main()
{
    node_t* cur = (node_t*) malloc(sizeof(node_t));
    int rate=MIN_PRIORITY;
    unsigned short choise=0;
    //+1 для повідомлення яке буде мінятися коли count==MAX_NODES
    char (*msg)[MAX_NODES+1] = malloc(MAX_MSG_SZ * sizeof(char));
    if(msg == NULL)
    {
          perror("Unable to allocate buffer");
          exit(1);
    }
    puts("Chose what u want to do:");
    puts("1)enter message");
    puts("2)exit");
    while (choise!=1 || choise!=2)
    {
        scanf("%hu",&choise);
        if (choise == 2)
        {
            if (isempty())
                printf("It`s sad\n");
            exit(0);
        }
        printf("Enter message and priority (must be between %hd and %hd)!\n",MIN_PRIORITY,MAX_PRIORITY);
        printf("Message (Max %hd symbols):",MAX_MSG_SZ);
        getchar();
        gets(msg[count]);
        printf("Priority:");
        scanf("%d",&rate);
        while (rate>MAX_PRIORITY || rate<0)
        {
            printf("Bad, must be between %hd and %hd. Try again.\n",MIN_PRIORITY,MAX_PRIORITY);
            printf("Priority:");
            scanf("%d",&rate);
        }

        if (isempty())
        {
            cur->rate=rate;
            cur->msg =msg[count];
            cur->next=NULL;
            count++;
        }
        else if (count==1)
        {
            //автозаповнення списку
            push(cur,rate,msg[count]);
            //не зовсім правильно але швидше. msg[i] буде пустий
            push(cur,5,"Hello");
            push(cur,3,"my");
            push(cur,8,"little");
            push(cur,2,"pony");
            push(cur,2,"lol");
            push(cur,2,"hoho");
            sort(cur);
            puts("Ups... Somebodey puts random messages");
            puts("But in future all will be fine. You can add your messages");
            printf("You can change limits in #define MAX_NODES part. Now limit - %d messages\n",MAX_NODES);
            print(cur);
        }
        else if(isfull())
        {
            printf("Queue is full!\n");
            printf("%d\n",count);
            // список відсортований. Переходимо в кінець, заміняємо повідомлення і повторно сортуємо
            insert (cur,rate,msg[count]);
            sort(cur);
            print(cur);
        }
        else
        {
            push(cur,rate,msg[count]);
            sort(cur);
            print(cur);
        }
        puts("1)enter message");
        puts("2)exit");

    }
    free(msg);
    free(cur);
    return 0;
}
int isempty()
{
    return count?0:1;
}

int isfull()
{
    return (count==MAX_NODES)?1:0;
}

void push(const node_t* it, int i,const char* msg)
{
    is_sort_flag = 0;
    node_t *cur = it;
    while (cur->next!=NULL)
            cur=cur->next;
    cur->next = (node_t*)malloc(sizeof(node_t));
    cur->next->rate = i;
    //cur->next->msg =  malloc(sizeof(msg));
    cur->next->msg = msg;
    cur->next->next = NULL;
    ++count;
}
void sort (const node_t* const it)
{
    node_t *i,*j;
    msg_t *buf = malloc(sizeof(msg_t));
    //сортування бульбашкою)
    for (i=it;i->next!=NULL;i=i->next)
    {
        for(j=i->next;j!=NULL;j=j->next)
        {
            if(i->rate < j->rate)
            {
                buf->rate = i->rate;
                i->rate = j->rate;
                j->rate = buf->rate;
                buf->msg = i->msg;
                i->msg = j->msg;
                j->msg = buf->msg;
            }
        }
    }
    is_sort_flag = 1;
    free(buf);
}

void print(node_t* const first)
{
    node_t* cur=first;
    while (cur->next!=NULL)
    {
        printf("priority= %d\t message=%s\n",cur->rate,cur->msg);
        cur=cur->next;
    }
    printf("priority= %d\t message=%s\n",cur->rate,cur->msg);
}

void insert(node_t* target, int rate, char *msg)
{
    //Так можна вставити в довільне місце
    /*
    while (target->next!=NULL)
    {
        if(target->rate<=it->rate && it->rate>target->next->rate)
        {
            target->rate = it->rate;
            target->msg = it->msg;
            return;
        }
        target = target->next;
    }
    */
    while (target->next!=NULL)
    {
        target = target->next;
    }
    if(rate<target->rate)
        printf("Priority is less than the least priority of the queue\n");
    else
    {
        printf("%d \t %s was deleted \n",target->rate,target->msg);
        target->rate = rate;
        target->msg = msg;
    }
}
