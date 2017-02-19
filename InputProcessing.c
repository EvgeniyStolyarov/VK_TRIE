//
//  InputProcessing.c
//  VK_test
//
//  Created by Stolyarov on 18.02.17.
//  Copyright © 2017 VK. All rights reserved.
//

#include "InputProcessing.h"
#include "MaxMinFuncs.h"

#include <stdlib.h>
#include <string.h>

#define STRING_NOT_FOUND         0
#define STRING_WAS_FOUND         1
#define INPUT_END               -1

Trie* ProcessLinePart(Trie* trie, char* buff, EdgeFuncPtr processedFunc)
{
    Trie* curTrie = trie;
    char* s = buff;
    while (curTrie && *s != '\0' && *s != '\n') {
        curTrie = (*processedFunc)(curTrie, *s);
        ++s;
    }
    return curTrie;
}

int FindNextLine(Trie* trie, FILE* input, const char* endString)
{
    Trie* curNode = trie;
    int isFirstPartWasChecked = 0;
    const size_t endStringLength = endString ? strlen(endString) : 0;
    const int readSize = maxInt(127, (int)endStringLength+1);
    char* buff = malloc(readSize+1);
    
    while (fgets(buff, readSize+1, input)) {
        strtok(buff, "\n");
        if (!isFirstPartWasChecked && endString) {
            if (strcmp(buff, endString) == 0)
                break;
        }
        isFirstPartWasChecked = 1;
        curNode = ProcessLinePart(curNode, buff, &TrieGetNodeWithSymbol);
        if (strlen(buff) < readSize)
            break;
    }
    free(buff);
    if (!isFirstPartWasChecked)
        return INPUT_END;
    return (curNode && curNode->isLeaf) ? STRING_WAS_FOUND : STRING_NOT_FOUND;
}

Trie* AddNextLine(Trie* trie, FILE* input)
{
    const int readSize = 127;
    char* buff = malloc(readSize+1);
    Trie* curNode = trie;
    while (fgets(buff, readSize+1, input)) {
        strtok(buff, "\n");
        curNode = ProcessLinePart(curNode, buff, &TrieAddNodeWithSymbol);
        if (strlen(buff) < readSize)
            break;
    }
    free(buff);
    return curNode;
}

Trie* BuildTrie(FILE* input)
{
    Trie* trie = CreateRootTrie();
    if (!trie)
        return NULL;
    while (!feof(input)) {
        Trie* lastNode = AddNextLine(trie, input);
        if (lastNode)
            lastNode->isLeaf = 1;
    }
    return trie;
}

void CheckInput(Trie* trie, FILE* input, const char* endString)
{
    int res;
    while ((res = FindNextLine(trie, input, endString)) != INPUT_END) {
        puts(res == STRING_NOT_FOUND ? "NO" : "YES");
    }
}