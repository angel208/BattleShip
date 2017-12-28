#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 10  //TAMAÑO DE LA MATRIZ

// DEFINICION DE LA ESTRUCTURA DE UN BARCO
struct ship { 
   int size;
   char name[20];
   char letra;
};



// FUNCIÓN PARA INICIALIZAR MATRIZ
void InicializarMatriz( char mat[][MATRIX_SIZE] ){
     
     int i=0;
     int j=0;

     for (i = 0; i < MATRIX_SIZE; ++i)
     {
     	for (j = 0; j < MATRIX_SIZE; ++j)
     	{
     		mat[i][j] = '~';
     	}
     }

}

void ImprimirMatriz( char mat[][MATRIX_SIZE] ){
int i=0;
 int j=0;

     printf("\n\n  ");
		
	 int e;	
		
     for (e = 0; e < 30; ++e)
      {
        printf(" "); //FOR PARA LLEVAR LA MATRIZ AL CENTRO DE EL TERMINAL
      }

     for ( i= 0 ; i < MATRIX_SIZE ; i++ )
      {
     	printf("%d \E[1;32m", i ); //COORDENAS EN X
      }

		printf("\n\E[30m");

      for (i = 0; i < MATRIX_SIZE; ++i)
        {// FOR BUCLE
          
          int e;
          
          for (e = 0; e < 30; ++e)
            {
              printf(" "); //FOR PARA LLEVAR LA MATRIZ AL CENTRO DE EL TERMINAL
              }
                printf("%d \E[1;32m", i); //COORDENADAS EN Y
                  printf("\E[30m");
        
                for (j = 0; j < MATRIX_SIZE; ++j)
     	            { // FOR VALIDA
                  
                    printf("%c ", mat[i][j]); //IMPRIME MATRIZ
                  }

              printf("\n");
        }//FIN FOR BUCLE
      printf("\n\n");

}// FIN  IMPRIMIR MTRIZ

int ValidarPosicion(char mat[][MATRIX_SIZE] , int ShipSize, char orientacion, int x, int y){
/* FUNCIÓN TIPO ENTERO VALIDA LA ORIENTACIÓN DEL BARCO, SI NO SE SALE DE LA MATRIZ MEDIANTE LAS COORDENADAS
Y SI DONDE SE QUIERE COLOCAR EL BARCO ES PURA AGUA
DEVUELVE 0 SI HAY ERROR. 
DEVUELVE 2  SI EL SITIO NO ES AGUA
DEVUELVE 1 SI SE VALIDO CORRECTAMENTE */
int i;
  if ( orientacion == 'h')
  {
    if( (x + ShipSize) > MATRIX_SIZE)
     {
	   		return 0;
	   }
     for ( i = 0 ; i < ShipSize ; i++)
     {
       if ( mat[y][x+i] != '~' )
        {
       	return 2;
       	 }
      }
return 1;
    }//fin if
	     else if (orientacion == 'v')
       {
        if( (y + ShipSize) > MATRIX_SIZE)
        {
	   		return 0;
        }
          for ( i = 0 ; i < ShipSize ; i++)
          {
       	    if ( mat[y+i][x] != '~' )
              {
       	    	return 2;
              }
          }// fin for

       return 1;
	   }// fin else if
}// fin validar posicion


int ColocarBarco( char mat[][MATRIX_SIZE] , int ShipSize, char orientacion, int x, int y){
/* FUNCIÓN QUE DEVUELVE UN ENTERO
 QUE UNA VEZ VALIDADO EL BARCO Y LO COLOCA EN LA MATRIZ DEVUELVE UN 1 SI SE COLOCO EXITOSAMENTE
Y UN CERO SI NO SE PUDO COLOCAR*/
	int i;

	if ( orientacion == 'h')
  {
    if ( ValidarPosicion(mat, ShipSize, orientacion, x, y) == 1 )
    {
      for ( i = 0 ; i < ShipSize ; i++)
       {
        mat[y][x+i] = 'B' ;
       }
				printf("%s\n", "Barco Colocado");
				return 1;
		}
  } // fin if
	else if (orientacion == 'v')
  {
    if ( ValidarPosicion(mat, ShipSize, orientacion, x, y) == 1 )
    {
      for ( i = 0 ; i < ShipSize ; i++)
        {
        mat[y+i][x] = 'B' ;
       	}
        printf("%s\n", "Barco Colocado");
				return 1;
		}
	} // fin else if
	
	printf("No se ha podido colocar el navio, compruebe sus coordenadas capitan!\n");
   return 0;
}

int ValidarDisparo(char mat[][MATRIX_SIZE] , int x, int y){
  /* FUNCIÓN TIPO ENTERA QUE VALIDA EL DISPARO ESTE DENTRO DE LA MATRIZ Y QUE LAS COORDENADAS 
  NO SE HUBIESE DISPARADO CON ANTERIORIDAD.
  DEVUELVE O SI SOBRESALE DE LOS LIMITE DE LA MATRIZ
  2 SI YA SE HA DISPARADO CON ANTERIORIDAD EN EL MISMO SITIO
  1 SI FUE CORRECTO EL DISPARO*/

	if ( x > MATRIX_SIZE || y > MATRIX_SIZE )
		return 0;

	   if ( x < 0 || y < 0)
		    return 0;

	     if( mat[y][x] == 'X' || mat[y][x] == '*')
		      return 2;

	return 1;

}

int VerificarDisparo( char mat[][MATRIX_SIZE], int x, int y){
  /* FUNCIÓN TIPO ENTERO QUE VERIFICA QUE EL DISPARO  EN LAS COORDENADAS NO PEGUE EN  AGUA
  DEVUELVE 1 SI PEGO EN EL OBJETIVO
   0 SI FUE EN EL AGUA*/

if( mat[y][x] != '~' ){
		return 1;
	}
  return 0;
}

void RegistrarDisparo( char mat[][MATRIX_SIZE], int Verificacion, int x, int y){
/* FUNCIÓN QUE REGISTRA EL DISPARO SI LA VERIFICACIÓN ES IGUAL A 1 SIGNIFICA QUE PEGUE EN EL OBJETIVO
POR LO QUE ACTUALIZO LA MATRIZ EN ESA COORDENADA A UNA X QUE SIGNIFICA QUE DI EN EL BARCO
SINO ACTUALIZO A * QUE SIGNFICA QUE CAYO EN EL AGUA*/
      if(Verificacion == 1)
      {
           mat[y][x] = 'X';
      }
        else if(Verificacion == 0)
        {
			     mat[y][x] = '*';
            }


}

int ValidarOrientcion(char orientacion)
{
   /* FUNCIÓN TIPO ENTERO QUE VERIFICA QUE EL DATO DE ENTRADA PARA LA ORIENTACIÓN SEA LAS LETRAS H  Ó V
   DEVUELVE 1 SI ES CORRECTO 
    0 SI ES INCORRECTO*/


if(orientacion=='h' || orientacion=='H')
{
return 1;
}

if(orientacion=='v' ||orientacion=='V')
{
return 1;
}

return 0;
}

int ValidarCoordenada(int x)
{
  printf(" xx:%d:\n",x );
  
  if(x<='9'){
    if(x>='0'){

      if(isdigit(x))
        printf("es un digito!!!" );
        return 1;
    }
  } 
    

return 0;
}





