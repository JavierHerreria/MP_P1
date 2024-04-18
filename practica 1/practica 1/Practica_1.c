/**********************************************************************
Programa:               Gestión del gimnasio.
Tarea qué realiza:      Gestiona los socios, cursos e informes económicos
                        de un gimnasio.
Autor:                  Javier Herrería Martín y Eduardo Martín Postigo.
Fecha:                  26 de abril de 2024.
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#define MAX_CADENA 20
#define MAX_CODIGOSOCIO 11
#define MAX_CODIGOCURSO 5
#define MAX_SOCIOS 100
#define MAX_CURSOS 10

typedef struct{
    char nombre[MAX_CADENA], apellido1[MAX_CADENA], apellido2[MAX_CADENA], codigo[MAX_CODIGOSOCIO]; /** 2 primeros nombre, iniciales apellidos, -, número de socio (5 cifras) **/
    char dni[10];
    int tipo;
}t_regSocio;

typedef struct{
    char nombre[MAX_CADENA], codigo[MAX_CODIGOCURSO];
    int plazas;
    float precio;
}t_regCurso;

int DNIcomp(char DNI_buscar[10], int cont_socios, t_regSocio socios[MAX_SOCIOS]);
char tipoSocio[](int tipo);
void gestionSocios(t_regSocio socios[MAX_SOCIOS], int *cont_socios);
void altaSocios(t_regSocio socios[MAX_SOCIOS], int *cont_socios);

void modificarDatos(t_regSocio socios[MAX_SOCIOS], int cont_socios);
void consultarDatos(t_regSocio socios[MAX_SOCIOS], int cont_socios);
//void generarRecibo(t_regSocio socios[]);
void listadoSocios(t_regSocio socios[MAX_SOCIOS], int cont_socios);

int main(void){
    t_regSocio socios[MAX_SOCIOS];
    t_regCurso cursos[MAX_CURSOS];

    int opcion1, cont_socios;

    setlocale(LC_ALL, "Spanish");

    do{
        system("cls");

        printf("MENÚ PRINCIPAL\n");
        printf("==============\n\n");
        printf("1.- Gestión de socios.\n");
        printf("2.- Gestión de Cursos.\n");
        printf("3.- Informes económicos.\n");
        printf("4.- Importar Cursos.\n\n");         /** FICHEROS **/
        printf("0.- Salir.\n\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion1);
        if(opcion1<0 || opcion1>4){
            printf("\n\nPor favor, indique una opción válida.\n");
            system("pause");
        }
        switch(opcion1){
            case 1:
                gestionSocios(socios, &cont_socios);
                break;
        }
    }while(opcion1!=0);

}

/***************************** BUSCADOR DE DNI *****************************
Subprograma: DNIcomp
Par E/ DNI para buscar, contador de socios y el array de registros de socios.
Par S/ posición del array del socio. (-1 si no se encuentra)
Tarea que realiza: Comparar el DNI con el de cada socio y devolver la posición
    que ocupa el socio en el array de registros. Devuelve -1 si no encuentra ese DNI.
****************************************************************************/
int DNIcomp(char DNI_buscar[10], int cont_socios, t_regSocio socios[MAX_SOCIOS]){

    int i, j;

    for(j=0; j<10; j++){
        DNI_buscar[j] = tolower(DNI_buscar[j]);
    }

    for(i=0; i<cont_socios; i++){
        for(j=0; j<10; j++){
        socios[i].dni[j] = tolower(socios[i].dni[j]);
        }

        if(strcmp(socios[i].dni, DNI_buscar) == 0){
            return i;
        }else if(strcmp(socios[i].dni, DNI_buscar) != 0){
            return -1;
        }
    }
    system("pause");
}

/***************************** CONVERSOR A TEXTO ****************************
Subprograma: tipoSocio.
Par E/ El tipo de socio.
Par S/ El tipo de socio, escrito en texto.
Tarea que realiza: Devolver en formato de texto el tipo de socio.
****************************************************************************/
char tipoSocio[](int tipo){

    switch(tipo){
        case 1:
            return "normal";
            break;
        case 2:
            return "jubilado";
            break;
        case 3:
            return "infantil";
            break;
    }

}


/***************************** GESTIÓN DE SOCIOS *****************************
Subprograma: gestionSocios
Par E/ El array de registros de socios y el contador de socios.
Par S/ ---
Tarea que realiza: Menú de opciones para la gestión de socios.
******************************************************************************/
void gestionSocios(t_regSocio socios[MAX_SOCIOS], int *cont_socios){

    int opcion2;

    do{
        system("cls");

        printf("SUBMENÚ 'GESTIÓN DE SOCIOS'");
        printf("\n===========================\n\n");
        printf("1.- Alta.\n");
        printf("2.- Baja.\n");                      /** FICHEROS **/
        printf("3.- Modificación de datos de un socio.\n\n");
        printf("4.- Consulta de datos de un socio.\n");
        printf("5.- Generar recibo.\n\n");
        printf("6.- Listado General de Socios.\n");
        printf("7.- Listado de Socios por categoría.\n");
        printf("8.- Listado de socios que han sido dados de baja en un mes y año determinado.\n\n"); /** FICHEROS **/
        printf("0.- Volver al menú principal.\n\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion2);
        if(opcion2<0 || opcion2 > 8){
            printf("\n\nPor favor introduzca una opción válida.\n");
            system("pause");
        }

        switch(opcion2){
            case 1:
                altaSocios(socios, &cont_socios);
                break;
            case 3:
                modificarDatos(socios, cont_socios);
                break;
            case 4:
                consultarDatos(socios, cont_socios);
                break;
            case 6:
                listadoSocios(socios, cont_socios);
        }
    }while(opcion2!=0);


}

/***************************** ALTA DE SOCIOS ********************************
Subprograma: altaSocios
Par E/ El array de registros de socios y el contador de socios.
Par S/ ---
Tarea que realiza: Solicitar y guardar la información de nuevos socios.
******************************************************************************/
void altaSocios(t_regSocio socios[MAX_SOCIOS], int *cont_socios){

    int i;

    char continuar;

    *cont_socios = 0;

    /** FALTA REMATAR CON EL DO WHILE CUANDO SEPA HACER EL CONTADOR **/

    do{

    system("cls");

    printf("AREA DE ALTA DE SOCIOS.\n");
    printf("=======================\n\n");
    printf("Introduzca el nombre del socio %d: ", *cont_socios+1);
    fflush(stdin); fgets(socios[*cont_socios].nombre, MAX_CADENA, stdin); fflush(stdin);
    if(socios[*cont_socios].nombre[strlen(socios[*cont_socios].nombre) - 1] == '\n'){
        socios[*cont_socios].nombre[strlen(socios[*cont_socios].nombre) - 1] = '\0';
        }

    printf("\nIntroduzca el primer apellido del socio %d: ", *cont_socios+1);
    fflush(stdin); fgets(socios[*cont_socios].apellido1, MAX_CADENA, stdin); fflush(stdin);
    if(socios[*cont_socios].apellido1[strlen(socios[*cont_socios].apellido1) - 1] == '\n'){
        socios[*cont_socios].apellido1[strlen(socios[*cont_socios].apellido1) - 1] = '\0';
    }

    printf("\nIntroduzca el segundo apellido del socio %d: ", *cont_socios+1);
    fflush(stdin); fgets(socios[*cont_socios].apellido2, MAX_CADENA, stdin); fflush(stdin);
    if(socios[*cont_socios].apellido2[strlen(socios[*cont_socios].apellido2) - 1] == '\n'){
        socios[*cont_socios].apellido2[strlen(socios[*cont_socios].apellido2) - 1] = '\0';
    }

    printf("\nIntroduzca el DNI del socio %d: ", *cont_socios +1);
    fflush(stdin); fgets(socios[*cont_socios].dni, 10, stdin); fflush(stdin);
    socios[*cont_socios].dni[9] = tolower(socios[*cont_socios].dni[9]);
    if(socios[*cont_socios].dni[strlen(socios[*cont_socios].dni) - 1] == '\n'){
        socios[*cont_socios].dni[strlen(socios[*cont_socios].dni) - 1] = '\0';
    }

    do{
        printf("\nIntroduzca la categoría del socio %d (1-Normal, 2-Jubilado, 3-Infantil): ", *cont_socios+1);
        fflush(stdin); scanf("%d", &socios[*cont_socios].tipo); fflush(stdin);
    }while(socios[*cont_socios].tipo<1 || socios[*cont_socios].tipo>3);

    socios[*cont_socios].codigo[0] = toupper(socios[*cont_socios].nombre[0]);
    socios[*cont_socios].codigo[1] = toupper(socios[*cont_socios].nombre[1]);
    socios[*cont_socios].codigo[2] = toupper(socios[*cont_socios].apellido1[0]);
    socios[*cont_socios].codigo[3] = toupper(socios[*cont_socios].apellido2[0]);
    socios[*cont_socios].codigo[4] = '-';
    /*
    socios[*cont_socios].codigo[5] = cont_Altas[0];
    socios[*cont_socios].codigo[6] = cont_Altas[1];
    socios[*cont_socios].codigo[7] = cont_Altas[2];
    socios[*cont_socios].codigo[8] = cont_Altas[3];
    socios[*cont_socios].codigo[9] = cont_Altas[4];
    */


    printf("\n\n%s\n\n", socios[*cont_socios].codigo);

    printf("\n\n¿Desea seguir introduciendo más datos? [Y=YES/N=NO]: ");
    fflush(stdin); scanf("%c", &continuar);
    continuar = towlower(continuar);

    *cont_socios = *cont_socios + 1;

    }while(*cont_socios < MAX_SOCIOS && continuar=='y');


    system("pause");

    /** FALTA REMATAR CON EL DO WHILE CUANDO SEPA HACER EL CONTADOR **/

}

/***************************** MODIFICAR DATOS *******************************
Subprograma: modificarDatos
Par E/ El array de registros de socios y el contador de socios.
Par S/ ---
Tarea que realiza: Solicita un DNI y permite modificar los datos del socio.
******************************************************************************/
void modificarDatos(t_regSocio socios[MAX_SOCIOS], int cont_socios){

    int i, opcion, opcion_nombre;
    char DNI_cambiar[10], tipo_escrito[10];

    system("cls");

    printf("MODIFICACIÓN DE DATOS DE SOCIOS.\n");
    printf("===============================\n\n");
    printf("Introduzca el DNI del socio al que desea modificar los datos: ");
    fflush(stdin); fgets(DNI_cambiar, 10, stdin); fflush(stdin);

    i = DNIcomp(DNI_cambiar, cont_socios, socios);

    if(i==-1){
        printf("\n\nERROR: el DNI que busca no está asociado a ningún socio. ");
    }else{
        system("cls");
        printf("MODIFICACIÓN DE DATOS DE SOCIOS.\n");
        printf("===============================\n\n");
        printf("Datos actuales del socio %s\n", socios[i].codigo);
        printf("-----------------------------------\n");
        printf("1.- Nombre completo: %s %s %s\n", socios[i].nombre, socios[i].apellido1, socios[i].apellido2);
        printf("2.- DNI: %s\n", socios[i].dni);
        printf("3.- Código: %s\n", socios[i].codigo);
        printf("4.- Tipo socio: ");
        switch(socios[i].tipo){
            case 1:
                printf("normal.\n");
                break;
            case 2:
                printf("jubilado.\n");
                break;
            case 3:
                printf("infantil.\n");
                break;
        }
        printf("5.- Cursos inscritos: \n\n"); /** TERMINAR MOSTRAR CURSOS INSCRITOS **/

        do{
            printf("\n\n***********************************************");
            printf("\n\n¿Qué información desea modificar?");
            printf("\n1.- DNI.");
            printf("\n2.- Nombre.");
            printf("\n3.- Tipo de socio.");
            printf("\n\n0.- Salir del menú de modificación de datos.");
            printf("\n\nSeleccione una opción: ");
            scanf("%d", &opcion);
            system("cls");
            printf("MODIFICACIÓN DE DATOS DE SOCIOS.\n");
            printf("===============================\n\n");
            switch(opcion){
                case 1:
                    printf("DNI actual del socio %s: %s", socios[i].codigo, socios[i].dni);
                    printf("\nIntroduzca el nuevo DNI del socio %s: ", socios[i].codigo);
                    fflush(stdin); fgets(socios[i].dni, 10, stdin); fflush(stdin);

                    socios[i].dni[9] = tolower(socios[i].dni[9]);

                    if(socios[i].dni[strlen(socios[i].dni) - 1] == '\n'){
                    socios[i].dni[strlen(socios[i].dni) - 1] = '\0';
                    }

                    break;

                case 2:
                    printf("¿Qué campo desea modificar?");
                    printf("\n1.- Nombre.");
                    printf("\n2.- Primer apellido.");
                    printf("\n3.- Segundo apellido.");
                    printf("\n\n0.- Cancelar.");
                    printf("\n\nSeleccione una opción: ");
                    scanf("%d", &opcion_nombre);
                    switch(opcion_nombre){
                        case 1:
                            printf("\n\nNombre actual del socio %s: %s", socios[i].codigo, socios[i].nombre);
                            printf("\nIntroduzca el nuevo nombre del socio %s: ");
                            fflush(stdin); fgets(socios[i].nombre, MAX_CADENA, stdin); fflush(stdin);
                            if(socios[i].nombre[strlen(socios[i].nombre) - 1] == '\n'){
                            socios[i].nombre[strlen(socios[i].nombre) - 1] = '\0';
                            }
                            break;
                        case 2:
                            printf("\n\nPrimer apellido actual del socio %s: %s", socios[i].codigo, socios[i].apellido1);
                            printf("\nIntroduzca el nuevo primer apellido del socio %s: ");
                            fflush(stdin); fgets(socios[i].apellido1, MAX_CADENA, stdin); fflush(stdin);
                            if(socios[i].apellido1[strlen(socios[i].apellido1)-1] == '\n'){
                                socios[i].apellido1[strlen(socios[i].apellido1)-1] = '\0';
                            }
                            break;
                        case 3:
                            printf("\n\nSegundo apellido actual del socio %s: %s", socios[i].codigo, socios[i].apellido2);
                            printf("\nIntroduzca el nuevo segundo apellido del socio %s: ");
                            fflush(stdin); fgets(socios[i].apellido2, MAX_CADENA, stdin); fflush(stdin);
                            if(socios[i].apellido2[strlen(socios[i].apellido2)-1] == '\n'){
                                socios[i].apellido2[strlen(socios[i].apellido2)-1] = '\0';
                            }
                            break;
                    }
                    break;

                case 3:
                    printf("\nTipo de socio actual del socio %s: %d", socios[i].codigo, socios[i].tipo);
                    printf("\nIntroduzca el nuevo tipo de socio para el socio %s: ", socios[i].codigo);
                    scanf("%d", &socios[i].tipo);
                    break;

                case 0:
                    break;

                default:
                    printf("\n\nERROR: Introduzca una opción correcta.");
            }
        }while(opcion!=0);
    }

    system("pause");
}

/***************************** CONSULTAR DATOS *******************************
Subprograma: consultarDatos
Par E/ El array de registros de socios y el contador de socios.
Par S/ ---
Tarea que realiza: Solicita un DNI y muestra los datos del socio.
******************************************************************************/
void consultarDatos(t_regSocio socios[MAX_SOCIOS], int cont_socios){

    char DNI_cambiar[10];
    int i;

    system("cls");

    printf("CONSULTA DE LOS DATOS DE UN SOCIO:\n");
    printf("==================================\n\n");
    printf("Introduzca el DNI del socio: ");
    fflush(stdin); fgets(DNI_cambiar, 10, stdin); fflush(stdin);

    i = DNIcomp(DNI_cambiar, cont_socios, socios);

    if(i==-1){
        printf("\n\nERROR: el DNI que busca no está asociado a ningún socio. ");
    }else{
        system("cls");
        printf("CONSULTA DE DATOS DE SOCIOS.\n");
        printf("===============================\n\n");
        printf("Datos del socio %s\n", socios[i].codigo);
        printf("-----------------------------------\n");
        printf("1.- Nombre completo: %s %s %s\n", socios[i].nombre, socios[i].apellido1, socios[i].apellido2);
        printf("2.- DNI: %s\n", socios[i].dni);
        printf("3.- Código: %s\n", socios[i].codigo);
        printf("4.- Tipo socio: ");
        switch(socios[i].tipo){
            case 1:
                printf("normal.\n");
                break;
            case 2:
                printf("jubilado.\n");
                break;
            case 3:
                printf("infantil.\n");
                break;
        }
        printf("5.- Cursos inscritos: \n\n"); /** TERMINAR MOSTRAR CURSOS INSCRITOS **/
    }
    system("pause");
}

/***************************** GENERAR RECIBOS *******************************
Subprograma: generarRecibos
Par E/ El array de registros de socios, el contador de socios.
Par S/ ---
Tarea que realiza: Genera un recibo de los cursos de un socio.
******************************************************************************/
/*
void generarRecibo(){



}
*/

/***************************** LISTADO SOCIOS ********************************
Subprograma: listadoSocios
Par E/ El array de registros de socios, el contador de socios.
Par S/ ---
Tarea que realiza: Genera una lista con los socios apuntados al gimnasio.
******************************************************************************/
void listadoSocios(t_regSocio socios[MAX_SOCIOS], int cont_socios){

    int i;

    system("cls");
    printf("----------------------------------------");
    printf("\n\tLISTADO GENERAL DE SOCIOS\n");
    printf("----------------------------------------\n\n");
    printf("Código\t\tNombre completo\t\t\t\tDNI\t\tCategoría");




}
