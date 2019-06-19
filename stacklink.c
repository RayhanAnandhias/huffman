#include "huffman.h"
#include "stacklink.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Konstruktor=================================================*/
STACK *InitStack() {
	return NULL;
}
/*Membuat 1 node stack kosong atau NULL*/
STACK* MakeStack(address1 X) {
	STACK* p;
	
	p = (STACK*) malloc(sizeof(STACK));
	p->data = X;
	p->next = NULL;
	return p;
}

/*Validator===================================================*/
bool IsEmpty(STACK *top) {
	return (top == NULL);
}


/*Selektor====================================================*/

/*Mengambil data yang paling atas sekaligus menghapus*/
address PopStack(STACK **top) {
	STACK* temp;
	address1 popped;
	if (IsEmpty(*top)) {
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
void PushStack(STACK **top, address1 data) {
	STACK* p;
	
	p = MakeStack(data);
	p->next = *top;
	*top = p; 
}

/*Read and write stack========================================================*/

/*Mencetak stack yang telah ada ke layar*/
void PrintStack(STACK *top) {
	STACK* temp;

	if (IsEmpty(top)) {
		printf("Stack Kosong\n");
		//exit(1);
	} else {
		temp = top;
		while (temp != NULL) {
			printf("%d ", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}

/*Destruktor================================================*/
/*Reset stack/ hapus semua node yang ada*/
void ResetStack(STACK **top) {
	STACK* temp;
	address1 X;

	while (*top != NULL) {
		temp = *top;
		*top = temp->next;
		free(temp);
	}
	printf("Stack Sudah Kosong\n");
}
