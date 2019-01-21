//	Mª Victoria Barylak Alcaraz

//	Para representar los grupos de amigos se utiliza un grafo, donde los vértices son las personas y las aristas son las relaciones de amistad.
//	Para encontrar el grupo más grande de amigos, basta con realizar un recorrido en profundidad sobre el grafo, contando los vértices que
//	hay en cada componente conexa, y devolviendo el mayor número de vértices.

//	El coste del recorrido en profundidad es de O(N + M), siendo N en número de personas, y M el número de relaciones de amistad.


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Grafo.h"


void DFS(Grafo const& amigos, std::vector<bool>& marked, int v, int& tam) {
	marked[v] = true;

	for (int w : amigos.ady(v)) {
		if (!marked[w]) {
			tam++;
			DFS(amigos, marked, w, tam);
		}
	}
}


int amigosDeMisAmigos(Grafo const& amigos) {
	std::vector<bool> marked(amigos.V(), false);
	int max_tam = 0;

	for (int i = 0; i < amigos.V(); ++i) {
		if (!marked[i]) {	//se recorre un nuevo grupo de amigos
			int tam = 1;
			DFS(amigos, marked, i, tam);
			max_tam = std::max(max_tam, tam);
		}
	}

	return max_tam;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
void resuelveCaso() {
	int N, M;

	std::cin >> N >> M;

	Grafo amigos(N);

	for (int i = 0; i < M; ++i) {
		int a, b;
		std::cin >> a >> b;

		amigos.ponArista(a - 1, b - 1);
	}

	int mayor_grupo = amigosDeMisAmigos(amigos);

	std::cout << mayor_grupo << "\n";
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