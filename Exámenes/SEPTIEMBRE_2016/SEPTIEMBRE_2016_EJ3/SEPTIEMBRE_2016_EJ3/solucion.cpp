//Grupo E, Mª Victoria Barylak Alcaraz


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Matriz.h"

const int INFINITO = 1000000000;

//	Definición de la función:
//		dianas(i, j) = número mínimo de dardos necesarios para obtener una puntuación de j usando los sectores de 1 al i

//	Definición recursiva:
//		dianas(i, j) = dianas(i - 1, j), si sector(i) > j
//					 = min(dianas(i - 1, j), dianas(i, j - sector(i)) + 1), si sector(i) <= j

//	Casos base:
//		dianas(i, 0) = 0;
//		dianas(0, j) = infinito;

//	Coste de la función:
//		O(n*V) en tiempo, y O(V) en espacio adicional; siendo n el número de sectores de la diana, y V el valor a obtener
int construyendo_dianas(std::vector<int> const& puntuaciones, const int V, std::vector<int>& sectores) {
	int n = puntuaciones.size();
	Matriz<int> dianas(n + 1, V + 1, INFINITO);

	dianas[0][0] = 0;

	for (int i = 1; i <= n; ++i) {
		dianas[i][0] = 0;
		for (int j = 1; j <= V; ++j) {
			if (puntuaciones[i - 1] > j)
				dianas[i][j] = dianas[i - 1][j];
			else
				dianas[i][j] = std::min(dianas[i - 1][j], dianas[i][j - puntuaciones[i - 1]] + 1);
		}
	}


	int i = n; int j = V;
	while (j > 0 && i > 0) {
		if (puntuaciones[i - 1] <= j && dianas[i][j - puntuaciones[i - 1]] + 1 <= dianas[i - 1][j]) {
			sectores.push_back(puntuaciones[i - 1]);
			j = j - puntuaciones[i - 1];
		}
		else
			--i;
	}

	return dianas[n][V];
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int V, S;

	std::cin >> V >> S;

	if (!std::cin)
		return false;

	std::vector<int> puntuaciones(S); std::vector<int> sectores;

	for (int i = 0; i < S; ++i)
		std::cin >> puntuaciones[i];

	int dardos = construyendo_dianas(puntuaciones, V, sectores);

	if (dardos == INFINITO)
		std::cout << "Imposible\n";
	else {

		std::cout << dardos << ": ";

		for (int i = 0; i < sectores.size(); ++i)
			std::cout << sectores[i] << " ";

		std::cout << "\n";
	}

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