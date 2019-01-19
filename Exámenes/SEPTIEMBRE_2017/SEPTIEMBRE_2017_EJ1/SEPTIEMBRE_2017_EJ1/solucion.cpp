//	M� Victoria Barylak Alcaraz

//	Se introducen los pesos de los usuarios en un vector y se ordenan de menor a mayor. A continuaci�n, con dos �ndices, se recorre el vector desde los
//	extremos hacia el centro. Si los usuarios a los que apuntan los �ndices no superan el peso m�ximo, se suma uno al n�mero de telesillas
//	y se avanzan ambos �ndices. Si por el contrario superan el peso m�ximo, se avanza �nicamente el �ndice de la derecha y se suma uno al n�mero de
//	telesillas.

//	El coste de la funci�n es el coste de ordenar el vector, es decir, O(N*logN), siendo N el n�mero de usuarios que esperan subir por el telesilla.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


int telesillas(std::vector<int>& usuarios, const int& P) {
	std::sort(usuarios.begin(), usuarios.end(), std::less<int>());

	int i = 0, j = usuarios.size() - 1;
	int telesillas = 0;

	while (i <= j) {
		if (usuarios[i] + usuarios[j] > P)
			--j;
		else {
			++i; --j;
		}

		telesillas++;
	}

	return telesillas;
}

//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int P, N;

	std::cin >> P >> N;

	if (!std::cin)
		return false;

	std::vector<int> usuarios(N);

	for (int i = 0; i < N; ++i)
		std::cin >> usuarios[i];

	int num_telesillas = telesillas(usuarios, P);
	
	std::cout << num_telesillas << "\n";

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