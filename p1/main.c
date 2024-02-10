/*
 * TITLE: Algoritmos LABS
 * SUBTITLE: Práctica 1
 * AUTHOR 1: Adrián Edreira Gantes LOGIN 1: adrian.gantes@udc.es
 * AUTHOR 2: Ángela Fouz Suárez LOGIN 2: angela.fouz@udc.es
 * AUTHOR 3: Gael Saavedra Pinho LOGIN 3: g.spinho@udc.es
 * GROUP: 1.2
 * DATE: 30 / 09 / 23
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

double microsegundos (){
    struct timeval t;
    if (gettimeofday (&t, NULL) < 0){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);

}

int sumaSubMax1 ( int v[], int n){
    int sumaMax=0, estaSuma;
    for (int i=0 ; i<n; i++){
        estaSuma=0;
        for (int j=i; j<n; j++){
            estaSuma = estaSuma + v[j];
            if (estaSuma > sumaMax){
                sumaMax = estaSuma;
            }
        }
    }
    return sumaMax;
}

int sumaSubMax2(int v[], int n){
    int estaSuma = 0;
    int sumaMax = 0;
    for(int j=0; j<n; j++){
        estaSuma = estaSuma + v[j];
        if(estaSuma > sumaMax){
            sumaMax = estaSuma;
        }else if(estaSuma < 0){
            estaSuma = 0;
        }
    }
    return sumaMax;
}

void inicializar_semilla (){
    srand (time(NULL));
}

void aleatorio (int v[], int n){
    int m=2*n+1;
    for (int i=0; i<n; i++){
        v[i]= (rand() % m) - n;
    }
}

void listar_vector(int v[], int n){
    printf ("[");
    for (int j=0; j<n; j++){
        printf ("%d  ", v[j]);
    }
    printf ("]");
}

void calcular_tiempos1(int n){
    double ta, tb, t;
    int v[n];
    aleatorio (v, n);
    ta=microsegundos(); sumaSubMax1 (v,n); tb=microsegundos();
    t=tb-ta;

    if (t<500){
    	printf("(*)");
        double t1, t2;
        ta = microsegundos();
        for (int i=0; i<1000; i++){
            aleatorio (v,n); sumaSubMax1 (v,n);
        }
        tb = microsegundos();
        t1 = tb-ta;

        ta = microsegundos();
        for (int i=0; i<1000; i++){
            aleatorio (v,n);
        }
        tb = microsegundos();

        t2 = tb-ta;
        t = (t1-t2) /1000;
    }
    printf ("%.3f   \t", t);
}

void calcular_tiempos2(int n){
    double ta, tb, t;
    int v[n];
    aleatorio (v, n);
    ta=microsegundos(); sumaSubMax2 (v,n); tb=microsegundos();
    t=tb-ta;

    if (t<500){
    	printf("(*)");
        double t1, t2;
        ta = microsegundos();
        for (int i=0; i<1000; i++){
            aleatorio (v,n); sumaSubMax2 (v,n);
        }
        tb = microsegundos();
        t1 = tb-ta;

        ta = microsegundos();
        for (int i=0; i<1000; i++){
            aleatorio (v,n);
        }
        tb = microsegundos();

        t2 = tb-ta;
        t = (t1-t2) /1000;
    }
    printf ("%.3f", t);
}

void test1() {
    int n[7]= {500, 1000, 2000, 4000, 8000, 16000, 32000};
    printf ("n\t\tsumaSubMax1\tsumaSubMax2\n\n");

    for (int i = 0; i<7; i++){
        printf ("%d:\t", n[i]);
        calcular_tiempos1(n[i]);
        calcular_tiempos2(n[i]);
        printf ("\n");
    }
}

void test2() {
    int i, a, b;
    int v[9];
    printf("test\n");
    printf("%33s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");

    for (i=0; i<10; i++) {
        aleatorio(v, 9);
        listar_vector(v, 9);
        a = sumaSubMax1(v, 9);
        b = sumaSubMax2(v, 9);
        printf("%15d%15d\n", a, b);
    }
}

int main() {
    inicializar_semilla();
    printf ("\n");
    test1();
    test2();

    int v[6][5] = {
    {-9, 2, -5, -4, 6},
    {4, 0, 9, 2, 5},
    {-2, -1, -9, -7, -1},
    {9, -2, 1, -7, -8},
    {15, -2, -5, -4, 16},
    {7, -5, 6, 7, -7}
	};

    printf ("\nVECTORES EJEMPLO:\n\n\n");
    for (int i=0;i<6;i++){
        printf ("Vector %d: ", i+1);
        listar_vector (v[i], 5);
        printf("   \tsumaSubMax1: %d", sumaSubMax1(v[i],5));
        printf("\t\tsumaSubMax2: %d\n\n",sumaSubMax2(v[i],5));
    }

    return 0;
}
