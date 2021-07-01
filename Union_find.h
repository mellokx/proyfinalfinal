#include <iostream>
#include <vector>

using namespace std;

struct celda {
	celda * padre ;
	int rank;
};

struct vertice {
	//Quiza se podria separar padre y rank uwu
	vertice * padre ;
	int rank;
	vertice * arriba;
    vertice * abajo;
    vertice * izquierda;
    vertice * derecha;
	int num;
};

struct arista {
	vertice * a;
	vertice * b;
	arista * siguiente;
	int peso;
	celda * c1;
	celda * c2;
};

class Union_find{
    private:

    public:
    	Union_find();
		~Union_find();
    	void Makeset(vertice * x);
		void Link(vertice * x,vertice * y);
    	vertice * Find(vertice * x);
    	void Union(vertice * x, vertice * y);
};