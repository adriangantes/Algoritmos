/*
 * TITLE: Algoritmos LABS
 * SUBTITLE: Práctica 2
 * AUTHOR 1: Adrián Edreira Gantes LOGIN 1: adrian.gantes@udc.es
 * AUTHOR 2: Ángela Fouz Suárez LOGIN 2: angela.fouz@udc.es
 * AUTHOR 3: Gael Saavedra Pinho LOGIN 3: g.spinho@udc.es
 * GROUP: 1.2
 * DATE: 11 / 10 / 23
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
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

    int m=2*n+1, i;

    for (i = 0; i<n; i++){
        v[i]= (rand() % m) - n;
    }
}

void listar_vector(int v[], int n){

    int i;

    printf ("[");
    for (i = 0; i<n; i++){
        printf ("%d  ", v[i]);
    }
    printf ("]");
}

void ord_ins (int v[], int n){

    int x, j, i;

    for (i = 1; i<n;i++){
        x = v[i];
        j = i-1;
        while (j >= 0 && v[j] > x){
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = x;
    }
}

void ord_shell (int v[],int n){

    int incremento = n , tmp, j, i;
    bool seguir;

    do{
        incremento = incremento/ 2;
        for(i = incremento; i < n ; i++){
            tmp = v[i];
            j = i;
            seguir = true;
            while(j-incremento >= 0 && seguir){
                if(tmp < v[j-incremento]){
                    v[j] = v[j-incremento];
                    j = j - incremento;
                }else{
                    seguir = false;
                }
            }
            v[j] = tmp;
        }

    }while(incremento != 1);
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

void calcular_tiempos1(int n, int i){

    double ta, tb, t, t1, t2;
    int v[n], j;

    printf ("\t\t");
    crear_vector(v, n, i);
    ta=microsegundos(); ord_ins (v,n); tb=microsegundos();
    t=tb-ta;

    if (t<500){
        printf("(*) ");
        ta = microsegundos();
        for (j = 0; j<1000; j++){
            crear_vector(v, n, i);
            ord_ins (v,n);
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
    if (i == 1 || i == 2){
        printf ("%.6f\t", t/pow(n, (1.8)));
        printf ("%.6f\t", t/pow(n, (2)));
        printf ("%.6f\t", t/pow(n, (2.2)));
    }else {
        printf ("%.6f\t", t/pow(n, (0.8)));
        printf ("%.6f\t", t/pow(n, (1)));
        printf ("%.6f\t", t/pow(n, (1.2)));
    }
}

void calcular_tiempos2(int n, int i){

    double ta, tb, t, t1, t2;
    int v[n], j;

    printf ("\t\t");
    crear_vector(v, n, i);
    ta=microsegundos(); ord_shell (v,n); tb=microsegundos();
    t=tb-ta;

    if (t<500){
        printf("(*) ");
        ta = microsegundos();
        for (j = 0; j<1000; j++){
            crear_vector(v, n, i);
            ord_shell (v,n);
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
    printf ("%.6f\t", t/pow(n, (1)));
    printf ("%.6f\t", t/(n * log(n)));
    printf ("%.6f\t", t/pow(n, (1.5)));
}

void test1() {

    int n = 17, v[n], i, vd[10];

    for (i = 1; i <=2; i++){

        if (i == 1){
            printf("\nPrueba de ordenación por inserccion:\n");
        }else{
            printf("\nPrueba de ordenación por shell:\n");
        }

        printf("\nInicializacion aleatorio: ");
        aleatorio(v, n); listar_vector(v, n);
        printf ("\nOrdenado? %s\n", vector_ordenado(v, n) ? "Si" : "No");

        if (i == 1){
            printf("Ordenación por inserccion:"); ord_ins (v, n);
        }else{
            printf("Ordenación por shell:"); ord_shell(v, n);
        }

        listar_vector(v, n);
        printf ("\nOrdenado? %s\n", vector_ordenado(v, n) ? "Si" : "No");

        printf("\nInicializacion descendente: ");
        vector_descendente(vd,10); listar_vector(vd, 10);
        printf ("\nOrdenado? %s\n", vector_ordenado(vd, 10) ? "Si" : "No");

        if (i == 1){
            printf("Ordenación por inserccion:"); ord_ins (vd, 10);
        }else{
            printf("Ordenación por shell:"); ord_shell(vd, 10);
        }

        listar_vector(vd, 10);
        printf ("\nOrdenado? %s\n\n", vector_ordenado(vd, 10) ? "Si" : "No");
    }
}

void test2() {

    int n[7]= {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int i, j;

    printf ("\nINSERCION\n");
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
            calcular_tiempos1(n[i], j);
            printf ("\n");
        }
    }

    printf ("\nSHELL\n");
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
            calcular_tiempos2(n[i], j);
            printf ("\n");
        }
    }
}

int main() {

    inicializar_semilla();
    printf ("\n");
    printf ("Puebas de algoritmos:\n");
    test1();
    printf ("\nMedicion de tiempos:\n");
    test2();

    printf("\n");
    return 0;
}
