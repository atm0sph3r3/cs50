/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**Struct outlining a Node
* A Node contains a pointer to a sibling Node,
* a child Node, and an alphabetic character.
*/
struct Node{
    struct Node* siblingNode;
    struct Node* childNode;
    char letter;
    bool isEnd;
};

/*
* Function that returns a reference to the first letter in a word.
* Pre-condition: Read word from dictionary
* Post-condition: Return a pointer to the first Node in a word
*/
struct Node* getFirstNode(struct Node* rootNode, const char* letter);

/*
* Function that adds word to trie
* Pre-condition: Successfully read word from file
* Post-condition: Returns pointer to current position in trie
*/
struct Node* addLetter(struct Node* currentNode, const char* letter);

/*
* Function to search sibling Nodes for letter
* Pre-condition: Found pointer to first letter
* Post-condition: Return pointer to next letter in word
*/
struct Node* searchSiblings(struct Node* currentNode, const char* letter);

/*
* Function to create root Node and Nodes a-z
* Pre-condition: None
* Post-condition: Root node and Nodes a-z created; returns pointer to root Node
*/
void createRoots();

/*
* Function to remove entries from Nodes
* Pre-condition: None
* Post-condition: Memory for each Node is released
*/
bool releaseNodes(struct Node* rootNode);

/*
* Function convert anypossible uppercase letters to lowercase letters
* Pre-condition: None
* Post-condition: If applicable, lowercase char returned
*/
const char toLower(const char* character);

/* 
* Initialize struct pointers to NULL
* Pre-condition: A Node exists
* Post-condition: Node pointers set to NULL
*/
void initialize(struct Node* node);

#endif // DICTIONARY_H
