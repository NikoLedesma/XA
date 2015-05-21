/*
 ============================================================================
 Name        : falsoJob.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 ============================================================================
 Name        : falsoJob.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */




#include "MYSOCK.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PuertoX 34032
#define IpX "127.0.0.1"



typedef struct _packer{
	char* ip;
	char* puerto;
	int	nroBloque ;
	char* nombreArchivoTMP;
} packMaper2 __attribute__ ((packed));

void recibir_estructura(int sock,packMaper2* paquete){

void* buffer=malloc(4*sizeof(int));
int ipLength,puertoLength,bloqLength,nombreArchLength;
recv(sock,buffer,4*sizeof(int),0);

memcpy(&ipLength,buffer,sizeof(int));
memcpy(&puertoLength,buffer+sizeof(int),sizeof(int));
memcpy(&bloqLength,buffer+sizeof(int)*2,sizeof(int));
memcpy(&nombreArchLength,buffer+sizeof(int)*3,sizeof(int));
printf("%d\n",ipLength);
printf("%d\n",puertoLength);
printf("%d\n",bloqLength);
printf("%d\n",nombreArchLength);
paquete->ip=malloc(ipLength);
paquete->puerto=malloc(puertoLength);
paquete->nombreArchivoTMP=malloc(nombreArchLength);
free(buffer);

buffer=malloc(ipLength+puertoLength+bloqLength+nombreArchLength);
recv(sock,buffer,ipLength+puertoLength+bloqLength+nombreArchLength,0);
memcpy(paquete->ip,buffer,ipLength);
memcpy(paquete->puerto,buffer+ipLength,puertoLength);
memcpy(&paquete->nroBloque,buffer+ipLength+puertoLength,bloqLength);
memcpy(paquete->nombreArchivoTMP,buffer+ipLength+puertoLength+bloqLength,nombreArchLength);
free(buffer);
}




int main(void) {
	int client=open_Socket();
	struct sockaddr_in dest_addr;
	if(client!=1)
	{
		Configure_Sockaddr(PuertoX,IpX,&dest_addr);
		connect(client,(struct sockaddr *)&dest_addr,sizeof(struct sockaddr));
		//recibo


		packMaper2 *paquete=malloc(sizeof(packMaper2));
		recibir_estructura(client,paquete);
		printf("%s\n",paquete->ip);
		printf("%s\n",paquete->puerto);
		printf("%d\n",paquete->nroBloque);
		printf("%s\n",paquete->nombreArchivoTMP);
		free(paquete->ip);
		free(paquete->nombreArchivoTMP);
		free(paquete->puerto);
		free(paquete);
		printf("Termino");
		getchar();
		close(client);
	}
	else
	{
		return -1;
	}
return 0;
}
