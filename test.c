#include <assert.h>
#include "list_node.h"
#include <stdio.h>

typedef struct simple {
    int data;
} tSimple;

void test_list_node();

int main()
{
    test_list_node();
     
    return 0;
}

void test_list_node()
{
    tListStruct * list = CreateList();
    tSimple a;
    a.data = 3;
    tSimple b;
    b.data = 4;
    tSimple c;
    c.data = 5;
    
    AddListNode(list, (void*)&(a), NULL, NULL);
    AddListNode(list, (void*)&(b), NULL, NULL);
    AddListNode(list, (void*)&(c), NULL, NULL);
    
    tListNode * node = list->head;
    
    int sign = 3;
    while (node != NULL) {
        printf("%d\n", ( (tSimple*)(node->data) )->data);
        assert(( (tSimple*)(node->data) )->data == sign);
        sign++;
        node = node->next;
    }
    
    DeleteList(list, NULL, NULL);
} 
