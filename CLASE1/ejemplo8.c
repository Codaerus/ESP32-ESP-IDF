#include <stdio.h>
#include <string.h>

typedef struct Humano{
    int edad;
    char nombre[30];
    union{
        char telefono[15];
        char correo[40];
    }contacto;
    struct {
        int matricula;
        float promedio;
    } e;
    void (*s)(const char *n);
}Humano;
//typedef struct Humano Humano;

void saludar(const char *n){
    printf("Hola, mi nombre es %s\n", n);
}
void imprimirDatos(struct Humano *p){
    printf("El nombre es %s\n", p->nombre);
    printf("La edad es %d\n", p->edad);
    printf("El codigo de alumno es %d y su promedio es %.1f\n",p->e.matricula,p->e.promedio);
}
Humano crearHumano(int e, char *n, int m, float p, char *t){
    Humano h;
    h.edad = e;
    strcpy(h.nombre,n);
    h.e.matricula = m;
    h.e.promedio = p;
    strcpy(h.contacto.telefono,t);
    h.s = saludar;
    return h;
}
void main(){
    Humano juan = crearHumano(27,"Juan",1234,14.0,"925147621");
    imprimirDatos(&juan);
    printf("El telefono es %s\n",juan.contacto.telefono);
    strcpy(juan.contacto.correo,"juan27@gmail.com");
    printf("El telefono es %s\n",juan.contacto.telefono);
    juan.s(juan.nombre);
    return;
}    
