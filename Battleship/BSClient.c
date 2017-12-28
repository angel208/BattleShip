#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrices.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 


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

       printf("\n\n\E[1;30m");

 for(i=0;str5[i]!='\0';i++)
    {
        putchar(str5[i]);
  fflush(stdout);
  usleep(100000);
    }
    printf("\n\n\n \E[00m");

}





int main(int argc, char *argv[])
{
 
    char Tablero[10][10];
    char TableroDisparos[10][10];
    int x, y;
    char orientacion;


    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[20];

    //VALIDACION DE LOS PARAMETROS DE ENTRADA
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    //transofrmacion del parametro de entrada a un numero de puerto
    portno = atoi(argv[2]);

    //apertura del socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    //obtencion del host.
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    //conexion con el servidor
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    //conexion
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    printf("Conexion realizada\n");
    system("clear");
     LOGO();

/*===============================================================================*/
                /*===========FASE DE COLOCACION=============*/
 /*===============================================================================*/   
    
    InicializarMatriz(Tablero);
    InicializarMatriz(TableroDisparos);
    

 /*===============================================================================*/
                     /*===Fase de Portavion ======*/
/*===============================================================================*/


    while(1){
    printf("ingrese la orientacion del \E[32m Portavion (5 casillas)\E[31m(h/v)\E[30m \n");
    scanf("%c", &orientacion);

    printf("ingrese las coordenadas del \E[32m Portavion (5 casillas) \E[30m \n");
    printf("\E[36m X= ");
    scanf("%d", &x);

    printf("Y= ");
    scanf("%d", &y);
    printf("\E[30m" );

			if ( ColocarBarco( Tablero, 5, orientacion, x,y) != 0 )
				break;
				
	}

    bzero(buffer,7);
    buffer[0]= orientacion;
    buffer[1]= x +'0';
    buffer[2]= y +'0';

    printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
    ImprimirMatriz(Tablero);
    

 /*===============================================================================*/   
                         /*===========BARCO=========*/
/*===============================================================================*/
	
     while(1){
	 
		 while ((orientacion = getchar()) != '\n' && orientacion != EOF) { }
			x=y=0;
			
		printf("ingrese la orientacion del \E[32m Barco (4 casillas)\E[31m(h/v)\E[30m \n");
		scanf("%c", &orientacion);

		printf("ingrese las coordenadas del \E[32m Barco (4 casillas) \E[30m \n");
		printf("\E[36m X= ");
		scanf("%d", &x);

		printf("Y= ");
		scanf("%d", &y);
		printf("\E[30m" );

				if ( ColocarBarco( Tablero, 4, orientacion, x,y) != 0 )
					break;	
				
	}

    buffer[3]= orientacion;
    buffer[4]= x +'0';
    buffer[5]= y +'0';
system("clear");
    printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
    ImprimirMatriz(Tablero);

   
 /*===============================================================================*/
                     /*===========FRAGATTA=========*/
/*===============================================================================*/	 
     
     while(1){
	 
		 while ((orientacion = getchar()) != '\n' && orientacion != EOF) { }
				x=y=0;
			
		printf("ingrese la orientacion de la \E[32m Fragatta (3 casillas)\E[31m(h/v)\E[30m \n");
		scanf("%c", &orientacion);

		printf("ingrese las coordenadas de la \E[32m Fragatta (3 casillas) \E[30m \n");
		printf("\E[36m X= ");
		scanf("%d", &x);

		printf("Y= ");
		scanf("%d", &y);
		printf("\E[30m" );

				if ( ColocarBarco( Tablero, 3, orientacion, x,y) != 0 )
					break;
				
	}

    buffer[6]= orientacion;
    buffer[7]= x +'0';
    buffer[8]= y +'0';
system("clear");
    printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
    ImprimirMatriz(Tablero);


    
 /*===============================================================================*/
                    /*===========LANCHA=========*/
 /*===============================================================================*/
    
    while(1){

        //Clear Buffer
		while ((orientacion = getchar()) != '\n' && orientacion != EOF) { }
		x=y=0;

	    printf("ingrese la orientacion de la \E[32m Lancha (2 casillas)\E[31m(h/v)\E[30m \n");
		scanf("%c", &orientacion);

		printf("ingrese las coordenadas de la \E[32m Lancha (2 casillas)\E[30m \n");
		printf("\E[36m X= ");
		scanf("%d", &x);

		printf("Y= ");
		scanf("%d", &y);
		printf("\E[30m" );

			if ( ColocarBarco( Tablero, 2, orientacion, x,y) != 0 )
				break;
				
	}
	

    buffer[9]= orientacion;
    buffer[10]= x +'0';
    buffer[11]= y +'0';
    
    //envio del mensaje
    n = write(sockfd,buffer,13);
    if (n < 0) 
         error("ERROR writing to socket");

system("clear");
 printf("                         \E[31m * * Tablero De Disparos * * \E[30m\n");
    ImprimirMatriz(TableroDisparos);
    printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
    ImprimirMatriz(Tablero);

/*===============================================================================*/
             /*=========FASE DE preinicializacion============*/ 
/*===============================================================================*/

            printf(" \E[31m \E[5m Esperando la jugada del enemigo...\E[00m\n");
                //recepcion de mensaje de espera para comenzar el juego
                bzero(buffer,7);
                    n = read(sockfd,buffer,7); //lee el mensaje
                     if (n < 0) 
                      error("ERROR reading from socket");

/*===============================================================================*/
                    /*============FASE DE JUEGO=============*/
/*===============================================================================*/

     while(1){
            while(1){
                //Clear Buffer
                    while ((orientacion = getchar()) != '\n' && orientacion != EOF) { }
                        x=y=0;

                printf(" \E[31m Introduzca la coordenada de disparo:\n");
                
                printf("X= ");
                scanf("%d", &x);

                printf("Y= ");
                scanf("%d", &y);
                printf(" \E[30m ");

                    int validacionDisparo = ValidarDisparo( TableroDisparos , x, y);

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

printf("\E[5m Esperando por la jugada del enemigo...\E[00m\n");
         } // fin segundo wwhile

            bzero(buffer,7); //LIMPIO BUFFER
            buffer[0]= x +'0';
            buffer[1]= y +'0';

    
         //Mando disparo al servidor
             n = write(sockfd,buffer,strlen(buffer));
                if (n < 0) 
                    error("ERROR writing to socket");


            //===ESPERAR POR LA VERIFICACION DEL DISPARO 
            //recepcion de mensaje de espera para continuar juego
                bzero(buffer,7);
                    n = read(sockfd,buffer,6); //lee el mensaje
                    if (n < 0) 
                    error("ERROR reading from socket");

                    RegistrarDisparo(Tablero, buffer[1] - '0', buffer[2] - '0', buffer[3] - '0');
                    RegistrarDisparo(TableroDisparos, buffer[0] - '0', x, y);
        
 system("clear");
                printf("                         \E[31m * * Tablero De Disparos * * \E[30m\n");
                ImprimirMatriz(TableroDisparos);
                printf("                         \E[31m * * Tablero De Barcos * * \E[30m\n");
                ImprimirMatriz(Tablero);
                
         
         

/*===============================================================================*/
         //====ESPERA POR LA VERIFICACION DE GANADOR========
/*===============================================================================*/
            bzero(buffer,7);

             n = read(sockfd,buffer,4); //lee el mensaje
                

         if (n < 0) 
             error("ERROR reading from socket");

         if( buffer[0] == '1'){
            printf("\E[31m \E[5m HAS SIDO HUNDIDO CAPITAN! \E[00m\n");
            break;
         }

         if( buffer[0] == '2'){
            printf("\E[31m  \E[5m HAS DERROTADO AL ENEMIGO!! \E[00m\n");
            break;
         }
    } // FIN PRIMER WHILE


     

    //cerrar sockets
     close(sockfd);
     return 0; 

   
}
