/*   
   Copyright 2016 electrolink-server-c

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "hash_table.h"

struct entry_s {
    char *key;
    funct_t value;
    struct entry_s *next;
};

struct hashtable_s {
    int size;
    struct entry_s **table;     
};


/* Create a new hashtable. */
hashtable_t *ht_create( int size ) {

    hashtable_t *hashtable = NULL;
    int i;

    if( size < 1 ) return NULL;

    /* Allocate the table itself. */
    if( ( hashtable = static_malloc( sizeof( hashtable_t ) ) ) == NULL ) {
        return NULL;
    }

    /* Allocate pointers to the head nodes. */
    if( ( hashtable->table = static_malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
        return NULL;
    }
    for( i = 0; i < size; i++ ) {
        hashtable->table[i] = NULL;
    }

    hashtable->size = size;

    return hashtable;   
}

/* Hash a string for a particular hash table. */
int ht_hash( hashtable_t *hashtable, char *key ) {

    unsigned long int hashval = 0;
    int i = 0;

    while(*key != '\0') {
        hashval = hashval * HASH_MULTIPLIER + *key;
        key++;
    }

    return hashval % hashtable->size;
}

/* Create a key-value pair. */
entry_t *ht_newpair( char *key, funct_t value ) {
    entry_t *newpair;

    if( ( newpair = static_malloc( sizeof( entry_t ) ) ) == NULL ) {
        return NULL;
    }

    if( ( newpair->key = strdup( key ) ) == NULL ) {
        return NULL;
    }

    if( ( newpair->value = value ) == NULL ) {
        return NULL;
    }

    newpair->next = NULL;

    return newpair;
}

/* Insert a key-value pair into a hash table. */
void ht_set( hashtable_t *hashtable, char *key, funct_t value ) {
    int bin = 0;
    entry_t *newpair = NULL;
    entry_t *next = NULL;
    entry_t *last = NULL;

    bin = ht_hash( hashtable, key );

    next = hashtable->table[ bin ];

    while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
        last = next;
        next = next->next;
    }

    /* There's already a pair.  Let's replace that string. */
    if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

        static_free( next->value );
        next->value = value;

    /* Nope, could't find it.  Time to grow a pair. */
    } else {
        newpair = ht_newpair( key, value );

        /* We're at the start of the linked list in this bin. */
        if( next == hashtable->table[ bin ] ) {
            newpair->next = next;
            hashtable->table[ bin ] = newpair;
    
        /* We're at the end of the linked list in this bin. */
        } else if ( next == NULL ) {
            last->next = newpair;
    
        /* We're in the middle of the list. */
        } else  {
            newpair->next = next;
            last->next = newpair;
        }
    }
}

/* Retrieve a key-value pair from a hash table. */
funct_t ht_get( hashtable_t *hashtable, char *key ) {
    int bin = 0;
    entry_t *pair;

    bin = ht_hash( hashtable, key );

    /* Step through the bin, looking for our value. */
    pair = hashtable->table[ bin ];
    while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
        pair = pair->next;
    }

    /* Did we actually find anything? */
    if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
        return NULL;

    } else {
        return pair->value;
    }
    
}

