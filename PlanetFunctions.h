/*Copyright 2021 Anghel Andrei - Stelian 312CA*/

#ifndef PLANETFUNCTIONS_H_
#define PLANETFUNCTIONS_H_

#include "CircularDoublyLinkedList.h"

#define MAX_STRING_SIZE 25

typedef struct planet_t planet_t;
struct planet_t {
    char name[MAX_STRING_SIZE];
    int nr_kills;
    doubly_linked_list_t* shields;
};

void add_planet(doubly_linked_list_t* list, char* name,
                int index, int nr_shields);

void
planet_list_free(doubly_linked_list_t** planet_list);

void
remove_planet(doubly_linked_list_t* planet_list, int index, int message);

void show(doubly_linked_list_t* planet_list, int planet_index);

void
collide_planets(doubly_linked_list_t* planet_list, int index1, int index2);

void
rotate_planet(doubly_linked_list_t* planet_list, int planet_index,
                char direction, int units);

#endif  // PLANETFUNCTIONS_H_
