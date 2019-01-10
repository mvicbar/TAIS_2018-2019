//Grupo E, Mª Victoria Barylak Alcaraz


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "Matriz.h"


//	longitudes(i, j) = logitud de la subsecuencia más larga teniendo en cuenta las letras de la 1 a la i de la primera palabra, y de la 1 a la j de la
//					   segunda palabra.

//	longitudes(i, j) = longitudes(i - 1, j - 1) + 1, si palabra1(i) = palabra2(j)
//					   max(longitudes(i - 1, j), longitudes(i, j - 1), si palabra1(i) != palabra2(j)

//	longitudes(0, j) = 0
//	longitudes(i, 0) = 0

//	Coste: O(f*c) tanto en tiempo como en espacio

int subsecuenciaMasLarga(std::string const& palabra1, std::string const& palabra2) {
	int f = palabra1.size();
	int c = palabra2.size();
	Matriz<int> longitudes(f + 1, c + 1, 0);

	for (int i = 1; i <= f; ++i) {
		for (int j = 1; j <= c; ++j) {

			if (palabra1[i - 1] == palabra2[j - 1])
				longitudes[i][j] = longitudes[i - 1][j - 1] + 1;
			else if (palabra1[i - 1] != palabra2[j - 1])
				longitudes[i][j] = std::max(longitudes[i][j - 1], longitudes[i - 1][j]);

		}
	}

	return longitudes[f][c];
}

//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	std::string palabra1, palabra2;

	std::cin >> palabra1 >> palabra2;

	if (!std::cin)
		return false;

	int longitud = subsecuenciaMasLarga(palabra1, palabra2);

	std::cout << longitud << "\n";

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