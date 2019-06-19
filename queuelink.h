/*Program : Queue.h
Nama    : Ani Rahmani 
Deskripsi : Spesifikasi queue dinamis
Versi     :  Okt- 2001(Edited 14/06/2019)
*/
#ifndef QUEUELINK_H
#define QUEUELINK_H
#include <stdbool.h>

typedef struct elm *alamat;
typedef struct elm{
	int data;
	alamat next;
}element;

typedef struct queue {
	alamat front;
	alamat rear;
}QUEUE;

void MakeQueue(QUEUE *Q);
void Insert(QUEUE *Q,int aData);
void DeleteFront(QUEUE *Q);
void DeleteRear(QUEUE *Q);
bool IsEmptyQue (QUEUE *Q);
char* Display(QUEUE Q);
int getRear(QUEUE Q);
#endif

