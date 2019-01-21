//	Grupo E, Mª Victoria Barylak Alcaraz

//	Para obtener el descuento más grande se ordenan los libros de menor a mayor precio. A continuación, se van considerando por grupos de
//	tres libros, acumulando en el descuento el precio del libro más barato. Se continúa hasta que ya no queden grupos de tres libros
//	por considerar.

//	El coste de la función es el coste de ordenar el vector de precios de los libros, O(N*logN), siendo N el número de libros que se
//	quieren comprar.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>


int libreria(std::vector<int>& libros) {
	std::sort(libros.begin(), libros.end(), std::greater<int>());
	int descuento = 0;
	int i = 0;

	while (libros.size() - i >= 3) {
		descuento = descuento + libros[i + 2];
		i = i + 2 + 1;
	}

	return descuento;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N;

	std::cin >> N;

	if (!std::cin)
		return false;

	std::vector<int> libros(N);

	for (int i = 0; i < N; ++i)
		std::cin >> libros[i];

	int descuento = libreria(libros);

	std::cout << descuento << "\n";

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