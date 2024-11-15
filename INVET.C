#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define long 20

int opcion, confirmacion, encontrado, i, j, cantidad_vender, inten = 1;
char ch;
char busqueda[100];


struct veri {
    char auser[10], apass[20];
} usuario;

struct producto {
    char codigo[10];
    char nombre[long];
    char descripcion[100];
    char unidad[20];
    char fecha_venc[10];
    int precio;
    int cantidad;
} pro;

struct cliente {
    char nombre[20];
    char direccion[80];
    char codigo[20];
    char telefono[20];
    int credito;
} cli;



struct producto inventario[100];
struct cliente clientes[100];


int total_productos = 0, total_clientes = 0;

/*PRUEBAS*/

void cargar_total_productos(void) {
    FILE *pc = fopen("c:\\tc20\\product\\total_productos.txt", "r");

    if (pc != NULL) {
        fscanf(pc, "%d", &total_productos);
        fclose(pc);
    }
}

void cargar_productos(void) {
    FILE *pa;
    pa = fopen("c:\\tc20\\product\\productos.txt", "r");

    if (pa == NULL) {
        printf("No se pudo abrir el archivo de productos.\n");
        getch();
        return;
    }

    while (fscanf(pa, "\n%s\n%s\n%d\n%d\n%s\n%s\n%s\n", 
        inventario[total_productos].nombre,
        &inventario[total_productos].precio,
        &inventario[total_productos].cantidad,
        inventario[total_productos].unidad,
        inventario[total_productos].descripcion,
		inventario[total_productos].fecha_venc,
		inventario[total_productos].codigo) != EOF) {

        total_productos++;
    }

    fclose(pa);
}

void cargar_clientes(void) {
    FILE *pa;
    pa = fopen("c:\\tc20\\product\\clientes.txt", "r");

    if (pa == NULL) {
        printf("No se pudo abrir el archivo de clientes.\n");
        getch();
        return;
    }

    while (fscanf(pa, "%s\n%s\n%s\n%s\n%d\n", 
        clientes[total_clientes].codigo,
        clientes[total_clientes].nombre,
        clientes[total_clientes].telefono,
        clientes[total_clientes].direccion,
        &clientes[total_clientes].credito) != EOF) {

        total_clientes++;
    }

    fclose(pa);
}

/**/

void agregar_cliente(void) {
    FILE *pa;
    pa = fopen("c:\\tc20\\product\\clientes.txt", "a+");

    if (pa == NULL) {
        printf("No se pudo abrir el archivo.\n");
        getch();
        return;
    }
    
    clrscr();

    if (total_clientes >= 100) {
        printf("No se pueden agregar mas clientes.\n");
        getch();
        return;
    }

    printf("Ingrese el nombre del cliente: ");
    scanf(" %[^\n]", clientes[total_clientes].nombre);
    printf("Ingrese el telefono del cliente: ");
    scanf(" %[^\n]", clientes[total_clientes].telefono);
    printf("Ingrese la direccion del cliente: ");
    scanf(" %[^\n]", clientes[total_clientes].direccion);
    printf("Ingrese el credito del cliente: ");
    scanf("%d", &clientes[total_clientes].credito);
    printf("Ingrese el codigo del cliente: ");
    scanf("%s", clientes[total_clientes].codigo);

    fprintf(pa, "%s\n", clientes[total_clientes].codigo);
    fprintf(pa, "%s\n", clientes[total_clientes].nombre);
    fprintf(pa, "%s\n", clientes[total_clientes].telefono);
    fprintf(pa, "%s\n", clientes[total_clientes].direccion);
    fprintf(pa, "%d\n", clientes[total_clientes].credito);

    total_clientes++;
    fclose(pa);
   
    printf("Cliente agregado exitosamente.\n");
    getch();
}

void mostrar_clientes(void) {
    int i;

    clrscr();

    if (total_clientes == 0) {
        printf("No hay clientes registrados.\n");
        getch();
        return;
    }

    printf("Lista de Clientes Registrados:\n\n");

    for (i = 0; i < total_clientes; i++) {
        printf("Cliente #%d\n", i + 1);
        printf("Nombre: %s\n", clientes[i].nombre);
		printf("Telefono: %s\n", clientes[i].telefono);
        printf("Direccion: %s\n", clientes[i].direccion);
        printf("Credito: %d\n", clientes[i].credito);
        printf("Codigo: %s\n", clientes[i].codigo);
        printf("--------------------------------------------------------------------------------\n");
    }

    getch();
}


void agregar_producto(void) {
    FILE *pa, *pc;
    pa = fopen("c:\\tc20\\product\\productos.txt", "a+");
    pc = fopen("c:\\tc20\\product\\total_productos.txt", "w+");
    clrscr();

    if (pa == NULL) {  
        printf("Error al abrir el archivo.\n");
        getch();
        return;
    }

    if (total_productos >= 100) {
        printf("No se pueden agregar mas productos.\n");
        return;
    }

    printf("Ingrese el nombre del producto: ");
    scanf(" %[^\n]", inventario[total_productos].nombre);
    
    printf("Ingrese el precio del producto: ");
    scanf("%d", &inventario[total_productos].precio);
    
    printf("Ingrese la cantidad del producto: ");
    scanf("%d", &inventario[total_productos].cantidad);
	
    printf("Ingrese la unidad de medida: ");
    scanf(" %[^\n]", inventario[total_productos].unidad);
    
    printf("Ingrese la descripcion del producto: ");
    scanf(" %[^\n]", inventario[total_productos].descripcion);
    
    printf("Ingrese la fecha de vencimiento (DD/MM/AAAA): ");
    scanf(" %[^\n]", inventario[total_productos].fecha_venc);
    
    printf("Ingrese el codigo del producto: ");
    scanf("%s", inventario[total_productos].codigo);
    

    /*esto es para guardar en el archivo*/

    fprintf(pa, "%s\n", inventario[total_productos].nombre);
    fprintf(pa, "%d\n", inventario[total_productos].precio);
    fprintf(pa, "%d\n", inventario[total_productos].cantidad);
    fprintf(pa, "%s\n", inventario[total_productos].unidad);
    fprintf(pa, "%s\n", inventario[total_productos].descripcion);
    fprintf(pa, "%s\n", inventario[total_productos].fecha_venc);
    fprintf(pa, "%s\n", inventario[total_productos].codigo);

    
    total_productos++;
    fprintf(pc, "%d", total_productos);
    fclose(pc);
    fclose(pa);

    printf("Producto agregado exitosamente.\n");
    getch();
}

void buscar_producto(void) {
    clrscr();

    printf("Ingrese el nombre o el codigo del producto: ");
    scanf("%s", busqueda);
    encontrado = 0;

    for ( i = 0; i < total_productos; i++) {
        if (strcmp(inventario[i].nombre, busqueda) == 0 || strcmp(inventario[i].codigo, busqueda) == 0) {
            encontrado = 1;
            printf("Producto encontrado:\n\n");
            printf("Nombre: %s\n", inventario[i].nombre);
            printf("Precio: %d\n", inventario[i].precio);
            printf("Cantidad: %d\n", inventario[i].cantidad);
            printf("Unidad: %s\n", inventario[i].unidad);
            printf("Descripcion: %s\n", inventario[i].descripcion);
            printf("Fecha de vencimiento: %s\n", inventario[i].fecha_venc);
            printf("Codigo: %s\n", inventario[i].codigo);
            getch();

        }
    }

    if(!encontrado){
        printf("Producto no encontrado.\n");
        getch();
    }
}

void actualizar_producto(void) {
    clrscr();

    printf("Ingrese el nombre o el codigo del producto que desea actualizar: ");
    scanf("%s", busqueda);
    encontrado = 0;

    for (i = 0; i < total_productos; i++) {
        if (strcmp(inventario[i].nombre, busqueda) == 0 || strcmp(inventario[i].codigo, busqueda) == 0) {
            encontrado = 1;
            printf("Producto encontrado. Ingrese los nuevos datos:\n");
            printf("Nuevo nombre (actual: %s): ", inventario[i].nombre);
            scanf("%s", inventario[i].nombre);
			printf("Nuevo precio (actual: %d): ", inventario[i].precio);
            scanf("%d", &inventario[i].precio);
			printf("Nueva cantidad (actual: %d): ", inventario[i].cantidad);
            scanf("%d", &inventario[i].cantidad);
            printf("Nueva unidad de medida (actual: %s): ", inventario[i].unidad);
            scanf("%s", inventario[i].unidad);
            printf("Nueva descripcion (actual: %s): ", inventario[i].descripcion);
            scanf(" %[^\n]", inventario[i].descripcion);
            printf("Nueva fecha de vencimiento (actual: %s): ", inventario[i].fecha_venc);
            scanf(" %[^\n]", inventario[i].fecha_venc);
            printf("Producto actualizado exitosamente.\n");
            getch();

        }
    }


    if(!encontrado){
        printf("Producto no encontrado.\n");
        getch();
    }
}

void eliminar_producto(void){
    clrscr();
    printf("Ingrese el nombre o el codigo del producto que desea eliminar: ");
    scanf("%s", busqueda);
    encontrado = 0;

    for (i = 0; i < total_productos; i++) {
        if (strcmp(inventario[i].nombre, busqueda) == 0 || strcmp(inventario[i].codigo, busqueda) == 0) {
            encontrado = 1;
            printf("Producto encontrado: %s. Esta seguro que desea eliminarlo? (1. Si / 2. No): \n", inventario[i].nombre);
            scanf("%d", &confirmacion);

            if (confirmacion == 1) {
                for ( j = i; j < total_productos - 1; j++) {
                    inventario[j] = inventario[j + 1];
                }
                total_productos--;
                printf("\nProducto eliminado exitosamente.\n");
            } else {
                printf("\nEliminacion cancelada.\n");
            }
            getch();

        }
    }

   if (!encontrado) {
        printf("Producto no encontrado.\n");
        getch();
    }
}

void ver_productos(void) {
    clrscr();
    if (total_productos == 0) {
        printf("No hay productos en el inventario.\n");
        getch();
    }

    for (i = 0; i < total_productos; i++) {
        
        printf("Nombre: %s\n", inventario[i].nombre);
        printf("Precio: %d\n", inventario[i].precio);
        printf("Cantidad: %d\n", inventario[i].cantidad);
        printf("Unidad: %s\n", inventario[i].unidad);
        printf("Descripcion: %s\n", inventario[i].descripcion);
        printf("Fecha de vencimiento: %s\n", inventario[i].fecha_venc);
        printf("Codigo: %s\n", inventario[i].codigo);
        printf("--------------------------------------------------------------------------------");
    }

    getch();
}

void vender_producto(void){
    clrscr();

    printf("Ingrese el nombre o el codigo del producto que desea vender: ");
    scanf("%s", busqueda);

    encontrado = 0;

    for (i = 0; i < total_productos; i++) {
        if (strcmp(inventario[i].nombre, busqueda) == 0 || strcmp(inventario[i].codigo, busqueda) == 0) {
            encontrado = 1;
            printf("Producto encontrado: %s\n", inventario[i].nombre);
            printf("Cantidad disponible: %d\n", inventario[i].cantidad);
            printf("Ingrese la cantidad que desea vender: ");
            scanf("%d", &cantidad_vender);

            if (cantidad_vender > inventario[i].cantidad) {
                printf("No hay suficiente cantidad en inventario. Cantidad disponible: %d\n", inventario[i].cantidad);
            } else {
                inventario[i].cantidad -= cantidad_vender;
                printf("Venta exitosa. Ha vendido %d unidades de %s.\n", cantidad_vender, inventario[i].nombre);
            }
            getch();

        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
    getch();
}

void menu_inventario(void) {

    while (1) {
        clrscr();
        printf("* INVENTARIO *\n\n");
        printf("1. Agregar producto\n");
        printf("2. Buscar producto\n");
        printf("3. Actualizar\n");
        printf("4. Eliminar\n");
        printf("5. Ver\n");
        printf("6. Vender\n");
        printf("7. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                agregar_producto();
                break;
            case 2:
                buscar_producto();
                break;
            case 3:
                actualizar_producto();
                break;
            case 4:
                eliminar_producto();
                break;
            case 5:
                ver_productos();
                break;
            case 6:
                vender_producto();
                break;
            case 7:
                return;
            default:
                printf("Opcion invalida.\n");
                getch();
        }
    }
}

void menu_clientes(void){
    while (1)
    {
    clrscr();
    printf("1. Agregar cliente\n");
    printf("2. Ver clientes\n");
    scanf("%d", &opcion);
        switch (opcion)
        {
            case 1:
                agregar_cliente();
                    break;
            case 2:
                mostrar_clientes();
                break;
            case 3:
                return;
            default:
                    printf("Opcion invalida");
                    break;
 
               }
    }
}

void menu_principal(void) {
    while (1) {
        clrscr();
        printf("Menu Principal\n");
        printf("1. Inventario\n");
        printf("2. Clientes\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch(opcion) {
            case 1:
                menu_inventario();
                break;
            case 2:
                menu_clientes();
                break;
            case 3:
                return;
            default:
                printf("Opcion invalida.\n");
                getch();
        }
    }
}

void inicio(void){
    while(inten <= 3){
        clrscr();
        printf("intento: %d\n\n", inten);
	    printf("Ingrese su usuario: ");
	    gets(usuario.auser);
	    printf("Ingrese la contrasena: ");
	    while (i < 100 && (ch = getch()) != '\r') {
            usuario.apass[i] = ch;
            printf("*");
            i++;
        }
        usuario.apass[i] = '\0';

        if(strcmp(usuario.auser, "admin") == 0){
            if(strcmp(usuario.apass, "euclides") == 0){
                
                menu_principal();
                inten = 4;
            }else{
                printf("\nCONTRASENA INCORRECTA");
                inten++;
                getch();
            }
        }else{
            printf("\nUSUARIO INCORRECTO");
            inten++;
            getch();
        }
    }
}

int main() {
    cargar_total_productos();
    cargar_clientes();
    cargar_productos();
    inicio();
    return 0;
}
