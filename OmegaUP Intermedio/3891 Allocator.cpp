#include <bits/stdc++.h>
#define op_ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
 
const int INF = (1 << 30);
 
struct Nodo{
	int lazy;
	int izq, der;
	int disponibles;
	int prefijo, sufijo;
	Nodo *hijo_izq, *hijo_der;
	Nodo(int izquierda, int derecha): 
		izq(izquierda), der(derecha), disponibles(1), lazy(-1), 
	 	  prefijo(1), sufijo(1), hijo_izq(NULL), hijo_der(NULL) {}
};
 
struct SegmentTree{
	int tam;
	Nodo raiz;
	SegmentTree(int n): 
		tam(n - 1), raiz(0, n - 1) {}
 
	int rango(Nodo *actual){
		return actual->der - actual->izq + 1;
	}
 
	void buildTree_(int izquierda, int derecha, Nodo *actual){
		if(izquierda == derecha) return;
 
		int mitad = (izquierda + derecha) / 2;
		actual->hijo_izq = new Nodo(izquierda, mitad);
		actual->hijo_der = new Nodo(mitad + 1, derecha);
 
		buildTree_(izquierda, mitad, actual->hijo_izq);
		buildTree_(mitad + 1, derecha, actual->hijo_der);
 
		int cardinalidad = actual->disponibles = (actual->der - actual->izq) + 1;
		actual-> sufijo = cardinalidad;
		actual-> prefijo = cardinalidad;
	}
 
	void propagar(Nodo *actual){
		actual->disponibles = rango(actual) * (actual->lazy);
		actual->prefijo = actual->sufijo = actual->disponibles;
		if(actual->hijo_izq != NULL) actual->hijo_izq->lazy = actual->lazy;
		if(actual->hijo_der != NULL) actual->hijo_der->lazy = actual->lazy;
		actual->lazy = -1;
	}
 
	void actualizar(Nodo * actual){
		actual->prefijo = (actual->hijo_izq->prefijo == rango(actual->hijo_izq))?
			rango(actual->hijo_izq) + actual->hijo_der->prefijo : actual->hijo_izq->prefijo;
 
		actual->sufijo = (actual->hijo_der->sufijo == rango(actual->hijo_der))? 
			rango(actual->hijo_der) + actual->hijo_izq->sufijo : actual->hijo_der->sufijo;
 
		actual->disponibles = max( actual->hijo_izq->sufijo + actual->hijo_der->prefijo, 
			                        max(actual->hijo_izq->disponibles, actual->hijo_der->disponibles) );
	}
 
	void update_(int izquierda, int derecha, int valor, Nodo *actual){
		if(actual->lazy != -1){ propagar(actual); } 
		if(derecha < actual->izq || izquierda > actual->der) return;
 
		if(izquierda <= actual->izq && actual->der <= derecha){ 
			actual->lazy = valor; propagar(actual); return; }
 
		update_(izquierda, derecha, valor, actual->hijo_izq);
		update_(izquierda, derecha, valor, actual->hijo_der);
 
		actualizar(actual);
	}
 
	int query_(int memoriaAReservar, Nodo *actual){	
		if( actual->lazy != -1) { propagar(actual); }
 
		if( actual->disponibles < memoriaAReservar) return INF;
		if( actual->izq == actual->der) return actual->izq;
 
		if(actual->hijo_izq->lazy != -1) propagar(actual->hijo_izq);
		if(actual->hijo_der->lazy != -1) propagar(actual->hijo_der);
 
		if(actual->hijo_izq->disponibles >= memoriaAReservar) 
			return query_( memoriaAReservar, actual->hijo_izq);
 
		if(actual->hijo_izq->sufijo + actual->hijo_der->prefijo >= memoriaAReservar )
			return (actual->hijo_izq->der - actual->hijo_izq->sufijo) + 1;
 
		if(actual->hijo_der->disponibles >= memoriaAReservar)
			return query_( memoriaAReservar, actual->hijo_der); 
	}
 
	void buildTree(){
		buildTree_(0, tam, &raiz);
	}
 
	int query(int reservar){
		return query_(reservar, &raiz);
	}
 
	void update(int izquierda, int derecha, int valor){
		update_(izquierda, derecha, 1 - valor, &raiz);
	}
};
 
int main(){
	op_
	int n, querys;
	cin >> n >> querys;
 
	SegmentTree segTree(n);
	segTree.buildTree();
	for(int i = 0; i < querys; i++){
		int comando;
		cin >> comando;
		if(comando == 1){
			int memoria;
			cin >> memoria;
			int indice = segTree.query(memoria);
			if(indice == INF){
				cout << "0\n";
			} else {
				cout << indice + 1 << "\n";
				segTree.update(indice, indice + memoria - 1, 1);
			}
		} else {
			int puntoInicial, puntoFinal;
			cin >> puntoInicial >> puntoFinal;
			segTree.update(puntoInicial - 1, puntoInicial + puntoFinal - 2, 0);
		}
	}
	return 0;
}