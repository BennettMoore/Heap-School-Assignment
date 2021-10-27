//
// file : HeapDT.c
//
// @author Bennett Moore bwm7637@rit.edu
//
// // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HeapDT.h"

/*
 * @brief A heap structure
 */
struct heap_s {
	void ** array;
	size_t size;
	size_t max_size;
	int (*compare)(const void * lhs, const void * rhs);
	void (*print_node)(const void * item, FILE * outfp);
};

/*
 * @brief Creates a new Heap
 */
Heap hdt_create(size_t capacity, int (*cmp_fun)(const void * lhs, const void * rhs), void (*print_item)(const void * item, FILE * outfp)){
	Heap newHeap = malloc(sizeof(Heap));
	newHeap->array = (void **)calloc(capacity, sizeof(void *));
	newHeap->max_size = capacity;
	newHeap->size = 0;
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
	return a_heap->array[0];
}

/*
 * @brief Adds an item to the heap
 */
void hdt_insert_item(Heap a_heap, const void * item){
	if(a_heap->size >= a_heap->max_size){ //Add a new layer to the heap
		a_heap->max_size = 2*(a_heap->max_size)+2;
		a_heap->array = (void **)realloc(a_heap->array, a_heap->max_size*sizeof(void *));
	}
	
	memcpy(a_heap->array[a_heap->size], item, sizeof(&item));
	
	for(size_t i = a_heap->size; i > 0; i--){ //Upsifting for insertion
		size_t parent = (i-1)/2;
		if(a_heap->compare(a_heap->array[parent], a_heap->array[i]) != 0){
			void * temp = malloc(sizeof(void*));
			memcpy(temp, a_heap->array[parent], sizeof(void *));
			memcpy(a_heap->array[parent], a_heap->array[i], sizeof(void *));
			memcpy(a_heap->array[i], temp, sizeof(void *));
			free(temp);
		}
	}
	a_heap->size++;
}
