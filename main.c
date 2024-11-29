#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.c"
Dict allocations = NULL;

void* lemalloc(size_t size, const char* file, int line, const char* func)
{
    void *p = malloc(size);
    MemoryTrack track = new_track(p,file,func,line);
    if(allocations == NULL){
        allocations = new_dict();
    }
    dict_add(allocations,track);
    return p;
}

#define malloc(X) lemalloc( X, __FILE__, __LINE__, __FUNCTION__)

void* lefree(void* p)
{
    dict_remove(allocations,p);
    free(p);
}

#define free(X) lefree(X)

int main(int argc, char* arguments[]){
    int* ip = (int*)malloc(sizeof(int));
    *ip = 4;
    int* i2p = (int*)malloc(sizeof(int));
    *i2p = 10;
    int* i3p = (int*)malloc(sizeof(int));
    char* character = (char*)malloc(sizeof(char));
    *character = 'h';
    dict_print(allocations);
    free(i3p);
    dict_print(allocations);
    free(i2p);
    dict_print(allocations);
    free(ip);
    free(character);
    dict_print(allocations);
}
