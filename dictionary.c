#include <stdio.h>
#include <stdlib.h>

typedef struct memoryTrack* MemoryTrack;
struct memoryTrack{
    size_t location;
    const char* file_name;
    const char* function_name;
    int line_number;
};

MemoryTrack new_track(size_t location,const char* file_name,const char* function_name,int line_number){
    MemoryTrack track = (MemoryTrack)malloc(sizeof(struct memoryTrack));
    track->location = location;
    track->file_name = file_name;
    track->function_name = function_name;
    track->line_number = line_number;
    return track;
}

typedef struct node* Node;
struct node{
    MemoryTrack track;
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

void dict_add(Dict dict,MemoryTrack track){
    Node node = dict->first_node;
    while(1){
        if(node == NULL){
            node = (Node)malloc(sizeof(struct node));
            node->track = track;
            break;
        }
        node = node->next_node;
    }
}
