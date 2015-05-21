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
/*int aux;
aux=0;
*/
memcpy(buffer, &st.ip_long,sizeof(int));
memcpy(buffer+sizeof(int),&st.puerto_long ,sizeof(int));
memcpy(buffer+sizeof(int)*2,&st.nroBloque_long ,sizeof(int));
memcpy(buffer+sizeof(int)*3, &st.nombreArchivoTMP_long,sizeof(int));
//////
memcpy(buffer+sizeof(int)*4,st.ip,st.ip_long);
memcpy(buffer+sizeof(int)*4+st.ip_long, st.puerto  ,st.puerto_long);
memcpy(buffer+sizeof(int)*4+st.ip_long+st.puerto_long,&st.nroBloque  ,st.nroBloque_long);
memcpy(buffer+sizeof(int)*4+st.ip_long+st.puerto_long+st.nroBloque_long,st.nombreArchivoTMP,st.nombreArchivoTMP_long);
printf("Envio:%d\n",lengthDeDatos);
getchar();
send(sock,buffer,lengthDeDatos+sizeof(int)*4 ,0);
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

packMaper s;
s.ip=malloc(20);
s.puerto=malloc(30);
s.nombreArchivoTMP=malloc(30);
strcpy(s.ip,"bbb");
strcpy(s.puerto,"324");
s.nroBloque=42;
strcpy(s.nombreArchivoTMP,"arch.txt");

printf("%s\n",s.ip);
printf("%s\n",s.puerto);
printf("%d\n",s.nroBloque);
printf("%s\n",s.nombreArchivoTMP);
getchar();
s.ip_long=strlen(s.ip)+1;
s.puerto_long=strlen(s.puerto)+1;
s.nroBloque_long=sizeof(int);
s.nombreArchivoTMP_long=strlen(s.nombreArchivoTMP)+1;

enviar_estructura(s,mailman);
				}else close(mailman);
			}
		}
	}
	close(listener);
	return 0;
}
