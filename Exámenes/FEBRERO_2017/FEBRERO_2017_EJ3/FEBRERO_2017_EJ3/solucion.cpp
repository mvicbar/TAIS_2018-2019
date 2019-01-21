//	Mª Victoria Barylak Alcaraz


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "Matriz.h"


//	Definición de la función:
//		subsecuencia(i, j) = longitud de la subsecuencia más larga teniendo en cuenta las letras de 1 a la i de la palbra 1, y las letras
//							 de la 1 a la j de la palabra 2

//	Definición recursiva:
//		subsecuencia(i, j) = subsecuencia(i - 1, j - 1) + 1; si letra1(i) == letra2(j);
//						   = max(subsecuencia(i, j - 1), subsecuencia(i - 1, j)); si letra1(i) != letra2(j);

//	Casos base:
//		subsecuencia(i, 0) = 0;
//		subsecuencia(0, j) = 0;

//	Coste de la función: O(N*M), en espacio y en tiempo, siendo N la longitud de la palabra 1, y M la longitud de la palabra 2;
int subsecuencia(std::string const& p1, std::string const& p2) {
	int n = p1.size();
	int m = p2.size();
	Matriz<int> subsecuencia(n + 1, m + 1, 0);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (p1[i - 1] == p2[j - 1])
				subsecuencia[i][j] = subsecuencia[i - 1][j - 1] + 1;
			else
				subsecuencia[i][j] = std::max(subsecuencia[i][j - 1], subsecuencia[i - 1][j]);
		}
	}


	return subsecuencia[n][m];
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	std::string palabra1, palabra2;

	std::cin >> palabra1 >> palabra2;

	if (!std::cin)
		return false;

	int tam = subsecuencia(palabra1, palabra2);

	std::cout << tam << "\n";

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