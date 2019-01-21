//	Mª Victoria Barylak Alcaraz

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Matriz.h"


//	Definción de la función:
//		tablero(i, j) = máxima puntuación que se puede conseguir al llegar a la casilla (i, j)
//						t es el estado inicial del tablero de juego


//	Definción recursiva:
//						std::max(tablero(i + 1, j - 1) + t(i, j), std::max(tablero(i + 1, j) + t(i, j), tablero(i + 1, j + 1) + t(i, j))); si 1 < j < N
//		tablero(i, j) = std::max(t(i, j) + tablero(i + 1,j), t(i, j) + tablero(i + 1, j + 1)); si j = 1
//						std::max(t(i, j) + tablero(i + 1, j-1), t(i, j) + tablero(i + 1, j)); si j = N

//	Caso base:
//		tablero(N, j) = t(N, j)

//	Coste de la función:
//		O(N*N), en tiempo y en espacion adicional
void jugar(Matriz<int>& t, int N) {
	Matriz<int> tablero(N, N, 0);

	for(int j = 0; j <= N - 1; ++j)
		tablero[N - 1][j] = t[N - 1][j];

	for (int i = N - 2; i >= 0; --i) {
		for (int j = N - 1; j >= 0; --j) {

			if (j == 0)
				tablero[i][j] = std::max(t[i][j] + tablero[i + 1][j], t[i][j] + tablero[i + 1][j + 1]);
			else if (j == N - 1)
				tablero[i][j] = std::max(t[i][j] + tablero[i + 1][j - 1], t[i][j] + tablero[i + 1][j]);
			else
				tablero[i][j] = std::max(tablero[i + 1][j - 1] + t[i][j], std::max(tablero[i + 1][j] + t[i][j], tablero[i + 1][j + 1] + t[i][j]));

		}
	}

	int max_puntuacion = *std::max_element(tablero[0].begin(), tablero[0].end());
	auto fin = std::max_element(tablero[0].begin(), tablero[0].end());
	auto casilla_final = std::distance(tablero[0].begin(), fin);

	int i = 0;
	int j = casilla_final;
	while (i < N - 1) {
		if (j == 0) {
			if (tablero[i + 1][j] >= tablero[i + 1][j + 1])
				j = j;
			else
				j = j + 1;
		}
		else if (j == N-1) {
			if (tablero[i + 1][j] > tablero[i + 1][j - 1]) 
				j = j;
			else 
				j = j - 1;
		}
		else {
			if (tablero[i + 1][j - 1] >= tablero[i + 1][j] && tablero[i + 1][j - 1] >= tablero[i + 1][j + 1])
				j = j - 1;
			else if (tablero[i + i][j] > tablero[i + 1][j - 1] && tablero[i + 1][j] > tablero[i + 1][j + 1])
				j = j;
			else
				j = j + 1;
		}

		i = i + 1;
	}

	std::cout << max_puntuacion << " " << j + 1 << "\n";
}

//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N;

	std::cin >> N;

	if (!std::cin)
		return false;

	Matriz<int> tablero(N, N);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			std::cin >> tablero[i][j];

	jugar(tablero, N);

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