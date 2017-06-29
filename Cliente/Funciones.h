#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
//#include <netinet/in.h>
//#include <sys/errno.h>
#include <netdb.h>
#include <unistd.h>
//#include <crypt.h>
#include <pthread.h>
#include <time.h>

#define MAX_LINE 120
//#define PUERTO 4400
extern int errno;

//se definen las estructuras a usar
typedef struct
{
	int id_cliente;
	int tablero[4][4];
} mensaje1;

typedef struct//guarda la información del jugador
{
	int id_Jugador;
	char nombreJugador[50];
	int tablero[4][4];
	int id_tablero;
} jugador;

typedef struct {
    //Or whatever information that you need
    GtkWidget *window1;
    GtkWidget *cont2;
} vent_principal;



GtkWidget *window, *window1, *window2, *window3, *window4, *window5;
GtkWidget *fondo, *fondo1;
GtkWidget *carta, *label_espera;
GtkWidget *cont1, *cont2, *cont3, *cont4, *cont5, *cont6;
GtkWidget *Dir, *Puerto, *Nombre;
GtkWidget *loading,*waiting, *mensaje_espera ;
GtkWidget *Inicio, *Jugar, *AcercaD, *Manual, *Salir, *Regresar, *Aceptar;
GtkWidget *F1, *F2, *F3, *F4, *F5, *F6, *F7, *F8, *F9, *F10, *F11, *F12, *F13, *F14, *F15, *F16, *Loteria, *Inicia;
GtkWidget *planilla[4][4];

GdkRGBA color;
PangoFontDescription *fuente;

struct sockaddr_in fsock;
jugador cliente;
struct hostent *hent; /* estructura que guarda el llamado a gethostbyname */
int s, len;
char msj[30];
int cartaActual;
int fin_juego;
int tablero_jugado[4][4];
char imagen_error[100];





void Conexion();
void principal();
void Menu();
void AcercaDe();
void ManualU ();
void Error(char const *imagen);

void imprimirPlanilla(int array[4][4]);
void printInfoPlayer(jugador j);
int connectToServer(const gchar *host, const gchar *port);
gboolean esperarJuego(gpointer data);
gboolean loteria(gpointer data);
void fila1(int col);
void fila2(int col);
void fila3(int col);
void fila4(int col);
int verificaJuego();
void ganador();


