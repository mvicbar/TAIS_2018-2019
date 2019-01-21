//	Mª Victoria Barylak Alcaraz

//	Se representa la ciudad mediante un grafo no dirigido valorado donde las aristas son las calles con sus anchuras, y los vértices son las
//	intersecciones. Se realiza un recorrido en anchura, marcando los vértices como visitados sólo si la anchura de la calle que llega a ellos
//	es mayor o igual a la anchura del camión.

//	Para saber si se puede realizar el reparto sólo hay que comprobar que el vértice destino puede ser visitado.

//	El coste de la función es de O(K*(V + E)), que es coste del recorrido en profundidad.

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#include "GrafoValorado.h"

const int INFINITO = 1000000000;


typedef struct {
	int origen, destino;
	int anchura_camion;
} Reparto;


bool BFS(GrafoValorado<int> const& ciudad, Reparto const& reparto, std::queue<int>& q, std::vector<bool>& marked, std::vector<int>& distTo) {
	distTo[reparto.origen] = 0;
	marked[reparto.origen] = true;
	q.push(reparto.origen);

	while (!q.empty()) {
		int v = q.front(); q.pop();

		for (Arista<int> a : ciudad.ady(v)) {
			if (!marked[a.otro(v)] && a.valor() >= reparto.anchura_camion) {
				distTo[a.otro(v)] = distTo[v] + 1;
				marked[a.otro(v)] = true;
				q.push(a.otro(v));
			}
		}
	}

	return marked[reparto.destino];
}


bool repartir(GrafoValorado<int> const& ciudad, Reparto const& reparto) {
	std::queue<int> q;
	std::vector<bool> marked(ciudad.V(), false);
	std::vector<int> distTo(ciudad.V(), INFINITO);

	return BFS(ciudad, reparto, q, marked, distTo);
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int V, E, K;

	std::cin >> V;

	if (!std::cin)
		return false;

	GrafoValorado<int> ciudad(V);

	std::cin >> E;

	for (int e = 0; e < E; ++e) {
		int v1, v2, anchura;
		std::cin >> v1 >> v2 >> anchura;
		
		ciudad.ponArista(Arista<int>(v1 - 1, v2 - 1, anchura));
	}

	std::cin >> K;
	int origen, destino, anchura_camion;
	Reparto r;
	std::vector<Reparto> repartos;

	for (int k = 0; k < K; ++k) {
		std::cin >> origen >> destino >> anchura_camion;
		r.origen = origen - 1;
		r.destino = destino - 1;
		r.anchura_camion = anchura_camion;

		if (repartir(ciudad, r))
			std::cout << "SI\n";
		else
			std::cout << "NO\n";
	}

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