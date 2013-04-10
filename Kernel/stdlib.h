#pragma once

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

typedef unsigned short size_t;

#ifdef KERNEL
void* malloc(size_t size);

void free(void* ptr);
#endif