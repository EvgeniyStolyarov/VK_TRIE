//
//  InputProcessing.h
//  VK_test
//
//  Created by Stolyarov on 18.02.17.
//  Copyright © 2017 VK. All rights reserved.
//

#ifndef InputProcessing_h
#define InputProcessing_h

#include "Trie.h"
#include <stdio.h>

Trie* BuildTrie(FILE* input);
void CheckInput(Trie* trie, FILE* input, const char* endString);

#endif /* InputProcessing_h */
