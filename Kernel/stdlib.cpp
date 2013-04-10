#include "stdlib.h"


#ifdef KERNEL
struct MemoryNode {
	void* start;
	size_t size;
	MemoryNode* next;
};

bool initialized = false;
MemoryNode* freeList = (MemoryNode*)0x9000;
MemoryNode* usedList = NULL;

void malloc_init() {
	freeList->start = (void*)(0x9000 + sizeof(MemoryNode));
	freeList->size = 0x4000 - sizeof(MemoryNode);

	initialized = true;
}

void* malloc(size_t size) {
	if (!initialized) malloc_init();

	MemoryNode* curr = freeList;
	void* allocation = NULL;
	while (allocation == NULL && curr != NULL) {
		if (curr->size == size) {
			freeList = curr->next;
		} else if (curr->size > size) {
			curr->start = (void*)((char*)curr->start + size);
			curr->size -= size;
		}
		allocation = curr->start;
	}

	return allocation;
}

void free(void* adr) {

}
#endif