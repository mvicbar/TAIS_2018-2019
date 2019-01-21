//	Mª Victoria Barylak Alcaraz


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Matriz.h"

typedef struct {
	int profundidad;
	int oro;
}Cofre;


//	Definición de la función:
//		cazatesoros(i, j) = máxima cantidad de oro que se puede conseguir con una bombona de j segundos de oxígeno, considerando
//						    los cofres del 1 al i

//	Definicion recursiva:
//		cazatesoros(i, j) = cazatesoros(i - 1, j), si profundidad(i) + 2*profundidad(i) > j
//						  = max(cazatesoros(i - 1, j), cazatesoros(i - 1, j - profundidad(i) + 2*profundidad(i)) + oro(i)), si profundidad(i) + 2*profundidad(i) <= j

//	Casos base:
//		cazatesoros(i, 0) = 0;
//		cazatesoros(0, j) = 0;

//	Coste de la función:
//		O(n*T), en espacio adicional y en tiempo, siendo n el número de cofres que hay para rescatar, y T el número de segundos que permite bucear la botella
void cazatesoros(std::vector<Cofre> const& cofres, int T) {
	int n = cofres.size() - 1;
	Matriz<int> tesoro(n + 1, T + 1, 0);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= T; ++j) {
			if ((cofres[i].profundidad + 2*cofres[i].profundidad) > j)
				tesoro[i][j] = tesoro[i - 1][j];
			else
				tesoro[i][j] = std::max(tesoro[i - 1][j], tesoro[i - 1][j - (cofres[i].profundidad + 2 * cofres[i].profundidad)] + cofres[i].oro);
		}
	}

	std::vector<bool> cuales(cofres.size());
	int resto = T, cuantos = 0;
	for (int i = n; i >= 1; --i) {
		if (tesoro[i][resto] == tesoro[i - 1][resto])
			cuales[i] = false;
		else {
			cuales[i] = true;
			cuantos++;
			resto = resto - (cofres[i].profundidad + 2 * cofres[i].profundidad);
		}
	}

	std::cout << tesoro[n][T] << "\n";
	std::cout << cuantos << "\n";

	for (int i = 0; i < cuales.size(); ++i) {
		if (cuales[i])
			std::cout << cofres[i].profundidad << " " << cofres[i].oro << "\n";
	}
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int T, N;

	std::cin >> T;

	if (!std::cin)
		return false;

	std::cin >> N;
	std::vector<Cofre> cofres(N + 1);

	for (int i = 1; i <= N; ++i) {
		int prof, oro;
		std::cin >> prof >> oro;

		cofres[i] = { prof, oro };
	}

	cazatesoros(cofres, T);

	std::cout << "----\n";

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