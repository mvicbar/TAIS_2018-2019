//Grupo E, M� Victoria Barylak Alcaraz

// Se representa la ciudad mediante un grafo valorado, donde las intersecciones son nodos y las calles son aristas que tienen como valor su anchura. 
// Para cada reparto, se empieza un recorrido en anchura desde el origen, a�adiendo una condici�n extra para que una intersecci�n se visite, que la anchura de la
// calle sea mayor o igual a la anchura del cami�n.
// Al terminar el recorrido en anchura, se pregunta si el destino ha sido visitado, es decir, si exite un camino que llega hasta �l en el que las anchuras de las calles
// son mayores o iguales a la anchura del cami�n.

// El coste del recorrido en anchura en un grado es de O(E + V), siendo E el n�mero de aritas del grafo y V el n�mero de nodos.

#include <iostream>
#include <fstream>
#include <queue>

#include "GrafoValorado.h"
#include "IndexPQ.h"

const int INFINITO = 1000000000;

// Coste de la funci�n: O(V + E), siendo V el n�mero de v�rtices y E el n�mero de aristas.
bool BFS(GrafoValorado<int> const& ciudad, int s, int destino, std::vector<bool>& marked, std::vector<int>& distTo, int anchuraCamion) {
	std::queue<int> q;
	marked[s] = true;
	distTo[s] = 0;
	q.push(s);

	while (!q.empty()) {
		int v = q.front(); q.pop();

		for (Arista<int> w : ciudad.ady(v)) {
			if (!marked[w.otro(v)] && w.valor() >= anchuraCamion) {
				distTo[w.otro(v)] = distTo[v] + 1;
				marked[w.otro(v)] = true;
				q.push(w.otro(v));
			}

		}
	}

	return marked[destino];	//Si el destino se ha visitado, existe un camino desde el origen en el que las anchuras de las calles son mayores o iguales a la del cami�n
}


void reparto(GrafoValorado<int> const& ciudad, int origen, int destino, int anchuraCamion) {
	std::vector<int> distTo(ciudad.V(), INFINITO);
	std::vector<bool> marked(ciudad.V(), false);

	if (BFS(ciudad, origen, destino, marked, distTo, anchuraCamion))
		std::cout << "SI\n";
	else
		std::cout << "NO\n";
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int V, E;

	std::cin >> V >> E;

	if (!std::cin)
		return false;

	GrafoValorado<int> ciudad(V);

	for (int i = 0; i < E; i++) {
		int v, w, peso;
		std::cin >> v >> w >> peso;
		ciudad.ponArista(Arista<int>(v-1,w-1,peso));
	}

	int repartos;

	std::cin >> repartos;

	for (int r = 0; r < repartos; r++) {
		int origen, destino, anchuraCamion;

		std::cin >> origen >> destino >> anchuraCamion;

		reparto(ciudad, origen-1, destino-1, anchuraCamion);
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