/****************************************
YOU ARE NOT ALLOWED TO MODIFY THE STRUCT
****************************************/
#ifndef NODE_HEADER
#define NODE_HEADER

struct Node{
    char *data;
    struct Node *pLink;
};

typedef struct Node sNode;

#endif