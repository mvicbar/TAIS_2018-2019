//Grupo E, Mª Victoria Barylak Alcaraz


#include <iostream>
#include <fstream>
#include <functional>
#include <climits>

#include "bintree_eda.h"


//Coste de la funcion: O(n), siendo n el numero de nodos del arbol.
bool equilibrado(bintree<int> const& arbol, int& altura) {
	bool eq; int altIz, altDr;

	if (arbol.empty()) {
		eq = true;
		altura = 0;
	}
	else if (arbol.right().empty() && arbol.left().empty()) {
		eq = true;
		altura = 1;
	}
	else {

		bool iz = equilibrado(arbol.left(), altIz);
		bool dr = equilibrado(arbol.right(), altDr);

		eq = (iz && dr) && (abs(altIz - altDr) <= 1);
		altura = 1 + std::max(altIz, altDr);
	}

	return eq;
}

//Coste de la funcion: O(n), siendo n el numero de nodos del arbol.
bool avl(bintree<int> const& arbol, bool& esAVL, int& max, int& min) {

	if (!arbol.empty() && avl) {

		if (arbol.left().empty() && arbol.right().empty()) {
			min = arbol.root();
			max = arbol.root();
		}
		else {

			int aux = -111; //centinela para saber si el árbol tiene hijo izquierdo.

			if (!arbol.left().empty()) {

				avl(arbol.left(), esAVL, max, min);

				if (max >= arbol.root())
					esAVL = false;
				else max = arbol.root();
				aux = min;
			}

			if (!arbol.right().empty()) {

				avl(arbol.right(), esAVL, max, min);

				if (min <= arbol.root())
					esAVL = false;
				if (aux != -111) //si el arbol tiene hijo izquierdo, su valor minimo es el minimo del hijo izquierdo.
					min = aux;
				else min = arbol.root();
			}
		}
	}

	return esAVL;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
void resuelveCaso() {
	bintree<int> arbol = leerArbol(-1);
	int altura = 0;
	int max = INT_MIN;
	int min = INT_MAX;
	bool esAVL = true;

	bool sol = equilibrado(arbol, altura) && avl(arbol, esAVL, max, min);
	
	if (sol)
		std::cout << "SI" << "\n";
	else
		std::cout << "NO" << "\n";
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