#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.c"
Dict allocations;

void* lemalloc(size_t size, const char *file, int line, const char *func)
{
    void *p = malloc(size);
    printf ("Allocated: File: %s, Line: %d, Func: %s, Memory: %p (%li bytes)\n", file, line, func,p,size);
    MemoryTrack track = new_track((int)p,file,func,line);
    if(allocations == NULL){
        allocations = new_dict();
    }
    dict_add(allocations,track);
    return p;
}

#define malloc(X) lemalloc( X, __FILE__, __LINE__, __FUNCTION__)


int main(int argc, char* arguments[]){
    int* ip = (int*)malloc(sizeof(int));
    printf("allocated using lemalloc: %d\n",*ip);
}
