#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include "funciones_estudiante.h"
#include "constantes.h"
/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Checcacci
    Nombre: Franco
    DNI:43.386.577
    Entrega: SI.
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    (Sólo para grupos de tres integrantes)
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------

    Comentarios (opcionales) que deseen hacer al docente sobre el TP:

*/

/* Bitmap file format
 *
 * SECTION
 * Address:Bytes	Name
 *
 * HEADER:
 *	  0:	2		"BM" magic number
 *	  2:	4		file size
 *	  6:	4		junk
 *	 10:	4		Starting address of image data
 * BITMAP HEADER:
 *	 14:	4		header size
 *	 18:	4		width  (signed)
 *	 22:	4		height (signed)
 *	 26:	2		Number of color planes
 *	 28:	2		Bits per pixel
 *	[...]
 * [OPTIONAL COLOR PALETTE, NOT PRESENT IN 32 BIT BITMAPS]
 * BITMAP DATA:
 *	DATA:	X	Pixels
 */

void solucion(int argc, char* argv[]){
    // agregar lectura de argumentos.
    t_pixel *img;
    t_metadata header;



    //declarar y que la funcion retorne header e imagen
    openBmpFile(img, &header);



    free(img);
    /*
        Aquí deben hacer el código que solucione lo solicitado.
        Todas las funciones utilizadas deben estar declaradas en este archivo, y en su respectivo .h
    */
}

void openBmpFile(t_pixel *img, t_metadata *header){
    FILE *pf;
    //abro el archivo
    pf = fopen("estudiante.bmp", "rb");

    if (pf == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }

    if(getc(pf) == 'B' && getc(pf) == 'M'){ // aca estoy parado en el byte 2
        fread(&header->tamArchivo, sizeof(unsigned int), 1, pf);
        fseek(pf, 4, SEEK_CUR); // me muevo 4 bytes, para posicionarme en el byte 10
                                // este byte nro 10 contiene el inicio de la imagen
        fread(&header->comienzoImagen, sizeof(unsigned int), 1, pf);// hago el fread, como es unsigned int ocupa 4bytes,
                                                                    // y el puntero queda en el byte 14, donde se encuentra el tamanio del header
        fread(&header->tamEncabezado, sizeof(unsigned int), 1, pf);
        fread(&header->ancho, sizeof(unsigned int), 1, pf);
        fread(&header->alto, sizeof(unsigned int), 1, pf);
        fseek(pf, 2, SEEK_CUR);
        fread(&header->profundidad, sizeof(unsigned short), 1, pf);

        printf("\n tam arch: %d \n comienzo: %d \n tam enca: %d \n ancho: %d \n alto: %d \n prof %d ",
               header->tamArchivo, header->comienzoImagen, header->tamEncabezado, header->ancho,
               header->alto, header->profundidad
               );

        // leo la imagen
        img = (t_pixel *)malloc(header->alto * header->ancho * (header->profundidad / 3) );
        if(img == NULL){
            printf("\n No se pudo reservar memoria para la imagen.");
            return;
        }

        fseek(pf, header->comienzoImagen, SEEK_SET);
        fread(img, sizeof(t_pixel), header->alto * header->ancho, pf);

        // mostrar imagen
        for(int i = 0; i < header->alto; i++) {
            for(int j = 0; j < header->ancho; j++) {
                printf("%d %d %d\n", img[i * header->ancho + j].pixel[0], img[i * header->ancho + j].pixel[1], img[i * header->ancho + j].pixel[2]);

            }
        }



        fclose(pf);

    }else{
        printf("\n El archivo indicado no es de tipo bit map.");
    }

    fclose(pf);

}

int escalaDeGrises( t_pixel *imagen, unsigned int alto, unsigned int ancho){
      for(int i = 0; i < alto; i++) {
        for(int j = 0; j < ancho; j++) {
            unsigned int gris = (imagen[i * ancho + j].pixel[0] + imagen[i * ancho + j].pixel[1] + imagen[i * ancho + j].pixel[2]) / 3;
            imagen[i * ancho + j].pixel[0] = gris;
            imagen[i * ancho + j].pixel[1] = gris;
            imagen[i * ancho + j].pixel[2] = gris;
        }
    }
    return TODO_OK;
}

