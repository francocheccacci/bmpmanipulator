#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED
#include "estructuras.h"

void solucion(int argc, char* argv[]);
void openBmpFile(t_pixel *img, t_metadata *header);
int escalaDeGrises(  t_pixel *imagen, t_metadata *header);
int crearBmpSalida(t_pixel *imagen, t_metadata *header,char nombre[20]);
#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
