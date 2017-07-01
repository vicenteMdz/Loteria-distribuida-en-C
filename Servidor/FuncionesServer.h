#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define MAX_LINE 120
#define NUMPLAYERS 2
#define _GNU_SOURCE  

typedef struct
{
	int id_cliente;
	int tablero[4][4];
} mensaje1;

typedef struct
{
	int id_Jugador;
	char nombreJugador[50];
	int tablero[4][4];
	int id_tablero;
} jugador;

extern int errno;
int cartas[54];
int cartasDesordenadas[54];
int aux[54];//se usa como auxiliar al desordenar las cartar
//se declaran las 10 planillas ya definidas
int planilla1[4][4] = {{1,2,3,4},{10,11,12,13},{19,20,21,22},{28,29,30,31}};
int planilla2[4][4] = {{6,7,8,9},{15,16,17,18},{24,25,26,27},{33,34,35,36}};
int planilla3[4][4] = {{2,3,4,5},{7,8,9,10},{12,13,14,15},{17,18,19,20}};
int planilla4[4][4] = {{43,44,45,21},{52,53,54,26},{7,8,9,31},{16,17,18,36}};
int planilla5[4][4] = {{22,23,24,25},{27,28,29,30},{32,33,34,35},{37,38,39,40}};
int planilla6[4][4] = {{21,22,23,24},{30,31,32,33},{39,40,41,42},{48,49,50,51}};
int planilla7[4][4] = {{25,26,27,41},{34,35,36,46},{43,44,45,51},{52,53,54,32}};
int planilla8[4][4] = {{42,43,44,45},{47,48,49,50},{52,53,54,1},{40,10,19,20}};
int planilla9[4][4] = {{41,42,37,38},{50,51,46,47},{5,6,1,2},{14,15,10,11}};
int planilla10[4][4] = {{39,40,19,20},{48,49,28,29},{3,4,37,38},{12,13,46,47}};
int planillas[10];
int aux2[10] = {1,1,1,1,1,1,1,1,1,1};//se usa para verificar que planillas ya fueron asignadas
int numClientes = 0;
int numPartidas = 0;
int i,j,k;
int cartaActual;
struct sockaddr_in lsock,fsock;
int s, ss[NUMPLAYERS];
int len;
jugador jugadores[NUMPLAYERS];	
char msj[30];

///********************** Interfaz del servidor
GtkWidget *window, *cont, *fondo, *puerto, *inicio, *labelNombre;
GtkWidget *window1, *cont1, *fondo1, *puerto1, *inicio1;

void ConexionSer();
void VistaSever();
gboolean esperarJugadores(gpointer data);
void muestraPartida();

void llenarCartas();
void imprimirCartas(int array[]);
void barajearCartas();
void imprimirPlanilla(int array[4][4]);
void obtenerPlanilla(int array[][4], int *id);
void copiarMatriz(int mat1[4][4],int mat2[4][4]);
void printInfoPlayer(jugador j);
int abrirServidor(const gchar *port);
void esperaClientes();
