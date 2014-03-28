/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

#define MAX_SIZE 45

//Root node
struct Node* rootNode;

//Number of words loaded
unsigned int numWords = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{

	bool hasWord = true;	
	
	struct Node* currentNode = rootNode->childNode;
	
    for(int i = 0; i < strlen(word) && hasWord; i++){
    	const char inputLetter = toLower(&(word[i]));
    	while(true){
    		//Unable to find letter at current Node
    		//Advance to sibling Node if possible
    		if(currentNode->letter != inputLetter){
    			if(currentNode->siblingNode != NULL){
    				currentNode = currentNode->siblingNode;
    			} else {
    				hasWord = false;
    				break;
    			}
    		//Letter at current Node matches word in text
    		//Advance to child Node and check next letter
    		} else {
    			if(i + 1 != strlen(word)){
					if(currentNode->childNode != NULL){
						currentNode = currentNode->childNode;
						break;
					} else {
						hasWord = false;
						break;
					}
				} else if(currentNode->isEnd) {
					break;
				//Handles cases where a misspelled substring is not considered correct
				} else {
					hasWord = false;
					break;
				}
    		}
    	}	
    }
    return hasWord;
}


void createRoots(){
	
	rootNode = malloc(sizeof(struct Node));
	initialize(rootNode);	
	rootNode->letter = '\0';

	//Create Node for 'a'
	struct Node* firstLetter = malloc(sizeof(struct Node));
	rootNode->childNode = firstLetter;
	initialize(firstLetter);
	firstLetter->letter = 'a';
	
    //First loop iteration root Node is the previous Node
    struct Node* previousNode = firstLetter;

    //Create Nodes for letters a-z
    for(int i = 0; i < 25; i++){
        struct Node* nextSibling = malloc(sizeof(struct Node));
        nextSibling->letter = 0x62 + i;
        initialize(nextSibling);
        previousNode->siblingNode = nextSibling;
        //Current Node will become previous Node for next iteration
        previousNode = nextSibling;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary) {
    //Create file pointer to file containing words to load
    FILE* infile = fopen(dictionary,"r");
    //Temporarily holds word read from dictionary
    char* word;
    //Letter to be read
    char letter;
    //Number of each word read
    int counter;
    
    createRoots();

    //Read words from dictionary
    while(true){
        //Allocate memory for word
    	word = malloc(sizeof(char)*(MAX_SIZE + 1));
    	//Reset counter
    	counter = 0;
    	//Continue until end of line character encountered
    	while((letter = fgetc(infile)) != '\n'){
    		if(ferror(infile) == 0){
    			if(feof(infile) == 0){
					word[counter] = letter;
					++counter;
				} else {
					fclose(infile);
					free(word);
					return true;
				}
			} else {
                //Error occured, free memory and break
                fclose(infile);
				free(word);
				return false;
			}
    	}
    	//Add null char
    	word[counter] = '\0';

    	//Holds pointer to current Node
    	struct Node* currentNode;

        //Add letters to trie
    	for(int i = 0; i < strlen(word); i++){
            if(i == 0){
                const char letter = word[i];
                currentNode = addLetter(rootNode, &letter);
            } else {
                const char letter = word[i];
                currentNode = addLetter(currentNode,&letter);
            }
            if(i + 1 == strlen(word)){
            	currentNode->isEnd = true;
            }
    	}
		++numWords;
		free(word);
    }
    //Succesfully read each word
    fclose(infile);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return numWords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
	return releaseNodes(rootNode);
}

struct Node* getFirstNode(struct Node* rootNode,const char* letter) {
    struct Node* currentNode = rootNode->childNode;
    while(true) {
        if(currentNode->letter == *letter){
            return currentNode;
        } else {
            currentNode = currentNode->siblingNode;
        }
    }

}

struct Node* searchSiblings(struct Node* currentNode, const char* letter){

    struct Node* toCheck = currentNode;
    struct Node* returnNode;

    while(true){
        if(toCheck->siblingNode != NULL){
        	//Sibling letter doesn't much current letter
            if(toCheck->siblingNode->letter != *letter){
            	//Check next sibling's letter
                toCheck = toCheck->siblingNode;
            } else {
            	//Sibling's letter matches current letter
                returnNode = toCheck->siblingNode;
                break;
            }
        } else {
            //No more siblings to search.
			//Create a new one.
			returnNode = malloc(sizeof(struct Node));
			initialize(returnNode);
			returnNode->letter = *letter;
			toCheck->siblingNode = returnNode;
			break;
        }
    }
	
	return returnNode;
}

struct Node* addLetter(struct Node* currentNode, const char* letter) {

    struct Node* returnNode;

    if(currentNode->childNode != NULL){
    	//First child node's letter doesn't match the current letter
        if(currentNode->childNode->letter != *letter) {
            //Start checking the sibling Nodes for the letter
            returnNode = searchSiblings(currentNode->childNode, letter);
        //Already has a child Node that matches the current letter
        } else {
            returnNode = currentNode->childNode;
        }
    } else {
    	//No child Nodes, add first one
		returnNode = malloc(sizeof(struct Node));
		initialize(returnNode);
		returnNode->letter = *letter;
		currentNode->childNode = returnNode;
    }
    return returnNode;
}

bool releaseNodes(struct Node* rootNode) {

    struct Node* childNode;
    struct Node* siblingNode;

    if(rootNode->childNode != NULL){
        childNode = rootNode->childNode;
        releaseNodes(childNode);
    }

    if(rootNode->siblingNode != NULL){
        siblingNode = rootNode->siblingNode;
        releaseNodes(siblingNode);
    }
    
    free(rootNode);
	
	return true;
}

const char toLower(const char* character){
		
	char toReturn;
	
	if(*character > 0x40 && *character < 0x5B){
		toReturn = *character + 0x20;
	} else {
		toReturn = *character;
	}
	
	return toReturn;
}

void initialize(struct Node* node){
	node->siblingNode = NULL;
	node->childNode = NULL;
	node->isEnd = false;
}
