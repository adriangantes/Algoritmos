/*
 * TITLE: Algoritmos LABS
 * SUBTITLE: Práctica 3
 * AUTHOR 1: Adrián Edreira Gantes LOGIN 1: adrian.gantes@udc.es
 * AUTHOR 2: Ángela Fouz Suárez LOGIN 2: angela.fouz@udc.es
 * AUTHOR 3: Gael Saavedra Pinho LOGIN 3: g.spinho@udc.es
 * GROUP: 1.2
 * DATE: 11 / 10 / 23
 */

#ifndef P3_MONTICULOS_H
#define P3_MONTICULOS_H

#include <stdlib.h>
#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};
typedef struct monticulo * pmonticulo;

void crearMonticulo (int v[], int n, pmonticulo m);
void ordenarPorMonticulos(int v[], int n);

#endif
