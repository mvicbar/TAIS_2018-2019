//Grupo E, Mª Victoria Barylak Alcaraz

//	Para conseguir maximizar la suma de las diferencias de los puntos de las victorias de los Broncos deben coincidir en un mismo partido la puntuación 
//	máxima de la temporada de los Broncos, con la puntuación mínima de la temporada de los rivales, así sucesivamente. Por lo tanto, se ordenan las puntuaciones
//	de los broncos de mayor a menor, y las puntuaciones de los rivales de menor a mayor. 

//	El coste del algoritmo es de O(N * logN), siendo N el número de partidos pronosticados, ya que esta es la complejidad del algoritmo "std::sort", y después 
//	de realizar la llamada sólo se hace un recorrido sobre un vector.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>


//	Coste: O(N * logN)
int superbowl(std::vector<int>& resultados_rivales, std::vector<int>& resultados_broncos) {
	int suma = 0;

	std::sort(resultados_rivales.begin(), resultados_rivales.end());
	std::sort(resultados_broncos.begin(), resultados_broncos.end(), std::greater<int>());

	for (int i = 0; i < resultados_broncos.size(); ++i) {
		if(resultados_broncos[i] > resultados_rivales[i])
			suma += resultados_broncos[i] - resultados_rivales[i];
	}

	return suma;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N;

	std::cin >> N;

	if (N == 0)
		return false;

	std::vector<int> resultados_rivales(N);
	std::vector<int> resultados_broncos(N);

	for (int i = 0; i < N; ++i)
		std::cin >> resultados_rivales[i];

	for (int j = 0; j < N; ++j)
		std::cin >> resultados_broncos[j];

	std::cout << superbowl(resultados_rivales, resultados_broncos) << "\n";

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