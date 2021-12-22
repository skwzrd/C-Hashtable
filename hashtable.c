#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASH_SIZE 6
#define KV_SIZE 32


// hash table structure
typedef struct hash_entry{
    char key[KV_SIZE];
    char value[KV_SIZE];
    struct hash_entry* next;
} hash_entry;


// initialize hash table with values NULL
hash_entry* hash_table[HASH_SIZE] = {NULL};


// function declarations
hash_entry* create_entry(char key[], char value[]);

unsigned int get_hash(char* key);
hash_entry* get_entry(char *key);
char* get_value(char* key);

void insert_entry(hash_entry* entry);
void insert_kv(char* key, char* value);

void remove_entry(char* key);

void print(char* key);
void print_entry(hash_entry* entry);


// compute djb2 hash
unsigned int get_hash(char* key){
    unsigned long hash_value = 5381;
    int c;
    while (c = *key){
        hash_value = ((hash_value << 5) + hash_value) + c; /* hash * 33 + c */
        key++;
    }
    // assures the hash_value to be
    // within the hash_table's index range
    unsigned int hash_int = hash_value%HASH_SIZE;
    return hash_int;
}


// add entry into hash table
void insert_entry(hash_entry* entry){
    if(entry==NULL || entry->key==NULL){
        return;
    }

    unsigned int hash_value = get_hash(entry->key);
    // check if an entry exists at this array index
    if(hash_table[hash_value] != NULL)
    {
        hash_entry* cursor = hash_table[hash_value];
        // check if entry contains sought after key
        while(cursor != NULL)
        {
            if(strcmp(cursor->key, entry->key) == 0){
                strcpy(cursor->value, entry->value);
                return;
            }
            cursor = cursor->next;
        }
        entry->next = hash_table[hash_value];
    }
    hash_table[hash_value] = entry;
}


// get entry from hash table given a key
hash_entry* get_entry(char* key){
    if(key == NULL){
        return NULL;
    }

    unsigned int hash_value = get_hash(key);
    // check if an entry exists at this array index
    if(hash_table[hash_value] != NULL)
    {
        hash_entry* cursor = hash_table[hash_value];
        // check if entry contains sought after key
        while(cursor != NULL)
        {
            if(strcmp(cursor->key, key) == 0){
                return cursor;
            }
            cursor = cursor->next;
        }
    }
    // no index yet, or no matching key at index yet
    return NULL;
}


// remove key, value from hash table
void remove_entry(char* key){
    if(key == NULL){
        return;
    }

    unsigned int hash_value = get_hash(key);
    // check if an entry exists at this array index
    if(hash_table[hash_value] != NULL)
    {
        hash_entry* cursor = hash_table[hash_value];
        hash_entry* prev = cursor;
        // check if entry contains sought after key
        while(cursor != NULL)
        {
            if(strcmp(cursor->key, key) == 0)
            {
                // rm [0] in: [0]->NULL
                if(cursor->next == NULL && prev == cursor){
                    // printf("1. removing key: %s\n", key);
                    hash_table[hash_value] = NULL;
                    free(cursor);
                    cursor = NULL;
                    return;
                }

                // rm [0] in: [0]->[1]->NULL
                if(cursor->next != NULL && prev == cursor){
                    // printf("2. removing key: %s\n", key);
                    cursor = cursor->next;
                    hash_table[hash_value] = cursor;
                    free(prev);
                    prev=NULL;
                    return;
                }

                // rm [1] in: [0]->[1]->[2]->NULL
                if(cursor->next != NULL && prev != cursor){
                    // printf("3. removing key: %s\n", key);
                    prev->next = cursor->next;
                    free(cursor);
                    cursor = NULL;
                    return;
                }

                // rm [1] in: [0]->[1]->NULL
                if(cursor->next == NULL && prev != cursor){
                    // printf("4. removing key: %s\n", key);
                    prev->next = NULL;
                    free(cursor);
                    cursor = NULL;
                    return;
                }
                printf("5. WARNING key: %s\n", key);
            }
            prev = cursor;
            cursor = cursor->next;
        }
    }
}


// add entry from key, value pair into hash table
void insert_kv(char key[], char value[]){
    hash_entry* entry = create_entry(key, value);
    insert_entry(entry);
}


// get value from hash table given a key
char* get_value(char* key){
    hash_entry* entry = get_entry(key);
    if(entry != NULL){
        return entry->value;
    }
    return NULL;
}


// print entry
void print_entry(hash_entry* entry){
    if(entry==NULL){
        return;
    }
    printf("key: %s  value: %s\n", entry->key, entry->value);
}


// print hash table
void print_hash_table(){
    for (int i = 0; i < HASH_SIZE; i++)
    {
        hash_entry* entry = hash_table[i];
        if(entry == NULL){
            continue;
        }
        printf("At index %d:\n", i);
        while(entry != NULL){
            printf("\tkey: %s  value: %s\n", entry->key, entry->value);
            entry = entry->next;
        }
    }
}


// create an entry
hash_entry* create_entry(char key[], char value[]){
    hash_entry* entry = malloc(sizeof(hash_entry));

    if(strlen(key) < KV_SIZE && strlen(value) < KV_SIZE){
        strcpy(entry->key, key);
        strcpy(entry->value, value);
        entry->next = NULL;

        return entry;
    }
    return NULL;
}

// given a key, prints the key, value pair
void print(char* key){
    char* value = get_value(key);
    printf("\nhash_table[\"%s\"] = \"%s\"\n", key, value);
}


int main()
{
    hash_entry* entry_1 = create_entry("A", "1");
    hash_entry* entry_2 = create_entry("B", "2");

    insert_entry(entry_1);
    insert_entry(entry_2);

    insert_kv("C", "3");

    remove_entry("C");

    print_hash_table();

    print("A");

    print("C");

    /*
    Outputs:
    
        At index 2:
            key: A  value: 1
        At index 3:
            key: B  value: 2

        hash_table["A"] = "1"

        hash_table["C"] = "(null)"
    */

    return 0;
}