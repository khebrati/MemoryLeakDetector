#include <stdlib.h>
#include <stdio.h>
#include "dictionary.c"

void* lemalloc(size_t size, const char *file, int line, const char *func)
{
    void *p = malloc(size);
    printf ("Allocated: File: %s, Line: %i, Func: %s, Memory: %p (%li bytes)\n", file, line, func,p,size);

    return p;
}

#define malloc(X) lemalloc( X, __FILE__, __LINE__, __FUNCTION__)


int main(int argc, char* arguments[]){
    size_t* ip = (size_t*)malloc(sizeof(int));
    *ip = 3;
    printf("number is: %li\n",*ip);
    Dict dictionary = new_dict();
    printf("dict is: %p\n",dictionary);
    Pair pair = new_pair(*ip,"someone");
    printf("pair is: %p\nlocation: %li, owner: %s\n",pair,pair->location,pair->owner);
    dict_add(dictionary,pair);
}
