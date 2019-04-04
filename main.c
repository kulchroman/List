#include "list.h"
int main()
{
    TRY
    {
        char *msg = malloc(MAX_MSG_SZ * sizeof(char));
        if ( msg==NULL) THROW (BAD_ALLOC);
        puts("Chose what u want to do:");
        puts("1)enter message");
        puts("2)exit");
        unsigned short choise=0;
        count=0;
        head=NULL;
        while (choise!=1 || choise!=2|| !isdigit(choise))
        {
            if (scanf("%hu",&choise)!=1) THROW(BAD_INPUT);
            if (choise == 2 )
            {
                if (isempty()) printf("It`s sad\n");
                exit(0);
            }
            printf("Enter message and priority (must be between %hd and %hd)!\n",MIN_PRIORITY,MAX_PRIORITY);
            printf("Message (Max %hd symbols):",MAX_MSG_SZ);
            getchar();
            //контроль вводу
            if(gets(msg)==NULL) THROW (BAD_INPUT);
            printf("Priority:");
            if(scanf("%ud",&rate)!=1) THROW(BAD_INPUT);
            while (rate>MAX_PRIORITY)
            {
                printf("Bad, must be between %hd and %hd. Try again.\n",MIN_PRIORITY,MAX_PRIORITY);
                printf("Priority:");
                scanf("%d",&rate);
            }
            cur = NewNode(rate,msg);
            push(&head,cur);
            print(head);
            puts("1)enter message");
            puts("2)exit");
        }
        free(msg);
        free_list(head);
    }
    CATCH (BAD_ALLOC)
    {
        perror("Unable to allocate buffer");
    }
    CATCH (BAD_INPUT)
    {
        puts("Bad input");
    }
    ETRY;
    return 0;
}
