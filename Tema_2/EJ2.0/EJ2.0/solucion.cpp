//Grupo E, Mª Victoria Barylak Alcaraz

#include <iostream>
#include <fstream>

#include "PriorityQueue.h"

//Funcion que resuelve el problema
//Coste de la funcion: O(n), siendo n el numero de elementos del monticulo
long long int resolver(PriorityQueue<long long int>& monticulo) {
	long long int sum1, sum2, esfuerzo = 0;

	while (monticulo.size() > 1) {
		monticulo.pop(sum1);
		monticulo.pop(sum2);
		sum1 += sum2;
		esfuerzo += sum1;
		monticulo.push(sum1);
	}

	return esfuerzo;
}


//Resuelve un caso de prueba, leyendo de la entrada la
//confguracion y escribiendo la respuesta
bool resuelveCaso() {
	PriorityQueue<long long int> monticulo;
	int total, num;

	std::cin >> total;

	if (total == 0)
		return false;

	for (int i = 0; i < total; ++i) {
		std::cin >> num;
		monticulo.push(num);
	}

	long long int sol = resolver(monticulo);

	std::cout << sol << "\n";

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
