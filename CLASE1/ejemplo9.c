#include <stdio.h>
#include <string.h>

typedef enum{
    TELEFONO,
    CORREO
}TipoContacto;

typedef struct Humano{
    int edad;
    char nombre[30];
    TipoContacto tipoContacto;
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
    if(p->tipoContacto == TELEFONO){
        printf("Telefono: %s\n", p->contacto.telefono);
    }
    else{
        printf("Correo: %s\n", p->contacto.correo);
    }
}
Humano crearHumano(int e, char *n, int m, float p, char *t, TipoContacto tipo){
    Humano h;
    h.edad = e;
    strcpy(h.nombre,n);
    h.e.matricula = m;
    h.e.promedio = p;
    if (tipo == TELEFONO){
        strcpy(h.contacto.telefono,t);
    }
    else{
        strcpy(h.contacto.correo,t);
    }
    h.s = saludar;
    h.tipoContacto = tipo;
    return h;
}
void main(){
    Humano juan = crearHumano(27,"Juan",1234,14.0,"987452168",TELEFONO);
    imprimirDatos(&juan);
    //printf("El telefono es %s\n",juan.contacto.telefono);
    //strcpy(juan.contacto.correo,"juan27@gmail.com");
    //printf("El telefono es %s\n",juan.contacto.telefono);
    juan.s(juan.nombre);
    return;
}    
