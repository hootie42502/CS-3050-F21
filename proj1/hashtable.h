#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdlib.h>
#include <string.h>
#define hash_size 10

typedef struct friend_list
{
    char friendName[100];
    struct friend_list * nextFriend;
} friend_list;

typedef struct linked_list
{
    char name[100];
    friend_list * nextFriend;
    struct linked_list * previous;
    struct linked_list * next;
} linked_list;

typedef struct
{
    linked_list * entries[hash_size];
} hash_table;


hash_table new_table();

int hash(char s[100]);
int get_index(char s[100]);

int get_empty_entries(hash_table * table);
void clean_up_linked_list(linked_list * a);

void clean_up_table(hash_table * table);

void append_head(linked_list * a, linked_list * append);

void append_after(linked_list * a, linked_list * append);

void remove_next(linked_list * a);

void remove_previous(linked_list * a);

void print_linked_list(linked_list * a);

void print_hash_table(hash_table table);

void add_entry(hash_table * table, char name[100]);

char * find_table(hash_table * table, char name[100]);

void delete_entry(hash_table * table, char name[100]);


#endif
