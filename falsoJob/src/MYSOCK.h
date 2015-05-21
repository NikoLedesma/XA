/*
 * MYSOCK.h
 *
 *  Created on: 6/5/2015
 *      Author: utnso
 */

#ifndef SRC_MYSOCK_H_
#define SRC_MYSOCK_H_
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @desc:abre un nuevo socket;
 *
 */
/**
 * @desc:abre un nuevo socket;
 *
 */
int open_Socket();

/**
 * @desc:configura la estructura del sockaddr_in
 * @param port:el puerto el cual nos comunicaremos
 * @param ip:la ip el cual va a ser una cadena
 * @param dest_addr:un puntero al struct sockaddr_in*
 */
void Configure_Sockaddr(unsigned short port,char* ip,struct sockaddr_in* dest_addr);


/**
 * @param dato:puntero al dato que se desea mandar.
 * @param tamanioDeDato:puntero al tamaño del dato---->puede ser sizeof(int) o el tamaño de la palabra
 * @param socketDeComunicacion:-
 * @param TipoDeDato: Este me indica si es una palabra o un numero entero(PALABRA O NUMINT)
 *
 */
void enviarDato(void* dato,int socketDeComunicacion, int TipoDeDato );


/**
 * @Descr:
 * @param dato:puntero al dato que se desea mandar.
 * @param socketDeComunicacion:-
 * @param TipoDeDato: Este me indica si es una palabra o un numero entero(PALABRA O NUMINT)o si Rompo el envio(ROMPER)
 */
void enviarDato2(void* dato,int socketDeComunicacion, int TipoDeDato );

/**
 * @Descr:Esta funcion se encarga de llenar un dato sea un numero o una palabra , pero se debe tener cuidado
 * que se usa para llenar de a poco una estructura y se debera cordinar el envio y el recibimiente entre el
 * servidor y el cliente, por ejemplo si el servidor tiene que enviar un string , int, int entonces el cliente
 * debera recibir del otro lado un string, int ,int en el mismo orden ,en caso de que no este bien coordinado
 * no funciona
 * @param dato:puntero a la dato el cual tengo q llenar con la info q me envian
 * @param socketDeComunicacion:-
 * @param TipoDeDato: Este me indica si es una palabra o un numero entero(PALABRA O NUMINT)o si Rompo el envio(ROMPER)
 * @retorna:devuelve el tamaño q se recibio
 */
int recibirDato(void* dato,int socketDeComunicacion);




enum SOCK{NUMINT,PALABRA,ROMPERENVIO};

#endif /* SRC_MYSOCK_H_ */
