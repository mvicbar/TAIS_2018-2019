//	Grupo E; Mª Victoria Barylak Alcaraz

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Matriz.h"

typedef struct {
	int profundidad;
	int monedas;
} Cofre;

//	cazatesoros(i, T) = número máximo de monedas de oro que se pueden recuperar en un tiempo T cogiendo algunos de los cofres del 1 al i

//	cazatesoros(i, T) = cazatesoros(i - 1, T); si p[i] + 2*p[i] > T 
//					  = max( cazatesoros(i - 1, T), cazatesoros(i - 1, T - p[i] + 2*p[i]) + m[i] ); si p[i] + 2*p[i] <= T

//cazatesoros(0, T) = 0;
//cazatesoros(i, 0) = 0;

//Coste temporal y espacial: O(N*T), siendo N el número de cofres, y T los segundos de inmersión
void cazatesoros(int N, int T, std::vector<Cofre>& cofres, std::vector<bool>& cuales, int& monedas, int& num_cofres) {
	int n = cofres.size() - 1;
	Matriz<int> cofre(n + 1, T + 1, 0); 
	//std::vector<int> cofre(T + 1, 0); 

	//Optimización
	/*for (int i = 1; i <= n; ++i) {
		for (int j = T; j >= 1; --j) {
			if (cofres[i].profundidad + (2 * cofres[i].profundidad) <= j) {
				cofre[j] = std::max(cofre[j], cofre[j - (cofres[i].profundidad + (2 * cofres[i].profundidad))] + cofres[i].monedas);
			}
		}
	}*/

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= T; ++j) {
			if (cofres[i].profundidad + (2 * cofres[i].profundidad) > j) {
				cofre[i][j] = cofre[i - 1][j];
			}
			else {
				cofre[i][j] = std::max(cofre[i - 1][j], cofre[i - 1][j - (cofres[i].profundidad + (2 * cofres[i].profundidad))] + cofres[i].monedas);
			}
		}
	}

	monedas = cofre[N][T];
	//monedas = cofre[T];

	int resto = T;
	for (int i = n; i >= 1; --i) {
		if (cofre[i][resto] == cofre[i - 1][resto]) {	//no se recupera el cofre i
			cuales[i] = false;
		}
		else {	//se recupera el cofre i
			cuales[i] = true;
			num_cofres++;
			resto = resto - (cofres[i].profundidad + (2 * cofres[i].profundidad));
		}
	}

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int T, N;
	int monedas = 0, num_cofres = 0;

	std::cin >> T;

	if (!std::cin)
		return false;

	std::cin >> N;

	std::vector<Cofre> cofres(N+1);
	std::vector<bool> cuales(N+1);

	for (int i = 1; i <= N; ++i) {
		Cofre c;
		std::cin >> c.profundidad >> c.monedas;
		cofres[i] = c;
	}

	cazatesoros(N, T, cofres, cuales, monedas, num_cofres);

	std::cout << monedas << "\n";
	std::cout << num_cofres << "\n";

	for (int i = 1; i <= N; ++i) {
		if (cuales[i])
			std::cout << cofres[i].profundidad << " " << cofres[i].monedas << "\n";
	}

	std::cout << "----\n";

	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}