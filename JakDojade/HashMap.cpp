#include "HashMap.h"
#include "ListaSasiedztwa.h"
#include <string.h>
#include "Zarzadzanie.h"
using namespace std;
unsigned long long hash_function(char* str)
{
    const int p = 40;
    const int m = HASHSIZE;
    long long hash_value = 0;
    long long p_pow = 1;
    for (int j = 0; str[j]; j++) {
        hash_value = (hash_value + (str[j] - '0' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;

    /*

    unsigned long i = 0;

    for (int j = 0; str[j]; j++)
        i += str[j];

    return i % CAPACITY;*/
}
LinkedList* allocate_list()
{
    // Allocates memory for a LinkedList pointer.
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->next = NULL;
    list->item = NULL;
    return list;
}

LinkedList* linkedlist_insert(LinkedList* list, Item* item)
{
    // Inserts the item onto the LinkedList.
    if (!list)
    {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }
    else if (list->next == NULL)
    {
        
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList* temp = list;

    while (temp->next->next)
    {
        temp = temp->next;
    }

    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    return list;
}
Item* linkedlist_remove(LinkedList* list)
{
    // Removes the head from the LinkedList.
    // Returns the item of the popped element.
    if (!list)
        return NULL;

    if (!list->next)
        return NULL;

    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    Item* it = NULL;
    memcpy(temp->item, it, sizeof(Item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}

void free_linkedlist(LinkedList* list)
{
    LinkedList* temp = list;

    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

LinkedList** create_overflow_buckets(HashMap* table)
{
    // Create the overflow buckets; an array of LinkedLists.
    LinkedList** buckets = (LinkedList**)calloc(table->size, sizeof(LinkedList*));

    for (int i = 0; i < table->size; i++)
        buckets[i] = NULL;

    return buckets;
}

void free_overflow_buckets(HashMap* table)
{
    // Free all the overflow bucket lists.
    LinkedList** buckets = table->overflow_buckets;

    for (int i = 0; i < table->size; i++)
        free_linkedlist(buckets[i]);

    free(buckets);
}

Item* create_item(char* key, ListaMiast* value)
{
    // alokownie pamieci
    Item* item = (Item*)malloc(sizeof(Item));
    item->key = (char*)malloc(strlen(key) + 1);
    item->value = (ListaMiast*)malloc(sizeof(ListaMiast*));
    //przypisanie wartosci 
    strcpy_s(item->key, strlen(key) + 1, key);
    item->value = value;
    return item;
}
HashMap* create_table(int size)
{
    // Creates a new HashTable.
    HashMap* table = (HashMap*)malloc(sizeof(HashMap));
    table->size = size;
    table->count = 0;
    table->items = (Item**)malloc(table->size* sizeof(Item*));

    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;

    table->overflow_buckets = create_overflow_buckets(table);

    return table;
}
void free_item(Item* item)
{
    // Frees an item.
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashMap* table)
{
    // Frees the table.
    for (int i = 0; i < table->size; i++)
    {
        Item* item = table->items[i];

        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}
void print_table(HashMap* table)
{
    printf("\nHash Table\n-------------------\n");

    for (int i = 0; i < table->size; i++)
    {
        if (table->items[i])
        {
            printf("Index:%d, Key:%s,", i, table->items[i]->key);
            cout << table->items[i]->value->Sasiedztwo->nazwa << endl;
        }
    }

    printf("-------------------\n\n");
}
void handle_collision(HashMap* table, unsigned long index, Item* item)
{
    LinkedList* head = table->overflow_buckets[index];

    if (head == NULL)
    {
        // Creates the list.
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else
    {
        // Insert to the list.
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
}

void ht_insert(HashMap* table, char* key, ListaMiast* value)
{
    // Creates the item.
    Item* item = create_item(key, value);

    // ---------------------------
    long long index = hash_function(key);

    Item* current_item = table->items[index];

    if (key[0] == '\0') {
        int a = 0;
    }

    if (current_item == NULL)
    {
        // Key does not exist.
        if (table->count == table->size)
        {
            // HashTable is full.
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }

        // Insert directly.
        table->items[index] = item;
        table->count++;
    }
    else {
        cout << "kolizja";
        if (strcmp(current_item->key, key) == 0)
        {
            current_item->value = value;
            return;
        }
        else {
            handle_collision(table, index, item);
            return;
        }
    }
}
ListaMiast* ht_search(HashMap* table, char* key)
{
    // Searches for the key in the HashTable.
    // Returns NULL if it doesn't exist.
    long long index = hash_function(key);
    Item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];

    // Provide only non-NULL values.
    if (item != NULL)
    {
        if (strcmp(item->key, key) == 0)
            return item->value;

        if (head == NULL)
            return NULL;

        item = head->item;
        head = head->next;
    }

    return NULL;
}
void ht_delete(HashMap* table, char* key)
{
    // Deletes an item from the table.
    long long index = hash_function(key);
    Item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];

    if (item == NULL)
    {
        // Does not exist.
        return;
    }
    else
    {
        if (head == NULL && strcmp(item->key, key) == 0)
        {
            // Collision chain does not exist.
            // Remove the item.
            // Set table index to NULL.
            table->items[index] = NULL;
            free_item(item);
            table->count--;
            return;
        }
        else if (head != NULL)
        {
            // Collision chain exists.
            if (strcmp(item->key, key) == 0)
            {
                // Remove this item.
                // Set the head of the list as the new item.
                free_item(item);
                LinkedList* node = head;
                head = head->next;
                node->next = NULL;
                table->items[index] = create_item(node->item->key, node->item->value);
                free_linkedlist(node);
                table->overflow_buckets[index] = head;
                return;
            }

            LinkedList* curr = head;
            LinkedList* prev = NULL;

            while (curr)
            {
                if (strcmp(curr->item->key, key) == 0)
                {
                    if (prev == NULL)
                    {
                        // First element of the chain.
                        // Remove the chain.
                        free_linkedlist(head);
                        table->overflow_buckets[index] = NULL;
                        return;
                    }
                    else
                    {
                        // This is somewhere in the chain.
                        prev->next = curr->next;
                        curr->next = NULL;
                        free_linkedlist(curr);
                        table->overflow_buckets[index] = head;
                        return;
                    }
                }

                curr = curr->next;
                prev = curr;
            }
        }
    }
}

void print_search(HashMap* table, char* key)
{
    ListaMiast* val;

    if ((val = ht_search(table, key)) == NULL)
    {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else
    {
        printf("Key:%s, Value:%s\n", key, val);
    }
}


