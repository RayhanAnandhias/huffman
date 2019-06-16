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
char* append(char* oldstring, char c);
void swap(address* a, address* b);
void sortCollection(addressCollection collection);
addressCollection createNodeCollection(char* text, unsigned int size, char* data);
address getMinFreqNode(addressCollection collection);
bool isCollectionSizeOne (addressCollection collection);
bool isLeaf(address root);
void insertToCollection(address internalNode, addressCollection collection);
int getLevel (address Troot, char data, unsigned int keyfreq, address currentAddress);
address newNode (char data, unsigned int frequency);
addressCollection createCollection(unsigned int capacity);
unsigned int frequency(char* text, char key);
char* findNode(address root,char find);
void GenerateCode(address root,char alph);
void encode(address root, char* text);
int StringToInt(char* binString);
int binaryToDecimal(int i);
void ShowCompressedText(char* binaryString);
void detail(address root, char* text);
void huffmanTable(address root, addressCollection collection, char* binaryString, int *sum, int size);
void HuffmanTree(address Troot, address root);
void printHuffmanTree(address TreeRoot, address node);
address buildHuffmanTree(char* text);
int StringToInt(char* binString);
#endif
