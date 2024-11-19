#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define long 20

int opcion, confirmacion, encontrado, i, j, k, l, opc, diferencia, cantidad_vender, inten = 1, total_venta, pago, efectivo;
char ch;
char busqueda[100];

FILE *pa;

struct veri {
    char auser[10], apass[20];
} usuario;

struct producto {
    char codigo[5];
    char nombre[long];
    char descripcion[100];
    char unidad[6];
    char fecha_venc[10];
    int precio;
    int cantidad;
} pro;

struct cliente {
    char nombre[20];
    char direccion[80];
    char codigo[5];
    char telefono[20];
    int credito;
} cli;

struct producto inventario[100];
struct cliente clientes[100];
int total_productos = 0, total_clientes = 0;

int validar(int a){
    while (scanf("%d", &a) != 1 || a < 0) {
        while (getchar() != '\n'); 
        printf("Entrada no valida. Por favor, ingrese un numero entero positivo: ");
    }
    return a;
}

/*PRUEBAS*/
void cargar_productos(void) {
    FILE *pa;
    pa = fopen("c:\\tc20\\product\\productos.txt", "r");
    if (pa == NULL) {
        printf("No se pudo abrir el archivo de productos.\n");
        getch();
        return;
    }

    while (fgets(inventario[total_productos].nombre, sizeof(inventario[total_productos].nombre), pa)) {
        inventario[total_productos].nombre[strcspn(inventario[total_productos].nombre, "\n")] = '\0';
        fgets(inventario[total_productos].unidad, sizeof(inventario[total_productos].unidad), pa);
        inventario[total_productos].unidad[strcspn(inventario[total_productos].unidad, "\n")] = '\0';
        fgets(inventario[total_productos].descripcion, sizeof(inventario[total_productos].descripcion), pa);
        inventario[total_productos].descripcion[strcspn(inventario[total_productos].descripcion, "\n")] = '\0';
        fgets(inventario[total_productos].fecha_venc, sizeof(inventario[total_productos].fecha_venc), pa);
        inventario[total_productos].fecha_venc[strcspn(inventario[total_productos].fecha_venc, "\n")] = '\0';
        fgets(inventario[total_productos].codigo, sizeof(inventario[total_productos].codigo), pa);
        inventario[total_productos].codigo[strcspn(inventario[total_productos].codigo, "\n")] = '\0';
        fscanf(pa, "%d", &inventario[total_productos].precio);
        fscanf(pa, "%d\n", &inventario[total_productos].cantidad);
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

   while (fgets(clientes[total_clientes].nombre, sizeof(clientes[total_clientes].nombre), pa)) {
        clientes[total_clientes].nombre[strcspn(clientes[total_clientes].nombre, "\n")] = '\0';
        fgets(clientes[total_clientes].telefono, sizeof(clientes[total_clientes].telefono), pa);
        clientes[total_clientes].telefono[strcspn(clientes[total_clientes].telefono, "\n")] = '\0';
        fgets(clientes[total_clientes].direccion, sizeof(clientes[total_clientes].direccion), pa);
        clientes[total_clientes].direccion[strcspn(clientes[total_clientes].direccion, "\n")] = '\0';
        fgets(clientes[total_clientes].codigo, sizeof(clientes[total_clientes].codigo), pa);
        clientes[total_clientes].codigo[strcspn(clientes[total_clientes].codigo, "\n")] = '\0';
        fscanf(pa, "%d\n", &clientes[total_clientes].credito);
        total_clientes++;
    }
    
    fclose(pa);
}
/**/
void agregar_cliente(void) {
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
    printf("Ingrese el codigo del cliente: ");
    scanf(" %[^\n]", clientes[total_clientes].codigo);
    printf("Ingrese el credito del cliente: ");
    clientes[total_clientes].credito = validar(clientes[total_clientes].credito);
    
    fprintf(pa, "%s\n", clientes[total_clientes].nombre);
    fprintf(pa, "%s\n", clientes[total_clientes].telefono);
    fprintf(pa, "%s\n", clientes[total_clientes].direccion);
    fprintf(pa, "%s\n", clientes[total_clientes].codigo);
    fprintf(pa, "%d\n", clientes[total_clientes].credito);
    
    total_clientes++;
    fclose(pa);
   
    printf("Cliente agregado exitosamente.\n");
    getch();
}

void mostrar_clientes(void) {
    clrscr();
    if (total_clientes == 0) {
        printf("No hay clientes registrados.\n");
        getch();
        return;
    }

    printf("Lista de Clientes Registrados:\n");
    printf("%-15s | %-10s | %-8s | %-8s\n", "Nombre", "Telefono", "Codigo", "Credito");
    printf("--------------------------------------------------------------------------------");
    for (i = 0; i < total_clientes; i++) {
        printf("%-15s | %-10s | %-8s | %-8d\n",
        clientes[i].nombre,
		clientes[i].telefono,
        clientes[i].codigo,
        clientes[i].credito);
        printf("--------------------------------------------------------------------------------");
    }
    getch();
}

void buscar_clientes(void){
    clrscr();
    printf("Ingrese el nombre o el codigo del cliente: ");
    scanf("%s", busqueda);
    encontrado = 0;

     for ( i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].nombre, busqueda) == 0 || strcmp(clientes[i].codigo, busqueda) == 0) {
            encontrado = 1;
            printf("Producto encontrado:\n\n");
            printf("Nombre: %s\n", clientes[i].nombre);
            printf("Telefono: %s\n", clientes[i].telefono);
            printf("Direccion: %s\n", clientes[i].direccion);
            printf("Codigo: %s\n", clientes[i].codigo);
            printf("Credito: %d\n", clientes[i].credito);
            getch();
        }
    }

    if(!encontrado){
        printf("Cliente no encontrado.\n");
        getch();
    }
}

void actualizar_clinete(void){
    clrscr();
    printf("Ingrese el nombre o el codigo del producto que desea actualizar: ");
    scanf("%s", busqueda);
    encontrado = 0;

     for (i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].nombre, busqueda) == 0 || strcmp(clientes[i].codigo, busqueda) == 0) {
            encontrado = 1;
            printf("Clinete encontrado. Ingrese los nuevos datos:\n");
            printf("Nuevo nombre (actual: %s): ", clientes[i].nombre);
            scanf(" %[^\n]", clientes[i].nombre);  
            printf("Nuevo numero celular (actual: %s): ", clientes[i].telefono);
            scanf(" %[^\n]", clientes[i].telefono);
            printf("Nueva direccion (actual: %s): ", clientes[i].direccion);
            scanf(" %[^\n]", clientes[i].direccion);
            printf("Nuevo codigo (actual: %s): ", clientes[i].codigo);
            scanf(" %[^\n]", clientes[i].codigo);
            printf("Nuevo credito (actual: %d): ", clientes[i].credito);
			clientes[total_clientes].credito = validar(clientes[total_clientes].credito);
     
            pa = fopen("c:\\tc20\\product\\clientes.txt", "w");  
            if (pa == NULL) {
                printf("Error al abrir el archivo de productos.\n");
                getchar();
                return;
            }
            for (i = 0; i < total_clientes; i++) {
                fprintf(pa, "%s\n", clientes[total_clientes].nombre);
                fprintf(pa, "%s\n", clientes[total_clientes].telefono);
                fprintf(pa, "%s\n", clientes[total_clientes].direccion);
                fprintf(pa, "%s\n", clientes[total_clientes].codigo);
                fprintf(pa, "%d\n", clientes[total_clientes].credito);
            }fclose(pa);
            printf("Producto actualizado exitosamente.\n");
            getchar(); 
            return;
        }
    }
}

void eliminar_cliente(void){
    clrscr();
    printf("Ingrese el nombre o el codigo del clinete que desea eliminar: ");
    scanf("%s", busqueda);
    encontrado = 0;

    for (i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].nombre, busqueda) == 0 || strcmp(clientes[i].codigo, busqueda) == 0) {
            encontrado = 1;
            printf("Cliente encontrado: %s. Esta seguro que desea eliminarlo? (1. Si / 2. No): \n", clientes[i].nombre);
            scanf("%d", &confirmacion);

            if (confirmacion == 1) {
                for ( j = i; j < total_clientes - 1; j++) {
                    clientes[j] = clientes[j + 1];
                }
                total_productos--;
                printf("\nCliente eliminado exitosamente.\n");
                pa = fopen("c:\\tc20\\product\\clientes.txt", "w");  
                if (pa == NULL) {
                    printf("Error al abrir el archivo de clientes.\n");
                    getchar();
                    return;
                }

                for (i = 0; i < total_clientes; i++) {
                    fprintf(pa, "%s\n", clientes[total_clientes].nombre);
                    fprintf(pa, "%s\n", clientes[total_clientes].telefono);
                    fprintf(pa, "%s\n", clientes[total_clientes].direccion);
                    fprintf(pa, "%s\n", clientes[total_clientes].codigo);
                    fprintf(pa, "%d\n", clientes[total_clientes].credito);
                }
                fclose(pa);
            } else {
                printf("\nEliminacion cancelada.\n");
            }
            getch();
        }
    }

   if (!encontrado) {
        printf("Cliente no encontrado.\n");
        getch();
    }
}

void agregar_producto(void) {
    FILE *pa;
    pa = fopen("c:\\tc20\\product\\productos.txt", "a+");
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
    printf("Ingrese la unidad de medida: ");
    scanf(" %[^\n]", inventario[total_productos].unidad);
    printf("Ingrese la descripcion del producto: ");
    scanf(" %[^\n]", inventario[total_productos].descripcion);
    printf("Ingrese la fecha de vencimiento (DD/MM/AAAA): ");
    scanf(" %[^\n]", inventario[total_productos].fecha_venc);
    printf("Ingrese el codigo del producto: ");
    scanf("%s", inventario[total_productos].codigo);
    printf("Ingrese el precio del producto: ");
    inventario[total_productos].precio = validar(inventario[total_productos].precio);
    printf("Ingrese la cantidad del producto: ");
    inventario[total_productos].cantidad = validar(inventario[total_productos].cantidad);
    
    /*esto es para guardar en el archivo*/
    fprintf(pa, "%s\n", inventario[total_productos].nombre);
    fprintf(pa, "%s\n", inventario[total_productos].unidad);
    fprintf(pa, "%s\n", inventario[total_productos].descripcion);
    fprintf(pa, "%s\n", inventario[total_productos].fecha_venc);
    fprintf(pa, "%s\n", inventario[total_productos].codigo);
    fprintf(pa, "%d\n", inventario[total_productos].precio);
    fprintf(pa, "%d\n", inventario[total_productos].cantidad);

    total_productos++;
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
            printf("Unidad: %s\n", inventario[i].unidad);
            printf("Descripcion: %s\n", inventario[i].descripcion);
            printf("Fecha de vencimiento: %s\n", inventario[i].fecha_venc);
            printf("Codigo: %s\n", inventario[i].codigo);
            printf("Precio: %d\n", inventario[i].precio);
            printf("Cantidad: %d\n", inventario[i].cantidad);
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
            scanf(" %[^\n]", inventario[i].nombre);  
            printf("Nueva unidad de medida (actual: %s): ", inventario[i].unidad);
            scanf(" %[^\n]", inventario[i].unidad);
            printf("Nueva descripcion (actual: %s): ", inventario[i].descripcion);
            scanf(" %[^\n]", inventario[i].descripcion);
            printf("Nueva fecha de vencimiento (actual: %s): ", inventario[i].fecha_venc);
            scanf(" %[^\n]", inventario[i].fecha_venc);
            printf("Nuevo codigo (actual: %s): ", inventario[i].codigo);
            scanf(" %[^\n]", inventario[i].codigo);
            printf("Nuevo precio (actual: %d): ", inventario[i].precio);
            inventario[total_productos].precio = validar(inventario[total_productos].precio);
            printf("Nueva cantidad (actual: %d): ", inventario[i].cantidad);
            inventario[total_productos].cantidad = validar(inventario[total_productos].cantidad);

            pa = fopen("c:\\tc20\\product\\productos.txt", "w");  
            if (pa == NULL) {
                printf("Error al abrir el archivo de productos.\n");
                getchar();
                return;
            }
            for (i = 0; i < total_productos; i++) {
                fprintf(pa, "%s\n", inventario[i].nombre);
                fprintf(pa, "%s\n", inventario[i].unidad);
                fprintf(pa, "%s\n", inventario[i].descripcion);
                fprintf(pa, "%s\n", inventario[i].fecha_venc);
                fprintf(pa, "%s\n", inventario[i].codigo);
                fprintf(pa, "%d\n", inventario[i].precio);
                fprintf(pa, "%d\n", inventario[i].cantidad);
            }

            fclose(pa);
            printf("Producto actualizado exitosamente.\n");
            getchar(); 
            return;
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
                pa = fopen("c:\\tc20\\product\\productos.txt", "w");  
                if (pa == NULL) {
                    printf("Error al abrir el archivo de productos.\n");
                    getchar();
                    return;
                }

                for (i = 0; i < total_productos; i++) {
                    fprintf(pa, "%s\n", inventario[i].nombre);
                    fprintf(pa, "%s\n", inventario[i].unidad);
                    fprintf(pa, "%s\n", inventario[i].descripcion);
                    fprintf(pa, "%s\n", inventario[i].fecha_venc);
                    fprintf(pa, "%s\n", inventario[i].codigo);
                    fprintf(pa, "%d\n", inventario[i].precio);
                    fprintf(pa, "%d\n", inventario[i].cantidad);
                }
                fclose(pa);
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

   printf("%-8s | %-10s | %-8s | %-8s | %-8s | %-15s\n", "Codigo", "Nombre", "Precio", "Cantidad", "Unidad", "Fecha Venc.");
    printf("--------------------------------------------------------------------------------\n");
    for (i = 0; i < total_productos; i++) {
        printf("%-8s | %-10s | %-8d | %-8d | %-10s | %-10s\n",
        inventario[i].codigo,
        inventario[i].nombre,
        inventario[i].precio,
        inventario[i].cantidad,
        inventario[i].unidad,
        inventario[i].fecha_venc);
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
            cantidad_vender = validar(cantidad_vender);
            if (cantidad_vender > inventario[i].cantidad) {
                printf("No hay suficiente cantidad en inventario. Cantidad disponible: %d\n", inventario[i].cantidad);
            } else {
                total_venta = cantidad_vender * inventario[i].precio;
                inventario[i].cantidad -= cantidad_vender;  
                printf("Ingrese el nombre o el codigo del cliente al que se le va a vender: ");
                scanf("%s", busqueda);
                encontrado = 0;                
                for (k = 0; k < total_clientes; k++) {
                    if (strcmp(clientes[k].nombre, busqueda) == 0 || strcmp(clientes[k].codigo, busqueda) == 0) {
                        encontrado = 1;
                        printf("Cliente encontrado: %s\n", clientes[k].nombre);
                        printf("Credito disponible: %d\n", clientes[k].credito);                    
                        if (clientes[k].credito >= total_venta) {                           
                            clientes[k].credito -= total_venta;                             
                            pa = fopen("c:\\tc20\\product\\clientes.txt", "w");
                            if (pa == NULL) {
                                printf("Error al abrir el archivo de clientes.\n");
                                return;
                            }
                            for ( l = 0; l < total_clientes; l++) {
								fprintf(pa, "%s\n", clientes[l].nombre);
								fprintf(pa, "%s\n", clientes[l].telefono);
								fprintf(pa, "%s\n", clientes[l].direccion);
								fprintf(pa, "%s\n", clientes[l].codigo);
								fprintf(pa, "%d\n", clientes[l].credito);
                            }
							fclose(pa);
                            pa = fopen("c:\\tc20\\product\\productos.txt", "w");
                            if (pa == NULL) {
                            printf("Error al abrir el archivo de productos.\n");
                            return;
                            }
				            for (j = 0; j < total_productos; j++) {
                                fprintf(pa, "%s\n", inventario[j].nombre);
                                fprintf(pa, "%s\n", inventario[j].unidad);
                                fprintf(pa, "%s\n", inventario[j].descripcion);
                                fprintf(pa, "%s\n", inventario[j].fecha_venc);
                                fprintf(pa, "%s\n", inventario[j].codigo);
                                fprintf(pa, "%d\n", inventario[j].precio);
                                fprintf(pa, "%d\n", inventario[j].cantidad);
                            }
                            fclose(pa);
                            printf("Venta exitosa. Ha vendido %d unidades de %s. Total venta: %d\n", cantidad_vender, inventario[i].nombre, total_venta);
                        } else {                            
                            diferencia = total_venta - clientes[k].credito;
                            printf("Credito insuficiente. Faltan %d para completar la compra.\n", diferencia);
                            printf("Desea pagar la diferencia en efectivo? (1 para si, 0 para no): ");
                            opc = validar(opc);
                            if (opc == 1) {
                                printf("Ingrese el monto en efectivo: ");
                                efectivo = validar(efectivo);
                                if (efectivo >= diferencia) {                                    
                                    clientes[k].credito = 0;  
									if (pa == NULL) {
                                        printf("Error al abrir el archivo de clientes.\n");
                                        return;
                                    }
                                    for ( l = 0; l < total_clientes; l++) {
										fprintf(pa, "%s\n", clientes[l].nombre);
										fprintf(pa, "%s\n", clientes[l].telefono);
										fprintf(pa, "%s\n", clientes[l].direccion);
										fprintf(pa, "%s\n", clientes[l].codigo);
										fprintf(pa, "%d\n", clientes[l].credito);
                                    }
									fclose(pa);
                                    pa = fopen("c:\\tc20\\product\\productos.txt", "w");
                                    if (pa == NULL) {
                                        printf("Error al abrir el archivo de productos.\n");
                                        return;
                                    }
				                    for (j = 0; j < total_productos; j++) {
                                        fprintf(pa, "%s\n", inventario[j].nombre);
                                        fprintf(pa, "%s\n", inventario[j].unidad);
                                        fprintf(pa, "%s\n", inventario[j].descripcion);
                                        fprintf(pa, "%s\n", inventario[j].fecha_venc);
                                        fprintf(pa, "%s\n", inventario[j].codigo);
                                        fprintf(pa, "%d\n", inventario[j].precio);
                                        fprintf(pa, "%d\n", inventario[j].cantidad);
                                    }
                                    fclose(pa);
                                    printf("Venta exitosa. El cliente ha pagado %d en efectivo.\n", efectivo);
                                    printf("Venta realizada: %d unidades de %s. Total venta: %d\n", cantidad_vender, inventario[i].nombre, total_venta);
                                    getch();
                                } else {
                                    printf("El monto en efectivo es insuficiente para cubrir la diferencia.\n");
                                    getch();
                                }
                            } else {
                                printf("Venta cancelada. El cliente no tiene suficiente credito ni desea pagar en efectivo.\n");
                                getch();
                            }
                        }
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Cliente no encontrado.\n");
                }
            }
            break;
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
        opcion = validar(opcion);
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
    printf("2. Buscar clientes\n");
    printf("3. Actualizar cliente\n");
    printf("4. Ver clientes\n");
    printf("5. Eliminar cliente\n");
    printf("6. Volver");
    opcion = validar(opcion);
        switch (opcion)
        {
            case 1:
                agregar_cliente();
                break;
            case 2:
                buscar_clientes();
                break;
            case 3:
                actualizar_clinete();
                break;
            case 4:
                mostrar_clientes();
                break;
            case 5:
                eliminar_cliente();
                break;
            case 6:
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
        opcion = validar(opcion);
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
    cargar_clientes();
    cargar_productos();
    inicio();
    return 0;
}
