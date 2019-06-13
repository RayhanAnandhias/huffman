#ifndef STACKLINK_H
#define STACKLINK_H
#include "huffman.h"
#include <stdbool.h>
typedef address address1;
typedef struct node { 
	address1 data;
	struct node* next;
}STACK;

/*Konstruktor=================================================*/
STACK *InitStack();
/*Membuat 1 node stack kosong atau NULL*/
STACK* MakeStack(address1 X);

/*Validator===================================================*/
bool IsEmpty(STACK *top);

/*Selektor====================================================*/

address PopStack(STACK **top);
/*Mengambil data yang paling atas sekaligus menghapus*/

void PushStack(STACK **top, address1 data);
/*Menambah stack dengan menambahkan di paling atas*/

/*Read and write stack========================================================*/

void PrintStack(STACK *top);
/*Mencetak stack yang telah ada ke layar*/

/*Destruktor================================================*/

void ResetStack(STACK **top);
/*Reset stack/ hapus semua node yang ada*/
#endif
