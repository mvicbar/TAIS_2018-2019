//Grupo E, M� Victoria Barylak Alcaraz

//	Para conseguir minimizar la suma de los valores absolutos de las diferencias entre las alturas de los esquiadores y las alturas de los esqu�s
//	hay que asignar a los esquiadores m�s bajos los esqu�s m�s cortos, y a los esquiadores m�s altos los esqu�s m�s largos. Por lo tanto, hay que
//	ordenar tanto alturas de esquiadores como longitudes de esqu�s de menor a mayor.

//	El coste de la funci�n es de O(N * logN), siendo N el n�mero de esquiadores y pares de esqu�s, ya que es la complejidad de la funci�n "std::sort"
//	y despu�s de �sta simplemente se hace un recorrido sobre un vector de N elementos.

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