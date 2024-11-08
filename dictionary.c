#include <stdio.h>
#include <stdlib.h>

typedef struct pair* Pair;
struct pair{
    size_t location;
    char* owner;
};
Pair new_pair(size_t location,char* owner){
    Pair pair = (Pair)malloc(sizeof(struct pair));
    pair->location = location;
    pair->owner = owner;
    return pair;
}

typedef struct node* Node;
struct node{
    Pair pair;
    // Next point
    Node next_node;
};

typedef struct dict* Dict;
struct dict{
    Node first_node;
};


Dict new_dict(){
    Dict dict = (Dict)malloc(sizeof(struct dict));
    dict->first_node = (Node)malloc(sizeof(struct node));
    return dict;
}

void dict_add(Dict dict,Pair pair){
    Node node = dict->first_node;
    while(1){
        if(node == NULL){
            node = (Node)malloc(sizeof(struct node));
            node->pair = pair;
            break;
        }
        node = node->next_node;
    }
}
