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
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

#include <commons/collections/list.h>

/*
 * Estructura que recibo del fileSystem
 */
typedef struct _paquete_FFileSystem{
	char * nombreArch; //nombre del archivo
	uint16_t nroFrag; //numero de la copia
	char* ip;//ip del nodo
	char* puerto;//puerto del nodo
	uint16_t bloque;//bloque donde se encuentra el nodo
}paquete_FFileSystem __attribute__ ((packed));


/*
 * Estructura que recibo del fileSystem
 */
typedef struct _paquete_FFileSystemLength{
	short int nombreArchLength; //nombre del archivo
	short int nroFragLength; //numero de la copia
	short int ipLength;//ip del nodo
	short int puertoLength;//puerto del nodo
	short int bloqueLength;//bloque donde se encuentra el nodo
}paquete_FFileSystemLength;



/**
 *RecibeEstructura el Marta del Filesystem
 */
void recibir_packete_FromFileSystemMP(paquete_FFileSystem *st,int sock){
void * buffer;
int length=sizeof(short int)*5;
size_t aux;
paquete_FFileSystemLength T;

buffer= malloc(length);
recv(sock,buffer,length,0);
memcpy(&(T.nombreArchLength),buffer,sizeof(short int));
length=T.nombreArchLength;

memcpy(&(T.nroFragLength),buffer+sizeof(short int),sizeof(short int));
length=length+T.nroFragLength;

memcpy(&(T.ipLength),buffer+sizeof(short int)*2,sizeof(short int));
length=length+T.ipLength;

memcpy(&(T.puertoLength),buffer+sizeof(short int)*3,sizeof(short int));
length=length+T.puertoLength;

memcpy(&(T.bloqueLength),buffer+sizeof(short int)*4,sizeof(short int));
length=length+T.bloqueLength;
free(buffer);

buffer= malloc(length);
recv(sock,buffer,length,0);
memcpy(st->nombreArch,buffer,T.nombreArchLength);
aux=T.nombreArchLength;

memcpy(&(st->nroFrag),buffer+aux,T.nroFragLength);
aux=aux+T.nroFragLength;

memcpy(st->ip,buffer+aux,T.ipLength);
aux=aux+T.ipLength;

memcpy(st->puerto,buffer+aux,T.puertoLength);
aux=aux+T.puertoLength;

memcpy(&(st->bloque),buffer+aux,T.nombreArchLength);
aux=aux+T.bloqueLength;
free(buffer);
printf("Sé Recibio %d bytes\n",aux);
}




/**
 *Envia estructura el fileSystem al MaRTA
 */
typedef struct _packer{
	char * nombreArch; //nombre del archivo
	uint16_t  nombreArchLength;
	short int nroFrag; //numero de la copia
	uint16_t  nroFragLength;
	char* ip;//ip del nodo
	uint16_t  ipLength;
	char* puerto;//puerto del nodo
	uint16_t  puertoLength;
	short int bloque;//bloque donde se encuentra el nodo
	uint16_t  bloqueLength;
} paquete_TMarta __attribute__ ((packed));

void enviar_estructura_ToMartaMP(paquete_TMarta  str,int sock){
void * buffer;
buffer= malloc(sizeof(short int)*5+ 40);
int aux=0;
memcpy(buffer, &str.nombreArchLength,sizeof(short int));
memcpy(buffer+sizeof(short int),&str.nroFragLength ,sizeof(int));
memcpy(buffer+sizeof(short int)*2,&str.ipLength ,sizeof(int));
memcpy(buffer+sizeof(short int)*3, &str.puertoLength,sizeof(int));
memcpy(buffer+sizeof(short int)*4, &str.bloqueLength,sizeof(int));

aux=sizeof(int)*5;
memcpy(buffer+aux,&(str.nombreArch),str.nombreArchLength);
aux=aux+str.nombreArchLength;
memcpy(buffer+aux, &(str.nroFrag)  ,str.nroFragLength);
aux=aux+str.nroFragLength;
memcpy(buffer+aux,&(str.ip) ,str.ipLength);
aux=aux+str.ipLength;
memcpy(buffer+aux,&(str.puerto),str.puertoLength);
aux=aux+str.puertoLength;
memcpy(buffer+aux,&(str.bloque),str.bloqueLength);
aux=aux+str.bloqueLength;

printf("Envio:%d\n",aux);
send(sock,buffer,aux ,0);
free(buffer);
}







///////////// Esta el nombre del nodo
/////////////Esta el lugar donde se ubica el bloque
typedef struct _nodos{
	char* nombreDeNodo;//
	int bloque;//bloque
}nodoInfo;

///////////// Esta el numero de copia
/////////////Estan los nodos en donde se encuentra la copia
typedef struct _copias{
	int posCopia;
	t_list* nodos;
}copiaInfo;

///////////// Esta el nombre del archivo
/////////////Estan los fragmentos(copias) del archivo;es decir la cantidad en que se dividen
typedef struct _archivo{
	char *nombreDeArchivo;
	t_list*copias;
}archInfo;

///////////// Esta el identificador del job(numero del cliente)
/////////////Esta si soporta o no combiner
/////////////Esta la lista de archivos
typedef struct _job{
	int jobClient;
	int combiner;
	t_list * archivos;
}jobInfo;

void agregarNodoALaListaN(int numeroDeBloq,char* nombreNodo,t_list *nodoList){
	nodoInfo *nodoNuevo;
	nodoNuevo=malloc(sizeof(nodoInfo));
	nodoNuevo->nombreDeNodo=malloc(strlen(nombreNodo)+1);
	nodoNuevo->bloque=numeroDeBloq;
	strcpy(nodoNuevo->nombreDeNodo,nombreNodo);
	list_add(nodoList,nodoNuevo);
}

void agregarCopiaALaListaC(int numeroDeCopia,t_list* nodoList,t_list *copiaList){
	copiaInfo *copiaNueva;
	copiaNueva=malloc(sizeof(copiaInfo));
	copiaNueva->posCopia=numeroDeCopia;
	copiaNueva->nodos=nodoList;
	list_add(copiaList,copiaNueva);
}

void agregarArchivoALaListaA(char*nombreArchivo,t_list* copiaList,t_list *archivoList){
	archInfo *archivoNuevo;
	archivoNuevo=malloc(sizeof(archInfo));
	archivoNuevo->nombreDeArchivo=malloc(strlen(nombreArchivo)+1);
	strcpy(archivoNuevo->nombreDeArchivo,nombreArchivo);
	archivoNuevo->copias=copiaList;//problemas de tipo pasar a t_list
	list_add(archivoList,archivoNuevo);
}

void agregarJobALaListaJ(int idJobCliente,int combiner,t_list* archivoList,t_list *jobList){
	jobInfo *jobNuevo;
	jobNuevo=malloc(sizeof(jobInfo));
	jobNuevo->jobClient=idJobCliente;
	jobNuevo->combiner=combiner;
	jobNuevo->archivos=archivoList;/////problemas de tipo pasar a t_list
	list_add(jobList,jobNuevo);
}




/////////////////////////////////////
/////////////////////////////////////Listas para el job y el nodo
/////////////////////////////////////
/////////////////////////////////////

/**
 * Lista de tareas
 */
typedef struct _tarea{
	short int numJob;
	short int numTarea;
}elementTarea;

void agregarTareaAListaDeTareas(int numJob,int numTarea,t_list *listaDeTareas){
	elementTarea* tareaNueva;
	tareaNueva=malloc(sizeof(elementTarea));
	tareaNueva->numJob=numJob;
	tareaNueva->numTarea=numTarea;
	list_add(listaDeTareas,tareaNueva);
}

void (*destruir)(void*);
void destruirTarea(void* task)
{
free(task);
}
void mostrarTarea(elementTarea* pepe){
	printf("numJob:%d y numTarea:%d\n",pepe->numJob,pepe->numTarea);
}


/**
 * Lista de Nodos
 */

typedef struct _elementNodo{
	char *nodoName;
	t_list*listaDeTareas;
}elementNodo;
/////
void mostrarNodo(elementNodo* pepe){
printf("nombre de nodo %s cantidad de tareas %d\n",pepe->nodoName,list_size(pepe->listaDeTareas));
}




/*
 *
 */
void agregarNodoALaLista(t_list* lista_De_Nodos,char* nodoName){
	elementNodo* nodoNuevo=malloc(sizeof(elementNodo));
	nodoNuevo->nodoName=malloc(strlen(nodoName)+1);
	strcpy(nodoNuevo->nodoName,nodoName);
	nodoNuevo->listaDeTareas=list_create();
	list_add(lista_De_Nodos,nodoNuevo);
}
////////
bool closure_comp_elDeMenorTareas(elementNodo* unNodoA,elementNodo* unNodoB){
int tamanioA,tamanioB;
tamanioA=list_size(unNodoA->listaDeTareas);
tamanioB=list_size(unNodoB->listaDeTareas);
return(tamanioA<=tamanioB?1:0);
}
/*
int getTamanioDelNodo(t_list* lista_De_Nodos,char* nodoName){


}*/


/*
buscarElMenorDeLaListaNodos(t_list* lista_De_Nodos){

	if(!list_is_empty(lista_De_Nodos)){


	}

}
*/

/**
 * Devuelve 0 si no lo encontro y si lo encontro devuelve la posicion en la lista de nodos
 *
 */
int BuscarNodoEnLista(t_list* lista_De_Nodos,char* nodoName){
		int index=0;
		int size=list_size(lista_De_Nodos);
		elementNodo *nodo;
		for(;index<size;index++){
			nodo=list_get(lista_De_Nodos,index);
			printf("%s    %s  \n",nodo->nodoName,nodoName);
			if (!(strcmp(nodo->nodoName,nodoName)))
				break;
		}
	return((index<size)?index:-1);
}


/**
 *agrego tarea a un nodo que si o si se presume que el nodo pertenece a la lista
 *y la ordena ya dentro la Ordena
 */
void agregarTareaAlNodo(t_list* lista_De_Nodos,char* nodoName,elementTarea tarea){
	int indice=BuscarNodoEnLista(lista_De_Nodos, nodoName);
	elementNodo *nodo;
	nodo=list_get(lista_De_Nodos,indice);
	agregarTareaAListaDeTareas(tarea.numJob,tarea.numTarea,nodo->listaDeTareas);

}










t_list* nodosLISTA;


int main(void) {
	t_list* tareas;
	t_list* lista_De_Nodos;
	elementTarea tarea;
	tarea.numJob=1;
	tarea.numTarea=2;
	lista_De_Nodos=list_create();
	agregarNodoALaLista(lista_De_Nodos,"NodoA");
	agregarNodoALaLista(lista_De_Nodos,"NodoB");
	agregarNodoALaLista(lista_De_Nodos,"NodoC");
	agregarTareaAlNodo(lista_De_Nodos,"NodoB",tarea);
	agregarTareaAlNodo(lista_De_Nodos,"NodoB",tarea);
	agregarTareaAlNodo(lista_De_Nodos,"NodoB",tarea);
	int i=BuscarNodoEnLista(lista_De_Nodos,"NodoB");
	elementNodo *nodo;
	nodo = list_get(lista_De_Nodos,i);
	printf("El tamaño del nodo es de :%d\n",list_size(nodo->listaDeTareas));
	printf("respuesta %s %d\n",(i+1)?"encontro":"no encontro",i);

list_iterate(lista_De_Nodos,mostrarNodo);

	///ordenar
	list_sort(lista_De_Nodos,closure_comp_elDeMenorTareas);
list_iterate(lista_De_Nodos,mostrarNodo);
nodo = list_get(lista_De_Nodos,0);
printf("%s\n",nodo->nodoName);
//destruir= destruirTarea;


return 1;
}
