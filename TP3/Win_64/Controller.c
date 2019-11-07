#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "controller.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    FILE* f;
    char buffer[4][100];
    int cant;
    Employee* aux = NULL;

    if(path != NULL && pArrayListEmployee != NULL)
    {

        f = fopen(path, "r");

        if( f == NULL)
        {
            printf("No se pudo abrir el archivo\n");
            return todoOk;
        }
        fscanf(f,"%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2],buffer[3]);

        while(!feof(f))
        {
//fscanf devuelve la cantidad de variables que pudo leer

            cant = fscanf(f,"%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2],buffer[3]);

            if( cant == 4)
            {
                aux = employee_newParametros(buffer[0], buffer[1], buffer[2],buffer[3]);
//atoi hace el parseint, convierte string a int, atof lo mismo pero en float
                if( aux != NULL)
                {
                    ll_add(pArrayListEmployee,aux);

                }
            }
            else
            {
                break;
            }
        }

        todoOk = 1;
    }

    int tam;
    tam = ll_len(pArrayListEmployee);
    printf("%d ",tam);
    return todoOk;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    FILE* f;
    int cant;
    Employee* aux = NULL;

    if(path != NULL && pArrayListEmployee != NULL)
    {

        f = fopen(path, "rb");

        if( f == NULL)
        {
            printf("No se pudo abrir el archivo\n");
            return todoOk;
        }


        while(!feof(f))
        {
            aux = employee_new();
            if(aux != NULL){
           cant =  fread( aux , sizeof(Employee),    1   ,  f );

            if(cant == 1){
                ll_add(pArrayListEmployee,aux);
        }

    }else{
        break;
    }
        }
        fclose(f);
        todoOk = 1;
    }

    int tam;
    tam = ll_len(pArrayListEmployee);
    printf("%d ",tam);
    return todoOk;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    char buffer[4][20];
    Employee* filtro = NULL;
    int flagFor = 0;

    if(pArrayListEmployee != NULL){

        printf("        ********        ALTA EMPLEADO       ********       \n\n\n");
        printf("Ingrese ID:");
        fflush(stdin);
        gets(buffer[0]);
        for(int i = 0;i<ll_len(pArrayListEmployee);i++){
            filtro = (Employee*) ll_get(pArrayListEmployee,i);
            if(filtro->id == atoi(buffer[0])){
                printf("ID YA CARGADA EN EL SISTEMA\n");
                flagFor = 1;
                break;
            }
        }
        if(flagFor == 1 ){
            while(filtro->id == atoi(buffer[0])){
                printf("Reingrese un ID valido:");
                fflush(stdin);
                gets(buffer[0]);
            }
        }

        printf("Ingrese nombre:");
        fflush(stdin);
        gets(buffer[1]);

        printf("Ingrese horas trabajadas:");
            fflush(stdin);
            gets(buffer[2]);
        while(atoi(buffer[2])< 0){
            printf("ERROR. las horas no pueden ser menores a 0.\nReingrese:");
            fflush(stdin);
            gets(buffer[2]);
        }
        printf("Ingrese Sueldo:");
            fflush(stdin);
            gets(buffer[3]);
        while(atoi(buffer[3])< 0){
            printf("ERROR. el sueldo no puede ser menor a 0.\nReingrese:");
            fflush(stdin);
            gets(buffer[3]);
        }

        ll_add(pArrayListEmployee,employee_newParametros(buffer[0],buffer[1],buffer[2],buffer[3]));

        todoOk = 1;

    }

    return todoOk;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    char buffer[1][20];
    Employee* filtro = NULL;
    Employee* aux = NULL;
    char flagFor = 'n';
    int nuevoID;
    char nuevoNombre[30];
    int nuevasHoras;
    int nuevoSueldo;

    if(pArrayListEmployee != NULL){

        printf("        ********        MODIFICACION EMPLEADO       ********       \n\n\n");
        printf("Ingrese ID:");
        fflush(stdin);
        gets(buffer[0]);
        for(int i = 0;i<ll_len(pArrayListEmployee);i++){
            filtro = (Employee*) ll_get(pArrayListEmployee,i);
            if(filtro->id == atoi(buffer[0])){
                printf("Id   Nombre   HorasTrabajadas   Sueldo\n\n");
                mostrarEmpleado(filtro);
                printf("confirma? \ns/n\nElija opcion:");
                flagFor = getchar();
                break;

            }
        }
if(flagFor == 's'){
        switch(menuModificacion()){

        case 1:
                printf("Ingrese nuevo ID: ");
                scanf("%d",&nuevoID);
                for(int i = 0; i< ll_len(pArrayListEmployee);i++){
                    aux = (Employee*) ll_get(pArrayListEmployee,i);
                    if(aux->id == nuevoID){
                        while(aux->id == nuevoID){
                            printf("ERROR. id ya cargado en el sistema. reingrese:");
                            scanf("%d",&nuevoID);
                        }
                    }

                }
                filtro->id = nuevoID;
            break;

        case 2:
                printf("Ingrese nuevo Nombre: ");
                fflush(stdin);
                gets(nuevoNombre);
                strcpy(filtro->nombre,nuevoNombre);
            break;

        case 3:
                printf("Ingrese nueva cantidad de horas: ");
                scanf("%d",&nuevasHoras);
                while(nuevasHoras<0){
                    printf("ERROR. Las horas no pueden ser menores a cero. Reingrese:");
                    scanf("%d",&nuevasHoras);
                }
                filtro->horasTrabajadas = nuevasHoras;
            break;

        case 4:
                printf("Ingrese nuevo Sueldo: ");
                scanf("%d",&nuevoSueldo);
                while(nuevoSueldo<0){
                    printf("ERROR. El sueldo no puede ser menor a cero. Reingrese:");
                    scanf("%d",&nuevoSueldo);
                }
                filtro->sueldo = nuevoSueldo;
            break;

        case 5:
                todoOk = -1;
                return todoOk;
            break;


        default:
            printf("Opcion invalida.");
            break;
        }

}else{
        todoOk = -1;
        return todoOk;
}

        todoOk = 1;

    }


    return todoOk;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{

    int todoOk = 0;
    char buffer[1][20];
    Employee* filtro = NULL;
    int flagFor = 0;
    int indice;

    if(pArrayListEmployee != NULL){

        printf("        ********        BAJA EMPLEADO       ********       \n\n\n");
        printf("Ingrese ID:");
        fflush(stdin);
        gets(buffer[0]);
        for(int i = 0;i<ll_len(pArrayListEmployee);i++){
            filtro = (Employee*) ll_get(pArrayListEmployee,i);
            if(filtro->id == atoi(buffer[0])){
                printf("confirma? \n1: si\n0: cancelar\nElija opcion:");
                scanf("%d",&flagFor);
                indice = i;
                break;

            }
        }
        if(flagFor == 1){
            ll_remove(pArrayListEmployee,indice);
            printf("Empleado dado de baja exitosamente\n\n");
        }else{
            printf("Se cancelo la operacion\n\n");
        }
            todoOk = 1;

        }



    return todoOk;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    Employee* aux;
    int flag = 0;
    if(pArrayListEmployee != NULL)
    {

        printf("Id   Nombre   HorasTrabajadas   Sueldo\n\n");
        for( int i=0; i < ll_len(pArrayListEmployee); i++)
        {
            aux = (Employee*) ll_get(pArrayListEmployee,i);
            mostrarEmpleado(aux);
            flag = 1;
        }
        if(flag == 0){
            printf("No hay empleados cargados para mostrar\n");
        }

        todoOk = 1;
    }
    return todoOk;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{

    int todoOk = 0;
    int opcion;
    char rta = 'n';
    int orden;

    if(pArrayListEmployee != NULL){

        printf("        ********        ORDENAR EMPLEADOS       ********       \n\n\n");
        printf("1- Ordenar por ID\n");
        printf("2- Ordenar por Nombre\n");
        printf("3- Ordenar por Horas Trabajadas\n");
        printf("4- Ordenar por Sueldo\n");
        printf("5- Volver al menu\n");
        printf("Elija opcion:");
        scanf("%d",&opcion);

        switch(opcion){

        case 1:
            printf("Ordena de forma descendente o ascendente?\n1 ascendente 0 descendente: ");
            scanf("%d",&orden);
            ll_sort(pArrayListEmployee,sortByID,orden);
            break;

        case 2:
            printf("Ordena de forma descendente o ascendente?\n1 ascendente 0 descendente: ");
            scanf("%d",&orden);
            ll_sort(pArrayListEmployee,sortByName,orden);
            break;

        case 3:
            printf("Ordena de forma descendente o ascendente?\n1 ascendente 0 descendente: ");
            scanf("%d",&orden);
            ll_sort(pArrayListEmployee,sortByHoras,orden);
            break;

        case 4:
            printf("Ordena de forma descendente o ascendente?\n1 ascendente 0 descendente: ");
            scanf("%d",&orden);
            ll_sort(pArrayListEmployee,sortBySueldo,orden);
            break;
        case 5:
            printf("Confirma? s/n ");
            fflush(stdin);
            rta = getchar();
            if(rta == 's'){
                break;
            }
            break;

        default:
            printf("Opcion incorrecta.\n");
            system("pause");
            break;
        }

     todoOk = 1;
}
        return todoOk;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{

    int todoOk = 0;
    int cant;
    FILE* f;
    Employee* aux = NULL;

    if(pArrayListEmployee!= NULL && path != NULL ){

        f = fopen(path,"w");
        if(f == NULL){
            return todoOk;
        }
        fprintf(f,"id,nombre,horasTrabajadas,sueldo\n");
        for(int i = 0; i < ll_len(pArrayListEmployee); i++){
            aux = ll_get(pArrayListEmployee,i);
            cant = fprintf(f,"%d,%s,%d,%d\n",aux->id,aux->nombre,aux->horasTrabajadas,aux->sueldo);
            if(cant < 1){
                return todoOk;
            }
        }
        fclose(f);
        todoOk = 1;
    }
    return todoOk;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    int cant;
    FILE* f;

    if(pArrayListEmployee!= NULL && path != NULL ){

        f = fopen(path,"wb");
        if(f == NULL){
            return todoOk;
        }
        for(int i = 0; i < ll_len(pArrayListEmployee); i++){
            cant = fwrite( ll_get(pArrayListEmployee,i) , sizeof(Employee)  ,   1  , f);
            if(cant < 1){
                return todoOk;
            }
        }
        fclose(f);
        todoOk = 1;
    }

    return todoOk;

}

int menuModificacion(){

    int opcion;

    printf("    *****   MENU MODIFICACION   *****\n\n\n");
    printf("1- Modificar ID\n");
    printf("2- Modificar Nombre\n");
    printf("3- Modificar Horas Trabajadas\n");
    printf("4- Modificar Sueldo\n");
    printf("5- Volver al menu\n");
    printf("Elija opcion: ");
    scanf("%d",&opcion);

    return opcion;
}

