/*Copyright 2021 Anghel Andrei - Stelian 312CA*/

#ifndef SHIELDFUNCTIONS_H_
#define SHIELDFUNCTIONS_H_

#include "CircularDoublyLinkedList.h"

void
upgrade_shield(doubly_linked_list_t* planet_list, int planet_index,
                int shield_index, int upgrade_value);

void
add_shield(doubly_linked_list_t* planet_list, int planet_index,
                int upgrade_value);

void
remove_shield(doubly_linked_list_t* planet_list, int planet_index,
                int shield_index);

#endif  // SHIELDFUNCTIONS_H_
