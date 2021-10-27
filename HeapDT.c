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

/*
 * @brief Pops the current root node
 */
void * hdt_remove_top(Heap a_heap){
	void * top = malloc(sizeof(void*));
	memcpy(top, a_heap->array[0], sizeof(void *));
	a_heap->size--;

	memcpy(a_heap->array[0], a_heap->array[a_heap->size], sizeof(void *));

	if(a_heap->size == 0){ //If the heap has only 1 node left
		return top;
	}
	for(size_t i = 0; i < a_heap->size; i++){ //Downsifting for removal
		size_t lChild = 1 + i*2;
		size_t rChild = 2 + i*2;
		void * temp = malloc(sizeof(void*));

		if(lChild >= a_heap->size){ //Leaf node
			free(temp);
			break;
		}
		else if(rChild >= a_heap->size || a_heap->compare(a_heap->array[rChild], a_heap->array[lChild]) != 0){ //Left child is more desirable or right child is empty
			if(a_heap->compare(a_heap->array[i], a_heap->array[lChild]) != 0){ //Can swap with left child
				memcpy(temp, a_heap->array[lChild], sizeof(void *));
				memcpy(a_heap->array[lChild], a_heap->array[i], sizeof(void *));
				memcpy(a_heap->array[i], temp, sizeof(void *));
			}
			else{
				free(temp);
				break;
			}
		}
		else{ //Right child is more desirable
			if(a_heap->compare(a_heap->array[i], a_heap->array[rChild]) != 0){ //Can swap with right child
				memcpy(temp, a_heap->array[rChild], sizeof(void *));
				memcpy(a_heap->array[rChild], a_heap->array[i], sizeof(void *));
				memcpy(a_heap->array[i], temp, sizeof(void *));
			}
			else{
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
	for(size_t i = 0; i < a_heap->size; i++){
		a_heap->print_node(a_heap->array[i], outfp);
	}
}
