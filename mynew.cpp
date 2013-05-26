#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "mynew.h"

#undef new

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct node node_t;

struct node {
    void *ptr;
    bool array;
    unsigned int line;
    const char *file;
    node_t *prev;
    node_t *next;
};

static node_t *head = NULL;
static node_t *tail = NULL;

static node_t *find(void *ptr) {
    node_t *pNode = head;
    while(pNode != NULL) {
        if (pNode->ptr == ptr)return pNode;
        pNode = pNode->next;
    }
    return NULL;
}

static void addToList(void * ptr, bool array, unsigned int line, const char * file) {
    pthread_mutex_lock( &mutex );
    if (!find(ptr)) {
        node_t *pNode = (node *)calloc(1, sizeof(node));
        pNode->ptr = ptr;
        pNode->array = array;
        pNode->line = line;
        pNode->file = file;
        if (head == NULL) {
            tail = head = pNode;
        }
        else {
             tail->next = pNode;
             pNode->prev = tail;
             tail = pNode;
        }
    }
    pthread_mutex_unlock( &mutex );
}

static void removeFromList(void *ptr, bool array) {
    pthread_mutex_lock( &mutex );
    node_t *pNode = NULL;
    if ((pNode = find(ptr)) && pNode->array == array) {
        if (pNode == head) {
            head = pNode->next;
        }
        else if (pNode == tail){
            tail = tail->prev;
        }
        else {
            pNode->prev->next = pNode->next;
            pNode->next->prev = pNode->prev;
        }
        free(pNode);
    }
    pthread_mutex_unlock( &mutex );
}

void printList() {
    pthread_mutex_lock( &mutex );
    node_t *pNode = head;
    while(pNode) {
        fprintf(stdout, "Not relased object at: %d, file: %s, line: %d\n",
                pNode->ptr,
                pNode->file,
                pNode->line);
        pNode = pNode->next;
    }
    pthread_mutex_unlock( &mutex );
}

void deleteList() {
    pthread_mutex_lock( &mutex );
    node_t *pNode = head;
    node_t *prevNode = NULL;
    while(pNode) {
        //free(pNode->ptr);
        prevNode = pNode;
        pNode = pNode->next;
        free(prevNode);
    }
    pthread_mutex_unlock( &mutex );
}

void* operator new(std::size_t size, const char *__file__, unsigned int __line__) {
    void *ptr = malloc(size);
    addToList(ptr, false, __line__, __file__);
    return ptr;
}

void* operator new[](std::size_t size, const char *__file__, unsigned int __line__) {
    void *ptr = malloc(size);
    addToList(ptr, true, __line__, __file__);
    return ptr;
}

void operator delete(void *ptr)throw()
{
    removeFromList(ptr, false);
    free(ptr);
}

void operator delete[](void *ptr)throw()
{
    removeFromList(ptr, true);
    free(ptr);
}

void* operator new(std::size_t size) throw(){
    void *ptr = malloc(size);
    return ptr;
}

void* operator new[](std::size_t size) throw() {
    void *ptr = malloc(size);
    return ptr;
}
