//Grupo E, M� Victoria Barylak Alcaraz

//	Para conseguir minimizar el n�mero de pasadizos a construir se ordenan los edificios de m�s lejano a m�s cercano extremo oriental. Se inicializa el
//	n�mero de pasadizos a 1, ya que con que haya un �nico edificio ya se necesita un pasadizo, y se mantiene en una variable el extremo m�s oriental
//	del edificio al que cubre el pasadizo, en este caso, el primero de ellos. A continuaci�n, se recorren los edificios y se comparan sus extremos m�s
//	occidentales con el extremo m�s oriental del edificio cubierto por el �ltimo pasadizo; si el extremo occidental es menor, no hace falta a�adir un 
//	nuevo pasadizo, si por el contrario es mayor, se suma 1 al n�mero de pasadizos y se actualiza el extremo oriental.

//	El coste de la funci�n es el coste de ordenar el vector de edificios, es decir, O(N * logN), siendo N el n�mero de edificios
//	, ya que despu�s s�lo se hace un recorrido sobre el mismo.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>


bool operator< (std::pair<int, int>& e1, std::pair<int, int>& e2) {
	return e1.second < e2.second;
}


//	Coste: O(N *logN), siendo N el n�mero de edificios
int primera_linea_de_playa(std::vector<std::pair<int, int>>& edificios) {
	std::sort(edificios.begin(), edificios.end(), operator<);

	int tuneles = 1, fin = edificios[0].second;

	for (int i = 1; i < edificios.size(); ++i) {

		if (edificios[i].first >= fin) {
			fin = edificios[i].second;
			tuneles++;
		}
	}

	return tuneles;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N;

	std::cin >> N;

	if (N == 0)
		return false;

	std::vector<std::pair<int, int>> edificios(N);

	for (int i = 0; i < N; ++i)
		std::cin >> edificios[i].first >> edificios[i].second;

	std::cout << primera_linea_de_playa(edificios) << "\n";

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