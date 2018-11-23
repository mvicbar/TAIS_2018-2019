// Grupo E, Mª Victoria Barylak Alcaraz

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#include "GrafoDirigido.h"


//Coste de la busqueda: O(E + V), siendo E el número de aristas y V el número de vértices del grafo.
void BreathFirstSearch(GrafoDirigido const& tablero, int s, std::vector<bool>& marked, std::vector<int>& distTo) {
	std::queue<int> q;
	distTo[s] = 0;
	marked[s] = true;
	q.push(s);

	while (!q.empty()) {
		int v = q.front(); q.pop();

		for (int w : tablero.ady(v)) {
			if (!marked[w]) {
				distTo[w] = distTo[v] + 1;
				marked[w] = true;
				q.push(w);
			}
		}
	}

}



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, K, S, E;

	std::cin >> N >> K >> S >> E;

	if (N == 0 && K == 0 && S == 0 && E == 0)
		return false;
	
	std::vector<int> ultima_casilla(N*N + 1, -1);	//Guarda las primeras y últimas casillas de las serpientes y escaleras.

	for (int i = 0; i < S + E; ++i) {
		int ini, fin;
		std::cin >> ini >> fin;
		ultima_casilla[ini] = fin;
	}

	GrafoDirigido tablero(N*N + 1);
	std::vector<bool> marked(tablero.V());
	std::vector<int> distTo(tablero.V());

	//Construcción del grafo
	for (int j = 1; j <= N*N; ++j) {
		for (int k = 1; k <= K; ++k) {
			int primera_casilla = j + k;

			if (primera_casilla <= N * N) {
				if (ultima_casilla[primera_casilla] != -1) //Si la casilla es el inicio de una serpiente o una escalera
					tablero.ponArista(j, ultima_casilla[primera_casilla]);	//se añade una arista desde la casilla inicial hasta la última casilla de la serpiente o escalera
				else
					tablero.ponArista(j, primera_casilla);	//si no, se añade una arista desde la casilla incial hasta la siguiente
			}
		}
	}

	BreathFirstSearch(tablero, 1, marked, distTo);

	std::cout << distTo[N*N] << "\n";

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