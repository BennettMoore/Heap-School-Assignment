//
// file : HeapDT.c
//
// @author Bennett Moore bwm7637@rit.edu
//
// // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "HeapDT.h"

#define ALLOC_BUF 50
/*
 * @brief A heap structure
 */
struct heap_s {
	void ** array; //Heap
	size_t size; //Number of nodes in the heap
	size_t max_size; //Current maximum node capacity
	int (*compare)(const void * lhs, const void * rhs); //Node comparison function
	void (*print_node)(const void * item, FILE * outfp); //Node printing function
};

/*
 * @brief Creates a new Heap
 */
Heap hdt_create(size_t capacity, int (*cmp_fun)(const void * lhs, const void * rhs), void (*print_item)(const void * item, FILE * outfp)){
	assert(cmp_fun != NULL && print_item != NULL); //Are function pointers valid

	//Initialize new heap
	Heap newHeap = malloc(sizeof(Heap)*sizeof(void**));
	assert(newHeap != NULL); //Did malloc run

	newHeap->array = (void **)calloc(capacity, sizeof(void*));
	assert(newHeap->array != NULL); //Did calloc run
	
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
	assert(a_heap->size <= 0); //Is a_heap->array empty

	free(a_heap->array);
	free(a_heap);
}

/*
 * @brief Returns the size of a heap
 */
size_t hdt_size(Heap a_heap){
	assert(a_heap != NULL); //Is a_heap valid
	
	return a_heap->size;
}

/*
 * @brief Peeks at the top of the heap
 */
const void * hdt_top(const Heap a_heap){
	assert(a_heap != NULL); //Is a_heap valid
	assert(a_heap->size > 0); //Does a_heap have at least one node
	
	return a_heap->array[0];
}

/*
 * @brief Adds an item to the heap
 */
void hdt_insert_item(Heap a_heap, const void * item){
	assert(a_heap != NULL); //Is a_heap valid

	if(a_heap->size >= a_heap->max_size-1){ //Add a new layer to the heap
		a_heap->max_size = 2*(a_heap->max_size)+2;
		a_heap->array = (void **)realloc(a_heap->array, a_heap->max_size*sizeof(void*));
		assert(a_heap->array != NULL); //Did realloc run
	}
	a_heap->array[a_heap->size] = malloc(ALLOC_BUF);
	assert(a_heap->array[a_heap->size] != NULL); //Did malloc run

	memcpy(a_heap->array[a_heap->size], item, ALLOC_BUF); //Set new node to the bottom of the heap
	
	for(size_t i = a_heap->size; i > 0; i--){ //Upsifting for insertion
		size_t parent = (i-1)/2;
		if(a_heap->compare(a_heap->array[i], a_heap->array[parent]) != 0){
			void * temp = malloc(ALLOC_BUF);
			assert(temp != NULL); //Did malloc run

			memcpy(temp, a_heap->array[parent], ALLOC_BUF);
			memcpy(a_heap->array[parent], a_heap->array[i], ALLOC_BUF);
			memcpy(a_heap->array[i], temp, ALLOC_BUF);
			free(temp);
		}
	}
	a_heap->size++;
}

/*
 * @brief Pops the current root node
 */
void * hdt_remove_top(Heap a_heap){
	assert(a_heap != NULL); //Is a_heap valid
	assert(a_heap->size > 0); //Does a_heap have at least one node
	
	void * top = malloc(ALLOC_BUF);
	assert(top != NULL); //Did malloc run

	memcpy(top, a_heap->array[0], ALLOC_BUF); //Save root node to return later
	
	a_heap->size--; //Index of leaf node being moved to the root
	memcpy(a_heap->array[0], a_heap->array[a_heap->size], ALLOC_BUF); //Replace root node with bottom leaf node
	free(a_heap->array[a_heap->size]); //Remove bottom leaf node

	if(a_heap->size == 0){ //If the heap has only 1 node left
		return top;
	}
	for(size_t i = 0; i < a_heap->size; i++){ //Downsifting for removal
		size_t lChild = 1 + i*2;
		size_t rChild = 2 + i*2;
		void * temp = malloc(ALLOC_BUF);
		assert(temp != NULL); //Did malloc run

		if(lChild >= a_heap->size){ //Leaf node
			free(temp);
			break;
		}
		else if(rChild >= a_heap->size || a_heap->compare(a_heap->array[lChild], a_heap->array[rChild]) != 0){ //Left child is more desirable or right child is empty
			if(a_heap->compare(a_heap->array[lChild], a_heap->array[i]) != 0){ //Can swap with left child
				memcpy(temp, a_heap->array[lChild], ALLOC_BUF);
				memcpy(a_heap->array[lChild], a_heap->array[i], ALLOC_BUF);
				memcpy(a_heap->array[i], temp, ALLOC_BUF);
			}
			else{ //Can't swap with children
				free(temp);
				break;
			}
		}
		else{ //Right child is more desirable
			if(a_heap->compare(a_heap->array[rChild], a_heap->array[i]) != 0){ //Can swap with right child
				memcpy(temp, a_heap->array[rChild], ALLOC_BUF);
				memcpy(a_heap->array[rChild], a_heap->array[i], ALLOC_BUF);
				memcpy(a_heap->array[i], temp, ALLOC_BUF);
			}
			else{ //Can't swap with children
				free(temp);
				break;
			}
		}
		free(temp);
	}
	return top;
}

/*
 * @brief Print all items in the heap
 */
void hdt_print(Heap a_heap, FILE * outfp){
	assert(a_heap != NULL); //Is a_heap valid

	for(size_t i = 0; i < a_heap->size; i++){
		a_heap->print_node(a_heap->array[i], outfp);
	}
}
