// Recibe una cadena del Cliente y se la devuelve en mayusculas
#include "FuncionesServer.h"

int main(int argc, char *argv[])
{
	gtk_init (&argc,&argv);
//	gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("icon.png"));//coloca el icono del programa
//	gtk_signal_connect (GTK_OBJECT (window), "destroy",GTK_SIGNAL_FUNC (gtk_main_quit), "WM destroy");
	ConexionSer();
	//muestraPartida();
	gtk_widget_show (window);
	gtk_main ();	
	return 0;
}

void ConexionSer(){
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Loteria");
	gtk_widget_set_size_request(window,350,250);//tamaño de la ventana creada
	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);// esta linea deja estatica la ventana
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	cont=gtk_fixed_new();// creamos un contenedor
	fondo=gtk_image_new_from_file("Images/puerto.jpg");//se llama la imagen de fondo	
	puerto=gtk_entry_new();	
	inicio = gtk_button_new_with_label("Conectar");// creamos un boton llamado inicio.
	gtk_entry_set_text (GTK_ENTRY(puerto),"4444");
	
	gtk_widget_set_size_request(puerto, 120,30);
	gtk_widget_set_size_request(inicio,120,50);
	gtk_fixed_put (GTK_FIXED(cont),inicio,120,140);

	gtk_fixed_put(GTK_FIXED(cont),fondo,0,0);//se coloca un objeto en la ventana

	gtk_fixed_put (GTK_FIXED (cont),puerto,141,60);
	
	g_signal_connect_swapped (G_OBJECT (inicio), "clicked",G_CALLBACK (VistaSever),(gpointer) window);
	gtk_container_add (GTK_CONTAINER(window),cont);// cerramos el contenedor
	gtk_widget_show_all(window);// terminamo de usar la ventana		
}

void VistaSever(){
	const gchar *port;
	port = gtk_entry_get_text (GTK_ENTRY (puerto));
	if(abrirServidor(port) == 0){
		gtk_widget_destroy(window);
		muestraPartida();
	}else{
		  GtkWidget *dialog;
		  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_ERROR,
					GTK_BUTTONS_OK,
					"Error al abrir el servidor, intenta con otro número de puerto");
		  gtk_window_set_title(GTK_WINDOW(dialog), "Error");
		  gtk_dialog_run(GTK_DIALOG(dialog));
		  gtk_widget_destroy(dialog);
	}
	
}

void muestraPartida(){
	window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	numPartidas++;
	char tittle[50];
	sprintf(tittle,"Loteria - Partida No %d",numPartidas);
	gtk_window_set_title (GTK_WINDOW (window1), tittle);
	gtk_widget_set_size_request(window1,1037,730);//tamaño de la ventana creada
	gtk_window_set_resizable(GTK_WINDOW(window1),FALSE);// esta linea deja estatica la ventana
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
	cont1=gtk_fixed_new();// creamos un contenedor
	fondo=gtk_image_new_from_file("Images/fondo.jpg");//se llama la imagen de fondo	
	gtk_fixed_put(GTK_FIXED(cont1),fondo,0,0);//se coloca un objeto en la ventana
	
	/*fondo=gtk_image_new_from_file("Images/1.png");//se llama la imagen de fondo	
	gtk_fixed_put(GTK_FIXED(cont1),fondo,100,100);//se coloca un objeto en la ventana
	
	fondo=gtk_image_new_from_file("Images/1.png");//se llama la imagen de fondo	
	gtk_fixed_put(GTK_FIXED(cont1),fondo,380,100);//se coloca un objeto en la ventana
	
	fondo=gtk_image_new_from_file("Images/1.png");//se llama la imagen de fondo	
	gtk_fixed_put(GTK_FIXED(cont1),fondo,660,100);//se coloca un objeto en la ventana
	
	fondo=gtk_image_new_from_file("Images/1.png");//se llama la imagen de fondo	
	gtk_fixed_put(GTK_FIXED(cont1),fondo,230,430);//se coloca un objeto en la ventana
	
	fondo=gtk_image_new_from_file("Images/1.png");//se llama la imagen de fondo	
	gtk_fixed_put(GTK_FIXED(cont1),fondo,510,430);//se coloca un objeto en la ventana
	
	GtkWidget *label = gtk_label_new(NULL);
	//char nombre[255];
	//sprintf(nombre,"<b><span foreground=\"black\" size=\"xx-large\">%s</span></b>",cliente.nombreJugador);
	gtk_label_set_markup(GTK_LABEL(label),"<b><span foreground=\"black\" size=\"xx-large\">vicente</span></b>");
	gtk_fixed_put(GTK_FIXED(cont1),label,100,70);label = gtk_label_new(NULL);
	//char nombre[255];
	//sprintf(nombre,"<b><span foreground=\"black\" size=\"xx-large\">%s</span></b>",cliente.nombreJugador);
	gtk_label_set_markup(GTK_LABEL(label),"<b><span foreground=\"black\" size=\"xx-large\">vicente</span></b>");
	gtk_fixed_put(GTK_FIXED(cont1),label,380,70);label = gtk_label_new(NULL);
	//char nombre[255];
	//sprintf(nombre,"<b><span foreground=\"black\" size=\"xx-large\">%s</span></b>",cliente.nombreJugador);
	gtk_label_set_markup(GTK_LABEL(label),"<b><span foreground=\"black\" size=\"xx-large\">vicente</span></b>");
	gtk_fixed_put(GTK_FIXED(cont1),label,660,70);label = gtk_label_new(NULL);
	//char nombre[255];
	//sprintf(nombre,"<b><span foreground=\"black\" size=\"xx-large\">%s</span></b>",cliente.nombreJugador);
	gtk_label_set_markup(GTK_LABEL(label),"<b><span foreground=\"black\" size=\"xx-large\">vicente</span></b>");
	gtk_fixed_put(GTK_FIXED(cont1),label,230,400);label = gtk_label_new(NULL);
	//char nombre[255];
	//sprintf(nombre,"<b><span foreground=\"black\" size=\"xx-large\">%s</span></b>",cliente.nombreJugador);
	gtk_label_set_markup(GTK_LABEL(label),"<b><span foreground=\"black\" size=\"xx-large\">vicente</span></b>");
	gtk_fixed_put(GTK_FIXED(cont1),label,510,400);*/
	
	gtk_container_add (GTK_CONTAINER(window1),cont1);// cerramos el contenedor
	gtk_widget_show_all(window1);// terminamo de usar la ventana
	g_idle_add (esperarJugadores,NULL);
}

int abrirServidor(const gchar *port){
	int puerto = atoi(port);	
	//Creación de socket
	if((s=socket(AF_INET,/*SOCK_STREAM*/SOCK_STREAM | SOCK_NONBLOCK,0)) < 0) {
		perror("SOCKET: ");
		return 1;
	}
	lsock.sin_family = AF_INET;
	lsock.sin_port = htons(puerto); /* puerto para dar el servicio */
	lsock.sin_addr.s_addr =0; /* direccion IP de mi maquina servidora */
	//Asignación de dirección local 
	if(bind(s,(struct sockaddr *)&lsock, sizeof(struct sockaddr_in)) < 0 ){
		perror("BIND: ");
		return 1;
	}
	//La llamada al sistema listen()  
	if(listen(s,3)<0){
		perror("LISTEN: ");
		return 1;
	}
	return 0;
}


gboolean esperarJugadores(gpointer data){
	while(gtk_events_pending()) gtk_main_iteration();
	while(1) {//Bucle infinito del cliente que dura hasta que finalize la partida	
		len = sizeof(struct sockaddr_in); /* &len: entra y sale el tamano del socket esperado */
		//La llamada al sistema accept() 
		if((ss[numClientes]=accept(s,(struct sockaddr *)&fsock, &len)) < 0){
			while(gtk_events_pending()) gtk_main_iteration();
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
        //mostramos el nombre del jugador conectado en la interfaz de servidor
        char nombre[255];
		sprintf(nombre,"<b><span foreground=\"black\" size=\"xx-large\">%s</span></b>",jugadores[numClientes].nombreJugador);
		labelNombre = gtk_label_new(NULL);
		gtk_label_set_markup(GTK_LABEL(labelNombre),nombre);
		if(numClientes<4){
			gtk_fixed_put(GTK_FIXED(cont1),labelNombre,100+(numClientes*280),70);
		}else{
			gtk_fixed_put(GTK_FIXED(cont1),labelNombre,100+(numClientes*280),400);
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
		gtk_widget_show_all(window1);// terminamo de usar la ventana
	}
	return FALSE;
}

void esperaClientes(){
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


