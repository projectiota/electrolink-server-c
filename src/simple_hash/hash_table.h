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

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "static_memory.h"

#define HASH_MULTIPLIER 33

typedef void (*funct_t)(void);

typedef struct entry_s entry_t;
typedef struct hashtable_s hashtable_t;

hashtable_t *ht_create(int size);
void ht_set(hashtable_t *hashtable, char *key, funct_t value);
funct_t ht_get(hashtable_t *hashtable, char *key );

#endif // _HASH_TABLE_H_
