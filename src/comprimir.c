#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzw.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *entrada;
    FILE *salida;
    unsigned char *datos_entrada;
    unsigned long tamano_entrada;
    unsigned long tamano_comprimido;
    unsigned char *datos_comprimidos;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "rb");
    if (!entrada) {
        perror("Error al abrir el archivo de entrada");
        return 1;
    }

    /* Obtener el tamaño del archivo de entrada */
    fseek(entrada, 0, SEEK_END);
    tamano_entrada = (unsigned long)ftell(entrada);
    fseek(entrada, 0, SEEK_SET);

    /* Leer el archivo de entrada */
    datos_entrada = (unsigned char *)malloc(tamano_entrada);
    if (!datos_entrada) {
        perror("Error al asignar memoria");
        fclose(entrada);
        return 1;
    }
    fread(datos_entrada, 1, tamano_entrada, entrada);
    fclose(entrada);

    /* Comprimir los datos */
    lzw_compress(8, tamano_entrada, datos_entrada, &tamano_comprimido, &datos_comprimidos);
    free(datos_entrada);

    /* Escribir el archivo comprimido */
    salida = fopen(argv[2], "wb");
    if (!salida) {
        perror("Error al abrir el archivo de salida");
        free(datos_comprimidos);
        return 1;
    }
    fwrite(datos_comprimidos, 1, tamano_comprimido, salida);
    fclose(salida);
    free(datos_comprimidos);

    return 0;
}

