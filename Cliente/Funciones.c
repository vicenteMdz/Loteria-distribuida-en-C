#include "Funciones.h"

void printInfoPlayer(jugador j){
	printf("\n****** INFO PLAYER *********\nID Jugador --> %d\n",j.id_Jugador);
	printf("Nombre Jugador --> %s\n",j.nombreJugador);
	printf("No de Planilla --> %d\n",j.id_tablero);
	printf("Planilla de jugador\n");
	imprimirPlanilla(j.tablero);
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

int connectToServer(const gchar *host, const gchar *port){
	if(!(hent = gethostbyname(host)) ){
		perror("GETHOSTBYNAME: ");
		return 1;
	}
	//Creación de socket 
	if((s=socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("SOCKET: ");
		return 1;
	}
	int puerto = atoi(port);
	fprintf(stderr,"host : %s   ---    puerto: %s\n",host,port);
	fsock.sin_family = AF_INET;
	fsock.sin_addr.s_addr = *(long *) hent->h_addr; /* direccion IP de Maq. Remota */
	fsock.sin_port = htons(puerto); /* puerto de la maq. remota */
	//Estableciendo conexión 
	if(connect(s,(struct sockaddr *)&fsock, sizeof(struct sockaddr_in)) == -1){
		perror("CONNECT: ");
		close(s);
		return 1;
	}   
	 //el jugador recibe su identificador por parte del servidor
	if( (len=recv(s,&cliente.id_Jugador,sizeof(cliente.id_Jugador),0))<= 0 ){
		perror("RECV: ");
		close(s);
		exit(0);
	}
	//printInfoPlayer(cliente);
	//El cliente envía los datos del jugador
	if( send(s,&cliente,sizeof(cliente),0) < sizeof(cliente) ){
		perror("SEND: ");
	}
	return 0;
}


gboolean esperarJuego(gpointer data){
	while(gtk_events_pending()) gtk_main_iteration();
	while(1) {//Bucle infinito del cliente que dura hasta que finalize la partida
		//printf("%s",msj);
		//while(gtk_events_pending()) gtk_main_iteration();
		len=recv(s,msj,4,MSG_DONTWAIT);
		
		if( len<= 0 ){
			// update GUI and treat events from it:
			while(gtk_events_pending()) gtk_main_iteration();
			//continue;
		}else{
			fprintf(stderr,"%d", len);
			msj[len] = '\0';
			printf("%s",msj);
			if(strcmp(msj,"init")==0){//se inicia la partida
				
				//while(1){
					//el cliente recibe toda la estructura de jugador, con la planilla asignada
					if( (len=recv(s,&cliente,sizeof(cliente),0))<= 0 ){
						perror("RECV: ");
						close(s);
						exit(0);
						/*while(gtk_events_pending()) gtk_main_iteration();
						continue;*/
					}
					
					gtk_widget_destroy(loading);
					gtk_widget_destroy(fondo1);
					fondo1=gtk_image_new_from_file("images/fondo3.jpg");//se llama la imagen de fondo
					gtk_fixed_put(GTK_FIXED(cont2),fondo1,0,0);//se coloca un objeto en la ventana
					GtkWidget *label = gtk_label_new(NULL);
					char nombre[255];
					sprintf(nombre,"<b><span foreground=\"black\" size=\"xx-large\">%s</span></b>",cliente.nombreJugador);
					gtk_label_set_markup(GTK_LABEL(label),nombre);
					gtk_fixed_put(GTK_FIXED(cont2),label,915,100);
					
					int i, y = 30;
					for(i=0;i<4;i++){
						planilla[i][0] = gtk_button_new();
						planilla[i][1] = gtk_button_new();	
						planilla[i][2] = gtk_button_new();	
						planilla[i][3] = gtk_button_new();
						gtk_widget_set_size_request(planilla[i][0],120,150);
						gtk_widget_set_size_request(planilla[i][1],120,150);
						gtk_widget_set_size_request(planilla[i][2],120,150);
						gtk_widget_set_size_request(planilla[i][3],120,150);
						gtk_fixed_put (GTK_FIXED(cont2),planilla[i][0],43,y);
						gtk_fixed_put (GTK_FIXED(cont2),planilla[i][1],183,y);
						gtk_fixed_put (GTK_FIXED(cont2),planilla[i][2],323,y);
						gtk_fixed_put (GTK_FIXED(cont2),planilla[i][3],463,y);
						y += 160;
					}
					g_signal_connect_swapped (G_OBJECT (planilla[0][0]), "clicked",G_CALLBACK (fila1),(gpointer) 0);
					g_signal_connect_swapped (G_OBJECT (planilla[0][1]), "clicked",G_CALLBACK (fila1),(gpointer) 1);
					g_signal_connect_swapped (G_OBJECT (planilla[0][2]), "clicked",G_CALLBACK (fila1),(gpointer) 2);
					g_signal_connect_swapped (G_OBJECT (planilla[0][3]), "clicked",G_CALLBACK (fila1),(gpointer) 3);
					g_signal_connect_swapped (G_OBJECT (planilla[1][0]), "clicked",G_CALLBACK (fila2),(gpointer) 0);
					g_signal_connect_swapped (G_OBJECT (planilla[1][1]), "clicked",G_CALLBACK (fila2),(gpointer) 1);
					g_signal_connect_swapped (G_OBJECT (planilla[1][2]), "clicked",G_CALLBACK (fila2),(gpointer) 2);
					g_signal_connect_swapped (G_OBJECT (planilla[1][3]), "clicked",G_CALLBACK (fila2),(gpointer) 3);
					g_signal_connect_swapped (G_OBJECT (planilla[2][0]), "clicked",G_CALLBACK (fila3),(gpointer) 0);
					g_signal_connect_swapped (G_OBJECT (planilla[2][1]), "clicked",G_CALLBACK (fila3),(gpointer) 1);
					g_signal_connect_swapped (G_OBJECT (planilla[2][2]), "clicked",G_CALLBACK (fila3),(gpointer) 2);
					g_signal_connect_swapped (G_OBJECT (planilla[2][3]), "clicked",G_CALLBACK (fila3),(gpointer) 3);
					g_signal_connect_swapped (G_OBJECT (planilla[3][0]), "clicked",G_CALLBACK (fila4),(gpointer) 0);
					g_signal_connect_swapped (G_OBJECT (planilla[3][1]), "clicked",G_CALLBACK (fila4),(gpointer) 1);
					g_signal_connect_swapped (G_OBJECT (planilla[3][2]), "clicked",G_CALLBACK (fila4),(gpointer) 2);
					g_signal_connect_swapped (G_OBJECT (planilla[3][3]), "clicked",G_CALLBACK (fila4),(gpointer) 3);
					Loteria = gtk_button_new_with_label("Loteria");							
					gtk_widget_set_size_request(Loteria,180,77);
					gtk_fixed_put (GTK_FIXED(cont2),Loteria,870,575);
					//Inicia = gtk_button_new_with_label("Iniciar partida");	
					//gtk_widget_set_size_request(Inicia,120,70);
					//gtk_fixed_put (GTK_FIXED(cont2),Inicia,750,510);
					
					char img[50];
					sprintf(img,"images/%d.jpg",cliente.id_tablero+1);
					fondo=gtk_image_new_from_file(img);//se llama la imagen de fondo
					gtk_fixed_put(GTK_FIXED(cont2),fondo,38,23);//se coloca un objeto en la ventana
					imgLoteriaButton = gtk_image_new_from_file("images/loteria.png");//se llama la imagen de fondo
					gtk_fixed_put(GTK_FIXED(cont2),imgLoteriaButton,865,570);//se coloca un objeto en la ventana
										
					waiting=gtk_image_new_from_file("images/54321.gif");//se llama la imagen de fondo
					gtk_fixed_put(GTK_FIXED(cont2),waiting,500,250);//se coloca un objeto en la ventana
					mensaje_espera=gtk_image_new_from_file("images/letras.png");//se llama la imagen de fondo
					gtk_fixed_put(GTK_FIXED(cont2),mensaje_espera,330,150);//se coloca un objeto en la ventana
					
					g_signal_connect_swapped (G_OBJECT (Loteria), "clicked",G_CALLBACK (ganador),(gpointer) Loteria);
					gtk_widget_show_all(window1);// terminamo de usar la ventana
					g_idle_add (loteria,NULL);
					break;
				//}
				
			} else if (strcmp(msj,"finish")==0){//El juego ah terminado
				
			}
		}		
	}
	return FALSE;
}

void ganador(){
	if(fin_juego == 0){
		if(verificaJuego() == 0 ){//El jugador ah ganado, y se emite el aviso al servidor
			int r[2];
			r[0] = -1;
			r[1] = cliente.id_Jugador;
			if(send(s,&r,sizeof(r),0) < sizeof(r)){
				perror("SEND: ");
			}
			printf("Se avisó exitosamente que el juego a terminado %d\n", r[0]);
		}else{//el jugador aún no ah ganado, se emite un msj de error
			sprintf(imagen_error,"images/msj/error_finalizar.jpg");
			Error(imagen_error);
		}
	}
}

void nuevaPartida(GtkWidget *widget, gpointer windowParent) {
    
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(windowParent),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			"¿Quieres realizar una nueva partida?");
	gtk_window_set_title(GTK_WINDOW(dialog), "Pregunta");
	gint result=gtk_dialog_run(GTK_DIALOG(dialog));
	if(result == -8){//Si el usuario aceptó el mensaje. Se inicia una nueva partida
		gtk_widget_destroy(window1);
		Conexion();
		//gtk_widget_destroy(window4);
	}else{//cerramos toda la aplicación
		exit(1);
	}
	gtk_widget_destroy(dialog);
}

gboolean loteria(gpointer data){
	while(gtk_events_pending()) gtk_main_iteration();
	carta=gtk_image_new_from_file("images/fichas/1.png");//se llama la imagen de fondo
	char cartaImg[50];
	cartaActual = -1;	
	int aux = 1;				
	while(1){
		//El cliente recibe la carta que se está jugando en el momento
		if( (len=recv(s,&cartaActual,sizeof(cartaActual),MSG_DONTWAIT))<= 0 ){
			while(gtk_events_pending()) gtk_main_iteration();
			continue;
		}else{
			//printf("Carta Actual %d\n  " ,cartaActual);
			if(aux == 1 ){
				aux = 2;
				gtk_widget_destroy(waiting);
				gtk_widget_destroy(mensaje_espera);
			}
			if(cartaActual>54){//el juego ah terminado y nadie ah ganado
				sprintf(imagen_error,"images/msj/sin_ganador.jpg");
				FinJuego(imagen_error);
				break;
			}else if(cartaActual<0){//el juego termino, hay un ganador
					fin_juego = 1;
					fprintf(stderr,"La Partida a finalizado, hay un ganador");
					sprintf(imagen_error,"images/msj/gano.jpg");
					FinJuego(imagen_error);
					break;		
				}else{				
					gtk_widget_destroy(carta);
					sprintf(cartaImg,"images/fichas/%d.png",cartaActual);
					carta=gtk_image_new_from_file(cartaImg);//se llama la imagen de fondo
					gtk_fixed_put(GTK_FIXED(cont2),carta,850,180);//se coloca un objeto en la ventana
					gtk_widget_show_all(window1);// terminamo de usar la ventana
				}
			//aquí enviar el estado del cliente
			/*if( send(s,&cliente,sizeof(cliente),0) < sizeof(cliente) ){
				perror("SEND: ");
			}*/
		}
	}
	return FALSE;
}

void fila1(int col){
	if(cartaActual == cliente.tablero[0][col]){
		GtkWidget *m=gtk_image_new_from_file("images/maiz.r.png");
		gtk_fixed_put (GTK_FIXED(cont2),m,63+(col*140),50);		
		cliente.tablero_jugado[0][col] = 1;
		if(verificaJuego() == 0 ){
			GtkWidget *gif_avisa=gtk_image_new_from_file("images/clic.gif");//se llama la imagen de fondo
			gtk_fixed_put (GTK_FIXED(cont2),gif_avisa,1050,440);
		}
		gtk_widget_show_all(window1);// terminamo de usar la ventana
	}else{
		sprintf(imagen_error,"images/msj/error_ficha.jpg");
		Error(imagen_error);
	}
}
void fila2(int col){
	if(cartaActual == cliente.tablero[1][col]){
		GtkWidget *m=gtk_image_new_from_file("images/maiz.r.png");
		gtk_fixed_put (GTK_FIXED(cont2),m,63+(col*140),210);
		cliente.tablero_jugado[1][col] = 1;
		if(verificaJuego() == 0 ){
			GtkWidget *gif_avisa=gtk_image_new_from_file("images/clic.gif");//se llama la imagen de fondo
			gtk_fixed_put (GTK_FIXED(cont2),gif_avisa,1050,440);
		}
		gtk_widget_show_all(window1);// terminamo de usar la ventana
	}else{
		sprintf(imagen_error,"images/msj/error_ficha.jpg");
		Error(imagen_error);
	}
}
void fila3(int col){
	if(cartaActual == cliente.tablero[2][col]){
		GtkWidget *m=gtk_image_new_from_file("images/maiz.r.png");
		gtk_fixed_put (GTK_FIXED(cont2),m,63+(col*140),370);
		cliente.tablero_jugado[2][col] = 1;
		if(verificaJuego() == 0 ){
			GtkWidget *gif_avisa=gtk_image_new_from_file("images/clic.gif");//se llama la imagen de fondo
			gtk_fixed_put (GTK_FIXED(cont2),gif_avisa,1050,440);
		}
		gtk_widget_show_all(window1);// terminamo de usar la ventana
	}else{
		sprintf(imagen_error,"images/msj/error_ficha.jpg");
		Error(imagen_error);
	}
}
void fila4(int col){
	if(cartaActual == cliente.tablero[3][col]){
		GtkWidget *m=gtk_image_new_from_file("images/maiz.r.png");
		gtk_fixed_put (GTK_FIXED(cont2),m,63+(col*140),530);
		cliente.tablero_jugado[3][col] = 1;
		if(verificaJuego() == 0 ){
			GtkWidget *gif_avisa=gtk_image_new_from_file("images/clic.gif");//se llama la imagen de fondo
			gtk_fixed_put (GTK_FIXED(cont2),gif_avisa,1050,440);
		}
		gtk_widget_show_all(window1);// terminamo de usar la ventana
	}else{
		sprintf(imagen_error,"images/msj/error_ficha.jpg");
		Error(imagen_error);
	}
}

int verificaJuego(){
	int i,j,sum=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(cliente.tablero_jugado[i][j]==1){
				sum++;
			}
		}
	}
	if(sum == 16)
		return 0;
	else
		return 1;
}

