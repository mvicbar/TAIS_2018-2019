//Grupo E, Mª Victoria Barylak Alcaraz

// Se usa la idea de los colores. Cogido un vértice, se colorea de rojo (R), si todos sus vértices adyancentes se colorean de azul (A). Si en el proceso de coloreado
// se encuentra que un vértice tiene el mismo color que uno de sus adyacentes, el grafo no es bipartito.

#include <iostream>
#include <fstream>
#include <vector>

#include "Grafo.h"


bool dfs(Grafo const& grafo, int v, std::vector<char>& color, std::vector<bool>& marked) {
	marked[v] = true;

	for (int w : grafo.ady(v)) {
		if (!marked[w]) {
			if (color[v] == 'R')
				color[w] = 'A';
			else
				color[w] = 'R';

			if (!dfs(grafo, w, color, marked))
				return false;
		}
		else if (color[w] == color[v])
			return false;
	}

	return true;
}


//Funcion que resuleve el problema
//Comentario sobre el coste
bool resolver(Grafo const& grafo) {
	std::vector<char> color(grafo.V());
	std::vector<bool> marked(grafo.V());

	for (int v = 0; v < grafo.V(); v++) {
		if (!marked[v]) {
			color[v] = 'R';
			if (!dfs(grafo, v, color, marked))
				return false;
		}
	}

	return true;
}

//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int V, A;
	int a1, a2;

	std::cin >> V;

	if (!std::cin)
		return false;

	std::cin >> A;

	Grafo grafo(V);

	for (int i = 0; i < A; i++) {
		std::cin >> a1 >> a2;
		grafo.ponArista(a1, a2);
	}

	if (resolver(grafo))
		std::cout << "SI\n";
	else
		std::cout << "NO\n";

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