#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie * children[26];
	int count;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word){
    if(pTrie == NULL){
    puts("can not insert. pTrie is null");
    return;
    }
    struct Trie * tmp = pTrie;
	int len = strlen(word);
	int i = 0;
	
	for(; i < len; i++){
		if(tmp->children[word[i]-'a'] == NULL)
			break;
    tmp = tmp->children[word[i]-'a'];
	}
  
    struct Trie * newTrie;
	for(; i < len; i++){
		newTrie = (struct Trie*)malloc(sizeof(struct Trie));
		for(int j = 0; j < 26; j++)
			newTrie->children[j] = NULL;
		newTrie->count = 0;
		tmp->children[word[i]-'a'] = newTrie;
    tmp = tmp->children[word[i]-'a'];
    //printf("inserted letter %c, ", word[i]);
	}
	tmp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word){
    if(pTrie == NULL)
		return 0;
	struct Trie * tmp = pTrie;
	int len = strlen(word);
	for(int i = 0; i < len; i++){
		tmp = tmp->children[word[i]-'a'];
		if(tmp == NULL)
			return 0;
	}
	return tmp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie){
    if(pTrie == NULL){
    	return NULL;
	}
	for(int i = 0; i < 26; i++){
		pTrie->children[i] = deallocateTrie(pTrie->children[i]);
	}
	free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie(){
  struct Trie * root = (struct Trie *)malloc(sizeof(struct Trie));
  root->count = 0;
  for(int i = 0; i < 26; i++)
    root->children[i] = NULL;
  return root;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords){
  FILE * fPtr = fopen(filename, "r");
  if(fPtr == NULL){
    puts("error opening file.");
    exit(-1);
  }

  puts("reading file\n");
  
  int numWords = 0;
  fscanf(fPtr, "%d ", &numWords);

  printf("%d words in file\n\n", numWords);
  
  for(int i = 0; i < numWords; i++){
    pInWords[i] = (char *)malloc(sizeof(char)*50);
    fscanf(fPtr, "%s ", pInWords[i]);
  }

  puts("done reading file\n\n");
  
  return numWords;
}

int main(void)
{
	char *inWords[256];

    puts("start main\n");
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
    puts("validating dictionary");
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
    }
    puts("done reading dictionary\n");
  
	struct Trie *pTrie = createTrie();

    puts("\ncreated Trie root\n");

	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
        printf("inserted word %s\n", inWords[i]);
	}

    puts("\n\ndone inserting from inWords. Now inserting from pWords.\n");
  
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for(int u = 0; u < 5; u++){
        insert(pTrie, pWords[u]);
        printf("inserted word %s\n", pWords[u]);
    }

    puts("\n\ntesting count of words in pWords:");
	for (int i=0;i<5;i++)
	{
	    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	
    puts("freeing memory\n");
  
    pTrie = deallocateTrie(pTrie);
    for(int k = 0; k < numWords; k++)
        free(inWords[k]);
  
	if (pTrie != NULL)
		printf("There is an error in this program\n");
    puts("program ending successfully");
    return 0;
}
