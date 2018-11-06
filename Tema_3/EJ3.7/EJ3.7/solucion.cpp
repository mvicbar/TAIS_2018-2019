//Grupo E, M� Victoria Barylak Alcaraz

//	Se representan las islas y los puentes mediante un grafo valorado; los v�rtices representan las islas, y las aristas representan los puentes, siendo el valor de 
//	cada arista el coste de construir el puente. 

//	El problema de conectar todas las islas con el menor coste posible es un problema de �rbol de recubrimiento m�nimo. Se hace uso del algoritmo de Prim para 
//	conseguir dicho �rbol. Una vez finalizado el algoritmo, se comprueba que se hayan visitado todos las islas, es decir, que todos los v�rtices del grafo formen parte del
//	�rbol. De ser as�, se recorren las aristas acumulando sus valores para obtener el coste total de construcci�n. De no ser as�, se indican que no hay suficientes 
//	puentes para conectar todas las islas.

//	El coste de obtener el �rbol de recubrimiento m�nimo con el algoritmo de Prim es de O(P * log I); siendo P el n�mero de puentes e I el n�mero de islas a conectar.
//	El coste se debe a que cada puente se visita s�lo una vez (coste O(P)) y, por cada visita, si el coste del puente mejora el �rbol de recubrimiento que se ten�a hasta el momento,
//	se cambia la prioridad de una de las islas en la cola de prioridad (coste O(log I)).

#include <iostream>
#include <fstream>

#include "GrafoValorado.h"
#include "IndexPQ.h"

const int INFINITO = 1000000000;


void visit(GrafoValorado<int> const& islas, int v, std::vector<bool>& marked, std::vector<int>& distTo, std::vector<Arista<int>>& edgeTo, IndexPQ<int>& pq) {
	marked[v] = true;

	for (Arista<int> a : islas.ady(v)) {
		int w = a.otro(v);
		if (marked[w]) continue;
		if (a.valor() < distTo[w]) {
			edgeTo[w] = a;
			distTo[w] = a.valor();
			pq.update(w, distTo[w]);
		}
	}
}


void construirPuentes(GrafoValorado<int> const& islas) {
	std::vector<Arista<int>> edgeTo(islas.V());
	std::vector<int> distTo(islas.V(), INFINITO);
	std::vector<bool> marked(islas.V(), false);
	IndexPQ<int> pq(islas.V());

	distTo[0] = 0;
	pq.push(0, 0);
	while (!pq.empty()) {
		int min = pq.top().elem; pq.pop();
		visit(islas, min, marked, distTo, edgeTo, pq);
	}

	/*Comprobaci�n de que todas las islas est�n conectadas*/
	int i = 0;
	while (i < marked.size() && marked[i]) {
		i++;
	}

	if (i < marked.size())
		std::cout << "No hay puentes suficientes\n";
	else {

		/*Acumulaci�n del coste total de construir los puentes*/
		int costeTotal = 0;

		for (int e = 1; e < edgeTo.size(); e++)
				costeTotal = costeTotal + edgeTo[e].valor();

		std::cout << costeTotal << "\n";
	}
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int I, P;

	std::cin >> I >> P;

	if (!std::cin)
		return false;

	GrafoValorado<int> islas(I);

	/*Construcci�n del grafo valorado*/
	for (int p = 0; p < P; p++) {
		int origen, destino, coste;

		std::cin >> origen >> destino >> coste;

		islas.ponArista(Arista<int>(origen - 1, destino - 1, coste));
	}

	construirPuentes(islas);

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