/*
 * TITLE: Algoritmos LABS
 * SUBTITLE: Práctica 3
 * AUTHOR 1: Adrián Edreira Gantes LOGIN 1: adrian.gantes@udc.es
 * AUTHOR 2: Ángela Fouz Suárez LOGIN 2: angela.fouz@udc.es
 * AUTHOR 3: Gael Saavedra Pinho LOGIN 3: g.spinho@udc.es
 * GROUP: 1.2
 * DATE: 11 / 11 / 23
 */

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "monticulos.h"



void inicializar_semilla() {
	srand(time(NULL));
}

void aleatorio (int v[], int n){

    int m=2*n+1, i;

    for (i = 0; i<n; i++){
        v[i]= (rand() % m) - n;
    }
}

void descendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = i + 1;
    }
}

double microsegundos (){

    struct timeval t;

    if (gettimeofday (&t, NULL) < 0){
        return 0.0;
    }

    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void listar_vector(int v[], int n){
    int i;
    printf ("[");
    for (i = 0; i<n; i++){
        printf ("%d  ", v[i]);
    }
    printf ("]");
}

void mostrar_monticulo(pmonticulo m){
	printf("Vector del montículo: ");
    listar_vector(m->vector, m->ultimo);
	printf("\tÚltima posición: %d\n", m->ultimo);
}

void test1(){
	int v[10];
    pmonticulo m = malloc(sizeof(struct monticulo));

    aleatorio(v, 10);
	printf("\nVector aleatorio: ");
    listar_vector(v, 10);

    crearMonticulo(v, 10, m);
	printf("\n\nMontículo:\n");
    mostrar_monticulo(m);
    free(m);
}

void test2(void orden ()){
	int v[10];

	printf("Vector original: ");
    orden(v,10);

	listar_vector(v, 10);
	
	printf("\nVector ordenado: ");
	ordenarPorMonticulos(v, 10);
	listar_vector(v, 10);
}

void calcular_tiempos1(int n, void orden(), double cota_sub(),
                      double cota_est(), double cota_sob()){

    double ta, tb, t, t1, t2;
    int v[n], j;
    pmonticulo m = malloc(sizeof(struct monticulo));

    printf ("\t\t");
    orden (v, n);
    ta=microsegundos(); crearMonticulo (v,n, m); tb=microsegundos();
    t=tb-ta;

    if (t<500){
        printf("(*) ");
        ta = microsegundos();
        for (j = 0; j<1000; j++){
            orden(v, n);
            crearMonticulo (v,n, m);
        }
        tb = microsegundos();
        t1 = tb-ta;
        ta = microsegundos();
        for (j = 0; j<1000; j++){
            orden(v, n);
        }
        tb = microsegundos();
        t2 = tb-ta;
        t = (t1-t2) /1000;
    }

    printf ("%.3f  \t", t);
    printf ("%.6f\t", t/cota_sub(n));
    printf ("%.6f\t", t/cota_est(n));
    printf ("%.6f\t", t/cota_sob(n));
    printf ("\n");
    free (m);
}

void calcular_tiempos2(int n, void orden(), double cota_sub(),
                       double cota_est(), double cota_sob()){

    double ta, tb, t, t1, t2;
    int v[n], j;

    printf ("\t\t");
    orden(v, n);
    ta=microsegundos(); ordenarPorMonticulos(v, n); tb=microsegundos();
    t=tb-ta;

    if (t<500){
        printf("(*) ");
        ta = microsegundos();
        for (j = 0; j<1000; j++){
            orden(v, n);
            ordenarPorMonticulos(v, n);
        }
        tb = microsegundos();
        t1 = tb-ta;
        ta = microsegundos();
        for (j = 0; j<1000; j++){
            orden(v, n);
        }
        tb = microsegundos();
        t2 = tb-ta;
        t = (t1-t2) /1000;
    }

    printf ("%.3f  \t", t);
    printf ("%.6f\t", t/cota_sub(n));
    printf ("%.6f\t", t/cota_est(n));
    printf ("%.6f\t", t/cota_sob(n));
    printf ("\n");
}

double cota_crea_sub(int n) {return pow(n, 0.8);}
double cota_crea_est(int n) {return pow(n, 1);}
double cota_crea_sob(int n) {return pow(n, 1.2);}


double cota_ale_sub(int n) {return pow(n, 0.9);}
double cota_ale_est(int n) {return (n * log2 (n));}
double cota_ale_sob(int n) {return pow(n, 1.3);}


double cota_des_sub(int n) {return pow(n, 0.9);}
double cota_des_est(int n) {return (n * log2 (n));}
double cota_des_sob(int n) {return pow(n, 1.3);}


double cota_asc_sub(int n) {return pow(n, 0.9);}
double cota_asc_est(int n) {return (n * log2 (n));}
double cota_asc_sob(int n) {return pow(n, 1.3);}


void mostrar_tablas (){
    int n;

    printf("\nCreación de montículo aleatorio:\n\n");
    printf ("n\t\tt(n)\t\tt(n)/f(n)\tt(n)/g(n)\tt(n)/h(n)\n\n");
    for (n = 500; n <= TAM; n *= 2){
        printf ("%d ", n);
        calcular_tiempos1(n, aleatorio, cota_crea_sub,
                          cota_crea_est, cota_crea_sob);
    }

    printf("\n\nOrdenacion por Montículos con inicializacion aleatoria\n\n");
    printf ("n\t\tt(n)\t\tt(n)/f(n)\tt(n)/g(n)\tt(n)/h(n)\n\n");
    for (n = 500; n <= TAM; n *= 2){
        printf ("%d ", n);
        calcular_tiempos2(n, aleatorio, cota_ale_sub,
                          cota_ale_est, cota_ale_sob);
    }

    printf("\n\nOrdenacion por Montículos con inicializacion descendente\n\n");
    printf ("n\t\tt(n)\t\tt(n)/f(n)\tt(n)/g(n)\tt(n)/h(n)\n\n");
    for (n = 500; n <= TAM; n *= 2){
        printf ("%d ", n);
        calcular_tiempos2(n, descendente, cota_des_sub,
                          cota_des_est, cota_des_sob);
    }

    printf("\n\nOrdenacion por Montículos con inicializacion ascendente\n\n");
    printf ("n\t\tt(n)\t\tt(n)/f(n)\tt(n)/g(n)\tt(n)/h(n)\n\n");
    for (n = 500; n <= TAM; n *= 2){
        printf ("%d ", n);
        calcular_tiempos2(n, ascendente, cota_asc_sub,
                          cota_asc_est, cota_asc_sob);
    }
}

int main(){
	inicializar_semilla();	

	printf("\nTest de funcionamiento:\n"),test1();
	printf("\n\nTest de ordenación (vector aleatorio):\n"),test2(aleatorio);
	printf("\n\nTest de ordenación (vector descendente):\n"),test2(descendente);
	printf("\n\nTest de ordenación (vector ascendente):\n"),test2(ascendente);

    printf("\n\n\n\nTiempos y cotas:\n\n");
    mostrar_tablas();
    printf("\n");

    return 0;
}
