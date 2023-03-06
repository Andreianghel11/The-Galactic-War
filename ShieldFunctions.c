/*Copyright 2021 Anghel Andrei - Stelian 312CA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/home/student/PlanetFunctions.h"
#include "/home/student/ShieldFunctions.h"
#include "/home/student/utils.h"
#include "/home/student/CircularDoublyLinkedList.h"

/*Functia corespunzatoare comenzii "UPG".*/
void
upgrade_shield(doubly_linked_list_t* planet_list, int planet_index,
                int shield_index, int upgrade_value)
{
    if ((unsigned int)planet_index >= planet_list->size) {
        printf("Planet out of bounds!\n");
        return;
    }

    dll_node_t* current = dll_get_nth_node(planet_list, planet_index);
    planet_t* planet = (planet_t*)(current->data);
    if ((unsigned int)shield_index >= planet->shields->size) {
        printf("Shield out of bounds!\n");
        return;
    }

    current = dll_get_nth_node(planet->shields, shield_index);
    (*(int*)(current->data)) += upgrade_value;
}

/*Functia corespunzatoare comenzii "EXP".*/
void
add_shield(doubly_linked_list_t* planet_list, int planet_index,
            int upgrade_value)
{
    if ((unsigned int)planet_index >= planet_list->size) {
        printf("Planet out of bounds!\n");
        return;
    }

    dll_node_t* current = dll_get_nth_node(planet_list, planet_index);
    planet_t* planet = (planet_t*)(current->data);
    /*Se apeleaza functia de adaugare a nodului cu un indice
    egal cu marimea listei (scutul se adauga mereu la finalul listei).*/
    dll_add_nth_node(planet->shields, planet->shields->size, &upgrade_value);
}

/*Functia corespunzatoare comenzii "RMV". Se elibereaza
memoria pentru nodul asociat scutului eliminat.*/
void
remove_shield(doubly_linked_list_t* planet_list, int planet_index,
                int shield_index)
{
    if ((unsigned int)planet_index >= planet_list->size) {
        printf("Planet out of bounds!\n");
        return;
    }

    dll_node_t* current = dll_get_nth_node(planet_list, planet_index);
    planet_t* planet = (planet_t*)(current->data);

    if ((unsigned int)shield_index >= planet->shields->size) {
        printf("Shield out of bounds!\n");
        return;
    }
    if (planet->shields->size == 4) {
        printf("A planet cannot have less than 4 shields!\n");
        return;
    }
    dll_node_t* removed_node =
            dll_remove_nth_node(planet->shields, shield_index);
    free(removed_node->data);
    free(removed_node);
}
