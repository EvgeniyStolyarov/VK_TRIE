//
//  Trie.c
//  VK_test
//
//  Created by Stolyarov on 15.02.17.
//  Copyright © 2017 VK. All rights reserved.
//

#include "Trie.h"
#include "MaxMinFuncs.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ALPHABET_START 32
#define ALPHABET_END 126
#define ALPHABET_SIZE ((ALPHABET_END) - (ALPHABET_START) + 1)

#define RESIZE_SUCCESS 1
#define RESIZE_FAILURE 0

void TrieNodesInit(Trie* trie)
{
    trie->nodesCapacity = 0;
    trie->nodes = NULL;
    trie->nodesSize = 0;
}
 

int TrieNodesResize(Trie* trie)
{
    if (trie->nodesSize < trie->nodesCapacity)
        return RESIZE_SUCCESS;
    const short newCapacity = minShort(ALPHABET_SIZE+1, trie->nodesCapacity ? 2 * trie->nodesCapacity : 1);
    Trie** data = realloc(trie->nodes, newCapacity * sizeof(Trie*));
    if (!data)
        return RESIZE_FAILURE;
    trie->nodes = data;
    trie->nodesCapacity = newCapacity;
    return RESIZE_SUCCESS;
}

Trie* CreateChildTrie(char c)
{
    Trie* newTrie = malloc(sizeof(Trie));
    if (!newTrie)
        return NULL;
    newTrie->isLeaf = 0;
    newTrie->inSymbol = c;
    TrieNodesInit(newTrie);
    return newTrie;
}

Trie* CreateRootTrie()
{
    return CreateChildTrie('\0');
}

Trie* TrieAddNodeWithSymbol(Trie* trie, const char c)
{
    if (!trie || c < ALPHABET_START || c > ALPHABET_END)
        return NULL;
    for (int i = 0; i < trie->nodesSize; ++i) {
        if (trie->nodes[i]->inSymbol == c) {
            return trie->nodes[i];
        }
    }
    if(TrieNodesResize(trie) == RESIZE_FAILURE)
            return NULL;
    Trie* newTrie = CreateChildTrie(c);
    trie->nodes[trie->nodesSize] = newTrie;
    ++trie->nodesSize;
    return newTrie;
}

Trie* TrieGetNodeWithSymbol(Trie* trie, const char c)
{
    if (!trie)
        return NULL;
    if (c < ALPHABET_START || c > ALPHABET_END) {
        printf("Invalid symbol, code: %d\n", c);
        return NULL;
    }
    for (int i = 0; i < trie->nodesSize; ++i) {
        if (trie->nodes[i]->inSymbol == c) {
            return trie->nodes[i];
        }
    }
    return NULL;
}

void TrieFree(Trie* trie)
{
    if (!trie)
        return;
    for (int i = 0; i < trie->nodesSize; ++i) {
        TrieFree(trie->nodes[i]);
    }
    free(trie->nodes);
    free(trie);
}


