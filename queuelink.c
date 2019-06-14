#include "queuelink.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int Antri=1;
void MakeQueue(QUEUE *Q){
	Q->front = NULL;
	Q->rear=NULL;
}
void Insert(QUEUE *Q,int aData){
	element *temp;
	temp = (element*)malloc(sizeof(element));
	temp->data=aData;
	if((*Q).front==NULL){
		(*Q).front=temp;
	}else {
		(*Q).rear->next=temp;
	}
	Q->rear=temp;
	Q->rear->next=NULL;
}
void DeleteFront(QUEUE *Q){
	element *temp;
	
	if((*Q).front!=NULL){
	temp = (*Q).front;
	(*Q).front=(*Q).front->next;
	free(temp);
	}
}
void setRear(QUEUE *Q,int data){
	Q->rear->data=data;
}
void DeleteRear(QUEUE *Q){
	element *temp;
	element *last;
	if((*Q).rear!=NULL){
		temp = (*Q).rear;
	 	last = (*Q).front;
		while(last->next!=temp){
			last=last->next;
		}
		(*Q).rear=last;
		last->next=NULL;
		free(temp);
	}
}
bool IsEmptyQue (QUEUE *Q){
	return ((*Q).front==NULL);
}

void Display(QUEUE Q){
	if(Q.front!=NULL){
		element *temp=Q.front;

		while(temp!=NULL){
			printf("%i",temp->data);
			temp = temp->next;
		}
	}else {
		printf("its empty");
	}
}

int getRear(QUEUE Q){
	element *temp=Q.rear;
	return(temp->data);
}


