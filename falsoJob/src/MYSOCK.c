/*
 * MYSOCK.c
 *
 *  Created on: 6/5/2015
 *      Author: utnso
 */
#include "MYSOCK.h"

int open_Socket(){
	int sock;
	sock=socket(AF_INET,SOCK_STREAM,0);
	return sock;
	}


void Configure_Sockaddr(unsigned short port,char* ip,struct sockaddr_in* dest_addr){

	dest_addr->sin_family=AF_INET;
	dest_addr->sin_port=htons(port);
	dest_addr->sin_addr.s_addr=inet_addr(ip);
	memset(dest_addr->sin_zero,'\0',8);

}


void enviarDato(void * dato,int socketDeComunicacion, int TipoDeDato ){

	size_t lengthReal;

	switch(TipoDeDato){
	case NUMINT:
		lengthReal=sizeof(int);
		break;
	case PALABRA:
		lengthReal=strlen( dato)+1;
		break;
	}
	void *buffer=malloc(sizeof(int)+lengthReal);
	memcpy(buffer,&lengthReal,sizeof(int));
	memcpy(buffer+sizeof(int),dato,lengthReal);
	send(socketDeComunicacion,buffer,lengthReal+sizeof(int),0);
	free(buffer);
}



void enviarDato2(void* dato,int socketDeComunicacion, int TipoDeDato ){

	size_t lengthReal;
	switch(TipoDeDato){
	case NUMINT:
		lengthReal=sizeof(int);
		break;
	case PALABRA:
		lengthReal=strlen(dato)+1;
		break;
	case ROMPERENVIO:
		lengthReal=0;
		break;
	}

	void *buffer=malloc(sizeof(int)+lengthReal);//reservo memoria para el tamaño y para el dato en si
	memcpy(buffer,&lengthReal,sizeof(int));///pongo el tamaño en el buffer
	if(lengthReal==0) { //en el caso q rompamos el envio
		  send(socketDeComunicacion,buffer,sizeof(int),0);//Envio solo el tamaño de 0 a travez del socket
		  }
	else{
		memcpy(buffer+sizeof(int),dato,lengthReal);///pongo el dato en el buffer seguido del tamaño antes puesto
		send(socketDeComunicacion,buffer,lengthReal+sizeof(int),0);///envio el tamño y el dato (buffer) al cliente
	}
	free(buffer);//libero la memoria dinamica
}


int recibirDato(void* dato,int socketDeComunicacion){
	int length;
	void* buffer=malloc(50);//esto esta predefinido
	recv(socketDeComunicacion,buffer,sizeof(int),0);
	memcpy(&length,buffer ,sizeof(int));//copio lo el tamaño q tengo en el buffer
	if(length!=0){  //si el tamaño no es cero
		recv(socketDeComunicacion,buffer+sizeof(int),length,0);//recibo el dato en el buffer seguido del tamaño
		memcpy(dato,buffer+sizeof(int),length);//copio el dato que esta en el buffer en mi estructura
	}

free(buffer);//libero memoria
return length;//devuelvo el tamaño recibido
}



















