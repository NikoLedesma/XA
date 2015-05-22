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


typedef struct _lTareas{
	char* tarea;
	int short bloque;
	struct _lTareas *sig;
}lTareas;

/**
 * me da el ultimo de la lista de tareas
 */
 lTareas* getElUltimo(lTareas*lista){
	lTareas* list=lista;
	lTareas* aux;
	while(list!=NULL){
		aux=list;
		list=list->sig;
	}
return aux;
}

//agrega tarea al ultimo

void agregarTarea(lTareas*lista,char*tarea,int bloque){
lTareas* list=malloc(sizeof(lTareas));
lTareas* aux;
list->bloque=bloque;
list->tarea=malloc(strlen(tarea)+1);
strcpy(list->tarea,tarea);
list->sig=NULL;
	if(lista!=NULL){
		aux=getElUltimo(lista);
		aux->sig=list;
	}
	else
		lista=list;
}




lTareas* crearListaDeTareas(char*tarea,int bloque)
{
   lTareas* Lista;
   Lista = (lTareas*) malloc (sizeof(lTareas));
   Lista->bloque= bloque;
   Lista->tarea=malloc(strlen(tarea)+1);
   strcpy(Lista->tarea,tarea);
   Lista->sig= NULL;
   return Lista;
}


int tamanioDeListaTareas(lTareas* lista)
{
	int inc=0;
	while(lista!=NULL){
		lista=lista->sig;
		inc++;
	}
	return inc;
}








int main(void) {

	/*lTareas * x=malloc(sizeof(lTareas));
	lTareas * aux;

	if(aux == NULL){
		printf("noo\n");
	}*/
	lTareas * x=crearListaDeTareas("pepe",43);
	lTareas * aux2=NULL;
	lTareas * aux;
	agregarTarea(x,"ppdas",53);
	agregarTarea(x,"pfasfe",32);
	/*agregarTarea(x,"pe5",42);
	agregarTarea(x,"pe3",42);
	*/
	aux=x;
	while(aux!=NULL){
		printf("la tarea se llama %s\n", aux->tarea);
		printf("el bloque es %d\n",aux->bloque);
		aux=aux->sig;
	}
	printf("tamanio de la lista %d",tamanioDeListaTareas(aux2));

	free(x->tarea);
	free(x);
	return EXIT_SUCCESS;
}
