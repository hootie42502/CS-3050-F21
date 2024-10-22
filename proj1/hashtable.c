#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashtable.h"

/*
 * Create the hash table
 * This creates a new hash table with
 * all empty entries
 * The number of entries is fixed 
 * for this demo
 */
hash_table new_table()
{
    hash_table h;
    for (int i = 0; i < hash_size; ++i)
    {
        h.entries[i] = NULL;
    }
    return h;
}

int hash(char s[100])
{
    int i = 0;
    int hash = 0;
    while (i < 100 && s[i] != '\0')
    {
        hash = (1 + hash * 128) % hash_size;
        hash = (hash + (s[i] % 128)) % hash_size;
        i++;
    }
    return hash;
}

/*
 * Get the index of an entry
 * this method is used to quickly swap
 * between hashing methods for a string
 */
int get_index(char s[100])
{
    return hash(s);
}





/*
 * Add an entry based on the hash of the key
 * Because the amount of possible keys is more
 * than my hash size, it is going to have a 
 * collision
 */
void add_entry(hash_table * table, char name[100])
{
    int index = get_index(name);
    if (table->entries[index] != NULL)
    {
        /*
        We had a collision
         */
        linked_list * a = table->entries[index];
        while (a != NULL)
        {
            /*
            We found the key
             */
            if (strcmp(a->name, name) == 0)
            {
                break;
            }
            else
            {
                a = a->next;
            }
        }
        if (a == NULL)
        {
            a = (linked_list*)malloc(sizeof(linked_list));
            strcpy(a->name, name);
            append_head(table->entries[index], a);
            table->entries[index] = a;
        }
    }
    else
    {
        /*
         There was no collision
         */

        table->entries[index] = (linked_list*)malloc(sizeof(linked_list));
        strcpy(table->entries[index]->name, name);
        if (table->entries[index] == NULL)
        {
            printf("oh\n");
        }
    }
}



void clean_up_linked_list(linked_list * a)
{
    linked_list * todel = a;
    while (todel != NULL)
    {
        linked_list * next = todel->next;
        free(todel);
        todel = next;
    }
}

void clean_up_table(hash_table * table)
{
    for (int i = 0; i < hash_size; ++i)
    {
        if (table->entries[i] != NULL)
        {
            clean_up_linked_list(table->entries[i]);
            table->entries[i] = NULL;
        }
    }
}

void add_friend(linked_list * a, linked_list * append)
{
    if (append->next == NULL)
    {
        append->previous = a->previous;
        a->previous = append;
        append->next = a;

    }
}

void append_head(linked_list * a, linked_list * append)
{
    if (append->next == NULL)
    {
        append->previous = a->previous;
        a->previous = append;
        append->next = a;

    }
}

void append_after(linked_list * a, linked_list * append)
{
    if (append->previous == NULL)
    {
        append->next = a->next;
        a->next = append;
        append->previous = a;
    }
}

void remove_next(linked_list * a)
{
    if (a->next != NULL)
    {
        linked_list * tmp = a->next;
        a->next = a->next->next;
        free(tmp);
    }
    else
    {
        printf("nothing to remove!\n");
    }
}

void remove_previous(linked_list * a)
{
    if (a->previous != NULL)
    {
        printf("removing name: %s \n", a->previous->name);
        linked_list * tmp = a->previous;
        printf("a->name: %s\n", a->name);

        a->previous = a->previous->previous;
        if (a->previous != NULL)
        {
            a->previous->next = a;
        }
        free(tmp);
        if (a->next == NULL)
        {
            printf("this person has no next\n");
        }
    }
    else
    {
        printf("nothing to remove!\n");
    }
}

void print_linked_list(linked_list * a)
{
	
    if (a == NULL)
    {
        printf("[]\n");
        return;
    }
    linked_list * t = a;

    printf("[(%s)", t->name);
    t = t->next;
    while (t != NULL)
    {
        printf("-->(%s)", t->name);
        t = t->next;
    }
    printf("]\n");
}

void print_friends_list(friends_list * a)
{
	
    if (a == NULL)
    {
        printf("[]\n");
        return;
    }
    friends_list * t = a;

    printf("[(%s)", t->friendName);
    t = t->nextFriend;
    while (t != NULL)
    {
        printf("-->(%s)", t->friendName);
        t = t->nextFriend;
    }
    printf("]\n");
}


void print_hash_table(hash_table table)
{

    for (int i = 0; i < hash_size; ++i)
    {
        print_linked_list(table.entries[i]);
    }
    return;
}

void delete_entry(hash_table * table, char name[100])
{
    int index = get_index(name);
    linked_list * a = table->entries[index];
    while (a != NULL)
    {
        if (strcmp(a->name, name) == 0)
        {
            // delete
            a = a->previous;
            if (a == NULL)
            {
                a = table->entries[index];
                a = a->next;
                if (a == NULL)
                {
                    clean_up_linked_list(table->entries[index]);
                }
                remove_previous(a);
                
                table->entries[index] = a;
            }
            else {
                remove_next(a);
            }

        }
        a = a->next;
    }

}

void run()
{
    hash_table table = new_table();
    char input;
    char *command = NULL;
    char *name1;
    char *name2;
    printf("input: \n");
    scanf("%s", &input);
    char *p = strtok(&input, " ");
	if(p != NULL)
	{
	    command = p;
	    p = strtok(NULL, " ");
	
		if(p != NULL)
		{	
			name1 = p;
	    		p = strtok(NULL, " ");
		
			if(p != NULL)
			{
			    name2 = p;
	    		    p = strtok(NULL, "\0");
			}
		}
	}
	if(*command == 'P')
	{
	    add_entry(&table,name1);
	}
	if(*command == 'F')
	{
	    //friend(name1,name2);
	}
	if(*command == 'U')
	{
	    //unfriend(name1,name2);
	}
	if(*command == 'L')
	{
	    //print_friends_list(name1);
	}
	if(*command == 'Q')
	{
	    //checkFriends(name1,name2);
	}
    while(*command != 'X')
    {
        scanf("%s", &input);
	char *p = strtok(&input, " ");
	if(p != NULL)
	{
	    command = p;
	    p = strtok(NULL, " ");
	
		if(p != NULL)
		{	
			name1 = p;
	    		p = strtok(NULL, " ");
			
			if(p != NULL)
			{
			    name2 = p;
	    		    p = strtok(NULL, "\0");
			}
		}
	}
	if(*command == 'P')
	{
	    add_entry(&table,name1);
	}
	if(*command == 'F')
	{
	    //friend(name1,name2);
	}
	if(*command == 'U')
	{
	    //unfriend(name1,name2);
	}
	if(*command == 'L')
	{
	    //print_friends_list(name1);
	}
	if(*command == 'Q')
	{
	    //checkFriends(name1,name2);
	}
		
    }
    
    printf("\nAll Done\n");
}

