#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrices.h"
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


//PUNTOS NECESARIOS PARA GANAR LA PARTIDA
#define MAX_POINTS 14


//FUNCION ERROR USADA POR LOS SOCKET
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
void LOGO()
{
char str[29]="Proyecto Sistema Distribuidos";
char str1[15]="Realizado por:";
char str2[15]="Moreno, José";
char str3[15]="Peña, Angel";
char str4[15]="Zaghab, Milad";
char str5[60]="          * * * * * * * * * * BATTLESHIP * * * * * * * * * *";
	int i = 0;
printf("\n\n\n\n\n\E[35m");
 
        printf("\E[1m");
    
    for(i=0;str[i]!='\0';i++)
    {
        putchar(str[i]);
  fflush(stdout);
  usleep(100000);
    }
    printf("\n");
   printf("\E[1;36m");
    
for(i=0;str1[i]!='\0';i++)
    {
        putchar(str1[i]);
  fflush(stdout);
  usleep(100000);
    }
     printf("\n");

 for(i=0;str2[i]!='\0';i++)
    {
        putchar(str2[i]);
  fflush(stdout);
  usleep(100000);
    }
     printf("\n");

   
    for(i=0;str3[i]!='\0';i++)
    {
        putchar(str3[i]);
  fflush(stdout);
  usleep(100000);
    }
     printf("\n");

    
    for(i=0;str4[i]!='\0';i++)
    {
        putchar(str4[i]);
  fflush(stdout);
  usleep(100000);
    }

       printf("\n\n \E[1;30m");

 for(i=0;str5[i]!='\0';i++)
    {
        putchar(str5[i]);
  fflush(stdout);
  usleep(100000);
    }
    printf("\n\n\n\E[00m");

}






int main(int argc, char *argv[])
{


     int sockfd, newsockfd, portno, n;
     char buffer[13];
     struct sockaddr_in serv_addr, cli_addr;

     socklen_t clilen;

// MATRICES DEL CLIENTE/SERVIDOR   Y EL OTRO CLIENTE
	char TableroCliente[10][10];
	char TableroHost[10][10];
	char TableroDisparosCliente[10][10];
	char TableroDisparosHost[10][10];

	// CONTADORES DE ACIERTOS PARA SABER CUANDO GANO
	int AciertosHost = 0;
	int AciertosClient = 0;


// COORDENADAS Y ORIENTACION DEL BARCO
	int x, y;
	char orientacion;


     
     //VALIDACION DE ARGUMENTOS 
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     //apertura de socket inicial
     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0) 
        error("ERROR opening socket");

     //conexion de server con cliente
     bzero((char *) &serv_addr, sizeof(serv_addr));  //setear srv_addr en 0
     portno = atoi(argv[1]);  //transforma el parametro del main en un numero de puerto

     //parametros del serv_Addr
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     //conexion.
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
system("clear");

	

     //Espera de una aceptacion desde el cliente 
     printf("%s\n", "\E[5m \E[31m Esperando por Jugador Enemigo...\E[00m" );   
     listen(sockfd,1);
     clilen = sizeof(cli_addr);


     //acepacion de la conexion
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

     //verificacion de la conexion
     if (newsockfd < 0) 
          error("ERROR on accept");


system("clear");
     
     LOGO();

     /*===============================================================================*/
     /*=================FASE DE COLOCACION==============================================*/
     /*===============================================================================*/

     InicializarMatriz(TableroHost);
       InicializarMatriz(TableroCliente);
         InicializarMatriz(TableroDisparosHost);
           InicializarMatriz(TableroDisparosCliente);



       /*===============================================================================*/
      							/*===Fase de Portavion ======*/
       /*===============================================================================*/

    while(1){
    
    	while(1){

		printf("ingrese la orientacion del  \E[32mPortavion (5 casillas)\E[31m (h/v) \E[30m \n");
			scanf("%c", &orientacion);
				if(ValidarOrientcion(orientacion)==1)
					break;
				//SE VALIDA QUE LA LETRA INTRODUCIDA SEA h o v

			system("clear");
				}


		
		printf("ingrese las coordenadas del \E[32m Portavion (5 casillas) \E[30m \n");
				printf("\E[36m X= ");
				scanf("%d", &x);

				printf("Y= ");
				scanf("%d", &y);
				
				
				//SE VERIFICA SI SE PUEDE COLOCAR EL BARCO PARA SALIR DEL WHILE
			if ( ColocarBarco( TableroHost, 5, orientacion, x,y) != 0 )
				break;
				
	}

	 			
	 			printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
	     		ImprimirMatriz(TableroHost);

   

  /*===============================================================================*/
      							/*===Fase de Barco ======*/
       /*===============================================================================*/
   


    while(1){
    
		//Clear Buffer
		while ((orientacion = getchar()) != '\n' && orientacion != EOF) { }
		x=y=0;
			while(1){
				printf("ingrese la orientacion del \E[32m Barco (4 casillas)\E[31m(h/v)\E[30m \n");
				scanf("%c", &orientacion);
				if(ValidarOrientcion(orientacion)==1)
				break;

			system("clear");
					}

						printf("ingrese las coordenadas del \E[32m barco (4 casillas)\E[30m \n");
						printf("\E[36m X= ");
						scanf("%d", &x);

						printf("Y= ");
						scanf("%d", &y);
						


						if ( ColocarBarco( TableroHost, 4, orientacion, x,y) != 0 )
							break;
				
						}
	
	 printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
	 ImprimirMatriz(TableroHost);
	 
  /*===============================================================================*/
      							/*===Fase de Fragatta======*/
       /*===============================================================================*/
   
    while(1){
    
		//Clear Buffer
		while ((orientacion = getchar()) != '\n' && orientacion != EOF) { }
		x=y=0;


		while(1){
		printf("ingrese la orientacion de la \E[32m Fragatta (3 casillas)\E[31m(h/v)\E[30m \n");
		scanf("%c", &orientacion);
		if(ValidarOrientcion(orientacion)==1)
				break;

			system("clear");
					}

					
						printf("ingrese las coordenadas de la \E[32m Fragatta (3 casillas)\E[30m \n");
						printf("\E[36m X= ");
						scanf("%d", &x);

						printf("Y= ");
						scanf("%d", &y);

							



		if ( ColocarBarco( TableroHost, 3, orientacion, x,y) != 0 )
			break;
				
	}
	
	 printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
	 ImprimirMatriz(TableroHost);
	 
  /*===============================================================================*/
      							/*===Fase de Lancha ======*/
  /*===============================================================================*/
   
    while(1){
    
		//Clear Buffer
		while ((orientacion = getchar()) != '\n' && orientacion != EOF) { }
		x=y=0;

			while(1){
		printf("ingrese la orientacion de la \E[32m Lancha (2 casillas)\E[31m(h/v)\E[30m \n");
		scanf("%c", &orientacion);
		if(ValidarOrientcion(orientacion)==1)
				break;

			system("clear");
					}


		printf("ingrese las coordenadas de la \E[32m Lancha (2 casillas)\E[30m \n");
		printf("\E[36m X= ");
		scanf("%d", &x);

		printf("Y= ");
		scanf("%d", &y);


		if ( ColocarBarco( TableroHost, 2, orientacion, x,y) != 0 )
			break;
				
	}
	
	 printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
	 ImprimirMatriz(TableroHost);
 	

 	/*===============================================================================*/
     /*=================FASE DE PREINICIALIZACION====================================*/
     /*===============================================================================*/
	 system("clear");
     
	 		printf(" \E[31m \E[5m Esperando por la jugada del enemigo...\E[00m\n");
					//limpia el mensaje
			     		bzero(buffer,13);

					     //espera del mensaje
			     		// SE RECIBE MENSAJE  CON EL BUFFER DEL CLIENTE Y SE ACTUALIZA LAS 
			     		//TABLA DEL JUGADOR (CLIENTE)

					     n = read(newsockfd,buffer,13);
					     if (n < 0) error("ERROR reading from socket");

					     ColocarBarco( TableroCliente, 5, buffer[0], buffer[1]-'0', buffer[2]-'0');
					     ColocarBarco( TableroCliente, 4, buffer[3], buffer[4]-'0', buffer[5]-'0');
					     ColocarBarco( TableroCliente, 3, buffer[6], buffer[7]-'0', buffer[8]-'0');
					     ColocarBarco( TableroCliente, 2, buffer[9], buffer[10]-'0', buffer[11]-'0');


						printf("                         \E[31m * * Tablero De Disparos * * \E[30m\n");
				     	ImprimirMatriz(TableroDisparosHost);
				     	printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
				     	ImprimirMatriz(TableroHost);
    


				     //escribe un mensaje al cliente para comenzar la partida
				     n = write(newsockfd,"start",5);
				     if (n < 0) error("ERROR writing to socket");

  /*===============================================================================*/
      							/*===Fase de Juego ======*/
       /*===============================================================================*/
 
     while(1){
         while(1){

         	    //Clear Buffer
   		 		while ((orientacion = getchar()) != '\n' && orientacion != EOF) { }
    	 		x=y=0;

	     	 printf("\E[31m Introduzca la coordenada de disparo:\n");

	     	 printf("X= ");
			 scanf("%d", &x);

			 printf("Y= ");
			 scanf("%d", &y);
			 printf("\E[30m");

			 int validacionDisparo = ValidarDisparo( TableroDisparosHost , x, y);

			 if ( validacionDisparo == 2 ){
			 	printf("Ya has disparado en esa posicion\n");
			 	continue;
			 }

			 if ( validacionDisparo == 0 ){
			 	printf("Esa Posicion no es Valida\n");
			 	continue;
			 }
			 if ( validacionDisparo == 1){

				 break;			 	
			 }


		 }


		 //Esperar mensaje de cliente
		  //system("Clear");


		   printf("                         \E[31m * * Tablero De Disparos * * \E[30m\n");
	     	ImprimirMatriz(TableroDisparosHost);
	     		printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
	     			ImprimirMatriz(TableroHost);
		 printf("Esperando por la jugada del enemigo...\n");
		
		 

	     //limpia el mensaje
	     bzero(buffer,13);

	     //espera del mensaje
	     n = read(newsockfd,buffer,6);
	     if (n < 0) error("ERROR reading from socket");

/*===============================================================================*/
				//====VERIFICACION DE LOS DISPAROS=======//
 /*===============================================================================*/


	     int verificacionDisparoCliente = VerificarDisparo( TableroHost , buffer[0] - '0', buffer[1] -'0');
		 int verificacionDisparoHost = VerificarDisparo( TableroCliente , x, y);

		 AciertosClient += verificacionDisparoCliente;

		 AciertosHost += verificacionDisparoHost;

		 RegistrarDisparo(TableroCliente, verificacionDisparoHost, x, y);
		 RegistrarDisparo(TableroDisparosHost, verificacionDisparoHost, x, y);

		 RegistrarDisparo(TableroHost, verificacionDisparoCliente, buffer[0] - '0', buffer[1] -'0');
		 RegistrarDisparo(TableroDisparosCliente, verificacionDisparoCliente, buffer[0] - '0', buffer[1] -'0');



	     //escribe un mensaje al cliente para dar notificacion de acierto/fallo
   		 bzero(buffer,7);
   		 buffer[0] = verificacionDisparoCliente + '0'; //verificacion del disparo de cliente
   		 buffer[1] = verificacionDisparoHost + '0'; //verificacion de mi disparo para el registro del cliente
   		 buffer[2] = x + '0'; //disparo mio para registro en el tablero del cliente
   		 buffer[3] = y + '0';

	     n = write(newsockfd,buffer,4);
	     if (n < 0) error("ERROR writing to socket");


	     printf("                         \E[31m * * Tablero De Disparos * * \E[30m\n");
	     	ImprimirMatriz(TableroDisparosHost);
	     		printf("                          \E[31m* * Tablero De Barcos * * \E[30m\n");
	     			ImprimirMatriz(TableroHost);

/*===============================================================================*/
	   			  //=====VERIFICACION DE GANADOR=========
/*===============================================================================*/

	     bzero(buffer,7);

	     if ( AciertosHost >= MAX_POINTS ){
	     	//EL sERVER GANA LA PARTIDA
	     	//escribir en el socket
	     	n = write(newsockfd,"0010",4);

	        if (n < 0) error("ERROR writing to socket");

	        printf("\E[5m HAS DERROTADO AL ENEMIGO!\E[00m\n");

	        break;
	     }

	     if (AciertosClient >= MAX_POINTS){
	     	//EL CLIENTE GANA LA PARTIDA
	     	//escribir en el socket
	     	n = write(newsockfd,"0020",4);
	        if (n < 0) error("ERROR writing to socket");

            printf("\E[5m HAS SIDO HUNDIDO CAPITAN!\E[00m\n");

	        break;
	     }
         else{
		     n = write(newsockfd,"0000",4);
		     if (n < 0) error("ERROR writing to socket");
	 	 } 



     }

     sleep(2);


     //cerrar sockets
     close(newsockfd);
     close(sockfd);
     return 0; 

}
