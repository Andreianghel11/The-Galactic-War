/*Copyright 2021 Anghel Andrei - Stelian 312CA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/home/student/PlanetFunctions.h"
#include "/home/student/CircularDoublyLinkedList.h"
#include "/home/student/utils.h"

/*Functie care trebuie apelata pentru alocarea si initializarea unei liste.
(Setare valori initiale pentru campurile specifice structurii LinkedList).*/
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    doubly_linked_list_t* list = malloc(sizeof(doubly_linked_list_t));
    DIE(!list, "Malloc error");

    list->head = NULL;
    list->size = 0;
    list->data_size = data_size;

    return list;
}

/*Functia intoarce un pointer la nodul de pe pozitia n din lista.
Daca n >= nr_noduri, atunci se intoarce nodul de pe pozitia rezultata
daca am "cicla" (posibil de mai multe ori) pe lista si amtrece de la
ultimul nod, inapoi la primul si am continua de acolo.*/
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    if (!list) {
		printf("Error - list not found\n");
		return NULL;
	}

    if (list->size == 0)
        return NULL;

    /*Atunci cand "ciclam" nu parcurgem lista de mai multe ori.*/
    n = n % list->size;
    dll_node_t* current = list->head;
    unsigned int pos = 0;
    while (pos != n) {
        current = current->next;
        pos++;
    }
    return current;
}

/*Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
adaugat pe pozitia n a listei reprezentata de pointerul list. Cand indexam
pozitiile nu "ciclam" pe lista circulara ca la get, ci consideram nodurile in
ordinea de la head la ultimul (adica acel nod care pointeaza la head ca nod
urmator in lista).*/
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
      if (!list) {
		printf("error - list not found\n");
		return;
	}

    dll_node_t* new_node = malloc(sizeof(dll_node_t));
    DIE(!new_node, "Malloc error");

    new_node->data = malloc(list->data_size);
    DIE(!new_node, "Malloc error");

    memcpy(new_node->data, data, list->data_size);
    new_node->next = NULL;
    new_node->prev = NULL;

    if (list->size == 0) {
        list->head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;

    } else if (n == 0) {
        dll_node_t* aux1 = list->head;
        dll_node_t* aux2 = list->head->prev;
        list->head = new_node;
        new_node->next = aux1;
        aux1->prev = new_node;
        aux2->next = new_node;
        new_node->prev = aux2;

    } else if (n >= list->size) {
        dll_node_t* aux1 = list->head->prev;
        aux1->next = new_node;
        new_node->prev = aux1;
        new_node->next = list->head;
        list->head->prev = new_node;

    } else {
        dll_node_t* current = list->head;
        unsigned int pos = 0;
        while (pos != n - 1) {
            current = current->next;
            pos++;
        }
        dll_node_t* aux = current->next;
        current->next = new_node;
        new_node->prev = current;
        new_node->next = aux;
        aux->prev = new_node;
    }

    list->size++;
    return;
}

/*Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
parametru. Functia intoarce un pointer spre acest nod proaspat eliminat din
lista. Memoria acestui nod va fi eliberata ulterior.*/
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
     if (!list) {
		printf("error - list not found\n");
		return NULL;
	}

    if (list->size == 0) {
        printf("Cannot remove element from empty list");
        return NULL;
    }

    if (list->size == 1) {
        dll_node_t* removed_node = list->head;
        list->head = NULL;
        list->size = 0;
        return(removed_node);
    }

    if (n == 0) {
        dll_node_t* aux1 = list->head->next;
        dll_node_t* aux2 = list->head->prev;
        dll_node_t* removed_node = list->head;
        list->head = aux1;
        aux1->prev = aux2;
        aux2->next = aux1;
        list->size--;
        return(removed_node);
    }

    if (n >= list->size - 1) {
        dll_node_t* aux1 = list->head->prev->prev;
        dll_node_t* removed_node = list->head->prev;
        aux1->next = list->head;
        list->head->prev = aux1;
        list->size--;
        return(removed_node);
    }

    dll_node_t* current = dll_get_nth_node(list, n);
    dll_node_t* aux1 = current->prev;
    dll_node_t* aux2 = current->next;
    dll_node_t* removed_node = current;
    aux1->next = aux2;
    aux2->prev = aux1;
    list->size--;
    return(removed_node);
}

/*Rotirea unei liste circulare generice se face
mutand pozitia HEAD-ului.*/
void dll_rotate(doubly_linked_list_t* list, char direction, int units)
{
    if (!list) {
		printf("error - list not found\n");
		return;
	}

    units = units % list->size;
    if (direction == 'c') {
        for (int i = 0; i < units; i++) {
            list->head = list->head->prev;
        }
    } else if (direction == 't') {
        for (int i = 0; i < units; i++) {
            list->head = list->head->next;
        }
    }
}

/*Procedura elibereaza memoria folosita de toate nodurile din lista,
iar la sfarsit, elibereaza memoria folosita de structura lista.*/
void
dll_free(doubly_linked_list_t** pp_list)
{
    doubly_linked_list_t* temp_list = *pp_list;

	if (!temp_list) {
		printf("error - list not found\n");
		return;
	}
    if (temp_list->head == NULL) {
        free(*pp_list);
        *pp_list = NULL;
        return;
    }

    dll_node_t* current = temp_list->head;
    dll_node_t* aux = current;
    current = current->next;
    free(aux->data);
    free(aux);
    while (current != temp_list->head) {
        aux = current;
        current = current->next;
        free(aux->data);
        free(aux);
    }

    free(*pp_list);
    *pp_list = NULL;
}

/*Functia afiseaza toate valorile int stocate in nodurile din lista
separate printr-un spatiu, incepand de la primul nod din lista.*/
void
dll_print_int_list(doubly_linked_list_t* list)
{
    if (!list) {
		printf("error - list not found\n");
		return;
	}

    if (!list->head)
        return;

    dll_node_t* current = list->head;
    printf("%d ", *(int*)(current->data));
    current = current->next;
    while (current != list->head) {
        printf("%d ", *(int*)(current->data));
        current = current->next;
    }

    printf("\n");
}
