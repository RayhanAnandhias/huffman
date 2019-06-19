#include "huffman.h"
#include "stacklink.h"
#include "queuelink.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

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

addressCollection createNodeCollection(char* text, unsigned int size, char* data) {
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

int getLevelOfNode (address root, char data, unsigned int keyfreq, int level, address currentAddress) {
	address current = root;
	if (current == NULL)
		return -1;
	if (current->data == data && current->freq == keyfreq && current == currentAddress)
		return level;
	int result = getLevelOfNode (current->left, data, keyfreq, level+1, currentAddress);
	if (result != -1) {
		return result;
	}
	result = getLevelOfNode(current->right, data, keyfreq, level+1, currentAddress);
	return result;
}

int getLevel (address Troot, char data, unsigned int keyfreq, address currentAddress) {
	return getLevelOfNode(Troot, data, keyfreq, 0, currentAddress);
}

void HuffmanTree(address Troot, address root) {
	int i;
	int level;
	address current = root;
	if (current != NULL) {
		level = getLevel(Troot, current->data, current->freq, current);
		for (i = 0;i <= level; i++) {  
			printf("   ");
		}
		printf("%c(%d)\n", current->data, current->freq);
		HuffmanTree(Troot, current->left);
		HuffmanTree(Troot, current->right);
	}
}

void printHuffmanTree(address TreeRoot, address node) {
	printf("\t\tHUFFMAN TREE\n");
	printf("============================================\n");
	HuffmanTree(TreeRoot, node);
}

address buildHuffmanTree(char* text) {
	char* charset;
	unsigned size;
	address left, right,top,temp;
	addressCollection collection;
	
	charset = characterSet(text);
	size = strlen(charset);
	collection = createNodeCollection(text, size, charset);
	
	while (!isCollectionSizeOne(collection)) {
		left = getMinFreqNode(collection);
		right = getMinFreqNode(collection);
		if(left->data == '*' && right->data != '*' && left->freq == right->freq) {
			temp = left;
			left = right;
			right = temp;
		}
		top = newNode('*', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertToCollection(top, collection);
	}
	return getMinFreqNode(collection);
}
void startProgram(){
	char text[MAX_ELMT];
	printf("========Welcome To HuffMan Generator=======");
	printf("\nThis Is Your First Launch ! Please Insert first text to be generate ");
	printf("\ninput here (Max 10.000 character): ");
	scanf("%[^\n]s",text);
	huffman(text);
}
void huffman(char* text) {
	address root;
	root = buildHuffmanTree(text);
	menu(root,text);
}

void menu(address root,char* text){
	int choice;
	bool exit=false;
	while(!exit){
	printf("\n");
	system("pause");
	printf("Press Enter to Back to menu");
	system("cls");
	printf("========Main Menu=======");
	printf("\n1.Show Hufman Tree");
	printf("\n2.Show Hufman Table and Detail");
	printf("\n0.exit");
	printf("\n Input Choice : ");
	scanf("%i",&choice);
		switch(choice){
			case 1	:
					printHuffmanTree(root, root);
					printf("Current Text :");
					printf("\n%s",text);
					break;
			case 2	:
					encode(root, text);
					break;
			default :
					printf("Invalid input");
					break;
			case 0 :
					exit=true;
					break;
		}
	}
	
}

char* findNode(address root,char find) {
	char* binary = malloc(sizeof(char) * MAX_ELMT);
	STACK *s=InitStack();
	QUEUE code;
	MakeQueue(&code);
	address current=root;
	while(current!=NULL) {
		if(current->data==find) {
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
	printf("\n");
	detail(root, text);
}

void detail(address root, char* text) {
	char* charset;
	unsigned int size;
    addressCollection collection;
    char* binaryString = malloc(sizeof(char) * MAX_ELMT);
    int i, codeLength, sum;
    float avgCLength = 0;
    
	charset = characterSet(text);
	size = strlen(charset);
	collection = createNodeCollection(text, size, charset);
	strcpy(binaryString, "");
	codeLength = sum = 0;
	huffmanTable(root, collection, binaryString, &sum, size, &avgCLength);
	printf("\nText Encoded With Total Code Length %d", sum);
	printf("\nAverage Code Length\t: %.2f\n", avgCLength);
	printf("Original Text\t\t: %s\n", text);
	printf("Encoded\t\t\t: ");
	for (i = 0; i <= strlen(text) - 1; i++) {
		binaryString = strcat(binaryString, findNode(root, text[i]));
	}
	printf("%s\n", binaryString);
	printf("Compressed Text\t\t: ");
	ShowCompressedText(binaryString);
	printf("\nOriginal Text Size\t: %2d byte", strlen(text));
	printf("\nCompressed Text Size\t: %.f  byte", ceil((float)sum / 8));
	printf("\nCompression Rate\t: %.2f %%", (float)(((float)strlen(text) - ceil((float)sum / 8))/(float)strlen(text))*(float)100);
}

void huffmanTable(address root, addressCollection collection, char* binaryString, int *sum, int size, float *avg) {
	int i = 0;
	int codeLength = 0;
	int sumFreq = 0;
	printf("\n==================================================================\n");
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
		sumFreq += collection->arr[i]->freq;
		*sum += codeLength;	
    	printf("------------------------------------------------------------------\n");	
	}
	*avg = (float)*sum/(float)sumFreq;
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
		if (decimal == 10 || decimal == 13) {
			printf(" ");	
		} else {
			printf("%c", decimal);	
		}
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
    return decimal_val;
}

int StringToInt(char* binString) {
	int i;
	sscanf(binString, "%d", &i);
	return i;
}


