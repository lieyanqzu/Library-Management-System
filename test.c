#include "list_node.h"
#include <stdio.h>

typedef struct simple {
    int data;
} tSimple;

int main()
{
    tListStruct * list = CreateList();
    tSimple a;
    a.data = 3;
    tSimple b;
    b.data = 4;
    tSimple c;
    c.data = 5;
    
    AddListNodeToTail(list, (void*)&(a));
    AddListNodeToTail(list, (void*)&(b));
    AddListNodeToTail(list, (void*)&(c));
    
    tListNode * node = list->head;
    
    while (node != NULL) {
        printf("%d\n", ((tSimple*)(node->data))->data);
        node = node->next;
    }
    
    DeleteList(list, NULL, NULL);

    return 0;
}
