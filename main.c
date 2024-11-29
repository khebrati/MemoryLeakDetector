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

void on_exit_function(){
    dict_print(allocations,1,"MemoryLeak");
    dict_free(allocations);
}

void memory_playground(){
    int* i = (int*)malloc(sizeof(int));
    char* c = (char*)malloc(sizeof(char));
}

int main(int argc, char* arguments[]){
    if(atexit(on_exit_function) != 0){
        perror("Error registering on exit function");
        return EXIT_FAILURE;
    }
    memory_playground();
}

