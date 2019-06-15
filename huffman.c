#include "huffman.h"
#include "stacklink.h"
#include "queuelink.h"
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
				if (collection->arr[j+1]->data != '*') {
					if (collection->arr[j]->freq > collection->arr[j+1]->freq) {
						swap(&collection->arr[j], &collection->arr[j+1]);
					}	
				} else {
					if (collection->arr[j]->freq >= collection->arr[j+1]->freq) {
						swap(&collection->arr[j], &collection->arr[j+1]);
					}
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
	//findNode(root,'T');//	GenerateCode(root,'I');
	detail(root, text);
	encode(root, text);
	printf("\n\n");
}

char* findNode(address root,char find){
	char* binary = malloc(sizeof(char) * 512);
	STACK *s=InitStack();
	QUEUE code;
	MakeQueue(&code);
	address current=root;
	while(current!=NULL) {
		if(current->data==find) {
			//printf("Kode dari %c : ",current->data);
			binary = Display(code);
			return binary;
		}
		if(current->left!=NULL){
			if(current->right!=NULL){
			PushStack(&s,current->right);
			}
			Insert(&code,0);
			current=current->left;
		}else {
			if(current->right!=NULL){
				current=current->right;
			}else {
				current=PopStack(&s);
				if(getRear(code)==0){
					setRear(&code,1);	
				}else{
					while(getRear(code)!=0){
						DeleteRear(&code);	
					}
					setRear(&code,1);
				}
			}
		} 
	}
}

void encode(address root, char* text) {
	char* origin_text = text;
	char* binaryString = malloc(sizeof(char) * 512);
	char* bitWord;
	int i;
	
	strcpy(binaryString, "");
	//char* set = characterSet(text);
	printf("\nOriginal Text\t: %s\n", origin_text);
	printf("Encoded\t\t: ");
	for (i = 0; i <= strlen(origin_text) - 1; i++) {
		binaryString = strcat(binaryString, findNode(root, text[i]));
	}
	printf("%s", binaryString);
	printf("\n");
	printf("Compressed Text\t: ");
	ShowCompressedText(binaryString);
}

void detail(address root, char* text) {
	char* charset;
	unsigned int size;
    addressCollection collection;
    char* binaryString = malloc(sizeof(char) * 512);
    int i, codeLength;
	charset = characterSet(text);
	size = strlen(charset);
	collection = createNodeCollection(text, size, charset);
	strcpy(binaryString, "");
	codeLength = 0;
	printf("                          Huffman Table\n==================================================================\n");
	printf("\t||\t       ||     Binary     ||   Bit   ||   Code   ||");
	printf("\n Symbol\t||  Frequency  ||      Code      ||  Length ||  Length  ||\n");
    printf("%s\n","==================================================================");
    for(i = 0; i <= size - 1; i++) {
    	printf("   %c", collection->arr[i]->data);
	    printf("\t\t%d", collection->arr[i]->freq);
		binaryString = findNode(root, collection->arr[i]->data);
		printf("\t       %5s", binaryString);
		printf("\t       %d", strlen(binaryString));
		codeLength = collection->arr[i]->freq * strlen(binaryString);
		printf("\t   %2d\n", codeLength);	
    	printf("------------------------------------------------------------------\n");	
	}
}

void ShowCompressedText(char* binaryString) {
	int i,j,k,q;
	int bit;
	int decimal = 0;
	char* result = malloc(sizeof(char)*8);
	char* compressedText = malloc(sizeof(char)*512);
	strcpy(compressedText, "");
	k=0;
	q = 0;
	for (i = 0; i <= strlen(binaryString) - 1; i++) {
		for (j = 0; j <= 7; j++) {
			result[j] = binaryString[k];
			k++;
		}
		decimal = binaryToDecimal(StringToInt(result));
		printf("%c", decimal);
		i = k - 1;
	}
}

int binaryToDecimal(int i) {
	int  num, binary_val, decimal_val = 0, base = 1, rem;
 	
 	num = i;
    binary_val = num;
    while (num > 0)
    {
        rem = num % 10;
        decimal_val = decimal_val + rem * base;
        num = num / 10 ;
        base = base * 2;
    }
    //printf("The Binary number is = %d \n", binary_val);
    //printf("Its decimal equivalent is = %d \n", decimal_val);
    return decimal_val;
}

int StringToInt(char* binString) {
	int i;
	sscanf(binString, "%d", &i);
	return i;
}
