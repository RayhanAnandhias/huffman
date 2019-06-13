#ifndef STACKINT_H
#define STACKINT_H
#include "huffman.h"
#include <stdbool.h>
typedef int Data;
typedef struct nodes { 
	Data data;
	struct nodes* next;
}STACKInt;

/*Konstruktor=================================================*/
STACKInt *InitStackInt();
/*Membuat 1 node stack kosong atau NULL*/
STACKInt* MakeStackInt(Data X);

/*Validator===================================================*/
bool IsEmptyInt(STACKInt *top);

/*Selektor====================================================*/

int PopStackInt(STACKInt **top);
/*Mengambil data yang paling atas sekaligus menghapus*/

void PushStackInt(STACKInt **top, Data x);
/*Menambah stack dengan menambahkan di paling atas*/

/*Read and write stack========================================================*/

void PrintStackInt(STACKInt *top);
/*Mencetak stack yang telah ada ke layar*/

/*Destruktor================================================*/

void ResetStackInt(STACKInt **top);
/*Reset stack/ hapus semua node yang ada*/

int checkTopElm(STACKInt *top,Data X);

void changeTopValue(STACKInt *top, Data x);
#endif
