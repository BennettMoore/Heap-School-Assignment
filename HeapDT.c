//
// file : HeapDT.c
//
// @author Bennett Moore bwm7637@rit.edu
//
// // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include "HeapDT.h"

#define BLOCK_SIZE 5

/*
 * @brief A heap structure
 */
struct heap_s {
	void * array;
	size_t size;
	int (*compare)(const void * lhs, const void * rhs);
	void (*print_node)(const void * item, FILE * outfp);
};

/*
 * @brief Creates a new Heap
 */
Heap hdt_create(size_t capacity, int (*cmp_fun)(const void * lhs, const void * rhs), void (*print_item)(const void * item, FILE * outfp)){
	Heap newHeap = malloc(sizeof(Heap));
	newHeap->array = calloc(capacity, sizeof(void *));
	newHeap->size = capacity;
	newHeap->compare = cmp_fun; 
	newHeap->print_node = print_item;
	return newHeap;
}

/*
 * @brief Destroys a heap
 */
void hdt_destroy(Heap a_heap){
	free(a_heap->array);
	free(a_heap);
}

/*
 * @brief Returns the size of a heap
 */
size_t hdt_size(Heap a_heap){
	return a_heap->size;
}

/*
 * @brief Peeks at the top of the heap
 */
const void * hdt_top(const Heap a_heap){
	return a_heap->array;
}
