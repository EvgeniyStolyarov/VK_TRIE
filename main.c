//
//  main.c
//  VK_test
//
//  Created by Stolyarov on 15.02.17.
//  Copyright © 2017 VK. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>

#include "Trie.h"
#include "InputProcessing.h"

int main(int argc, const char * argv[]) {
    if (argc < 2)
        return EXIT_FAILURE;
    FILE* dictionary = fopen(argv[1], "r");
    if (!dictionary)
        return EXIT_FAILURE;
    puts("Process dictionary...");
    Trie* trie = BuildTrie(dictionary);
    fclose(dictionary);
        
    puts("Enter strings");
    CheckInput(trie, stdin, "exit");

    TrieFree(trie);
    return EXIT_SUCCESS;
}