/*
 ============================================================================
 Name        : listas.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _tareaM{
	char* tarea;
	int short bloque;
}tareaM;


typedef struct _lTarea{
	char* tarea;
	int short bloque;
	struct _lTarea *sig;
}lTarea;

typedef struct ListaIdentificar {
  lTarea *inicio;
  lTarea *fin;
  int tamanio;
}ListaTareas;


void inicializacionListaDeTareas (ListaTareas *lista){
  lista->inicio = NULL;
  lista->fin = NULL;
  lista->tamanio=0;
}

//agrega tarea al ultimo
void agregarTarea(ListaTareas *lista,char*tarea,int bloque){
lTarea* list=(lTarea*)malloc(sizeof(lTarea));
list->tarea=malloc(strlen(tarea)+1);
list->bloque=bloque;
strcpy(list->tarea,tarea);
list->sig=NULL;

if(lista->tamanio==0){
	lista->inicio=list;
	lista->fin=list;
}
else{
	if(lista->tamanio==1){
		lista->fin=list;
		lista->inicio->sig=lista->fin;
	}
	else{
		lista->fin->sig=list;
		lista->fin=list;
	}
}
(lista->tamanio)++;
}

/**
 *liberar primeraTarea
 */
tareaM* sacarLaPrimeraTareaDeLaLista(ListaTareas*  Lista) {
	tareaM* primerTarea=(tareaM*)malloc(sizeof(tareaM));
	lTarea *aux;
		if (Lista->tamanio!=0){
		aux=(lTarea*)(Lista->inicio);
		Lista->inicio=aux->sig;
		primerTarea->tarea=malloc(strlen(aux->tarea)+1);
		strcpy(primerTarea->tarea,aux->tarea);
		primerTarea->bloque=aux->bloque;

		if(!(--Lista->tamanio)){
			 Lista->inicio = NULL;
			 Lista->fin = NULL;
		}
		free(aux->tarea);
		free(aux);
		}
return primerTarea;
}



int main(void) {
	ListaTareas x;
	tareaM *s;
	lTarea * aux;
	inicializacionListaDeTareas (&x);
	printf("%p y %p",x.fin,x.inicio);
	agregarTarea(&x,"Rx",42);
	agregarTarea(&x,"ra",54);
	agregarTarea(&x,"RT",98);
	agregarTarea(&x,"TH",67);
	aux=x.inicio;
	printf("el inicio es:%d y %s y el final es:%d y %s",
			x.inicio->bloque,x.inicio->tarea
			,x.fin->bloque,x.fin->tarea);
	while(aux!=NULL){
		printf("%d y %s\n",aux->bloque,aux->tarea);
		aux=aux->sig;
	}

	s=sacarLaPrimeraTareaDeLaLista(&x);
	printf("%d y %s\n",s->bloque,s->tarea);
	free(s->tarea);
	free(s);
	s=sacarLaPrimeraTareaDeLaLista(&x);
	printf("%d y %s\n",s->bloque,s->tarea);
		free(s->tarea);
		free(s);
	s=sacarLaPrimeraTareaDeLaLista(&x);
	printf("%d y %s\n",s->bloque,s->tarea);
		free(s->tarea);
		free(s);
	s=sacarLaPrimeraTareaDeLaLista(&x);
	printf("%d y %s\n",s->bloque,s->tarea);
		free(s->tarea);
		free(s);
	if(x.fin==NULL && x.inicio==NULL){
		printf("Todo bien se borro todo\n");
	}

	printf("tamanio de la lista %d",x.tamanio);
	return EXIT_SUCCESS;
}
