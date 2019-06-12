#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

address newNode (char data, unsigned int frequency) {
	address nNew = (address) malloc(sizeof(node));
	nNew->data = data;
	nNew->freq = frequency;
	nNew->left = nNew->right = NULL;
	return nNew;
}

addressCollection createCollection(unsigned int capacity) {
	addressCollection collection = (addressCollection) malloc(sizeof(nCollection));
	collection->size = 0;
	collection->capacity = capacity;
	collection->arr = (arrayOfNode) malloc(sizeof(address) * collection->capacity);
	return collection;
}  

char* append(char* oldstring, char c) {
    int result;
    char *newstring;
    result = asprintf(&newstring, "%s%c", oldstring, c);
    if (result == -1) newstring = NULL;
    return newstring;
}

char* characterSet(char* text) {
	char* temp = malloc(sizeof(char)*MAX_ELMT);
	char* result = malloc(sizeof(char)*CHAR_SET);
	int i,j;
	strcpy(temp, text);
	strcpy(result, "");
	
	for (i = 0; i <= strlen(text) - 1; i++) {
		for (j = i+1; j <= strlen(text) - 1; j++) {
			if (temp[i] == temp[j]) 
				temp[j] = '\0';
		}
	}
	
	j = 1;
	for (i = 0; i <= strlen(text) - 1; i++) {
		if (temp[i] != '\0') {
			strcpy(result, append(result, temp[i]));
			j++;
		}
	}
	return result;
}

unsigned int frequency(char* text, char key) {
	unsigned int freq;
	char* temp = malloc(sizeof(char)*MAX_ELMT);
	int i,j;
	
	temp = characterSet(text);
	for(i = 0; i <= strlen(temp) - 1; i++) {
		if (temp[i] == key) {
			freq = 0;
			for(j = 0;j <= strlen(text) - 1; j++) {
				if(temp[i] == text[j])
					freq++;
			}
			break;
		}
	}
	return freq;
}

void swap(address* a, address* b) { 
	address temp = *a; 
	*a = *b; 
	*b = temp; 
}

void sortCollection(addressCollection collection) {
	int i,j;
	
	if (collection->size != 0) {
		for(i = 0; i < collection->size - 1; i++) {
			for(j = 0; j < collection->size - i - 1; j++) {
				if (collection->arr[j]->freq >= collection->arr[j+1]->freq) {
					swap(&collection->arr[j], &collection->arr[j+1]);
				}
			}
		}
	}
}

addressCollection createNodeCollection(char* text, unsigned int size, 
										char* data) {
	int i;
	addressCollection collection = createCollection(size);
	
	for(i = 0; i < size; i++)
		collection->arr[i] = newNode(data[i], frequency(text, data[i]));
	
	collection->size = size;
	sortCollection(collection);	
	return collection;
}

address getMinFreqNode(addressCollection collection) {
	address temp = collection->arr[0];
	collection->arr[0] = collection->arr[collection->size - 1];
	collection->size--;
	sortCollection(collection);
	return temp;
}

bool isCollectionSizeOne (addressCollection collection) {
	return (collection->size == 1);
}

bool isLeaf(address root) {
	return (!(root->left) && !(root->right));
}

void insertToCollection(address internalNode, addressCollection collection) {
	int i;
	
	collection->size++;
	i = collection->size - 1;
	collection->arr[i] = internalNode;
	sortCollection(collection);
}

int getLevelOfNode (address root, char data, unsigned int keyfreq, int level) {
	address current = root;
	if (current == NULL)
		return -1;
	if (current->data == data && current->freq == keyfreq)
		return level;
	int result = getLevelOfNode (current->left, data, keyfreq, level+1);
	if (result != -1) {
		return result;
	}
	result = getLevelOfNode(current->right, data, keyfreq, level+1);
	return result;
}

int getLevel (address Troot, char data, unsigned int keyfreq) {
	return getLevelOfNode(Troot, data, keyfreq, 0);
}

void printHuffmanTree(address Troot, address root) {
	int i;
	address current = root;
	if (current != NULL) {
		for (i = 0;i <= getLevel(Troot, current->data, current->freq); i++) {  
			printf("   ");
		}
		printf("%c(%d)\n", current->data, current->freq);
		printHuffmanTree(Troot, current->left);
		printHuffmanTree(Troot, current->right);
	}
}

//beta module
address buildHuffmanTree(char* text) {
	char* charset;
	unsigned size;
	address left, right,top;
	addressCollection collection;
	
	charset = characterSet(text);
	size = strlen(charset);
	collection = createNodeCollection(text, size, charset);
	
	while (!isCollectionSizeOne(collection)) {
		left = getMinFreqNode(collection);
		right = getMinFreqNode(collection);
		top = newNode('*', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertToCollection(top, collection);
	}
	return getMinFreqNode(collection);
}

void huffman(char* text) {
	address root;
	
	root = buildHuffmanTree(text);
	printHuffmanTree(root, root);
	printf("\n");
}
