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
        t_pixel *ini = img;
        if(img == NULL){
            printf("\n No se pudo reservar memoria para la imagen.");
            return;
        }

        fseek(pf, header->comienzoImagen, SEEK_SET);
        fread(img->pixel, sizeof(img->pixel),header->alto * header->ancho,pf);

//        unsigned int padding = (4 - (header->ancho * sizeof(img->pixel)) % 4) % 4; // Calcula el padding
//        for (int i = 0; i < header->alto; i++) {
//            fread(img + i * header->ancho, sizeof(img->pixel),header->ancho, pf);
//            fseek(pf, padding, SEEK_CUR); // Salta los bytes de relleno
//        }

          printf("Primer pixel: R=%u, G=%u, B=%u\n", img[0].pixel[0], img[0].pixel[1], img[0].pixel[2]);

//        // mostrar imagen


        // archivo de salida
        //crearBmpSalida(img, header);
        //escalaDeGrises(img, header->alto, header->ancho);
        crearBmpSalida(img, header, "estudio.bmp");
        img = ini;
        escalaDeGrises(img, header);

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

// funcion que convierte la imagen a escala de grises
int escalaDeGrises(t_pixel *imagen, t_metadata *header){
    unsigned int promedio;
    for(int i = 0; i < header->alto; i++) {
        for(int j = 0; j < header->ancho; j++) {
            promedio = (imagen[i * header->ancho + j].pixel[0] + imagen[i * header->ancho + j].pixel[1] + imagen[i * header->ancho + j].pixel[2]) / 3;
            imagen[i * header->ancho + j].pixel[0] = promedio;
            imagen[i * header->ancho + j].pixel[1] = promedio;
            imagen[i * header->ancho + j].pixel[2] = promedio;
        }
    }

    crearBmpSalida(imagen, header, "escala_grises.bmp");
}

// funcion que cree un archivo de salida
int crearBmpSalida(t_pixel *imagen, t_metadata *header, char nombre[20]){
    FILE *pf;
    pf = fopen(nombre, "wb");

    if (pf == NULL) {
        printf("No se pudo abrir el archivo.");
        return 1;
    }

    fwrite("BM", sizeof(char), 2, pf);
    fwrite(&header->tamArchivo, sizeof(unsigned int), 1, pf);
    fseek(pf, 4, SEEK_CUR); // me muevo 4 bytes, para posicionarme en el byte 10
                            // este byte nro 10 contiene el inicio de la imagen
    fwrite(&header->comienzoImagen, sizeof(unsigned int), 1, pf);// hago el fread, como es unsigned int ocupa 4bytes,
                                                                // y el puntero queda en el byte 14, donde se encuentra el tamanio del header
    fwrite(&header->tamEncabezado, sizeof(unsigned int), 1, pf);
    fwrite(&header->ancho, sizeof(unsigned int), 1, pf);
    fwrite(&header->alto, sizeof(unsigned int), 1, pf);
    fseek(pf, 2, SEEK_CUR);
    fwrite(&header->profundidad, sizeof(unsigned short), 1, pf);
    fseek(pf, header->comienzoImagen, SEEK_SET);
    fwrite(imagen, sizeof(imagen->pixel), header->alto * header->ancho, pf);

    fclose(pf);

    return TODO_OK;
}
