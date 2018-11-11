
// Veronika Yankova y M� Victoria Barylak

// Representamos los cruzes como v�rices de un grafo, y las calles como sus aristas. Hacemos un recorrido en profundidad
// de todos los v�rtices, asignando alternativamente un booleano que indica si en el cruce hay un guardia o no. 
// En el caso de que en dos cruces adyacentes haya guardias, se da una pelea, y por lo tanto, es imposible asignar los 
// guardias. Tambi�n, cuando una calle se queda sin guardia al no poder poner dos guardias en dos cruces adyacentes, 
// se da el resultado de que es imposible.

// El coste del recorrido en profundidad de los grafos es O(V + E), siendo V el n�mero de v�rtices y E el n�mero de 
// aristas, ya que cada v�rtice se recorre s�lo una vez, y despu�s se recorren sus aristas.

// El coste de la funci�n es O(cruces + calles).

#include <iostream>
#include <fstream>
using namespace std;

#include "Grafo.h"

bool dfs(Grafo const& g, int v, vector<bool> &marked, vector<bool> &guardia, bool hayGuardia, int &numG) {
	bool pelea = false;
	bool result = false;
	marked[v] = true;
	guardia[v] = hayGuardia;
	if (hayGuardia)
		numG++;
	hayGuardia = !hayGuardia;
	for (int i : g.ady(v))
	{
		if (!marked[i]) {
			result = dfs(g, i, marked, guardia, hayGuardia, numG);
			pelea = result || pelea;
		}
		else {
			//Si hay dos guardias en cruces adyacentes, o no hay guardia vigilando la calle que une dos cruces, hay conflicto.
			pelea = guardia[v] == guardia[i];

		}
	}
	return pelea;
}

bool resuelveCaso() {
	int cruces, calles;
	cin >> cruces >> calles;

	if (!cin)
		return false;

	// completa para terminar de leer y resolver un caso
	Grafo graph(cruces);
	int v, w;
	for (int i = 0; i < calles; i++)
	{
		cin >> v >> w;
		graph.ponArista(v - 1, w - 1);
	}
	vector<bool> marked(cruces, false);
	vector<bool> guardias(cruces, false); //vector que indica en qu� cruces hay un guardia
	bool pelea = false;
	bool result = false;
	int numG = 0;
	for (int i = 0; i < graph.V(); i++)
	{
		if (!marked[i] && !graph.ady(i).empty()) {
			result = dfs(graph, i, marked, guardias, true, numG);
			pelea = result || pelea;
		}
	}

	if (pelea)
		cout << "IMPOSIBLE" << endl;
	else
		cout << numG << endl;
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
