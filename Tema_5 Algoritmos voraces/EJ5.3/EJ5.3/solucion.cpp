//Grupo E, M� Victoria Barylak Alcaraz

//	Para conseguir maximizar el n�mero de coches que pueden ponerse en funcionamiento, hay que intentar juntar en un mismo coche la pila con mayor voltaje
//	y la pila con menor voltaje de forma que la suma de sus voltajes sea mayor o igual al voltaje m�nimo necesario.
//	Para ello, ordenamos las pilas de menor a mayor voltaje y las recorremos con dos �ndices, uno que empieza por la pila de menor voltaje y otro por la pila
//	de mayor voltaje. Se comparan ambas pilas; si la suma de los voltajes es mayor o igual al voltaje m�nimo necesario, se suma 1 al n�mero de coches y se avanzan
//	ambos �ndices (cada uno en la direcci�n que corresponde), si por el contrario la suma de los voltajes es menor que el voltaje m�nimo necesario, se mantiene
//	el �ndice de la pila con mayor voltaje y se avanza s�lo el de la pila de menor voltaje. Se contin�a hasta que ambos �ndices se cruzan.

//	El coste de la funci�n es el coste de ordenar el vector de menor a mayor, es decir, O(N * logN), siendo N el n�mero de pilas, ya que despu�s de ordenar
//	simplemente se hace un recorrido sobre el vector.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


//	Coste: O(N * logN)
int carreras_de_coches(std::vector<int>& pilas, const int& voltaje) {
	std::sort(pilas.begin(), pilas.end());

	int ini = 0, fin = pilas.size() - 1, coches = 0;

	while (ini < fin) {
		if (pilas[ini] + pilas[fin] >= voltaje) {
			coches++;
			ini++; fin--;
		}
		else
			ini++;
	}

	return coches;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
void resuelveCaso() {
	int N, V;

	std::cin >> N >> V;

	std::vector<int> pilas(N);

	for (int p = 0; p < N; ++p)
		std::cin >> pilas[p];

	std::cout << carreras_de_coches(pilas, V) << "\n";
}


int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}