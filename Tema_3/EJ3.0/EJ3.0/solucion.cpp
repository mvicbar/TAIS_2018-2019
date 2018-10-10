//Grupo E, Mª Victoria Barylak Alcaraz

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Grafo.h"


void dfs(Grafo const& amigos, int v, int& tam, std::vector<bool>& marked) {
	marked[v] = true;
	tam++;

	for (int vertice : amigos.ady(v)) {
		if (!marked[vertice])
			dfs(amigos, vertice, tam, marked);
	}
}


int resolver(Grafo const& amigos) {
	int max = 0;
	std::vector<bool> marked(amigos.V());

	for (int v = 0; v < amigos.V(); v++) {
		if (!marked[v]) {
			int tam = 0;
			dfs(amigos, v, tam, marked);
			max = std::max(max, tam);
		}
	}

	return max;
}

//Coste de la funcion: O(N + M), siendo N el numero de nodos del grafos y M el numero de aristas.
void resuelveCaso() {
	int N, M;
	int a1, a2;

	std::cin >> N >> M;

	Grafo amigos(N);

	for (int i = 0; i < M; ++i) {
		std::cin >> a1 >> a2;
		amigos.ponArista(a1-1, a2-1);
	}

	std::cout << resolver(amigos) << "\n";
}


int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;

	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}