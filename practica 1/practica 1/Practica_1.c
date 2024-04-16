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

typedef struct {
    char nombre[MAX_CADENA], apellido1[MAX_CADENA], apellido2[MAX_CADENA], codigo[MAX_CODIGOSOCIO]; /** 2 primeros nombre, iniciales apellidos, -, número de socio (5 cifras) **/
    char dni[10];
    int tipo;
}t_regSocio;

typedef struct {
    char nombre[MAX_CADENA], codigo[MAX_CODIGOCURSO];
    int plazas;
    float precio;
}t_regCurso;


void gestionSocios(t_regSocio socios[MAX_SOCIOS], int* cont_socios);
void altaSocios(t_regSocio socios[MAX_SOCIOS], int* cont_socios);

void modificarDatos(t_regSocio socios[MAX_SOCIOS]);
char tipoEscrito(t_regSocio socios[MAX_SOCIOS], int i);

int main(void)
{
    t_regSocio socios[MAX_SOCIOS];
    t_regCurso cursos[MAX_CURSOS];

    int opcion1, cont_socios;

    setlocale(LC_ALL, "Spanish");

    do {
        system("cls");

        printf("MENÚ PRINCIPAL\n");
        printf("==============\n\n");
        printf("1.- Gestión de socios.\n");
        printf("2.- Gestión de Cursos.\n");
        printf("3.- Informes económicos.\n");
        printf("4.- Importar Cursos.\n\n");         /** FICHEROS **/
        printf("0.- Salir.\n\n");
        printf("Elija una opción: ");
        scanf("%d", &opcion1);
        if (opcion1 < 0 || opcion1>4) {
            printf("\n\nPor favor, indique una opción válida.\n");
            system("pause");
        }
        switch (opcion1) {
        case 1:
            gestionSocios(socios, &cont_socios);
            break;

        }
    } while (opcion1 != 0);

}


/**************************************************************************
GESTIÓN DE SOCIOS
**************************************************************************/
void gestionSocios(t_regSocio socios[MAX_SOCIOS], int* cont_socios) {

    int opcion2;

    do {
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
        printf("Elija una opción: ");
        scanf("%d", &opcion2);
        if (opcion2 < 0 || opcion2 > 8) {
            printf("\n\nPor favor introduzca una opción válida.\n");
            system("pause");
        }

        switch (opcion2) {
        case 1:
            altaSocios(socios, &cont_socios);
            break;
        }
    } while (opcion2 != 0);


}

/**************************************************************************
DAR DE ALTA SOCIOS
**************************************************************************/
void altaSocios(t_regSocio socios[MAX_SOCIOS], int* cont_socios) {

    int i;

    char continuar;

    *cont_socios = 0;

    printf("AREA DE ALTA DE SOCIOS.\n");
    printf("=======================\n\n");

    /** FALTA REMATAR CON EL DO WHILE CUANDO SEPA HACER EL CONTADOR **/

    do {

        system("cls");

        printf("Introduzca el nombre del socio %d: ", *cont_socios + 1);
        fflush(stdin); fgets(socios[*cont_socios].nombre, MAX_CADENA, stdin); fflush(stdin);
        if (socios[*cont_socios].nombre[strlen(socios[*cont_socios].nombre) - 1] == '\n') {
            socios[*cont_socios].nombre[strlen(socios[*cont_socios].nombre) - 1] = '\0';
        }

        printf("\nIntroduzca el primer apellido del socio %d: ", *cont_socios + 1);
        fflush(stdin); fgets(socios[*cont_socios].apellido1, MAX_CADENA, stdin); fflush(stdin);
        if (socios[*cont_socios].apellido1[strlen(socios[*cont_socios].apellido1) - 1] == '\n') {
            socios[*cont_socios].apellido1[strlen(socios[*cont_socios].apellido1) - 1] = '\0';
        }

        printf("\nIntroduzca el segundo apellido del socio %d: ", *cont_socios + 1);
        fflush(stdin); fgets(socios[*cont_socios].apellido2, MAX_CADENA, stdin); fflush(stdin);
        if (socios[*cont_socios].apellido2[strlen(socios[*cont_socios].apellido2) - 1] == '\n') {
            socios[*cont_socios].apellido2[strlen(socios[*cont_socios].apellido2) - 1] = '\0';
        }

        printf("\nIntroduzca el DNI del socio %d: ", *cont_socios + 1);
        fflush(stdin); fgets(socios[*cont_socios].dni, 10, stdin); fflush(stdin);
        if (socios[*cont_socios].dni[strlen(socios[*cont_socios].dni) - 1] == '\n') {
            socios[*cont_socios].dni[strlen(socios[*cont_socios].dni) - 1] = '\0';
        }

        printf("\nIntroduzca la categoría del socio %d (1-Normal, 2-Jubilado, 3-Infantil): ", *cont_socios + 1);
        fflush(stdin); scanf("%d", &socios[*cont_socios].tipo); fflush(stdin);

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

    } while (*cont_socios < MAX_SOCIOS && continuar == 'y');


    system("pause");

    /** FALTA REMATAR CON EL DO WHILE CUANDO SEPA HACER EL CONTADOR **/

}

/*****************************************************************************
MODIFICAR DATOS DE UN USUARIO
*****************************************************************************/
void modificarDatos(t_regSocio socios[MAX_SOCIOS]) {

    int usuario_cambiar;
    char DNI_cambiar[10];

    printf("MODIFICACIÓN DE DATOS DE SOCIOS.\n");
    printf("===============================\n\n");
    printf("Introduzca el DNI del usuario al que desea modificar los datos: ");
    fgets(DNI_cambiar, 10, stdin);

    /***************************************
    FALTA BUSCAR AL USUARIO
    ***************************************/

    printf("MODIFICACIÓN DE DATOS DE SOCIOS.\n");
    printf("===============================\n\n");
    printf("Datos actuales:");
    printf("---------------");
    printf("Código: %s\n", socios[usuario_cambiar].codigo);
    printf("Nombre: %s\n", socios[usuario_cambiar].nombre);
    printf("DNI: %s\n", socios[usuario_cambiar].dni);
    printf("Tipo socio: &s", tipoEscrito(socios, usuario_cambiar));
}

/*****************************************************************************
MODIFICAR DATOS DE UN USUARIO
*****************************************************************************/
char tipoEscrito(t_regSocio socios[MAX_SOCIOS], int i) {

    switch (socios[i].tipo) {
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

//PRUEBA