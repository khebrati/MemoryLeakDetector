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

Node new_node(MemoryTrack track){
    Node new_node = (Node)malloc(sizeof(struct node));
    new_node->track = track;
    new_node->next_node = NULL;
}

typedef struct dict* Dict;
struct dict{
    Node first_node;
};


Dict new_dict(){
    Dict dict = (Dict)malloc(sizeof(struct dict));
    return dict;
}

void dict_add(Dict dict,MemoryTrack track){
    //todo: handle if dict is null
    Node first_node = dict->first_node;
    if(first_node == NULL){
        dict->first_node = new_node(track);
        return;
    }
    Node previous_node = first_node;
    Node node = first_node->next_node;
    while(1){
        if(node == NULL){
            node = new_node(track);
            previous_node->next_node = node;
            return;
        }
        previous_node = node;
        node = node->next_node;
    }
}
void dict_free(Dict dict){
    Node node = dict->first_node;
    Node next_node;
    while(node != NULL){
        if(node->track != NULL) free(node->track);
        next_node = node->next_node;
        free(node);
        node = next_node;
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
    if(first_node == NULL) return;
    if(first_node->track == NULL) return;
    if(first_node->track->address == NULL) return;
    if(first_node->track->address == address){
        dict->first_node = first_node->next_node;
        de_allocate_all(first_node);
        return;
    }
    Node previous_node = first_node;
    Node node = first_node->next_node;
    while(1){
        if(node->track->address == address){
            previous_node->next_node = node->next_node;
            de_allocate_all(node);
            return;
        }
        previous_node = node;
        node = node->next_node;
        if(node == NULL) return;
    }
}

void dict_print(Dict dict,int toFile,char* file_location){
    Node node = dict->first_node;
    char* intro = "There are memory leaks in: \n";
    printf("%s",intro);
    FILE* file;
    if(toFile) {
        file = fopen(file_location, "w");
        if (file == NULL) {
            perror("Error creating file");
        }
        fprintf(file, "%s", intro);
    }
    while(1){
        if(node == NULL) return;
        MemoryTrack track = node->track;
        printf("Address: %p, File Name: %s, Function Name: %s, Line Number: %d\n",track->address,track->file_name,track->function_name,track->line_number);
        if(toFile){
            fprintf(file,"Address: %p, File Name: %s, Function Name: %s, Line Number: %d\n",track->address,track->file_name,track->function_name,track->line_number);
        }
        node = node->next_node;
    }
    if(toFile){
        fclose(file);
    }

}
