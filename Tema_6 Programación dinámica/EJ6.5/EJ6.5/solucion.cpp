//Grupo E, Mª Victoria Barylak Alcaraz


#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "Matriz.h"

const int INFINITO = 1000000000;


//	Matriz de adyacencia:
//							 = 0, si i = j;
//			adyacencia(i, j) = 1, si la persona i tiene relación con la persona j
//							 = INFINITO, si la persona i no está relacionada con la persona j


//	grado^k(i, j) = número mínimo de relaciones que conectan la persona i con la persona j utilizando como personas intermedias aquellas
//				  entre la 1 y la k

//	grado^k(i, j) = min( grado^k-1(i, j), grado^k-1(i, k), grado^k-1(k, j) )

//	grado(i, j) = 0, si i = j;


//	Coste: O(n^3) en tiempo, siendo n el número de personas, y O(n*n) en espacio.
void gradoDeSeparacion(Matriz<int>& adyacencia) {
	int n = adyacencia.numfils() - 1;

	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				int temp = adyacencia[i][k] + adyacencia[k][j];

				if (temp < adyacencia[i][j])
					adyacencia[i][j] = temp;
			}
		}
	}

}


//	Asigna un índice de un array a cada persona (si no lo tenía ya asignado) y lo devuelve
int indicePersona(std::string const& nombre, std::vector<std::string>& indices) {

	int indice = 1;
	bool ok = false;

	while (!ok) {

		if (nombre == indices[indice])
			ok = true;

		if (indices[indice] == "XXX") {
			indices[indice] = nombre;
			ok = true;
		}

		indice++;
	}

	return indice - 1;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int personas, relaciones;

	std::cin >> personas >> relaciones;

	if (!std::cin)
		return false;

	Matriz<int> adyacencia(personas + 1, personas + 1, INFINITO);
	for (int i = 1; i <= personas; ++i)	//Se actualiza la distancia de cada persona consigo misma
		adyacencia[i][i] = 0;

	std::string p1, p2;
	std::vector<std::string> indices(personas + 1, "XXX");

	//	Se asigna un índice a cada persona, y se actualiza la matriz de adyacencia con su relación
	for (int j = 1; j <= relaciones; ++j) {
		std::cin >> p1 >> p2;

		int ind1 = indicePersona(p1, indices);
		int ind2 = indicePersona(p2, indices);

		adyacencia[ind1][ind2] = 1;
		adyacencia[ind2][ind1] = 1;
	}

	int minGrado = 0;
	gradoDeSeparacion(adyacencia);

	//	Se recupera la solución (se busca el grado mínimo más grande)
	for (int i = 1; i <= personas; ++i) {
		for (int j = i + 1; j <= personas; ++j) {

			if (adyacencia[i][j] > minGrado)
				minGrado = adyacencia[i][j];
		}
	}

	if (minGrado == INFINITO)
		std::cout << "DESCONECTADA\n";
	else
		std::cout << minGrado << "\n";

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