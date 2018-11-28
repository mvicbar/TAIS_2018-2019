//Grupo E, Mª Victoria Barylak Alcaraz

//	Para minimizar el número de telesillas necesario, se ordena a los esquiadores por pesos de menor a mayor. A continuación, se recorre el vector con dos
//	índices, uno que empieza por el esquiador más ligero y otro por el esquiador más pesado. Se comparan los dos esquiadores; si el telesilla puede aguantar
//	la suma de ambos pesos, se avanzan ambos índices y se suma uno al número de telesillas que se necesitas, si el telesilla no puede aguantar los pesos,
//	se avanza el índice de la derecha (el que empieza por el más pesado), en busca de alguien cuyo peso sea menor, y se suma uno al número de telesillas necesarios.

//	El coste de la función es el coste de ordenar a los esquiadores por pesos, es decir, O(N * logN), siendo N el número de esquiadores.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


int telesilla(std::vector<int>& esquiadores, const int& peso) {
	int telesillas = 0;

	std::sort(esquiadores.begin(), esquiadores.end());

	int i = 0, j = esquiadores.size() - 1;
	while (i <= j) {

		if (i != j && esquiadores[i] + esquiadores[j] <= peso) {	//el telesilla puede aguantar el peso de ambos esquiadores
			i++;
		}
		
		j--; telesillas++;	//buscamos un esquiador más ligero y añadimos un telesilla para el esquiador que se ha quedado desparejado
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

	std::vector<int> esquiadores(N);

	for (int i = 0; i < N; i++)
		std::cin >> esquiadores[i];

	std::cout << telesilla(esquiadores, P) << "\n";

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