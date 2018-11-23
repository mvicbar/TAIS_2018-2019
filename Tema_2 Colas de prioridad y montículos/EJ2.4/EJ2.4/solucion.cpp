//Grupo E, Mª Victoria Barylak Alcaraz

#include <iostream>
#include <fstream>
#include <algorithm>

#include "PriorityQueue.h"


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
//Coste de la funcion: O(n * logn), siendo n el numero de elementos que se introducen en las colas.
bool resuelveCaso() {
	int num, n;

	std::cin >> num;

	if (num == 0)
		return false;

	PriorityQueue<int, std::less<int>> colaMenor;
	PriorityQueue<int, std::greater<int>> colaMayor;

	std::cin >> n;
	std::cout << 2 * n << " ";
	colaMenor.push(n);

	for (int i = 1; i < num; ++i) {
		std::cin >> n;

		if (n > colaMenor.top()) {
			colaMenor.push(n);
		}
		else {
			colaMayor.push(n);
		}

		/*Balanceo de las colas*/
		if (colaMenor.size() == colaMayor.size() + 2) {
			colaMayor.push(colaMenor.top());
			colaMenor.pop();
		}
		else if (colaMayor.size() == colaMenor.size() + 2) {
			colaMenor.push(colaMayor.top());
			colaMayor.pop();
		}

		/*Numero impar de elementos*/
		if (colaMenor.size() > colaMayor.size()) {
			std::cout << 2 * colaMenor.top() << " ";
		}
		else if (colaMayor.size() > colaMenor.size()) {
			std::cout << 2 * colaMayor.top() << " ";
		}
		else { /*Numero par de elementos*/
			std::cout << colaMayor.top() + colaMenor.top() << " ";
		}
	}
		
	std::cout << "\n";

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