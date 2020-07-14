/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Programa que tem como objetivo estudar a propagacao perculacao do
fogo em uma floresta, 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "stdio.h"
#include "math.h"

#define vazio_int 0
#define verde_int 1
#define cinzas_int 2
#define fogo_int 3

#define size_x_int 100
#define size_y_int 100

#define coeficiente_percucao_float 0.65
#define numero_simulacao_int 1

unsigned r_uint = 661105                                                       ;

float conti_random( )                                                          ;
void new_matrix( int rede_matrix[size_x_int][size_y_int] )                     ;
void print_matrix( int rede_matrix[size_x_int][size_y_int] )                   ;
void burn_nature( int rede_matrix[size_x_int][size_y_int] )                    ;
void stats(                               \
  int rede_matrix[size_x_int][size_y_int],\
  int stats_vector[fogo_int]              \
)                                                                              ;
void copy_matrix(                           \
  int real_matrix[size_x_int][size_y_int],  \
  int virtual_matrix[size_x_int][size_y_int]\
)                                                                              ;

FILE *output, *status                                                          ;

main()
{

  int i_int                                                                    ; 
  int forest_matrix[size_x_int][size_y_int]                                    ;
  int test_matrix[size_x_int][ size_y_int]                                     ;

  for(i_int=0; i_int < numero_simulacao_int; i_int++)
  {
    new_matrix( forest_matrix )                                                ;
    burn_nature( forest_matrix)                                                ;
  }

  fclose( output )                                                             ;
  printf("End of program!\n")                                                  ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~RAND()
float conti_random(  )
{
  unsigned seed_uint, max_uint                                                 ;
  
  max_uint  = pow(2,32)-1                                                      ;
  seed_uint = 16562261                                                         ;
  r_uint = r_uint * seed_uint                                                  ;

  return (float)(r_uint)/(float)max_uint                                       ; 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CRIACAO DA REDE

void new_matrix( int rede_matrix[size_x_int][size_y_int] )
{
  int i_int , j_int                                                            ;

  for(i_int=0 ; i_int < size_x_int ; i_int++)
  {
    for(j_int=0; j_int < size_y_int ; j_int++)
    {
      if( i_int == 0 || i_int == size_x_int-1 )
      {
        rede_matrix[i_int][j_int] = vazio_int                                  ;
      }
      else if( j_int == 0 || j_int == size_y_int-1 )
      {
        rede_matrix[i_int][j_int] = vazio_int                                  ; 
      }
      else if( conti_random() < coeficiente_percucao_float )
      {
        rede_matrix[i_int][j_int] = verde_int                                  ;
      }
      else
      {
        rede_matrix[i_int][j_int] = vazio_int                                  ;
      }
    }
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~STATS

void stats( int rede_matrix[size_x_int][size_y_int], int stats_vector[fogo_int])
{
  int i_int, j_int, k_int                                                      ;

  for(i_int=0; i_int<=fogo_int; i_int++)
  {
    stats_vector[i_int] = 0                                                    ;
  }

  for( i_int=0; i_int<size_x_int; i_int++ )
  {
    for( j_int=0; j_int<size_y_int; j_int++ )
    {
      for( k_int=0; k_int<=fogo_int; k_int++ )
      {
        if( rede_matrix[i_int][j_int] == k_int )
        {
           stats_vector[k_int] ++                                              ;
        }
      }
    }
  }
  for(i_int=0; i_int<=fogo_int; i_int++ )
  {
    fprintf(status, "%d\t\t  ", stats_vector[i_int] )                            ;
  }
  fprintf(status,"\n" )                                                        ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PRINT MATRIX

void print_matrix( int rede_matrix[size_x_int][size_y_int] )
{
  int i_int, j_int                                                             ;

  for( i_int=0 ; i_int < size_x_int ; i_int++ )
  {
    for( j_int=0; j_int < size_y_int ; j_int++ )
    {
      if(j_int == size_y_int-1 )
      {
        fprintf(output,"%d\n",rede_matrix[i_int][j_int])                       ;
      }
      else
      {
        fprintf(output,"%d  ",rede_matrix[i_int][j_int])                       ;
      }
    }
  }
  fprintf(output,"\n")                                                         ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~COPY MATRIX

void copy_matrix(                          \
  int real_matrix[size_x_int][size_y_int],  \
  int virtual_matrix[size_x_int][size_y_int]\
)
{
  int i_int, j_int                                                             ;
  for( i_int=0; i_int < size_x_int; i_int++ )
  {
    for( j_int=0; j_int < size_y_int; j_int++ )
    {
      real_matrix[i_int][j_int] = virtual_matrix[i_int][j_int]                 ;
    }
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BURN BABY BURN (DISCO INFERNO)

void burn_nature( int rede_matrix[size_x_int][size_y_int] )
{
  int i_int, j_int, time_int                                                   ;
  int rede_virtual_matrix[size_x_int][size_y_int]                              ;
  int stats_vector[fogo_int]                                                   ;

  status = fopen("status.txt", "w")                                            ;
  output = fopen("forest.txt", "w")                                            ;

  if ( status == NULL )
  {
    printf("Can't open output file status.txt !\n")                            ;
  }

  if (output == NULL )
  {
    printf("Can't open output file forest.txt !\n")                            ;
  }

  for( i_int=0; i_int<=fogo_int; i_int++ )
  {
    stats_vector[i_int] = 0                                                    ;
  }

  for( j_int=1; j_int < size_y_int-1; j_int++)
  {
    if( rede_matrix[1][j_int] == verde_int )
    {
      rede_matrix[1][j_int] = fogo_int                                         ;
    }
  }
  
  stats( rede_matrix, stats_vector )                                           ;
  copy_matrix(rede_virtual_matrix,rede_matrix)                                 ;
  print_matrix( rede_matrix )                                                  ;
  
  while( stats_vector[fogo_int] > 0 )
  {
    for( i_int=1 ; i_int < size_x_int-1 ; i_int++ )
    {
      for( j_int=1; j_int < size_y_int-1 ; j_int++ )
      {
        if( rede_matrix[i_int][j_int] == verde_int )
        {
          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Von Newman neighborhood
          if( rede_matrix[ i_int - 1 ][ j_int ] == fogo_int )
          {
            rede_virtual_matrix[ i_int ][ j_int ] = fogo_int                   ;
          }
          else if( rede_matrix[ i_int ][ j_int - 1] == fogo_int )
          {
            rede_virtual_matrix[ i_int ][ j_int ] = fogo_int                   ;
          }
          else if( rede_matrix[ i_int ][ j_int + 1 ] == fogo_int )
          {
            rede_virtual_matrix[ i_int ][ j_int ] = fogo_int                   ;
          }
          else if( rede_matrix[ i_int + 1 ][ j_int ] == fogo_int )
          {
            rede_virtual_matrix[ i_int ][ j_int ] = fogo_int                   ;
          }
          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Morre neighborhood
          // if( rede_matrix[ i_int-1 ][ j_int-1 ] == fogo_int )
          // {
          //   rede_matrix[ i_int ][ j_int ] = faisca_int ;
          // }
          // else if( rede_matrix[ i_int-1 ][ j_int+1 ] == fogo_int )
          // {
          //   rede_matrix[ i_int ][ j_int ] = faisca_int ;
          // }
          // else if( rede_matrix[ i_int+1 ][ j_int-1 ] == fogo_int )
          // {
          //   rede_matrix[ i_int ][ j_int ] = faisca_int;
          // }
          // else if( rede_matrix[ i_int+1 ][ j_int+1 ] == fogo_int )
          // {
          //   rede_matrix[ i_int ][ j_int ] = faisca_int;
          // }       
        }
        else if( rede_matrix[i_int][j_int] == fogo_int )
        {
          rede_virtual_matrix[i_int][j_int] = cinzas_int                       ;
        }
      }
    }
    copy_matrix( rede_matrix, rede_virtual_matrix )                            ;    
    print_matrix( rede_matrix )                                                ;
    stats( rede_matrix, stats_vector )                                         ;
  }
}
