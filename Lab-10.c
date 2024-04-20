#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count;
    struct Trie *children[26];
};

// Inserts the word to the trie structure
// Update the count of the word in loop
void insert(struct Trie *pTrie, char *word)
{
    if(pTrie == NULL){
        return;
    }

    int length = strlen(word);
    struct Trie *current = pTrie;

    for(int i = 0; i < length; i++){
        int index = word[i] - 'a';
        if(current->children[index] == NULL){
            struct Trie *newNode = (struct Trie *)malloc(sizeof(struct Trie));
            newNode->count = 0;
            for(int j = 0; j < 26; j++){
                newNode->children[j] = NULL;
            }
            current->children[index] = newNode;
        }
        current = current->children[index];
    }
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if(pTrie == NULL){
        return 0;
    }

    int length = strlen(word);
    int count = 0;
    struct Trie *current = pTrie;

    for (int i = 0; i < length; i++){
        int index = word[i] - 'a';
        if(current->children[index] == NULL){
            return 0;
        }
        if(i == length - 1){
            count = current->children[index]->count;
        }
        current = current->children[index];

    }
    return count;

}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie == NULL){
        return NULL;
    }

    for(int i = 0; i < 26; i++){
        if(pTrie->children[i] != NULL){
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return pTrie;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *newTrie = (struct Trie *)malloc(sizeof(struct Trie));
    newTrie->count = 0;
    for(int i = 0; i < 26; i++){
        newTrie->children[i] = NULL;
    }
    return newTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        return 0;
    }

    int count = 0;
    for(int i = 0; i < 256; i++){
        pInWords[i] = (char *)malloc(256);
        if(fscanf(file, "%s", pInWords[i]) == EOF){
            break;
        }
        fscanf(file, "%s", pInWords[i]);
        count++;

    }

    return count;
}

int main(void)
{
    char *inWords[256];

    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary-1.txt", inWords);
    for (int i=0;i<numWords;++i)
    {
        printf("%s\n",inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i=0;i<numWords;i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}