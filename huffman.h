#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdbool.h>
#define MAX_ELMT 280
#define CHAR_SET 255

typedef struct huffmanNode* address;
typedef struct huffmanNode node;
struct huffmanNode {
	char data;
	unsigned int freq;
	address left, right;
};

typedef struct huffmanNode** arrayOfNode;
typedef struct nodeCollection nCollection;
typedef struct nodeCollection* addressCollection;
struct nodeCollection {
	unsigned int size;
	unsigned int capacity;
	arrayOfNode arr;
};

void huffman(char* text);
char* characterSet(char* text);
address newNode (char data, unsigned int frequency);
addressCollection createCollection(unsigned int capacity);
unsigned int frequency(char* text, char key);
int findNode(address root,char find);
void GenerateCode(address root,char alph);
#endif
