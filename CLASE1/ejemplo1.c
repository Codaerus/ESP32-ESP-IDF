#include <stdio.h>
struct Humano{
    int edad;
    char nombre[30];
};
void main(){
    int n = 8;
    int *a = &n;

    printf("El valor es: %d\n",n);
    printf("El valor es: %d\n",*a);

    printf("La direccion es: %p\n",&n);
    printf("La direccion es: %p\n",a);

    struct Humano juan = {27,"Juan"};
    printf("El nombre es %s y la edad %d\n", juan.nombre,juan.edad);
    return;
}
