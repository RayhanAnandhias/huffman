#include "huffman.h"
#include "stackint.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Konstruktor=================================================*/
STACKInt *InitStackInt() {
	return NULL;
}
/*Membuat 1 node stack kosong atau NULL*/
STACKInt* MakeStackInt(Data X) {
	STACKInt* p;

	p = (STACKInt*) malloc(sizeof(STACKInt));
	p->data = X;
	p->next = NULL;
	return p;
}

/*Validator===================================================*/
bool IsEmptyInt(STACKInt *top) {
	return (top == NULL);
}
/*Selektor====================================================*/

/*Mengambil data yang paling atas sekaligus menghapus*/
int PopStackInt(STACKInt **top) {
	STACKInt* temp;
	int popped;
	if (IsEmptyInt(*top)) {
		return NULL;
		//exit(1);
	} else {
		temp = *top;
		*top = temp->next;
		popped = temp->data;
		free(temp);
		return popped;	
	}
}

/*Menambah stack dengan menambahkan di paling atas*/
void PushStackInt(STACKInt **top, Data x) {
	STACKInt* p;
	
	p = MakeStackInt(x);
	p->next = *top;
	*top = p;
}

/*Read and write stack========================================================*/

/*Mencetak stack yang telah ada ke layar*/
void PrintStackInt(STACKInt *top) {
	STACKInt* temp;

	if (IsEmptyInt(top)) {
		printf("Stack Kosong\n");
		//exit(1);
	} else {
		temp = top;
		while (temp != NULL) {
			printf("%i", temp->data);
			temp = temp->next;
		}
	}
}

/*Destruktor================================================*/
/*Reset stack/ hapus semua node yang ada*/
void ResetStackInt(STACKInt **top) {
	STACKInt* temp;
	while (*top != NULL) {
		temp = *top;
		*top = temp->next;
		free(temp);
	}
	printf("\nStack Sudah Kosong\n");
}

void changeTopValue(STACKInt *top, Data x){
	top->data=x;
	printf("%i",top->data);
}

int checkTopElm(STACKInt *top,Data X){
	if(top->data==X){
		return 1;
	}
	return 0;
}
