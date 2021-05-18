#include <stdio.h>  /* gets */
#include <stdlib.h> /* atoi, malloc */
#include <string.h> /* strcpy */
#include "uthash.h"

typedef struct my_struct {
    int ikey; /* key */
    char value[10];
    UT_hash_handle hh; /* makes this structure hashable */
} UTHash;

static UTHash *g_users = NULL;

void add_user(int mykey, char *value)
{
    UTHash *s;

    HASH_FIND_INT(g_users, &mykey, s); /* mykey already in the hash? */
    if (s == NULL) {
        s = (UTHash *)malloc(sizeof(UTHash));
        s->ikey = mykey;
        HASH_ADD_INT(g_users, ikey, s); /* ikey: name of key field */
    }
    strcpy(s->value, value);
}

UTHash *find_user(int mykey)
{
    UTHash *s;

    HASH_FIND_INT(g_users, &mykey, s); /* s: output pointer */
    return s;
}

void delete_user(UTHash *user)
{
    HASH_DEL(g_users, user); /* user: pointer to deletee */
    free(user);
}

void delete_all()
{
    UTHash *current_user, *tmp;

    HASH_ITER(hh, g_users, current_user, tmp)
    {
        HASH_DEL(g_users, current_user); /* delete it (users advances to next) */
        free(current_user);              /* free it */
    }
}

void print_users()
{
    UTHash *s;

    for (s = g_users; s != NULL; s = (UTHash *)(s->hh.next)) {
        printf("user ikey %d: value %s\n", s->ikey, s->value);
    }
}

int name_sort(UTHash *a, UTHash *b)
{
    return strcmp(a->value, b->value);
}

int id_sort(UTHash *a, UTHash *b)
{
    return (a->ikey - b->ikey);
}

void sort_by_name()
{
    HASH_SORT(g_users, name_sort);
}

void sort_by_id()
{
    HASH_SORT(g_users, id_sort);
}

int main(int argc, char *argv[])
{
    char in[10];
    int ikey = 1, running = 1;
    UTHash *s;
    unsigned num_users;

    printf(" 1. add user\n");
    printf(" 2. add/rename user by id\n");
    printf(" 3. find user\n");
    printf(" 4. delete user\n");
    printf(" 5. delete all users\n");
    printf(" 6. sort items by name\n");
    printf(" 7. sort items by id\n");
    printf(" 8. print users\n");
    printf(" 9. count users\n");
    printf("10. quit\n");

    while (running) {
        gets(in);
        switch (atoi(in)) {
            case 1:
                printf("name?\n");
                add_user(ikey++, gets(in));
                break;
            case 2:
                printf("id?\n");
                gets(in);
                ikey = atoi(in);
                printf("name?\n");
                add_user(ikey, gets(in));
                break;
            case 3:
                printf("id?\n");
                s = find_user(atoi(gets(in)));
                printf("user: %s\n", s ? s->value : "unknown");
                break;
            case 4:
                printf("id?\n");
                s = find_user(atoi(gets(in)));
                if (s)
                    delete_user(s);
                else
                    printf("id unknown\n");
                break;
            case 5:
                delete_all();
                break;
            case 6:
                sort_by_name();
                break;
            case 7:
                sort_by_id();
                break;
            case 8:
                print_users();
                break;
            case 9:
                num_users = HASH_COUNT(g_users);
                printf("there are %u users\n", num_users);
                break;
            case 10:
                running = 0;
                break;
        }
    }

    delete_all(); /* free any structures */
    return 0;
}
