#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED
#include "estructuras.h"

void solucion(int argc, char* argv[]);
void openBmpFile(t_pixel *img, t_metadata *header);
int escalaDeGrises( t_pixel *imagen, unsigned int alto, unsigned int ancho);
int guardarImagenEnEscalaDeGrises(t_metadata encabezado, t_pixel *imagen);
#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
