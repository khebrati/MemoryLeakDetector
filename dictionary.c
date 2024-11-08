#include <stdio.h>
#include <stdlib.h>

typedef struct pair* Pair;
struct pair{
    size_t location;
    char* owner;
};

typedef struct node* Node;
struct node{
    Pair pair;
    // Next point
    Node np;
};

typedef struct dict* Dict;
struct dict{
    Node first_node;
};


Dict create_dict(){
    Dict dict = (Dict)malloc(sizeof(struct dict));
    dict->first_node = (Node)malloc(sizeof(struct node));
    return dict;
}
