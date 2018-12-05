//	Mª Victoria Barylak Alcaraz, Grupo E

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Matriz.h"

const int INFINITO = 1000000000;

typedef struct {
	int longitud, coste;
}tVarilla;


//	posible(i, L) = si es posible obtener una vara de longitud L soldand algunas de las varillas de la 1 hasta la i.

//	posible(i, L) = posible(i - 1, L); si li > L
//				  = (posible(i - 1, L - li) || posible(i - 1, L)); si li <= L

//	posible(i, 0) = true;
//	posible(0, L) = false;

//	Coste de la función: O(n * L), siendo n el número de varillas, y L la longitude de la vara deseada
bool posible(std::vector<tVarilla>& varillas, const int& L) {
	int n = varillas.size() - 1;
	Matriz<bool> posible(n + 1, L + 1);

	posible[0][0] = true;
	for (int i = 1; i <= n; i++) {
		posible[i][0] = true;
		for (int j = 1; j <= L; j++) {
			posible[0][j] = false;
			if (varillas[i].longitud > j)
				posible[i][j] = posible[i - 1][j];
			else
				posible[i][j] = (posible[i - 1][j - varillas[i].longitud] || posible[i - 1][j]);
		}
	}

	return posible[n][L];
}


//	formas(i, L) = número de formas de obtener una vara de longitud L soldando algunas de las varillas de la 1 hasta la i.

//	formas(i, L) = formas(i - 1, L); si li > L
//				 = formas(i - 1, L) + formas(i - 1, L - li); si li <= L

//	formas(0, L) = 0;
//	formas(i, 0) = 1;

//	Coste de la función: O(n * L), siendo n el número de varillas, y L la longitude de la vara deseada
int formas(std::vector<tVarilla>& varillas, const int& L) {
	int n = varillas.size() - 1;
	Matriz<int> formas(n + 1, L + 1);

	formas[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		formas[i][0] = 1;
		for (int j = 1; j <= L; j++) {
			formas[0][j] = 0;
			if (varillas[i].longitud > j)
				formas[i][j] = formas[i - 1][j];
			else
				formas[i][j] = formas[i - 1][j] + formas[i - 1][j - varillas[i].longitud];
		}
	}

	return formas[n][L];
}


//	minimo(i, L) = el número mínimo de varillas de la 1 hasta la i que pueden formar una vara de longitud L

//	minimo(i, L) = minimo(i - 1, L); si li > L
//				 = min(minimo(i - 1, L), minimo(i - 1, L - li) + 1); si li <= L

//	minimo(i, 0) = 0;
//	minimo(0, L) = infinito;

//	Coste de la función: O(n * L), siendo n el número de varillas, y L la longitude de la vara deseada
int minimo(std::vector<tVarilla>& varillas, const int& L) {
	int n = varillas.size() - 1;
	Matriz<int> minimo(n + 1, L + 1, INFINITO);

	minimo[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		minimo[i][0] = 0;
		for (int j = 1; j <= L; j++) {
			minimo[0][j] = INFINITO;
			if (varillas[i].longitud > j)
				minimo[i][j] = minimo[i - 1][j];
			else
				minimo[i][j] = std::min(minimo[i - 1][j], minimo[i - 1][j - varillas[i].longitud] + 1);
		}
	}

	return minimo[n][L];
}


//	coste(i, L) = el coste mínimo para formar una vara de longitud L con varillas de la 1 hasta la i

//	coste(i, L) = coste(i - 1, L); si li > L
//				= min(coste(i - 1, L), coste(i - 1, L - li) + ci); si li <= L

//	coste(i, 0) = 0;
//	coste(0, L) = infinito;

//	Coste de la función: O(n * L), siendo n el número de varillas, y L la longitude de la vara deseada
int coste(std::vector<tVarilla>& varillas, const int& L) {
	int n = varillas.size() - 1;
	Matriz<int> coste(n + 1, L + 1, INFINITO);

	coste[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		coste[i][0] = 0;
		for (int j = 1; j <= L; j++) {
			coste[0][j] = INFINITO;
			if (varillas[i].longitud > j)
				coste[i][j] = coste[i - 1][j];
			else
				coste[i][j] = std::min(coste[i - 1][j], coste[i - 1][j - varillas[i].longitud] + varillas[i].coste);
		}
	}

	return coste[n][L];
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, L;

	std::cin >> N >> L;

	if (!std::cin)
		return false;

	std::vector<tVarilla> varillas(N + 1);

	for (int i = 1; i <= N; i++) {
		tVarilla varilla;
		std::cin >> varilla.longitud;
		std::cin >> varilla.coste;

		varillas[i] = varilla;
	}

	if (posible(varillas, L)) {
		std::cout << "SI ";
		std::cout << formas(varillas, L);
		std::cout << " " << minimo(varillas, L);
		std::cout << " " << coste(varillas, L);
		std::cout << "\n";
	}
	else 
		std::cout << "NO\n";

	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}