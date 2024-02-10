/*
 * TITLE: Algoritmos LABS
 * SUBTITLE: Práctica 3
 * AUTHOR 1: Adrián Edreira Gantes LOGIN 1: adrian.gantes@udc.es
 * AUTHOR 2: Ángela Fouz Suárez LOGIN 2: angela.fouz@udc.es
 * AUTHOR 3: Gael Saavedra Pinho LOGIN 3: g.spinho@udc.es
 * GROUP: 1.2
 * DATE: 11 / 10 / 23
 */

#include "monticulos.h"

void hundir(pmonticulo m, int i) {
    int HijoIzq, HijoDer, j, temp;

    do {
        HijoIzq = 2 * i + 1;
        HijoDer = 2 * i + 2;
        j = i;

        if (HijoDer < m->ultimo && m->vector[HijoDer] > m->vector[i]) {
            i = HijoDer;
        }
        if (HijoIzq < m->ultimo && m->vector[HijoIzq] > m->vector[i]) {
            i = HijoIzq;
        }

        if (j != i) {
            temp = m->vector[j];
            m->vector[j] = m->vector[i];
            m->vector[i] = temp;
        }
    } while (j != i);
}

void crearMonticulo(int v[], int n, pmonticulo m) {
    int i;
    m->ultimo = n;

    for (i = 0; i < n; i++) {
        m->vector[i] = v[i];
    }

    for (i = (n - 1) / 2; i >= 0; i--) {
        hundir(m, i);
    }
}

int quitarMayor(pmonticulo m) {

    int mayor = m->vector[0];

    m->vector[0] = m->vector[m->ultimo - 1];
    m->ultimo--;

    hundir(m, 0);

    return mayor;
}

void ordenarPorMonticulos(int v[], int n) {
    int i;
    pmonticulo m = malloc(sizeof(struct monticulo));
    crearMonticulo(v, n, m);

    for (i = 0; i < n; i++) {
        v[n-i-1] = quitarMayor(m);
    }
    free (m);
}
