#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 3e6 + 9
class ListaMiast;
unsigned long long hash_function(char* str);

typedef struct Item
{
    char* key;
    ListaMiast* value;
} Item;
typedef struct LinkedList
{
    Item* item;
    LinkedList* next = NULL;
} LinkedList;

class HashMap
{
public:
    Item** items;
    LinkedList** overflow_buckets;
    int size;
    int count;
};
LinkedList* allocate_list();


LinkedList* linkedlist_insert(LinkedList* list, Item* item);
Item* linkedlist_remove(LinkedList* list);

void free_linkedlist(LinkedList* list);

LinkedList** create_overflow_buckets(HashMap* table);

void free_overflow_buckets(HashMap* table);

Item* create_item(char* key, ListaMiast* value);
HashMap* create_table(int size);
void free_item(Item* item);

void free_table(HashMap* table);
void print_table(HashMap* table);
void handle_collision(HashMap* table, unsigned long index, Item* item);

void ht_insert(HashMap* table, char* key, ListaMiast* value);
ListaMiast* ht_search(HashMap* table, char* key);
void ht_delete(HashMap* table, char* key);

void print_search(HashMap* table, char* key);



