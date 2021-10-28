//
// file: test_HeapDT.c 
// 
// test_HeapDT.c is a simple test of a Heap abstract data type implementation.
// 
// @author CS @ RIT.EDU
// @author Bennett Moore bwm7637@rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "HeapDT.h"

/// less-than-or-equal compares entries as pointers to int values.
///
/// @param item1 pointer to the left hand side of the comparison
/// @param item2 pointer to the right hand side of the comparison
/// @return non-zero if *item1 <= *item2
/// @pre values are pointers to integer values.

static int cmpintmin( const void * item1, const void * item2 ) {
    int v1 = *(int*)item1;
    int v2 = *(int*)item2;
    return v1 <= v2;
}

/// greater-than-or-equal compares entries as pointers to int values.
///
/// @param item1 pointer to the left hand side of the comparison
/// @param item2 pointer to the right hand side of the comparison
/// @return non-zero if *item1 >= *item2
/// @pre values are pointers to integer values.

static int cmpintmax( const void * item1, const void * item2 ) {
    int v1 = *(int*)item1;
    int v2 = *(int*)item2;
    return v1 >= v2;
}

/// prints entry as an int value.
///
/// @param item1 pointer to the value to print
/// @param outfp pointer to output file stream
/// @pre values are pointers to integer values.

static void print_int( const void * item1, FILE * outfp ) {
    if ( ! item1 ) {
        fprintf( outfp, "\n\tWARNING: null entry! This should not happen.\n" );
        return;
    }
    int v1 = *(int*)item1;
    fprintf( outfp, "%d\n", v1 );
    return;
}


/// less-than-or-equal compares entries as pointers to char values.
///
/// @param item1 pointer to the left hand side of the comparison
/// @param item2 pointer to the right hand side of the comparison
/// @return non-zero if *item1 <= *item2
/// @pre values are pointers to char values.

static int cmpcharmin( const void * item1, const void * item2 ) {
    char v1 = *(char*)item1;
    char v2 = *(char*)item2;
    return v1 <= v2;
}

/// greater-than-or-equal compares entries as pointers to char values.
///
/// @param item1 pointer to the left hand side of the comparison
/// @param item2 pointer to the right hand side of the comparison
/// @return non-zero if *item1 >= *item2
/// @pre values are pointers to char values.

static int cmpcharmax( const void * item1, const void * item2 ) {
    char v1 = *(char*)item1;
    char v2 = *(char*)item2;
    return v1 >= v2;
}

/// prints entry as a single char value.
///
/// @param item1 pointer to the value to print
/// @param outfp pointer to output file stream
/// @pre values are pointers to char values.

static void print_char( const void * item1, FILE * outfp ) {
    if ( ! item1 ) {
        fprintf( outfp, "\n\tWARNING: null entry! This should not happen.\n" );
        return;
    }
    char v1 = *(char*)item1;
    fprintf( outfp, "%c\n", v1 );
    return;
}


/// test_int_heap tests an integer heap.
///
/// @param max_flag is true if heap is a maxheap.

void test_int_heap( bool max_flag ) {

    printf( "test_int_heap using %s ordering\n"
          , (max_flag ? "max" : "min") );

    int test_data[] = { 1, 9, 3, 8, 5, 7, 10, 9, 6, 4, 2, -1 };

    printf( "test data: [ " );
    for ( size_t i = 0; i < sizeof( test_data ) / sizeof( int ); i++ ) {
        printf( "%d ", test_data[i] );
    }
    printf( "]\n" );

    Heap theheap = NULL;
    if ( max_flag ) {
        theheap = hdt_create( 10, cmpintmax, print_int );
    } else {
        theheap = hdt_create( 10, cmpintmin, print_int );
    }

    for ( size_t i = 0; i < sizeof( test_data ) / sizeof( int ); i++ ) {
        hdt_insert_item( theheap, (void*)&test_data[i] );
    }

    printf( "Heap size is now %zu\n", hdt_size( theheap ) );
    fprintf( stderr, "hdt_print to stderr:\n" );
    hdt_print( theheap, stderr ); 

    printf( "Emptying the heap: " );
    while ( hdt_size( theheap ) ) {
        int* vPointer = (int*)hdt_remove_top(theheap);
	int value = *vPointer;
	free(vPointer);
        printf( "%d ", value );
    }
    printf( "\n" );

    hdt_destroy( theheap );

    return;
}

/// test_char_heap tests a character heap.
///
/// @param max_flag is true if heap is a maxheap.

void test_char_heap( bool max_flag ) {

    printf( "test_char_heap using %s ordering\n"
          , (max_flag ? "max" : "min") );

    char test_data[] = { 'a', 'c', 'g', 'e', 'm', 'u', 'i', 'e', 'o', 'y', 'A' };

    printf( "test data: [ " );
    for ( size_t i = 0; i < sizeof( test_data ) / sizeof( char ); i++ ) {
        printf( "%c ", test_data[i] );
    }
    printf( "]\n" );

    Heap theheap = NULL;
    if ( max_flag ) {
        theheap = hdt_create( 10, cmpcharmax, print_char );
    } else {
        theheap = hdt_create( 10, cmpcharmin, print_char );
    }
    assert( theheap );

    for ( size_t i = 0; i < sizeof( test_data ) / sizeof( char ); i++ ) {
        hdt_insert_item( theheap, (void*)&test_data[i] );
    }

    printf( "Heap size is now %zu\n", hdt_size( theheap ) );
    fprintf( stderr, "hdt_print to stderr:\n" );
    hdt_print( theheap, stderr );

    printf( "Emptying the heap: " );
    while ( hdt_size( theheap ) ) {
	char* vPointer = hdt_remove_top(theheap);
        char value = *vPointer;
	free(vPointer);
        printf( "%c ", value );
    }
    printf( "\n" );

    hdt_destroy( theheap );

    return;
}

/// test_multi_heap tests having multiple Heaps active at a time, as well as very large heaps
///
/// @param max_flag is true if heap is a maxheap.
void test_multi_heap(bool max_flag) {

    printf( "test_multi_heap using %s ordering\n"
          , (max_flag ? "max" : "min") );

    char test_data_c[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
	    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int test_data_i[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 
	    37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52};
    
    printf( "character test data: [ " );
    for ( size_t i = 0; i < sizeof( test_data_c ) / sizeof( char ); i++ ) {
        printf( "%c ", test_data_c[i] );
    }
    printf( "]\n" );
    
    printf( "integer test data: [ " );
    for ( size_t i = 0; i < sizeof( test_data_i ) / sizeof( int ); i++ ) {
        printf( "%i ", test_data_i[i] );
    }
    printf( "]\n" );

    Heap charHeap = NULL;
    Heap intHeap = NULL;
    if(max_flag){
        charHeap = hdt_create(10, cmpcharmax, print_char);
	intHeap = hdt_create(10, cmpintmax, print_int);
    }
    else{
        charHeap = hdt_create(10, cmpcharmin, print_char);
	intHeap = hdt_create(10, cmpintmin, print_int);
    }
    assert(charHeap);
    assert(intHeap);
    
    for ( size_t i = 0; i < sizeof( test_data_c ) / sizeof( char ); i++ ) {
        hdt_insert_item( charHeap, (void*)&test_data_c[i] );
    }

    for ( size_t i = 0; i < sizeof( test_data_i ) / sizeof( int ); i++ ) {
        hdt_insert_item( intHeap, (void*)&test_data_i[i] );
    }
    printf( "Character heap size is now %zu\n", hdt_size( charHeap ) );
    fprintf( stderr, "Character hdt_print to stderr:\n" );
    hdt_print( charHeap, stderr );
    
    printf( "Emptying the character heap: " );
    while ( hdt_size( charHeap ) ) {
        char* vPointer = hdt_remove_top(charHeap);
        char value = *vPointer;
        free(vPointer);
        printf( "%c ", value );
    }
    printf( "\n" );

    hdt_destroy( charHeap );

    
    printf( "Integer heap size is now %zu\n", hdt_size( intHeap ) );
    fprintf( stderr, "Integer hdt_print to stderr:\n" );
    hdt_print( intHeap, stderr );

    printf( "Emptying the integer heap: " );
    while ( hdt_size( intHeap ) ) {
        int* vPointer = hdt_remove_top(intHeap);
        int value = *vPointer;
        free(vPointer);
        printf( "%i ", value );
    }
    printf( "\n" );

    hdt_destroy( intHeap );

    return;

}

/// main function runs tests using integer and char data payloads.
/// The tests use both a minheap and a maxheap.
///
/// @return EXIT_SUCCESS

int main( void ) {

    test_int_heap( false );     // minheap
    test_int_heap( true );      // maxheap

    test_char_heap( false );
    test_char_heap( true );

    test_multi_heap( false );
    test_multi_heap( true );
    
    return EXIT_SUCCESS;
}

