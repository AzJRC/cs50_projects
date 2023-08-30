#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node 
{
    char *phrase;
    struct node *next;
}
node;

#define LIST_SIZE 2
#define HASH_TABLE_SIZE 26

char *get_string() {
    char c;
    int len = 0;
    char *phrase = malloc(sizeof(char));
    if (phrase == NULL) {
            printf("Memory allocation error.\n");
            return "1";
        }
    while ((c = getchar()) != '\n') {
        phrase = realloc(phrase, sizeof(char) * (len + 1));
        if (phrase == NULL) {
            printf("Memory reallocation error.\n");
            return "1";
        }
        phrase[len] = c;
        len++;
    }
    // Replace new-line character with NUL character
    phrase[len] = '\0';
    return phrase;
}

int hash_function(char *str) {
    char c = str[0];
    int value = c - 'A';
    return value;
}

node *linked_list(node *main_list, char *str) {
    //add str to new node
    node *n = malloc(sizeof(node));
    n->phrase = str;
    n->next = main_list;
    main_list = n;
    return main_list;
}

node *print_linked_list_from_end(node *list) {
    if (list->next != NULL) {
        print_linked_list_from_end(list->next);
    }
    printf("%s\n", list->phrase);
    return 0;
};

node *free_linked_list(node *list) {
    if (list->next != NULL) {
        free_linked_list(list->next);
    }
    free(list);
    return 0;
};


int main() 
{
    node *hash_table[HASH_TABLE_SIZE];
    node *list = NULL;
    int bucket;
    char *str = NULL;

    for (int i = 0; i < LIST_SIZE; i++) {
        printf("Input a string: ");
        str = get_string(); //function to obtain input from the user
        bucket = hash_function(str); //Obtain the hash value of the string in order to store it in the correct bucket
        list = linked_list(list, str); //function to store input in the linked list
        hash_table[bucket] = list; //Store pointer in the hash table
    }

    //print linked list
    print_linked_list_from_end(list);

    //free nodes
    free_linked_list(list);

    return 0;
}