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

struct heap_s {
	void * array;
	size_t size;
	int (*compare)(const void * lhs, const void * rhs);
	void (*print_node)(const void * item, FILE * outfp);
};

/*
 * Creates a new Heap
 *
 * @param capacity the intial size of the heap
 * @param cmp_fun a pointer to a comparison function for the nodes
 * @param print_item a pointer to a function which correctly prints the value of a node
 *
 * @return A pointer to a new heap 
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
 * Destroys a heap
 *
 * @param a_heap the heap to be destroyed
 *
 */
void hdt_destroy(Heap a_heap){
	free(a_heap->array);
	free(a_heap);
}

/*
 * The main method
 *
 * @return whether the program ran successfully or not
 */
int main(void){
	
	return 0;
}
