//	Mª Victoria Barylak Alcaraz

//	Se representan los edificios con una estructuca con dos enteros, el extremo occidental (ini) y el extremo oriental (fin) del edificio, y
//	se ordenan de menor a mayor extremo oriental. Se tiene un contador de los túneles que hay que construir, inicializado a 1 (ya que con que sólo haya
//	un edificio, ya se necesita un túnel), y una variable que almacena el alcance del túnel (el extremo más oriental del primer edificio que cubre que,
//	en un primer momento, es el primer edificio).
//	A continuación se recorren los demás edificios; si su extremo occidental está cubierto por el alcance del túnel, no hace falta construir más, si por el 
//	contrario, el extremo occidental es mayor que el alcance del túnel, se incrementa en uno el número de túneles a construir, y se actualiza el alcance
//	del último túnel con el extremo más oriental del último edificio recorrido.

//	El coste del problema es de O(N*logN), siendo N el número de edificios.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


typedef struct {
	int ini, fin;
}Edificio;

bool operator<(Edificio const& e1, Edificio const& e2) {
	return e1.fin < e2.fin;
}

int primera_linea(std::vector<Edificio>& edificios) {
	std::sort(edificios.begin(), edificios.end());
	int tuneles = 1, alcance = edificios[0].fin;

	for (int e = 1; e < edificios.size(); ++e) {
		if (edificios[e].ini >= alcance) {
			tuneles++;
			alcance = edificios[e].fin;
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

	std::vector<Edificio> edificios;

	for (int i = 0; i < N; ++i) {
		int ini, fin;

		std::cin >> ini >> fin;

		edificios.push_back({ ini, fin });
	}

	int tuneles = primera_linea(edificios);

	std::cout << tuneles << "\n";

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