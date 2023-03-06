/*Copyright 2021 Anghel Andrei - Stelian 312CA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/home/student/CircularDoublyLinkedList.h"
#include "/home/student/PlanetFunctions.h"
#include "/home/student/ShieldFunctions.h"

#define MAX_LINE_SIZE 256
#define MAX_STRING_SIZE 25

int main(void)
{
    int command_number = 0;
    /*Variabila "trash" este folosita pentru citirea
    caracterului "\n" de la finalul primei linii de input.*/
    char line[MAX_LINE_SIZE], trash;

    scanf("%d%c", &command_number, &trash);

    /*Initializarea listei ce stocheaza
    datele de tipul "planet_t".*/
    doubly_linked_list_t* planet_list = dll_create(sizeof(planet_t));

    for (int i = 0; i < command_number; i++) {
        fgets(line, MAX_LINE_SIZE, stdin);
        /*Eliminarea caracterului "\n"
        citit de functia fgets().*/
        char* p = strchr(line, '\n');
        if (p)
            *p = '\0';

        char command[MAX_STRING_SIZE] = {0};
        sscanf(line, "%s", command);

        /*In functie de valoarea string-ului "command" se va
        apela functia corespunzatoare comenzii dorite.*/
        if (strcmp(command, "ADD") == 0) {
            char planet_name[MAX_STRING_SIZE];
            int planet_index, nr_shields;
            sscanf(line, "%s%s%d%d", command, planet_name,
                    &planet_index, &nr_shields);
            add_planet(planet_list, planet_name, planet_index, nr_shields);

        } else if (strcmp(command, "BLH") == 0) {
            int planet_index;
            sscanf(line, "%s%d", command, &planet_index);
            remove_planet(planet_list, planet_index, 1);

        } else if (strcmp(command, "UPG") == 0) {
            int planet_index, shield_index, upgrade_value;
            sscanf(line, "%s%d%d%d", command, &planet_index,
                    &shield_index, &upgrade_value);
            upgrade_shield(planet_list, planet_index,
                            shield_index, upgrade_value);

        } else if (strcmp(command, "EXP") == 0) {
            int planet_index, upgrade_value;
            sscanf(line, "%s%d%d", command, &planet_index, &upgrade_value);
            add_shield(planet_list, planet_index, upgrade_value);

        } else if (strcmp(command, "RMV") == 0) {
            int planet_index, shield_index;
            sscanf(line, "%s%d%d", command, &planet_index, &shield_index);
            remove_shield(planet_list, planet_index, shield_index);

        } else if (strcmp(command, "COL") == 0) {
            int index1, index2;
            sscanf(line, "%s%d%d", command, &index1, &index2);
            collide_planets(planet_list, index1, index2);

        } else if (strcmp(command, "ROT") == 0) {
            char direction;
            int planet_index, units;
            sscanf(line, "%s %d %c %d", command, &planet_index,
                    &direction, &units);
            rotate_planet(planet_list, planet_index, direction, units);

        } else if (strcmp(command, "SHW") == 0) {
            int planet_index;
            sscanf(line, "%s%d", command, &planet_index);
            show(planet_list, planet_index);

        } else {
            /*Cazul in care comanda introdusa
            este una invalida.*/
            printf("Invalid command!\n");
        }
    }

    /*Eliberarea memoriei utilizate.*/
    planet_list_free(&planet_list);
    return 0;
}
