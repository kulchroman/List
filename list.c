#include "list.h"
bool isempty()
{
    return count?0:1;
}

bool isfull()
{
    return (count==MAX_NODES+1)?1:0;
}

void print(node_t* const first)
{
    node_t* temp=first;
    while (temp!=NULL)
    {
        printf("priority= %d\t message=%s\n",temp->rate,temp->msg);
        temp=temp->next;
    }
}
node_t* NewNode(int rate, char* msg)
{
    TRY
    {
        node_t* new_node = (node_t*) malloc(sizeof(node_t));
        new_node->msg = malloc(sizeof(msg));
        if (new_node==NULL || new_node->msg==NULL) THROW (BAD_ALLOC);
        if(strncpy(new_node->msg,msg,strlen(msg)+1)==NULL) THROW (BAD_INPUT);
        new_node->rate=rate;
        new_node->next=NULL;
        ++count;
        return new_node;
    }ETRY;

}
//видалення з початку списку

/*
void beg_del(node_t** head)
{
   node_t* ptr=*head;
   //переналаштовуємо вказівник на наступний елемент
   *head=ptr->next;
   free(ptr);
   --count;
}
*/

void push(node_t **head_ref, node_t *new_node)
{
    node_t* current;
    //1-й елемент або якщо 2-й елемент більший за перший
    if (*head_ref == NULL || (*head_ref)->rate >= new_node->rate)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
     {
        current = *head_ref;
        while (current->next!=NULL &&
                current->next->rate < new_node->rate)
           {
               current = current->next;
           }
        new_node->next = current->next;
        current->next = new_node;
     }
    printf("List not full %d\n",count);
    //логіка по видаленню імплементована
    if (isfull())
    {
        node_t* ptr=*head_ref;
        printf("List is full\n");
        //переналаштовуємо вказівник на наступний елемент
        *head_ref=ptr->next;
        free(ptr);
        --count;
    }


}


//4) memory leak
void free_list(node_t* head)
{
    while (head!=NULL)
    {
        free(head->msg);
        free(head);
        head=head->next;
    }
}
