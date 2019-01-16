//	M� Victoria Barylak Alcaraz

//	Para resolver el problema se recorren los v�rtices del grafo en profundidad y se comprueba que s�lo tenga una componente conexa, y que no tenga ciclos.

//	Para comprobar que s�lo tenga una componente conexa se lleva un contador que se pone a 1 en al primera llamada a DFS. Si despu�s de esa primera llamada
//	a�n quedan nodos que no han sido visitados, quiere decir que hay m�s de una componente conexa y, por lo tanto, el grafo no es conexo.

//	Para comprobar que el grafo es ac�clico, se utiliza un vector "padre" en el que se asigna el v�rtice v como padre de sus adyacentes. De esta forma, 
//	si se llega a un v�rtice que ya ha sido visitado, y no es el "padre" del v�rtice actual, se ha encontrado un ciclo.

//	El coste del recorrido en profundidad es de O(V + A), siendo V el n�mero de v�rtices del grafo, y A el n�mero de aristas.

#include <iostream>
#include <fstream>
#include <vector>

#include "Grafo.h"

bool DFS(Grafo const& grafo, int v, std::vector<int>& padre, std::vector<bool>& marked) {
	marked[v] = true;

	for (int w : grafo.ady(v)) {
		if (!marked[w]) {
			padre[w] = v;
			if (DFS(grafo, w, padre, marked))
				return true;
		}
		else if (padre[v] != w)
			return true;
	}

	return false;
}


bool arbol_libre(Grafo const& grafo, int& componentes) {
	std::vector<int> padre(grafo.V(), -1);	//vector que representa los padres de cada v�rtice adyacente
	std::vector<bool> marked(grafo.V(), false);	//vector que representa si un v�rtice ya ha sido visitado en el recorrido o no

	bool ciclo = false;

	for (int v = 0; v < grafo.V() && !ciclo; ++v) {
		if (!marked[v]) {	//nueva componente conexa
			componentes++;
			ciclo = DFS(grafo, v, padre, marked);
		}
	}

	return !ciclo && componentes == 1;
}

//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int V, A;
	int componentes = 0;

	std::cin >> V;

	if (!std::cin)
		return false;

	std::cin >> A;

	Grafo grafo(V);

	int v, w;
	for (int a = 0; a < A; ++a) {
		std::cin >> v >> w;
		grafo.ponArista(v, w);
	}

	if (arbol_libre(grafo, componentes))
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