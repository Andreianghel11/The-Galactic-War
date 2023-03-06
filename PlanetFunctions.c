/*Copyright 2021 Anghel Andrei - Stelian 312CA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/home/student/PlanetFunctions.h"
#include "/home/student/utils.h"
#include "/home/student/CircularDoublyLinkedList.h"
#define MAX_STRING_SIZE 25

/*Adauga in lista de planete un nou nod ce pointeaza
la structura de tip "planet_t". Se initializeaza
campurile structurii, inclusiv lista de scuturi cu valoarea
initiala 1.*/
void add_planet(doubly_linked_list_t* planet_list, char* name,
                int index, int nr_shields)
{
    if ((unsigned int)index > planet_list->size) {
        printf("Planet out of bounds!\n");
        return;
    }

    /*Initializarea structurii.*/
    planet_t planet;
    snprintf(planet.name, MAX_STRING_SIZE, "%s", name);
    planet.nr_kills = 0;
    /*Crearea listei de scuturi.*/
    planet.shields = dll_create(sizeof(int));
    for (int i = 0; i < nr_shields; i++) {
        int shield_value = 1;
        dll_add_nth_node(planet.shields, 0, &shield_value);
    }

    /*Adaugarea nodului creat la lista de planete.*/
    dll_add_nth_node(planet_list, index, &planet);
    printf("The planet %s has joined the galaxy.\n", name);
}

/*Elimina din lista de planete nodul specificat. Se dealoca
memoria necesara stocarii nodului. ATENTIE! Dealocarea memoriei
pentru lista de scuturi trebuie sa aiba loc inainte de eliberarea
memoriei pentru structura de tip "planet_t".*/
void remove_planet(doubly_linked_list_t* planet_list, int index, int message)
{
    if ((unsigned int)index >= planet_list->size) {
        printf("Planet out of bounds!\n");
        return;
    }

    dll_node_t* removed_node = dll_remove_nth_node(planet_list, index);
    planet_t* planet = (planet_t*)(removed_node->data);
    dll_free(&(planet->shields));
    char name[MAX_STRING_SIZE];
    snprintf(name, MAX_STRING_SIZE, "%s", planet->name);
    free(removed_node->data);
    free(removed_node);

    /*Eliminarea nodului are loc atat in cadrul comenzii "BLH", cat si
    in cadrul comenzii "COL". Apelam functia cu parametrul message = 1
    doar pentru comanda "BLH", cand vrem sa afisam mesajul de mai jos.*/
    if (message == 1)
        printf("The planet %s has been eaten by the vortex.\n", name);
}

/*Identificarea scuturilor ce se vor "ciocni" se realizeaza prin
intermediul functiei dll_get_nth_node(). Sunt tratate separat cazurile
pentru diferitele valori ale scuturilor.*/
void
collide_planets(doubly_linked_list_t* planet_list, int index1, int index2)
{
    if ((unsigned int)index1 >= planet_list->size ||
        (unsigned int)index2 >= planet_list->size) {
        printf("Planet out of bounds!\n");
        return;
    }

    dll_node_t* current_planet = dll_get_nth_node(planet_list, index1);
    planet_t* planet1 = (planet_t*)(current_planet->data);
    dll_node_t* next_planet = current_planet->next;
    planet_t* planet2 = (planet_t*)(next_planet->data);

    int shield_index1 = (planet1->shields->size) / 4;
    int shield_index2 = ((planet2->shields->size) / 4) * 3;

    dll_node_t* shield1 = dll_get_nth_node(planet1->shields, shield_index1);
    dll_node_t* shield2 = dll_get_nth_node(planet2->shields, shield_index2);

    /*Atunci cand ambele scuturi au valoarea 0, iar planetele se distrug
    una pe cealalta, eliminarea primeia dintre planete va duce la
    modificarea listei. Astfel, trebuie ca functia remove_planet()sa fie
    apelata de doua ori cu acelasi indice, cel corespunzator
    planetei intai (in cazul de fata, "index1").*/ 
    if (*(int*)(shield1->data) == 0 && *(int*)(shield2->data) == 0) {
        printf("The planet %s has imploded.\n", planet1->name);
        remove_planet(planet_list, index1, 0);
        printf("The planet %s has imploded.\n", planet2->name);
        remove_planet(planet_list, index1, 0);

    } else if (*(int*)(shield1->data) == 0) {
        printf("The planet %s has imploded.\n", planet1->name);
        (planet2->nr_kills)++;
        (*(int*)(shield2->data))--;
        remove_planet(planet_list, index1, 0);

    } else if (*(int*)(shield2->data) == 0) {
        printf("The planet %s has imploded.\n", planet2->name);
        (planet1->nr_kills)++;
        (*(int*)(shield1->data))--;
        remove_planet(planet_list, index2, 0);

    } else {
        (*(int*)(shield1->data))--;
        (*(int*)(shield2->data))--;
    }
}

/*Functia corespunzatoare operatiei de ROTATE.*/
void
rotate_planet(doubly_linked_list_t* planet_list, int planet_index,
                char direction, int units)
{
    if ((unsigned int)planet_index >= planet_list->size) {
        printf("Planet out of bounds!\n");
        return;
    }

    if (direction != 'c' && direction != 't') {
        printf("Not a valid direction!\n");
        return;
    }

    dll_node_t* current = dll_get_nth_node(planet_list, planet_index);
    planet_t* planet = (planet_t*)(current->data);

    /*Se apeleaza functia de rotatie
    pentru o lista circulara generica.*/
    dll_rotate(planet->shields, direction, units);
}

/*Functia corespunzatoare comenzii "SHW". Sunt tratate
cazurile limita (cand galaxia are doar una sau doua planete).*/
void show(doubly_linked_list_t* planet_list, int planet_index)
{
    if ((unsigned int)planet_index >= planet_list->size
        || planet_list->head == NULL) {
        printf("Planet out of bounds!\n");
        return;
    }

    dll_node_t* current = dll_get_nth_node(planet_list, planet_index);
    planet_t* planet = (planet_t*)(current->data);
    printf("NAME: %s\nCLOSEST: ", planet->name);

    if (planet_list->size == 1) {
        printf("none\n");
    } else if (planet_list->size == 2) {
        planet_t* next_planet = (planet_t*)(current->next->data);
        printf("%s\n", next_planet->name);
    } else {
        planet_t* next_planet = (planet_t*)(current->next->data);
        planet_t* prev_planet = (planet_t*)(current->prev->data);
        printf("%s and %s\n", prev_planet->name, next_planet->name);
    }

    printf("SHIELDS: ");
    dll_print_int_list(planet->shields);
    printf("KILLED: %d\n", planet->nr_kills);
}

/*Eliberarea memoriei alocate pentru lista de planete.
Sunt eliberate mai intai listele ce stocheaza scuturile.*/
void planet_list_free(doubly_linked_list_t** planet_list)
{
    doubly_linked_list_t* temp_list = *planet_list;

	if (!temp_list) {
		printf("error - list not found\n");
		return;
	}
    if (temp_list->head == NULL) {
        free(*planet_list);
        *planet_list = NULL;
        return;
    }

    dll_node_t* current = temp_list->head;
    dll_node_t* aux = current;
    current = current->next;
    planet_t* planet = (planet_t*)(aux->data);

    dll_free(&(planet->shields));
    free(aux->data);
    free(aux);

    while (current != temp_list->head) {
        aux = current;
        current = current->next;
        planet_t* planet = (planet_t*)(aux->data);
        dll_free(&(planet->shields));
        free(aux->data);
        free(aux);
    }

    free(*planet_list);
    *planet_list = NULL;
}
