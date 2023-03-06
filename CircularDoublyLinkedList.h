/*Copyright 2021 Anghel Andrei - Stelian 312CA*/

#ifndef CIRCULARDOUBLYLINKEDLIST_H_
#define CIRCULARDOUBLYLINKEDLIST_H_
#define MAX_STRING_SIZE 25

typedef struct dll_node_t dll_node_t;
struct dll_node_t {
    /* Pentru ca datele stocate sa poata avea orice tip, folosim un
    pointer la void. */
    void* data;
    dll_node_t *prev, *next;
};

typedef struct doubly_linked_list_t doubly_linked_list_t;
struct doubly_linked_list_t {
    dll_node_t* head;
    unsigned int data_size;
    unsigned int size;
};

/*
 * Acestea sunt functiile pe care trebuie sa le implementam.
 * Implementarea acestora se va face in LinkedList.c .
 */

doubly_linked_list_t*
dll_create(unsigned int data_size);

dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n);

void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data);

dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n);

void
dll_free(doubly_linked_list_t** pp_list);

void
dll_print_int_list(doubly_linked_list_t* list);

void dll_rotate(doubly_linked_list_t* list, char direction, int units);

#endif  // CIRCULARDOUBLYLINKEDLIST_H_
