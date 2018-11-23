//Grupo E, Mª Victoria Barylak Alcaraz

#include <iostream>
#include <fstream>
#include <algorithm>

#include "bintree_eda.h"


//Funcion que resuleve el problema
//Coste de la funcion: O(n), siendo n el número de nodos del árbol.
bool resolver(bintree<char> const& arbol, int& altura) {
	bool eq; int altIz, altDr;

	if (arbol.empty()) {
		eq = true;
		altura = 0;
	}
	else if(arbol.right().empty() && arbol.left().empty()) {
		eq = true;
		altura = 1;
	}
	else {

		bool iz = resolver(arbol.left(), altIz);
		bool dr = resolver(arbol.right(), altDr);

		eq = (iz && dr) && (abs(altIz - altDr) <= 1);
		altura = 1 + std::max(altIz, altDr);
	}

	return eq;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
void resuelveCaso() {
	auto arbol = leerArbol('.');
	int altura = 0;
	bool sol = resolver(arbol, altura);
	
	if (sol)
		std::cout << "SI" << std::endl;
	else {
		std::cout << "NO" << std::endl;
	}
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