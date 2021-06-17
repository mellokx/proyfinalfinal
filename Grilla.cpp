#include "Grilla.h"
#include <iostream>

using namespace std;

Grilla::Grilla(int n,int m,bool conPesos){
    int a = 0;
    int b = 10;
	mysize = 0;
    head_v = new vertice();
    head_a = new arista();
    if((n < 0)||(m < 0)){
        cout<<"Ingrese valores de n y m validos"<<endl;
        throw;
    }else{
        //aux_v manejan los vértices en dirección vertical
        //aux_h manejan los vértices en dirección horizontal
        vertice * aux_v2 = head_v;
        vertice * aux_v1;
        vertice * aux_h2;
        vertice * aux_h1;
        arista * aux_arista = head_a;
        // Forma primera parte de la Grilla
        // Esto incluye todos los vertices, n*m/2 aristas necesarias para completar la Grilla
        for(int i = 0; i<n; ++i){
            aux_h2 = aux_v2;
            for(int j = 0; j<m; ++j){
                aux_h2->derecha = new vertice();
                aux_h2->derecha->num = j + 1;
                aux_h1 = aux_h2;
                aux_h2 = aux_h2->derecha;
                aux_h2->izquierda = aux_h1;
                aux_arista->siguiente = new arista();
                if(conPesos == true){
                    aux_arista->siguiente->peso = funcion_random(a,b);
                }else{
                    aux_arista->siguiente->peso = 1;
                }
                aux_arista->siguiente->a = aux_h1;
                aux_arista->siguiente->b = aux_h2;
                aux_arista = aux_arista->siguiente;
            }
            aux_v2->abajo = new vertice();
            aux_v2->abajo->num = i + 1;
            aux_v1 = aux_v2;
            aux_v2 = aux_v2->abajo;
            aux_v2->arriba = aux_v1;
            aux_arista->siguiente = new arista();
            if(conPesos == true){
                aux_arista->siguiente->peso = funcion_random(a,b);
            }else{
                aux_arista->siguiente->peso = 1;
            }
            aux_arista->siguiente->a = aux_v1;
            aux_arista->siguiente->b = aux_v2;
            aux_arista = aux_arista->siguiente;
        }
        // Termina de formar las aristas aux_h2es finales faltantes
        aux_h2 = aux_v2;
        for(int i = 0; i<m; ++i){
                aux_h2->derecha = new vertice();
                aux_h2->derecha->num = i + 1;
                aux_h1 = aux_h2;
                aux_h2 = aux_h2->derecha;
                aux_h2->izquierda = aux_h1;
                aux_arista->siguiente = new arista();
                if(conPesos == true){
                    aux_arista->siguiente->peso = funcion_random(a,b);
                }else{
                    aux_arista->siguiente->peso = 1;
                }
                aux_arista->a = aux_h1;
                aux_arista->b = aux_h2;
        }
        // Termina de formar las aristas aux_v2es intermedias y finales faltantes
        aux_v1 = head_v; 
        aux_v2 = head_v->abajo;
        for(int i = 0; i<n; ++i){
            aux_h1 = aux_v1->derecha;
            aux_h2 = aux_v2->derecha;
            for(int j = 0; j<m; ++j){
                aux_h1->abajo = aux_h2;
                aux_h2->arriba = aux_h1;
                aux_arista->siguiente = new arista();
                if(conPesos == true){
                    aux_arista->siguiente->peso = funcion_random(a,b);
                }else{
                    aux_arista->siguiente->peso = 1;
                }
                aux_arista->siguiente->a = aux_h1;
                aux_arista->siguiente->b = aux_h2;
                aux_arista = aux_arista->siguiente;
                aux_h1 = aux_h1->derecha;
                aux_h2 = aux_h2->derecha;
            }
            aux_v1 = aux_v2;
            aux_v2 = aux_v2->abajo;
        }
    }
}

Grilla::~Grilla(){
    //Borra Vértices
    vertice * aux_v = head_v;
    vertice * aux_h = aux_v;
    vertice * aux_v2;
    vertice * aux_h2;
    while(aux_v != NULL){
        while(aux_h != NULL){
            if(aux_h->derecha != NULL){
                if(aux_h != aux_v){
                    aux_h2 = aux_h->derecha;
                    delete aux_h;
                    aux_h = aux_h2;
                }else{
                    aux_h = aux_h->derecha;
                }
            }else{
                delete aux_h;
                aux_h = NULL;
            }
        }
        if(aux_v->abajo != NULL){
            aux_v2 = aux_v->abajo;
            delete aux_v;
            aux_v = aux_v2;
        }else{
            aux_v = aux_v->abajo;
        }
        aux_h = aux_v;
    }
    //Borra Aristas
    arista * aux_arista = head_a;
    while(aux_arista != NULL){
        head_a = aux_arista->siguiente;
        delete aux_arista;
        aux_arista = head_a;
    }
}

void Grilla::dibuja_grilla(){
    vertice * aux_v = head_v;
    vertice * aux_h = aux_v;
    vertice * aux_h2;
    while(aux_v != NULL){
        cout<<"O";
        while(aux_h != NULL){
            if(aux_h->derecha != NULL){
                cout<<" -- O";
            }
            aux_h = aux_h->derecha;
        }
        cout<<endl;
        aux_v = aux_v->abajo;
        aux_h = aux_v;
        if(aux_v != NULL){
            aux_h2 = aux_v;
            cout<<"|";
            while(aux_h2 != NULL){
                if(aux_h2->derecha != NULL){
                    cout<<"    |";
                }
                aux_h2 = aux_h2->derecha;
            }
            cout<<endl;
        }
    }
}

int Grilla::funcion_random(int a, int b){
    if(a > b){
        cout<<"a y b no representan un intervalo [a,b] correcto"<<endl;
        throw;
    }
    int aux;
    aux = rand()&1;
    if(aux == 0){
        if((b == 1) && (a == 0)){
            aux = rand()%(b+1);
        }else{
            if(a == b){
                aux = a;
            }else{
                aux = a + rand()%(((b+1)/2)-a);
            }
        }
    }else{
       if((b == 1) && (a == 0)){
            aux = rand()%(b+1);
        }else{
            if(a == b){
                aux = a;
            }else{
                aux = (b/2) + rand()%((b+1)/2);
            }
        }
    }
    return aux;
}

void Grilla::pesos_aristas(){
    while(head_a->siguiente != NULL){
        head_a;
    }
}

vertice * Grilla::head_vertice(){
    return head_v;
}


arista * Grilla::head_arista(){
    return head_a;
}
int Grilla::size(){
    //(n+1)*(m+1)
    return -1;
}