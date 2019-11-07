#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.bin (modo binario).
    10. Salir
*****************************************************/

int menu();

int main()
{
    char rta = 'n';
    LinkedList* listaEmpleados = ll_newLinkedList();
    int flag = 0;


    if( listaEmpleados == NULL)
    {
        printf("No se pudo asignar memoria\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    do
    {
        switch(menu())
        {

        case 1:
            if(flag == 0)
            {

                if(controller_loadFromText("data.csv",listaEmpleados))
                {
                    printf("Empleados cargados con exito\n");
                }
                flag = 1;
            }
            else
            {
                printf("Los empleados ya han sido cargados.\n");
            }
            break;
        case 2:
            if(flag ==0)
            {
                if(controller_loadFromBinary("data.bin",listaEmpleados))
                {
                    printf("Empleados cargados con exito\n");
                }
                flag = 1;
            }
            else
            {
                printf("Los empleados ya han sido cargados.\n");
            }
            break;
        case 3:
            if(flag)
            {
                controller_addEmployee(listaEmpleados);
            }
            else
            {
                printf("No hay empleados cargados.\n");
            }
            break;
        case 4:
            if(flag)
            {
                if(controller_editEmployee(listaEmpleados))
                {
                    printf("Modificacion exitosa\n");
                }
                else if(controller_editEmployee(listaEmpleados) == -1)
                {
                    printf("Se cancelo la modificacion\n");
                }
                else
                {
                    printf("Error. no se completo la modificacion\n");
                }
            }
            else
            {
                printf("No hay empleados cargados.\n");
            }
            break;
        case 5:
            if(flag)
            {
                controller_removeEmployee(listaEmpleados);
            }
            else
            {
                printf("No hay empleados cargados.\n");
            }
            break;
        case 6:
            if(flag)
            {
                controller_ListEmployee(listaEmpleados);
            }
            else
            {
                printf("No hay empleados cargados.\n");
            }
            break;
        case 7:
            if(flag)
            {
                controller_sortEmployee(listaEmpleados);
            }
            else
            {
                printf("No hay empleados cargados.\n");
            }
            break;
        case 8:
            if(flag)
            {
                if(controller_saveAsText("data.csv",listaEmpleados))
                {
                    printf("Empleados Guardados en modo texto con exito\n");
                }
            }
            else
            {
                printf("No hay empleados cargados.\n");
            }
            break;
        case 9:
            if(flag)
            {
                if(controller_saveAsBinary("data.bin",listaEmpleados))
                {
                    printf("Empleados Guardados en modo binario con exito\n");
                }
            }
            else
            {
                printf("No hay empleados cargados.\n");
            }
            break;
        case 10:
            printf("Confirma salida? s/n ");
            fflush(stdin);
            rta = getchar();
            break;
        default:
            printf("opcion invalida.\n");
            break;

        }

        system("pause");
        system("cls");

    }
    while(rta != 's');
    return 0;
}

int menu()
{
    int opcion;

    printf("*****       Menu De Inicio      *****\n\n");
    printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n");
    printf("2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n");
    printf("3. Alta de empleado\n");
    printf("4. Modificar datos de empleado\n");
    printf("5. Baja de empleado\n");
    printf("6. Listar empleados\n");
    printf("7. Ordenar empleados\n");
    printf("8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n");
    printf("9. Guardar los datos de los empleados en el archivo data.csv (modo binario).\n");
    printf("10. Salir\n\n");
    printf("Ingrese opcion: ");
    scanf("%d",&opcion);

    return opcion;
}
