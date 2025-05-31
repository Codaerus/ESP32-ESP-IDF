#include <stdio.h>
#include <string.h>
struct Humano{
    int edad;
    char nombre[30];
};

void imprimirDatos(struct Humano *p){
    printf("El nombre es %s\n", p->nombre);
    printf("La edad es %d\n", p->edad);
}
struct Humano crearHumano(int e, char *n){
    struct Humano h;
    h.edad = e;
    strcpy(h.nombre,n);
    return h;
}
void main(){
    struct Humano juan = crearHumano(27,"Juan");
    imprimirDatos(&juan);
    return;
}
