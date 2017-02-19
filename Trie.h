//
//  Trie.h
//  VK_test
//
//  Created by Stolyarov on 15.02.17.
//  Copyright © 2017 VK. All rights reserved.
//

#ifndef Trie_h
#define Trie_h

typedef struct Trie Trie;
struct Trie
{
    char inSymbol;
    char isLeaf;
    short nodesSize;
    short nodesCapacity;
    Trie** nodes;
};

typedef Trie* (*EdgeFuncPtr)(Trie*, char);

Trie* CreateRootTrie();
Trie* TrieAddNodeWithSymbol(Trie* trie, const char c);
Trie* TrieGetNodeWithSymbol(Trie* trie, const char c);
void TrieFree(Trie* trie);

#endif /* Trie_h */
