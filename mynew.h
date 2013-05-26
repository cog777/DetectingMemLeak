#ifndef MYNEW_H
#define MYNEW_H

#include <cstddef>

void* operator new(std::size_t size, const char *__file__, unsigned int __line__);

void* operator new[](std::size_t size, const char *__file__, unsigned int __line__);

void operator delete(void *ptr)throw();

void operator delete[](void *ptr)throw();

void* operator new(std::size_t size) throw();

void* operator new[](std::size_t size) throw();

void printList();
void deleteList();

#define new new (__FILE__, __LINE__)

#endif // MYNEW_H
