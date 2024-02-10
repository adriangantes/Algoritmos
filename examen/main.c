/*
 * TITLE: Algoritmos LABS
 * SUBTITLE: Práctica Examen
 * AUTHOR: Adrián Edreira Gantes
 * LOGIN: adrian.gantes@udc.es
 * DNI: 79347143-H
 * GROUP: 1.2
 * DATE: 18 / 01 / 24
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>

double microsegundos (){
    struct timeval t;
    if (gettimeofday (&t, NULL) < 0){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);

}

void inicializar_semilla (){
    srand (time(NULL));
}

void aleatorio (int v[], int n){
    int m=2*n+1;
    int i;
    
    for (i=0; i<n; i++){
        v[i]= (rand() % m) - n;
    }
}

void vector_descendente(int v[], int n) {

    int i;

    for (i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

void vector_ascendente(int v[], int n) {

    int i;

    for (i = 0; i < n; i++) {
        v[i] = i + 1;
    }
}

bool vector_ordenado(int v[], int n) {

    int i;

    for (i = 1; i < n; i++) {
        if (v[i] < v[i - 1]) {
            return false;
        }
    }

    return true;
}

void crear_vector (int v[], int n, int i){

    if (i == 1){
        aleatorio (v, n);
    } else if (i == 2){
        vector_descendente(v, n);
    } else {
        vector_ascendente(v, n);
    }
}

void listar_vector(int v[], int n){
    printf ("[");
    for (int j=0; j<n; j++){
        printf ("%d  ", v[j]);
    }
    printf ("]");
}

void auxOrd (int v[], int izq, int der){

    int piv, tmp, j, i;

    if (izq < der){
        piv = v[der - 1];
        tmp = v[izq];
        v[izq] = piv;
        v[der - 1] = tmp;
        i = izq + 1;
        j = der;

        while (i <= j){
            while (v[j] > piv){
                j--;
            }
            while (i <= der && v[i] < piv){
                i++;
            }
            if (i<=j){
                tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
                i++;j--;
            }
        }
        tmp = v[izq];
        v[izq] = v[j];
        v[j] = tmp;
        auxOrd (v, izq, j-1);
        auxOrd (v, j+1, der);
    }
}

void ordenar (int v [], int n){
    auxOrd (v, 0, n-1);
}

void calcular_tiempos(int n, int i){

    double ta, tb, t, t1, t2;
    int v[n], j;

    printf ("\t\t");
    crear_vector(v, n, i);
    ta=microsegundos(); ordenar (v,n); tb=microsegundos();
    t=tb-ta;

    if (t<500){
        printf("(*) ");
        ta = microsegundos();
        for (j = 0; j<1000; j++){
            crear_vector(v, n, i);
            ordenar (v,n);
        }
        tb = microsegundos();
        t1 = tb-ta;
        ta = microsegundos();
        for (j = 0; j<1000; j++){
            crear_vector(v, n, i);
        }
        tb = microsegundos();
        t2 = tb-ta;
        t = (t1-t2) /1000;
    }

    printf ("%.3f  \t", t);
    if (i == 2 || i == 3){
        printf ("%.8f\t", t/pow(n, (1.8)));
        printf ("%.8f\t", t/pow(n, (2)));
        printf ("%.8f\t", t/pow(n, (2.1)));
    }else {
        printf ("%.8f\t", t/pow(n, (0.9)));
        printf ("%.8f\t", t/pow(n, (1.1)));
        printf ("%.8f\t", t/pow(n, (1.3)));
    }
}

void test() {

    int n = 10, v[n], vd[10];

    printf("\nPrueba de Quicksort:\n");

    printf("\nInicializacion aleatorio: ");
    aleatorio(v, n); listar_vector(v, n);
    printf ("\nOrdenado? %s\n", vector_ordenado(v, n) ? "Si" : "No");

    printf("Vector ordenado:"); ordenar (v, n);
    listar_vector(v, n);
    printf ("\nOrdenado? %s\n", vector_ordenado(v, n) ? "Si" : "No");

    printf("\nInicializacion descendente: ");
    vector_descendente(vd,10); listar_vector(vd, 10);
    printf ("\nOrdenado? %s\n", vector_ordenado(vd, 10) ? "Si" : "No");

    printf("Vector ordenado:"); ordenar (vd, n);
    listar_vector(vd, n);
    printf ("\nOrdenado? %s\n", vector_ordenado(vd, n) ? "Si" : "No");

    printf("\nInicializacion ascendente: ");
    vector_ascendente(vd,10); listar_vector(vd, 10);
    printf ("\nOrdenado? %s\n", vector_ordenado(vd, 10) ? "Si" : "No");

    printf("Vector ordenado:"); ordenar (vd, n);
    listar_vector(vd, n);
    printf ("\nOrdenado? %s\n", vector_ordenado(vd, n) ? "Si" : "No");
}

int main() {
    int n[7]= {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int i, j, k;
    inicializar_semilla();
    printf ("\n");


    printf ("\nVECTORES EJEMPLO:\n\n\n");
    test();
    printf ("\n\nTiempos y cotas:\n\n");


    for (k = 0; k < 4; k++){
        printf ("\nQUICKSORT\n");
        for (j = 1; j <= 3; j++){
            if (j == 1){
                printf ("\nVector aleatorio\n");
            }else if (j == 2){
                printf ("\nVector descendente\n");
            }else{
                printf ("\nVector ascendente\n");
            }
            printf ("n\t\tt(n)\t\tt(n)/f(n)\tt(n)/g(n)\tt(n)/h(n)\n\n");
            for (i = 0; i<7; i++){
                printf ("%d ", n[i]);
                calcular_tiempos(n[i],j);
                printf ("\n");
            }
        }
    }

    return 0;
}
