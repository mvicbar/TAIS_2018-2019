//Grupo E, Mª Victoria Barylak Alcaraz

//	Para conseguir minimizar la suma de los valores absolutos de las diferencias entre las alturas de los esquiadores y las alturas de los esquís
//	hay que asignar a los esquiadores más bajos los esquís más cortos, y a los esquiadores más altos los esquís más largos. Por lo tanto, hay que
//	ordenar tanto alturas de esquiadores como longitudes de esquís de menor a mayor.

//	El coste de la función es de O(N * logN), siendo N el número de esquiadores y pares de esquís, ya que es la complejidad de la función "std::sort"
//	y después de ésta simplemente se hace un recorrido sobre un vector de N elementos.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


//	Coste: O(N * logN)
int esquiando_en_alaska(std::vector<int>& alturas_esquiadores, std::vector<int>& alturas_esquis) {
	int suma = 0;

	std::sort(alturas_esquiadores.begin(), alturas_esquiadores.end());
	std::sort(alturas_esquis.begin(), alturas_esquis.end());

	for (int i = 0; i < alturas_esquiadores.size(); ++i) 
		suma += std::abs(alturas_esquiadores[i] - alturas_esquis[i]);

	return suma;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N;

	std::cin >> N;

	if (N == 0)
		return false;

	std::vector<int> alturas_esquiadores(N);
	std::vector<int> alturas_esquis(N);

	for (int i = 0; i < N; ++i) 
		std::cin >> alturas_esquiadores[i];

	for (int j = 0; j < N; ++j)
		std::cin >> alturas_esquis[j];

	std::cout << esquiando_en_alaska(alturas_esquiadores, alturas_esquis) << "\n";

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