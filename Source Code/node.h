/****************************************
YOU ARE NOT ALLOWED TO MODIFY THE STRUCT
****************************************/
#ifndef NODE_HEADER
#define NODE_HEADER

struct Node{
    char *data;             //The string value stored in a Node in the linked list.
    struct Node *pLink;     //POINTER to the NEXT Node in the linked list.
};

typedef struct Node sNode;

#endif