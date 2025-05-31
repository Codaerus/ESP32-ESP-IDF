#include <stdio.h>
#include <string.h>
struct Humano{
    int edad;
    char nombre[30];
    struct Estudiante{
        int matricula;
        float promedio;
    };
    struct Estudiante e;
};
void imprimirDatos(struct Humano *p){
    printf("El nombre es %s\n", p->nombre);
    printf("La edad es %d\n", p->edad);
    printf("El codigo de alumno es %d y su promedio es %.1f",p->e.matricula,p->e.promedio);
}
struct Humano crearHumano(int e, char *n, int m, float p){
    struct Humano h;
    h.edad = e;
    strcpy(h.nombre,n);
    h.e.matricula = m;
    h.e.promedio = p;
    return h;
}
void main(){
    struct Humano juan = crearHumano(27,"Juan",1234,14.0);
    imprimirDatos(&juan);
    return;
}
