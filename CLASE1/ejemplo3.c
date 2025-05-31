#include <stdio.h>
#include <string.h>
struct Humano{
    int edad;
    char nombre[30];
    float peso;
};

void imprimirDatos(struct Humano *p){
    printf("El nombre es %s\n", p->nombre);
    printf("La edad es %d\n", p->edad);
}

void main(){
    struct Humano juan = {
        .edad = 27,
        .peso = 70.5
    };
    strcpy(juan.nombre,"Juan");
    imprimirDatos(&juan);
    return;
}
