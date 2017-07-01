// Recibe una cadena del Cliente y se la devuelve en mayusculas
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define PUERTO 4444
#define MAX_LINE 120
#define NUMPLAYERS 2

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
int i,j,k;
int cartaActual;

void llenarCartas();
void imprimirCartas(int array[]);
void barajearCartas();
void imprimirPlanilla(int array[4][4]);
void obtenerPlanilla(int array[][4], int *id);
void copiarMatriz(int mat1[4][4],int mat2[4][4]);
void printInfoPlayer(jugador j);

int main()
{
	struct sockaddr_in lsock,fsock;
	int s, ss[NUMPLAYERS];
	int len;
	jugador jugadores[NUMPLAYERS];	
	char msj[30];
	//Creación de socket
	if((s=socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("SOCKET: ");
		exit(0);
	}
	lsock.sin_family = AF_INET;
	lsock.sin_port = htons(PUERTO); /* puerto para dar el servicio */
	lsock.sin_addr.s_addr =0; /* direccion IP de mi maquina servidora */
	//Asignación de dirección local 
	if(bind(s,(struct sockaddr *)&lsock, sizeof(struct sockaddr_in)) < 0 ){
		perror("BIND: ");
		exit(1);
	}
	//La llamada al sistema listen()  
	if(listen(s,3)<0){
		perror("LISTEN: ");
		exit(1);
	}
	
	while(1){ 
		len = sizeof(struct sockaddr_in); /* &len: entra y sale el tamano del socket esperado */
		//La llamada al sistema accept() 
		if((ss[numClientes]=accept(s,(struct sockaddr *)&fsock, &len)) < 0){
			perror("ACCEPT: ");
			continue;
		}
		printf("Un cliente conectado\n");
		if(send(ss[numClientes],&numClientes,sizeof(numClientes),0) < len) /* responde al cliente */
               perror("SEND: ");
               
        //el servidor recibe los datos del jugador recien conectado
        if((len=recv(ss[numClientes],&jugadores[numClientes],sizeof(jugadores[numClientes]),0))<=0){
               perror("RECV: "); /* Si len==0 entonces el cliente cerro la conexion */
               exit(1);
        }
		//Hasta este punto ya se tiene guardado los datos de cada jugador que se conectó		
		numClientes++;
		printf("No Clientes : %d\n",numClientes);
		if(numClientes == NUMPLAYERS){/********* Aqui Iniciar la Partida ***********/
			strcpy(msj,"init");	
			printf("%s",msj);
			for(i=0;i<NUMPLAYERS;i++)
			{
				if(send(ss[i],msj,strlen(msj),0) < len) /* responde al cliente */
					perror("SEND: ");
			}	
			numClientes = 0;//se reinicia el contador para una nueva partida
			if (fork() == 0) {
				/* Aqui se ejecuta el proceso hijo */
				llenarCartas();
				imprimirCartas(cartas);
				//barajearCartas();
				//imprimirCartas(cartasDesordenadas);
				//Recorrer el arreglo de sokets clientes y mandarle la 
				//planilla que le asignó el servidor				
				for(j = 0; j < NUMPLAYERS;j++){
					obtenerPlanilla(jugadores[j].tablero, &jugadores[j].id_tablero);
					//printInfoPlayer(jugadores[j]);
					if(send(ss[jugadores[j].id_Jugador],&jugadores[j],sizeof(jugadores[j]),0) < len) /* responde al cliente */
						perror("SEND: ");
				}
				int r[2];
				int band = 0;
				sleep(6);
				//aquí recorrer el areglo de cartas desordenadas y mandarselas a los jugadores
				for(j=0;j < 54 && band == 0;j++){
					cartaActual = cartasDesordenadas[j];
					//se le envía a todos los clientes la carta que se está jugando en este momento
					for(k=0;k<NUMPLAYERS && band == 0;k++){
						if(send(ss[jugadores[k].id_Jugador],&cartaActual,sizeof(cartaActual),0) < len){ // responde al cliente 
							perror("SEND: ");
						}
						if( (len=recv(ss[jugadores[k].id_Jugador],&r,sizeof(r),MSG_DONTWAIT))<= 0 ){
							//printf("Aún no hay ganador\n");
							continue;
						}else{
							//printf("Ya hay un ganador");
							if(r[0]<0){//ya hay un ganador, avisar a los demas
								printf("Ya hay un ganador %d \n",r[0]);
								band = 1;
							}
						}
					}
					//printf("Enviado Carta No: %d\n",cartaActual);
					sleep(2);
				}
				printf("Valor de la bandera --> %d\n",band);
				if(band == 0){//se recorrió todas las fichas y no hay ganador, se avisa a todos los clientes
					printf("fin del juego, no hay ganador\n");
					cartaActual=55;
					for(k=0;k<NUMPLAYERS;k++){
						if(send(ss[jugadores[k].id_Jugador],&cartaActual,sizeof(cartaActual),0) < len) // responde al cliente 
							perror("SEND: ");
					}
				}else{
					cartaActual = r[0];
					printf("Mensaje el juego a terminado %d\n", cartaActual);
					for(k=0;k<NUMPLAYERS;k++){
						if(send(ss[jugadores[k].id_Jugador],&cartaActual,sizeof(cartaActual),0) < len) // responde al cliente 
							perror("SEND: ");
					}					
				}
				
			} /* if fork */
			else /* Aqui continua el proceso vigia para aceptar otra conexion */
			{
				numClientes = 0;//se reinicia el contador para una nueva partida
				for(int k=0;k<NUMPLAYERS;k++)
					close(ss[k]); /* el padre cierra el socket completo que dejo al hijo */
			}	
		}
	} /*while*/
	
	return 0;
}

void llenarCartas(){
	for(int i = 0; i<54 ; i++){
		cartas[i] = i+1;
		cartasDesordenadas[i] = i+1;
		aux[i] = 1;
	}
}

void imprimirCartas(int array[]){
	int i;
	for(i = 0; i<54 ; i++){
		printf("%d  ",array[i]);
	}
	printf("\n\n");
}

void imprimirPlanilla(int array[4][4]){
	int i, j;
	for(i = 0; i<4 ; i++){
		for(j = 0; j<4 ; j++){
			printf("%d   ",array[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void barajearCartas(){
	int index=0;	
	srand(time(NULL)); 
	for (int i=0; i < 54; i++){
		do{
			index = (rand() % 54);
		}
		while (aux[index] == 0);
		cartasDesordenadas[i] = cartas[index];
		aux[index]=0;
	}
}

void obtenerPlanilla(int array[][4], int * id){
	int index=0;
	srand(time(NULL));
	for (int i=0; i < 2; i++){
		do{
			index = (rand() % 2);
		}
		while (aux2[index] == 0);
		aux2[index]=0;
		*id = index;
		switch(index){
			case 0:
				copiarMatriz(array,planilla1);
				break;
			case 1:
				copiarMatriz(array,planilla2);
				break;
			case 2:
				copiarMatriz(array,planilla3);
				break;
			case 3:
				copiarMatriz(array,planilla4);
				break;
			case 4:
				copiarMatriz(array,planilla5);
				break;
			case 5:
				copiarMatriz(array,planilla6);
				break;
			case 6:
				copiarMatriz(array,planilla7);
				break;
			case 7:
				copiarMatriz(array,planilla8);
				break;
			case 8:
				copiarMatriz(array,planilla9);
				break;
			case 9:
				copiarMatriz(array,planilla10);
				break;
		}		
		return;
	}
}

void copiarMatriz(int mat1[4][4],int mat2[4][4]){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			mat1[i][j] = mat2[i][j];
		}
	}
}

void printInfoPlayer(jugador j){
	printf("\n****** INFO PLAYER *********\nID Jugador --> %d\n",j.id_Jugador);
	printf("Nombre Jugador --> %s\n",j.nombreJugador);
	printf("No de Planilla --> %d\n",j.id_tablero);
	printf("Planilla de jugador\n");
	imprimirPlanilla(j.tablero);
}

