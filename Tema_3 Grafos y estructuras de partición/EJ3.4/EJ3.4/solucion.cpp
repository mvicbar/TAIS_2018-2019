// Grupo E, Mª Victoria Barylak Alcaraz

// Se recorre en profundidad las manchas del estado inicial del mar, uniendo las casillas de una misma mancha en un mismo conjunto, y se devuelve el tamaño de la mancha más grande.
// A continuación, por cada nueva mancha que aparece, se recorren las casillas adyacentes; si alguna está manchada, se una la nueva mancha al conjunto de la casilla manchada, si no se sigue mirando.
// Se actualiza el tamaño de la mancha más grande y se muestra por pantalla.


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#include "ConjuntosDisjuntos.h"


const std::vector<std::pair<int, int>> dirs = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 },{ -1,-1 },{ -1,1 },{ 1,-1 },{ 1,1 } };


/*Recorre en profundidad una mancha y une las casillas de una misma mancha en un mismo conjunto*/
void DFS(std::vector<std::vector<int>> const& mar, int f, int c, const int filas, const int columnas, std::vector<std::vector<bool>>& marked, ConjuntosDisjuntos& manchas) {
	marked[f][c] = true;
	int casilla = (f*columnas) + c; //Convierte la casilla <f,c> en un índice para los conjutos

	for (auto d : dirs) {
		int nf = f + d.first;
		int nc = c + d.second;

		if (nf >= 0 && nf < filas && nc >= 0 && nc < columnas && mar[nf][nc] == 1 && !marked[nf][nc]) {
			int nueva_casilla = (nf*columnas) + nc;
			manchas.unir(casilla, nueva_casilla);
			DFS(mar, nf, nc, filas, columnas, marked, manchas);
		}
	}

}


/*Recorre el mar y devuelve el tamaño de la mancha más grande*/
int petrolero(std::vector<std::vector<int>> const& mar, const int filas, const int columnas, ConjuntosDisjuntos& manchas) {
	std::vector<std::vector<bool>> marked(filas, std::vector<bool>(columnas, false));
	int max = 0;

	for (int f = 0; f < filas; ++f) {
		for (int c = 0; c < columnas; ++c) {
			if (mar[f][c] == 1 && !marked[f][c]) {
				DFS(mar, f, c, filas, columnas, marked, manchas);
				max = std::max(max, manchas.tam((f*columnas) + c));
			}
		}
	}

	return max;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int filas, columnas;
	char marca;

	std::cin >> filas >> columnas;

	if (!std::cin)
		return false;

	std::vector<std::vector<int>> mar(filas, std::vector<int>(columnas, 0));
	ConjuntosDisjuntos manchas(filas*columnas);

	std::cin.get(); //Lee el salto de línea

					/*Lectura del estado inicial del mar*/
	for (int f = 0; f < filas; ++f) {
		for (int c = 0; c < columnas; ++c) {
			marca = std::cin.get();

			if (marca == '#')
				mar[f][c] = 1;
		}

		std::cin.get(); //Lee el salto de línea
	}

	int tam = petrolero(mar, filas, columnas, manchas);

	std::cout << tam << " ";

	int nuevas_manchas, nueva_fila, nueva_columna;

	std::cin >> nuevas_manchas;

	/*Por cada mancha nueva que aparece, se compreban sus casillas adyacentes para ver si están manchadas; si lo están, se añade la nueva casilla al conjunto, si no, se sigue mirando.*/
	for (int n = 0; n < nuevas_manchas; ++n) {
		std::cin >> nueva_fila >> nueva_columna;
		nueva_fila--; nueva_columna--;

		mar[nueva_fila][nueva_columna] = 1;	//Actualización del mar con la nueva mancha

		for (auto d : dirs) {
			int nf = nueva_fila + d.first;
			int nc = nueva_columna + d.second;

			if (nf >= 0 && nf < filas && nc >= 0 && nc < columnas && mar[nf][nc] == 1)
				manchas.unir((nueva_fila * columnas + nueva_columna), (nf*columnas + nc));

		}

		tam = std::max(tam, manchas.tam(nueva_fila*columnas + nueva_columna));

		std::cout << tam << " ";
	}

	std::cout << "\n";

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