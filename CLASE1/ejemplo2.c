#include <stdio.h>
struct Humano{
    int edad;
    char nombre[30];
};

void imprimirDatos(struct Humano p){
    printf("El nombre es %s\n", p.nombre);
    printf("La edad es %d\n", p.edad);
}

void main(){
    struct Humano juan = {27,"Juan"};
    imprimirDatos(juan);
    return;
}
