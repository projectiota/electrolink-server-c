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

#include <stdlib.h> // For NULL
#include "static_memory.h"

#ifndef BLKSIZE
#define BLKSIZE         8
#endif

#ifndef MEMSIZE
#define MEMSIZE        512
#endif

#define BLOCKCOUNT        (MEMSIZE/BLKSIZE)

static uint8_t static_block_id[BLOCKCOUNT];
static uint8_t static_memory[MEMSIZE];

void* static_malloc(uint32_t size) 
{
    if (size == 0)
    {
        size = 1;
    }

    uint32_t blockCount = (size+BLKSIZE-1)/BLKSIZE;

    uint32_t startBlock = 0;
    uint32_t freeBlocks = 0;
    uint32_t i;
    for (i=0; i<BLOCKCOUNT; i++) {
        if (static_block_id[i] == 0) 
        {
            if (freeBlocks == 0)
            {
                startBlock = i;
            }
            freeBlocks++;
        } 
        else 
        {
            freeBlocks = 0;
        }

        if (freeBlocks == blockCount)
            break;
    }

    if (freeBlocks < blockCount)
    {
        return NULL;
    }

    uint32_t block_id = startBlock + 1;
    for (i=0; i<blockCount; i++) 
    {
        static_block_id[startBlock+i] = block_id;
    }

    return &static_memory[startBlock*BLKSIZE];
}


void static_free(void* ptr) 
{
    if (((intptr_t)ptr < (intptr_t)&static_memory[0]) 
        || ((intptr_t)ptr >= (intptr_t)&static_memory[MEMSIZE]))
    {
        return;
    }

    uint32_t block_id = static_block_id[((intptr_t)ptr-(intptr_t)&static_memory[0])/BLKSIZE];

    if (block_id == 0) // Asked to free empty memory
    {
        return;
    }

    uint32_t i = block_id-1;
    while (static_block_id[i] == block_id) 
    {
        static_block_id[i++] = 0;
    }
}
