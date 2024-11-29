#include <stdio.h>
#include <conio.h>

int opcion;

int val(int a){
    while (scanf("%d", &a) != 1 || a < 0) {
        while (getchar() != '\n'); 
        printf("Entrada no valida. Por favor, ingrese un numero entero positivo: ");
    }
    return a;
}

void agregarpro(void){
    clrscr();
    printf("* QUE HACE 'AGREGAR PRODUCTO' *\n\n");
    printf("Como su nombre lo indica, esta opcion es para agregar productos, en donde se nos va a pedir el nombre, la unidad que se refiere a unidad de medida, mg en caso de pastillas ml en caso de liquidos, su descripcion en donde se tiene qe poner el para que es bueno este medicamento, la fecha de vencimiento donde solo es necesario el mes y el ano, el codigo con el que se va a diferenciar para una busqueda mas rapida, el precio y la cantidad en el inventario\n");
    printf("\n* IMPORTANTE *\n");
    printf("*- Si por error se pone un numero negativo o una letra el programa esta preparado para ese tipo de situaciones y simplemente te pedira nuevamente el dato");
    printf("\n*- Tampoco se podra poner un codigo de producto ya existente");
    getch();
}

void buscarpro(void){
    clrscr();
    printf("* QUE HACE 'BUSCAR PRODUCTO' *\n\n");
    printf("Dentro de esta opcion como bien dice, podemos buscar un producto existente atravez de su nombre o su codigo, pero es mas recomendable hacerlo por su codigo por posibles fallas ortograficas\n");
    getch();
}

void actualizarpro(void){
    clrscr();
    printf("* QUE HACE 'ACTUALIZAR PRODUCTO' *\n\n");
    printf("En esta opcion vamos a poder actualizar la informacion de un producto a esepcion del codigo\n");
    getch();
}

void eliminarpro(void){
    clrscr();
    printf("* QUE HACE 'ELIMINAR PRODUCTO' *\n\n");
    printf("Sinedo evidente, en esta opcion vamos a poder eliminar toda la informacion de un producto\n");
    printf("\n* IMPORTANTE *\n");
    printf("El producto que se elimine no se podra recuperar de ninguna manera y se tendra que ingresar todos los datos del producto");
    getch();
}

void venderpro(void){
    clrscr();
    printf("* QUE HACE 'VENDER PRODUCTO' *\n\n");
    printf("En este apartado es claro que se relizara una venta, pero hay algunos aspectoas a aclarar.\n");
    printf("\n1. Con los clientes se trabajan con creditos, en el apartado de las opciones de cliente de 'Ayuda' podras encontrar mas detalles\n");
    printf("\n2. Se le pedira que ingrese el codigo o el nombre del producto que desea vender, le dira cuanto de este producto hay disponible su precio.\n");
    printf("\n3. Luego se le pedira que ingrese el nombre o el codigo del cliente previamente registrado al que se le esta realizando el proceso de venta\n");
    printf("\n4. Se hara una revision rapida al usuario sobre el estado de su cedito\n");
    printf("\n5. En el caso de que no cuente con credito suficiente se tendra la opcion de hacer una recarga de ecredito en el momento\n");
    printf("\n6. Lugo de esto la compra finalizara con exito\n");
    getch();
}

void verpro(void){
    clrscr();
    printf("* QUE HACE 'VER PRODUCTOS' *\n\n");
    printf("En esta ocion se va a poder visualizar todos los productos y sus datos mas relevantes");
    getch();
}

/*CLIENTES*/

void agrecli(void){
    clrscr();
    printf("* QUE HACE 'AGREGAR CLIENTES' *\n\n");
    printf("En este opcion se prodra crear un nuevo cliente, nos pediran los datos de este cliente como su nombre completo, su numero celular, su direccion (para futiras entregas a domicilio), su codigo distinvo y el credito con el que desea aperturar su cuente en la farmacia\n");
    printf("\n* IMPORTANTE *\n");
    printf("Al ingresar el credito sera imposible poner numeros negativos o caracteres, el marjen de error es minimo");
    getch();
}

void buscarcli(void){
    clrscr();
    printf("* QUE HACE 'BUSCAR CLIENTES' *\n\n");
    printf("En esta opcion podremos buscar clientes previamentes registrados y poder ver su estado e informacion");
    getch();
}

void actuacli(void){
    clrscr();
    printf("* QUE HACE 'ACTUALIZAR CLIENTE' *\n\n");
    printf("En esta opcion se podra actualizar todos los datos del cliente seleccionado a esepcion de su codigo");
    getch();
}

void mostrarcli(void){
    clrscr();
    printf("* QUE HACE 'VER CLIENTES' *\n\n");
    printf("En esta opcion lo unico que se podra hacer es visualizar a todoso los clientes y sus datos mas relevantes\n");
    getch();
}

void eliminarcli(void){
    clrscr();
    printf("* QUE HACE 'ELIMINAR CLIENTES' *\n\n");
    printf("En esta opcion se podra eliminar a un cliente previamente registrado, para hacerlo se tendra que ingresar el nombre del cleinte o su codigo y luego hacer una confirmacion para poder finalizar con esta accion");
    getch();
}

void ayudapro(void){
    clrscr();
    printf("Menu de Ayuda Para Productos\n");
    printf("1. Agregar producto\n");
    printf("2. Buscar producto\n");
    printf("3. Actualizar\n");
    printf("4. Eliminar\n");
    printf("5. Ver\n");
    printf("6. Vender\n");
    printf("7. Volver\n");
    printf("Seleccione una opcion: \n");
    opcion = val(opcion);

    switch(opcion){
        case 1:
            agregarpro();
            break;
        case 2:
            buscarpro();
            break;
        case 3:
            actualizarpro();
            break;
        case 4:
            eliminarpro();
            break;
        case 5:
            verpro();
            break;
        case 6:
            venderpro();
            break;
        case 7:
            return;
        default:
            printf("Opcion invalida.\n");
            getch();
    }
}

void menucli(void){
    clrscr();
    printf("Menu de Ayuda Para Clientes\n");
    printf("1. Agregar cliente\n");
    printf("2. Buscar clientes\n");
    printf("3. Actualizar cliente\n");
    printf("4. Ver clientes\n");
    printf("5. Eliminar cliente\n");
    printf("6. Volver");
    opcion = val(opcion);

    switch(opcion){
        case 1:
            agrecli();
            break;
        case 2:
            buscarcli();
            break;
        case 3:
            actuacli();
            break;
        case 4:
            mostrarcli();
            break;
        case 5:
            eliminarcli();
            break;
        case 6:
            return;
        default:
           printf("Opcion invalida.\n");
           getch(); 
    }
}

void menuayuda(void){
    clrscr();
    printf("Menu de Ayuda\n");
    printf("1. Ayuda con Productos\n");
    printf("2. Ayuda con Clientes\n");
    printf("3. Volver\n");
    opcion = val(opcion);

    switch(opcion){
        case 1:
            ayudapro();
            break;
        case 2:
            menucli();
            break;
        case 3:
            return;
        default:
            printf("Opcion invalida.\n");
           getch(); 
    }
}

