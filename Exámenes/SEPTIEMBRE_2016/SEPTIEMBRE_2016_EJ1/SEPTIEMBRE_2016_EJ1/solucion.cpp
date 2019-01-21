//	M� Victoria Barylak Alcaraz

//	Para representar el archipi�lago utilizamos un grafo valorado, donde los v�rtices son las islas, las aritas son los puentes que las unen,
//	y el valor de cada arista el coste de construir el puente.

//	Para conseguir que todas las ilas est�n conectadas con el menor coste posible se realiza el algoritmo del �rbol de recubrimiento m�nimo
//	de Prim.
//	Al final del algoritmo, si todos los v�rtices han sido visitados, si distancia ser� distinta de infinito, y bastar� con devolver la suma 
//	de los valores del vector "distTo", que ser� el coste m�nimo de conectar todas las islas.
//	Si por el contrario alg�n v�rtice tiene distancia igual a infinito, quiere decir que no se ha podido visitar, por lo que no hay suficientes
//	puentes presupuestados para conectar todas las islas.

//	El coste de obtener el �rbol de recubrimiento con el algoritmo de Prim es de O(P * logI), siendo P el n�mero de puentes presupuestados, e I
//	el n�mero de islas del archipi�lago. Esto se debe a que cada puente se visita s�lo una vez (O(P)) y, por cada visita, si el coste del 
//	puente mejora el �rbol de recubrimiento que se ten�a hasta ese momento, se cambia la prioridad de una de las islas en la cola de 
//	prioridad (O(logI)).

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#include "GrafoValorado.h"
#include "IndexPQ.h"

const int INFINITO = 1000000000;


void visitar(GrafoValorado<int> const& milislotes, int v, std::vector<bool>& marked, std::vector<int>& distTo, std::vector<Arista<int>>& edgeTo, IndexPQ<int>& pq) {
	marked[v] = true;

	for (Arista<int> a : milislotes.ady(v)) {
		int w = a.otro(v);
		if (!marked[w]) {
			if (a.valor() < distTo[w]) {
				edgeTo[w] = a;
				distTo[w] = a.valor();
				pq.update(w, distTo[w]);
			}
		}
	}
}


bool archipielago(GrafoValorado<int> const& milislotes, int& coste_total) {
	std::vector<bool> marked(milislotes.V(), false);
	std::vector<int> distTo(milislotes.V(), INFINITO);
	std::vector<Arista<int>> edgeTo(milislotes.V());
	IndexPQ<int> pq(milislotes.V());

	distTo[0] = 0;
	pq.push(0, 0);

	while (!pq.empty()) {
		int min = pq.top().elem;
		pq.pop();
		visitar(milislotes, min, marked, distTo, edgeTo, pq);
	}

	int i = 0;
	bool suficientes = true;
	while (i < distTo.size() && suficientes) {
		suficientes = distTo[i] != INFINITO;
		
		coste_total = coste_total + distTo[i];
		i++;
	}

	return suficientes;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int I, P;

	std::cin >> I;

	if (!std::cin)
		return false;

	GrafoValorado<int> milislotes(I);

	std::cin >> P;

	for (int i = 0; i < P; ++i) {
		int i1, i2, coste;
		std::cin >> i1 >> i2 >> coste;

		milislotes.ponArista({ i1 - 1, i2 - 1, coste });
	}

	int coste_total = 0;

	if (archipielago(milislotes, coste_total))
		std::cout << coste_total << "\n";
	else
		std::cout << "No hay puentes suficientes\n";

	return true;
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}