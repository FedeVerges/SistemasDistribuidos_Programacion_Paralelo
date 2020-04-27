#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
   char texto[20];
   int valor= 20;
   char numero[20];

   sprintf(numero, "%d",valor);
   strcpy(texto, numero);
   printf("hola el valor es: %s ", texto);
   return 0;
}