#include "Funciones.h"

int main (int argc, char *argv[]){
	gtk_init (&argc,&argv);

//	gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("icon.png"));//coloca el icono del programa
	//gtk_signal_connect (GTK_OBJECT (window), "destroy",GTK_SIGNAL_FUNC (gtk_main_quit), "WM destroy");
	Menu();
	//gtk_widget_show (window);
	gtk_main ();
	return 0;
}

void Menu ()
{	
	window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window2), "Menú Principal");
	gtk_widget_set_size_request(window2,400,531);//tamaño de la ventana creada
	gtk_window_set_resizable(GTK_WINDOW(window2),FALSE);// esta linea deja estatica la ventana
	gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER);

	cont3 = gtk_fixed_new();// creamos un contenedor
	fondo=gtk_image_new_from_file("images/principal.jpg");//se llama la imagen de fondo

	Jugar = gtk_button_new_with_label("Jugar");
	AcercaD = gtk_button_new_with_label("Acerca de");	
	Manual = gtk_button_new_with_label("Manual");	
	Salir = gtk_button_new_with_label("Salir");
	
	gtk_widget_set_size_request(Jugar,120,67);
	gtk_widget_set_size_request(AcercaD,118,46);
	gtk_widget_set_size_request(Manual,115,70);
	gtk_widget_set_size_request(Salir,117,47);
	
	gtk_fixed_put (GTK_FIXED(cont3),Jugar,141,89);
	gtk_fixed_put (GTK_FIXED(cont3),AcercaD,144,197);
	gtk_fixed_put (GTK_FIXED(cont3),Manual,145,277);
	gtk_fixed_put (GTK_FIXED(cont3),Salir,143,382);

	gtk_fixed_put(GTK_FIXED(cont3),fondo,0,0);//se coloca un objeto en la ventana
	
	g_signal_connect_swapped (G_OBJECT (Jugar), "clicked",G_CALLBACK (Conexion),(gpointer) window2);
	g_signal_connect_swapped (G_OBJECT (Jugar), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window2);

	g_signal_connect_swapped (G_OBJECT (AcercaD), "clicked",G_CALLBACK (AcercaDe),(gpointer) window2);
	g_signal_connect_swapped (G_OBJECT (AcercaD), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window2);

	g_signal_connect_swapped (G_OBJECT (Manual), "clicked",G_CALLBACK (ManualU),(gpointer) window2);
	g_signal_connect_swapped (G_OBJECT (Manual), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window2);
	
	g_signal_connect_swapped (G_OBJECT (Salir), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window2);
	gtk_container_add (GTK_CONTAINER(window2),cont3);// cerramos el contenedor
	gtk_widget_show_all(window2);// terminamo de usar la ventana		
}

void Conexion(){
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Loteria");
	gtk_widget_set_size_request(window,800,531);//tamaño de la ventana creada
	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);// esta linea deja estatica la ventana
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	cont1=gtk_fixed_new();// creamos un contenedor
	fondo=gtk_image_new_from_file("images/conexion.jpg");//se llama la imagen de fondo
	Dir=gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(Dir),"132.18.52.1");	
	Puerto=gtk_entry_new();	
	gtk_entry_set_text(GTK_ENTRY(Puerto),"4444");	
	Nombre=gtk_entry_new();	
	Inicio = gtk_button_new_with_label("Conectar");// creamos un boton llamado inicio.
	Regresar = gtk_button_new_with_label("Regresar");// creamos un boton llamado inicio.
	
	gtk_widget_set_size_request(Dir, 240,30);
	gtk_widget_set_size_request(Puerto, 150,30);
	gtk_widget_set_size_request(Nombre, 360,30);
	gtk_widget_set_size_request(Inicio,148,45);
	gtk_widget_set_size_request(Regresar,148,45);	
	
	gtk_fixed_put (GTK_FIXED(cont1),Inicio,203,390);
	gtk_fixed_put (GTK_FIXED(cont1),Regresar,455,390);
	gtk_fixed_put(GTK_FIXED(cont1),fondo,0,0);//se coloca un objeto en la ventana

	gtk_fixed_put (GTK_FIXED (cont1),Dir,280,130);
	gtk_fixed_put (GTK_FIXED (cont1),Puerto,618,130);
	gtk_fixed_put (GTK_FIXED (cont1),Nombre,360,223);
	
	g_signal_connect_swapped (G_OBJECT (Inicio), "clicked",G_CALLBACK (principal),(gpointer) window);
	//g_signal_connect_swapped (G_OBJECT (Inicio), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window);

	g_signal_connect_swapped (G_OBJECT (Regresar), "clicked",G_CALLBACK (Menu),(gpointer) window);
	g_signal_connect_swapped (G_OBJECT (Regresar), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window);
	gtk_container_add (GTK_CONTAINER(window),cont1);// cerramos el contenedor
	gtk_widget_show_all(window);// terminamo de usar la ventana	
}

void principal ()
{	
	const gchar *host;
	host = gtk_entry_get_text (GTK_ENTRY (Dir));
	const gchar *port;
	port = gtk_entry_get_text (GTK_ENTRY (Puerto));
	sprintf(cliente.nombreJugador,"%s", gtk_entry_get_text(GTK_ENTRY (Nombre)));
	if(connectToServer(host,port) == 0){
		fin_juego = 0;
		gtk_widget_destroy(window);
		g_idle_add (esperarJuego,NULL);
		window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (window1), "Partida");
		gtk_widget_set_size_request(window1,1300,680);//tamaño de la ventana creada
		gtk_window_set_resizable(GTK_WINDOW(window1),FALSE);// esta linea deja estatica la ventana
		gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

		cont2 = gtk_fixed_new();// creamos un contenedor
		
		fondo1=gtk_image_new_from_file("images/fondoespera.jpg");//se llama la imagen de fondo
		loading = gtk_image_new_from_file("images/loading.gif");
		gtk_fixed_put(GTK_FIXED(cont2),fondo1,0,0);//se coloca un objeto en la ventana
		gtk_fixed_put(GTK_FIXED(cont2),loading,550,270);//se coloca un objeto en la ventana		
		
		//gtk_fixed_put(GTK_FIXED(cont2),loading,200,200);//se coloca un objeto en la ventana
		gtk_container_add (GTK_CONTAINER(window1),cont2);// cerramos el contenedor
		gtk_widget_show_all(window1);// terminamo de usar la ventana
			
	}else{
		sprintf(imagen_error,"images/msj/error_conexion.jpg");
		Error(imagen_error);
	}
}

void AcercaDe ()
{	
	window3 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window3), "Acerca de:");
	gtk_widget_set_size_request(window3,500,531);//tamaño de la ventana creada
	gtk_window_set_resizable(GTK_WINDOW(window3),FALSE);// esta linea deja estatica la ventana
	gtk_window_set_position(GTK_WINDOW(window3), GTK_WIN_POS_CENTER);

	cont4 = gtk_fixed_new();// creamos un contenedor
	fondo=gtk_image_new_from_file("images/desarrolladores.jpg");//se llama la imagen de fondo

	Regresar = gtk_button_new_with_label("Regresar");
	Salir = gtk_button_new_with_label("Salir");

	gtk_widget_set_size_request(Regresar,120,38);
	gtk_widget_set_size_request(Salir,120,38);
	
	gtk_fixed_put(GTK_FIXED(cont4),fondo,0,0);//se coloca un objeto en la ventana

	gtk_fixed_put (GTK_FIXED(cont4),Regresar,82,400);
	gtk_fixed_put (GTK_FIXED(cont4),Salir,292,398);
		
	g_signal_connect_swapped (G_OBJECT (Regresar), "clicked",G_CALLBACK (Menu),(gpointer) window3);
	g_signal_connect_swapped (G_OBJECT (Regresar), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window3);

	
	g_signal_connect_swapped (G_OBJECT (Salir), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window3);
	gtk_container_add (GTK_CONTAINER(window3),cont4);// cerramos el contenedor
	gtk_widget_show_all(window3);// terminamo de usar la ventana	
}

void ManualU ()
{	
	window5 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window5), "Manual de usuario");
	gtk_widget_set_size_request(window5,500,600);//tamaño de la ventana creada
	gtk_window_set_resizable(GTK_WINDOW(window5),FALSE);// esta linea deja estatica la ventana
	gtk_window_set_position(GTK_WINDOW(window5), GTK_WIN_POS_CENTER);

	cont6 = gtk_fixed_new();// creamos un contenedor
	//fondo=gtk_image_new_from_file("principal.png");//se llama la imagen de fondo

	Regresar = gtk_button_new_with_label("Regresar");
	Salir = gtk_button_new_with_label("Salir");

	gtk_widget_set_size_request(Regresar,120,70);
	gtk_widget_set_size_request(Salir,120,70);
	
	gtk_fixed_put (GTK_FIXED(cont6),Regresar,80,480);
	gtk_fixed_put (GTK_FIXED(cont6),Salir,300,480);
	
	//gtk_fixed_put(GTK_FIXED(contenedor),fondo,0,0);//se coloca un objeto en la ventana
	
	g_signal_connect_swapped (G_OBJECT (Regresar), "clicked",G_CALLBACK (Menu),(gpointer) window5);
	g_signal_connect_swapped (G_OBJECT (Regresar), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window5);

	
	g_signal_connect_swapped (G_OBJECT (Salir), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window5);
	gtk_container_add (GTK_CONTAINER(window5),cont6);// cerramos el contenedor
	gtk_widget_show_all(window5);// terminamo de usar la ventana	
}

void Error (char const *imagen)
{	
	window4 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window4), "Error");
	gtk_widget_set_size_request(window4,550,215);//tamaño de la ventana creada
	gtk_window_set_resizable(GTK_WINDOW(window4),FALSE);// esta linea deja estatica la ventana
	gtk_window_set_position(GTK_WINDOW(window4), GTK_WIN_POS_CENTER);

	cont5 = gtk_fixed_new();// creamos un contenedor
	fondo=gtk_image_new_from_file(imagen);//se llama la imagen de fondo
	Aceptar = gtk_button_new_with_label("Aceptar");
	gtk_widget_set_size_request(Aceptar,98,33);
	gtk_fixed_put (GTK_FIXED(cont5),Aceptar,385,148);	
	gtk_fixed_put(GTK_FIXED(cont5),fondo,0,0);//se coloca un objeto en la ventana
	
	g_signal_connect_swapped (G_OBJECT (Aceptar), "clicked",G_CALLBACK (gtk_widget_destroy),(gpointer) window4);
	gtk_container_add (GTK_CONTAINER(window4),cont5);// cerramos el contenedor
	gtk_widget_show_all(window4);// terminamo de usar la ventana
}
