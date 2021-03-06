/*
 ============================================================================
 Name        : Marta.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "MYSOCK.h"
#define PuertoX 34032
#define PuertoF 34034
#define IpX "127.0.0.1"


typedef struct _packer{
	char* ip;
	uint32_t ip_long;
	char* puerto;
	uint32_t puerto_long;
	int	nroBloque ;
	uint32_t nroBloque_long;
	char* nombreArchivoTMP;
	uint32_t nombreArchivoTMP_long;
} packMaper __attribute__ ((packed));


void enviar_estructura(packMaper st,int sock){
	void * buffer;
int lengthDeDatos=st.ip_long+st.puerto_long+st.nroBloque_long+st.nombreArchivoTMP_long ;
buffer= malloc(sizeof(int)*4+ lengthDeDatos);

printf("%d\n",st.ip_long);
printf("%d\n",st.puerto_long);
printf("%d\n",st.nroBloque_long);
printf("%d\n",st.nombreArchivoTMP_long);
 int aux;
memcpy(buffer, &st.ip_long,sizeof(int));
aux=sizeof(int);
memcpy(buffer+aux,&st.puerto_long ,sizeof(int));
aux=aux+sizeof(int);
memcpy(buffer+aux,&st.nroBloque_long ,sizeof(int));
aux=aux+sizeof(int);
memcpy(buffer+aux, &st.nombreArchivoTMP_long,sizeof(int));
aux=aux+sizeof(int);
memcpy(buffer+aux,st.ip,st.ip_long);
aux=aux+st.ip_long;
memcpy(buffer+aux, st.puerto  ,st.puerto_long);
aux=aux+st.puerto_long;
memcpy(buffer+aux,&st.nroBloque  ,st.nroBloque_long);
aux=aux+st.nroBloque_long;
memcpy(buffer+aux,st.nombreArchivoTMP,st.nombreArchivoTMP_long);
aux=aux+st.nombreArchivoTMP_long;
send(sock,buffer,aux ,0);
free(buffer);
}














////////paqute para enviarle al job de mapeo
typedef struct _paquete_SToJobM {
	char ip [15];
	uint32_t ip_long;
	char puerto[10];
	uint32_t puerto_long;
	int	nroBloque ;
	uint32_t nroBloque_long;
	char nombreArchivoTMP[20];
	uint32_t nombreArchivoTMP_long;
} paquete_SToJobM __attribute__ ((packed));

void enviar_paquete_SToJobM(paquete_SToJobM paquete,int sock){
	void * buffer;
paquete.ip_long=strlen(paquete.ip)+1;;
paquete.puerto_long=strlen(paquete.puerto)+1;
paquete.nroBloque_long=sizeof(int);
paquete.nombreArchivoTMP_long=strlen(paquete.nombreArchivoTMP)+1;
buffer= malloc(sizeof(int)*4+ 50);  ///50>length de todos los datos juntos
 int aux;
memcpy(buffer, &paquete.ip_long,sizeof(int));
aux=sizeof(int);
memcpy(buffer+aux,&paquete.puerto_long ,sizeof(int));
aux=aux+sizeof(int);
memcpy(buffer+aux,&paquete.nroBloque_long ,sizeof(int));
aux=aux+sizeof(int);
memcpy(buffer+aux, &paquete.nombreArchivoTMP_long,sizeof(int));
aux=aux+sizeof(int);
memcpy(buffer+aux,paquete.ip,paquete.ip_long);
aux=aux+paquete.ip_long;
memcpy(buffer+aux, paquete.puerto  ,paquete.puerto_long);
aux=aux+paquete.puerto_long;
memcpy(buffer+aux,&paquete.nroBloque  ,paquete.nroBloque_long);
aux=aux+paquete.nroBloque_long;
memcpy(buffer+aux,paquete.nombreArchivoTMP,paquete.nombreArchivoTMP_long);
aux=aux+paquete.nombreArchivoTMP_long;
send(sock,buffer,aux ,0);
free(buffer);
}



int main(void) {
	int listener=socket(AF_INET,SOCK_STREAM,0);
	int mailman;
	socklen_t longitud_cliente;
	struct sockaddr_in server ,client;
	char buf[255];
	socklen_t lonsitud_server=sizeof(server);
	if(listener!=-1)
	{
		Configure_Sockaddr(PuertoX,IpX,&server);
		if(bind(listener,(struct sockaddr*)&server, lonsitud_server)!=-1)
		{
			if(listen(listener,5) !=-1)
			{
				printf("Esperando por el saludo....\n");
				longitud_cliente= sizeof(struct sockaddr_in);
				mailman = accept(listener,(struct sockaddr*)&client,&longitud_cliente);
				if (mailman !=-1)
				{

/*
packMaper s;
s.ip=malloc(20);
s.puerto=malloc(30);
s.nombreArchivoTMP=malloc(30);
strcpy(s.ip,"bbb");
strcpy(s.puerto,"324");
s.nroBloque=42;
strcpy(s.nombreArchivoTMP,"arch.txt");
s.ip_long=strlen(s.ip)+1;
s.puerto_long=strlen(s.puerto)+1;
s.nroBloque_long=sizeof(int);
s.nombreArchivoTMP_long=strlen(s.nombreArchivoTMP)+1;


enviar_estructura(s,mailman);*/


					paquete_SToJobM pepe;

					strcpy(pepe.ip,"hola");
					strcpy(pepe.puerto,"hola");
					pepe.nroBloque=3;
					strcpy(pepe.nombreArchivoTMP,"hola");
					enviar_paquete_SToJobM(pepe,mailman);
				}else close(mailman);
			}
		}
	}
	close(listener);
	return 0;
}
