/*
											UNIVERSIDAD AUT�NOMA DE BAJA CALIFORNIA
										  FACULTAD DE CIENCIAS QU�MICAS E INGENIER�A
											  ALGORITMOS Y ESTRUCTURA DE DATOS
														   2020-1
					                                     PR�CTICA #3
Alumnos:
	* Cota Robledo Benjam�n [1225836]
	* Rodriguez Mu�oz Jos� Luis [1260368]

Pr�ctica: Estructuras FIFO con Listas Enlazadas
Fecha: 17/02/2020
GitHub:

Competencia: El alumno estructurar� programas en los que se utilicen colas para almacenar datos.

Ejercicio:
    * Un verdugo es mandado a ejecutar N prisioneros. El orden de ejecuci�n lo determina de la siguiente forma: El
      verdugo elige un n�mero K al azar, de la cola saca K-1 prisioneros y los pasa hacia el final de la cola, el K-�simo
      prisionero es el que ser� ejecutado. Este proceso se repite las veces que sea necesario hasta que queda solo uno. El
      �ltimo prisionero ser� dejado en libertad.

Hacer un programa que tenga las siguientes opciones:

    1) Agregar prisionero a la lista.
    2) Ejecuci�n de prisioneros

        * La opci�n ejecuci�n debe mostrar el orden de ejecuci�n.
        * La opci�n ejecuci�n debe mostrar el nombre del prisionero liberado
        * Los prisioneros ser�n ingresados por el usuario.
        * El valor de K es proporcionado por el usuario
        * La can1dad de prisioneros es ilimitada
        * Lenguaje C.
        * Debe utilizar una cola implementada con listas enlazadas

        Nota: El apodo y el tipo de muerte se agreg� para darle un toque m�s din�mico a la pr�ctica, no es obligatorio.
              As� como el Delay para simular un tiempo de ejecuci�n.

*/

#include <stdio.h> // Librer�a principal
#include <string.h> // Manejo de cadenas
#include <stdlib.h> // Uso de memoria din�mica
#include <time.h> // Para el uso del delay

// Estructura para manejar al Prisionero
typedef struct
{
    char nombrePrisionero[15]; // Nombre del prisionero
    char apodo[10]; // Apodo del prisionero
    int tipoMuerte; // Tipo de muerte para el prisionero
} Prisionero;

// Estructura para manipular el Nodo de la Cola
struct Nodo
{
    Prisionero prisionero; // Atributo de la estructura Prisionero
    struct Nodo* siguiente; // Atributo de la estructura Nodo con apuntador
};

/* Funciones prototipo */
void capturaDatos(char nombrePrisionero[15], char apodo[10], int* tipoMuerte); // Captura los datos del prisionero
void delay(int segundos); // Simula el tiempo
void clearBuffer(); // Limpia el buffer para que no haya conflicto con los gets

/* Funciones para la Cola */
void insertarNodo(struct Nodo** inicio, char nombrePrisionero[15], char apodo[10], int tipoMuerte); // Inserta prisionero a la cola
void borrarNodo(struct Nodo** inicio, int posicion);
void moverFinal(struct Nodo** inicio); // Interact�a con la lista de los prisioneros para hacer el corrimiento
void mostrar(struct Nodo* inicio); // Muestra la lista de los prisioneros agregados

void capturaDatos(char nombrePrisionero[15], char apodo[10], int* tipoMuerte)
{
    int opcion; // Variable para manejar el tipo de ejecuci�n
    printf("\n\n\t Prisionero");
    printf("\n\n Nombre: "); // Pide nombre del prisionero
    gets(nombrePrisionero); // Captura el nombre
    printf("\n Apodo: "); // Pide el apodo del prisionero
    gets(apodo); // Captura el apodo
    printf("\n\n **************************************************** "); // Cuesti�n de est�tica
    printf("\n\n\t Tipo de ejecuci%cn", 162);
    printf("\n\n 1) R%cpida", 160);
    printf("\n 2) Lenta");              // Este bloque imprime los tipos de ejecuci�n
    printf("\n 3) Dolorosa");
    do
    {
        if(opcion < 1 || opcion > 3) // Rango de opciones 1-3
            printf("\n\n\t Elige el tipo de ejecuci%cn: ", 162);
            scanf("%d", &opcion); // Lee el tipo de ejecuci�n
            *tipoMuerte = opcion; // Se le asigna la variable tipoMuerte con apuntador a la variable opci�n
            printf("\n\n Prisionero listo para ejecutar ...");
    } while(opcion < 1 || opcion > 3); // Mientras la opci�n sea entre 1 y 3
    delay(1000); // Simula el tiempo
	clearBuffer(); // Limpia el buffer para los gets
}

// Funci�n para simular el tiempo
void delay(int segundos)
{
    clock_t start = clock();
    while(clock() < start + segundos); /* Este bloque realiza un retardo para ejecutar alguna instrucci�n */
}

// Funci�n para limpiar el buffer
void clearBuffer()
{
    while(getchar() != '\n'); // Evita conflictos con los gets
}

// Funci�n para insertar elemento a la lista enlazada
void insertarNodo(struct Nodo** inicio, char nombrePrisionero[15], char apodo[10], int tipoMuerte)
{
    struct Nodo* nuevo; // Atributo de la estructura Nodo
    nuevo = (struct Nodo*)malloc(sizeof(struct Nodo)); // Se utiliza la memoria din�mica
    strcpy(nuevo -> prisionero.nombrePrisionero, nombrePrisionero); // Copia la cadena apuntada por origen en la cadena apuntada por destino
    strcpy(nuevo -> prisionero.apodo, apodo); // Copia la cadena apuntada por origen en la cadena apuntada por destino.
    nuevo -> prisionero.tipoMuerte = tipoMuerte; // Tipo de muerte
    nuevo -> siguiente = NULL; // Si el nuevo es siguiente entonces ser� nulo

    if(*inicio == NULL)
    {
        *inicio = nuevo; // Se podr�a decir que este es c�mo un caso base
    }
    else
    {
        struct Nodo *p, *q; // Atributos de la estructura Nodo
        p = *inicio; // Se le asigna el inicio con apuntador al atributo p

        while(p != NULL)
        {
            q = p;
            p = p -> siguiente; /* Este bloque agrega un elemento mientras no sea nulo */
        }
        q -> siguiente = nuevo;
    }
}

// Funci�n para eliminar nodo de la lista enlazada
void borrarNodo(struct Nodo** inicio, int posicion)
{
    int i; // Variable contador

    if(*inicio == NULL) // Si inicio apunta a nulo es un caso base
        return;
    struct Nodo *aux = *inicio; // Se le asigna el inicio al atributo aux de la estructura Nodo con apuntador

    if(posicion == 0) // Si posici�n es 0 entonces realiza el siguiente bloque
    {
        *inicio = aux -> siguiente; // aux pasa a ser el nodo siguiente
        free(aux); // Libera memoria de aux
        return;
    }
    for(i = 0; aux != NULL && i < posicion - 1; i++) // Itera K veces seg�n la posici�n ingresada
        aux = aux -> siguiente; // Se asigna a aux el nodo que hace referencia como siguiente

    if(aux == NULL || aux -> siguiente == NULL) // Si aux es nulo o aux siguiente es nulo, esto quiere decir que estas al final de la cola
    {
        //system("cls"); // Limpia pantalla
        printf("\n No existe prisionero en esa posici%cn ...", 162); // Imprime el mensaje para el usuario
        return;
    }
    struct Nodo *siguiente = aux -> siguiente -> siguiente; // Hace el corrimiento de los nodos
    free(aux -> siguiente); // Libera memoria del nodo auxiliar siguiente
    aux -> siguiente = siguiente; // Se le asigna el nodo siguiente al nodo auxiliar siguiente
}

// Funci�n para interactuar con la lista enlazada
void moverFinal(struct Nodo** inicio)
{
    if(*inicio == NULL || (*inicio) -> siguiente == NULL)
        return; // Se podr�a decir que es c�mo un caso base

    struct Nodo* primero = *inicio; // Se le asigna el inicio con apuntador al atributo primero
    struct Nodo* ultimo = *inicio; // Se le asigna el inicio con apuntador al atributo ultimo

    while(ultimo -> siguiente != NULL)
    {
        ultimo = ultimo -> siguiente; // Cuando el �ltimo sea diferente de nulo se asigna elemento
    }

    *inicio = primero -> siguiente;
    primero -> siguiente = NULL;        /* Este bloque realiza los movimientos en la lista enlazada */
    ultimo -> siguiente = primero;
}

// Funci�n para mostrar el contenido de la lista enlazada
void mostrar(struct Nodo* inicio)
{
    struct Nodo* aux; // Auxiliar de la estructura Nodo
    int i = 0; // Contador para los prisioneros
    aux = inicio; // Se le asigna el inicio al auxiliar
    printf("\n\n\t\t Prisioneros en espera");
    do
    {
        printf("\n\n %d. %s \t %s", i, aux -> prisionero.nombrePrisionero, aux -> prisionero.apodo); // Muestra el nombre y el apodo en orden

        if(aux -> prisionero.tipoMuerte == 1)
        {
            printf("\t Muerte r%cpida", 160); // Si la opci�n es 1 entonces es muerte r�pida
        }
        else if(aux -> prisionero.tipoMuerte == 2)
        {
            printf("\t Muerte lenta"); // Si la opci�n es 2 entonces es muerte lenta
        }
        else if(aux -> prisionero.tipoMuerte == 3)
        {
            printf("\t Muerte dolorosa"); // Si la opci�n es 3 entonces es muerte dolorosa
        }
        aux = aux -> siguiente; // Asignaci�n al auxiliar
        i++; // Incrementa el contador
    } while(aux != NULL); // Mientras que el auxiliar sea diferente de nulo
}

int main()
{
    struct Nodo* inicio = NULL; // Se crea el nodo de la lista enlazada
    char nombrePrisionero[15], apodo[10]; // Nombre y apodo del prisionero
    int tipoMuerte, K; // Variable para el tipo de muerte y para la posici�n a eliminar
    char opcion; // Variable para las opciones del men�
    do
    {
        //system("cls");
		printf("\n\n **************************************************** ");
        printf("\n\n\t FIFO con Listas Enlazadas");
        printf("\n\n 1) Agregar prisionero a la lista");
        printf("\n 2) Ejecuci%cn de prisioneros", 162);
        printf("\n 3) Mostrar lista de prisioneros");       /* Bloque que muestra el men� */
        printf("\n 4) Salir");
        printf("\n\n\t Introduce una opci%cn: ", 162);
        opcion = getchar(); // Captura la opci�n

        switch(opcion)
        {
        case '1':
            //system("cls");
			clearBuffer(); // Limpia el buffer
            capturaDatos(nombrePrisionero, apodo, &tipoMuerte); // Captura los datos del prisionero
            insertarNodo(&inicio, nombrePrisionero, apodo, tipoMuerte); // Inserta elemento
            getch(); // Espera un enter para continuar
            break; // Rompe el bucle

        case '2':
            //system("cls");
			clearBuffer(); // Limpia el buffer

            if(inicio != NULL) // Si el inicio es diferente de nulo
            {
                printf("\n Ingresa la posici%cn a remover [0, ... n]: ", 162); // Pide la posici�n a eliminar
                scanf("%d", &K); // Captura el dato
                mostrar(inicio); // Muestra la lista enlazada
                borrarNodo(&inicio, K); // Borra el nodo
                moverFinal(&inicio); // Hace el corrimiento en la lista
                printf("\n\n **************************************************** "); // Cuesti�n de est�tica
                delay(2000); // Simula el tiempo
                printf("\n\n\t -> Se elimin%c al prisionero ...", 162); // Monitoreo
                printf("\n"); // Salto de l�nea para que se vea mejor
                mostrar(inicio); // Muestra la lista enlazada
                getch(); // Espera enter para continuar
            }
            else
            {
                printf("\n No hay prisioneros en cola ..."); // No hay elementos en la lista
                getch(); // Espera enter para continuar
            }
            break; // Rompe bucle

        case '3':
            //system("cls");
            clearBuffer(); // Limpia el buffer

            if(inicio != NULL) // Si inicio es diferente de nulo
            {
                mostrar(inicio); // Muestra la lista enlazada
                getch(); // Espera enter para continuar
            }
            else
            {
                printf("\n No hay prisioneros en cola ..."); // No hay elementos en la lista
                getch(); // Espera enter para continuar
            }
            break; // Rompe bucle
        }
    } while(opcion != '4' && opcion != EOF); // Realiza el men� mientras no sea opci�n 4 o Fin de archivo
      {
          //system("cls");
          printf("\n Cierre exitoso ..."); /* Termina el programa */
      }
	  
	return 0;
}