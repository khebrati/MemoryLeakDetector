#include <stdio.h>
#include <stdlib.h>

typedef struct memoryTrack* MemoryTrack;
struct memoryTrack{
    void* address;
    const char* file_name;
    const char* function_name;
    int line_number;
};

MemoryTrack new_track(void* address,const char* file_name,const char* function_name,int line_number){
    MemoryTrack track = (MemoryTrack)malloc(sizeof(struct memoryTrack));
    track->address = address;
    track->file_name = file_name;
    track->function_name = function_name;
    track->line_number = line_number;
    return track;
}

typedef struct node* Node;
struct node{
    MemoryTrack track;
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

void dict_add(Dict dict,MemoryTrack track){
    //todo: handle if dict is null
    Node first_node = dict->first_node;
    if(first_node == NULL){
        Node new_node = (Node)malloc(sizeof(struct node));
        new_node->track = track;
        dict->first_node = new_node;
        return;
    }
    Node previous_node = first_node;
    Node node = first_node->next_node;
    while(1){
        if(node == NULL){
            node = (Node)malloc(sizeof(struct node));
            node->track = track;
            previous_node->next_node = node;
            return;
        }
        previous_node = node;
        node = node->next_node;
    }
}

void de_allocate_all(Node node){
    node->next_node = NULL;
    free(node->track);
    free(node);
}

void dict_remove(Dict dict, void* address){
    //todo: handle when location is not in dictionary
    Node first_node = dict->first_node;
    if(first_node->track->address == address){
        de_allocate_all(first_node);
    }
    Node previous_node = first_node;
    Node node = first_node->next_node;
    while(1){
        if(node->track->address == address){
            previous_node->next_node = node->next_node;
            de_allocate_all(node);
        }
    }
}


