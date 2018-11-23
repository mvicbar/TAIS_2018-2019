//Grupo E, Mª Victoria Barylak Alcaraz

// Tenemos una matriz de 0s en la que los árboles se representan con 1s. También se tiene un vector de pares donde se guardan las posiciones de los árboles
// talados, y tantos conjuntos disjuntos como casillas hay en el bosque. 

// Se recorren los árboles talados en orden inverso al que fueron cortados (se empieza por el último árbol talado), y cada árbol se une en un mismo conjunto
// con aquellos árboles a los que la ardilla puede llegar saltando. Si después de comprobar todas las posiciones alcanzables quedan unidas las posiciones origen (0,0)
// y destino (N,M), el árbol que se consideraba es el resultado.

// Si después de considerar todos los árbol talados siguen sin estar unidas las posiciones origen y destino, nunca se pudo alcanzar el destino desde el origen.

// Por cada árbol talado se recorren sus posiciones alcanzables, por lo que se podría decir que se realiza un recorrido en profundidad. Los recorridos en
// profundidad tienen un coste de O(V+E), siendo V el número de vectores y E el número de aristas. En este caso, no se consideran las posiciones alcanzables de todas
// las casillas, por lo que sería un coste de O(n + E), donde n es el número de árboles talados, y E el número de posiciones alzanzables.

#include <iostream>
#include <fstream>
#include <cmath>

#include "ConjuntosDisjuntos.h"


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N, M, K, n;

	std::cin >> N >> M >> K >> n;

	if (!std::cin)
		return false;

	ConjuntosDisjuntos bosque((N+1)*(M+1)); //Conjuntos para indicar los árbol alcanzables
	std::vector<std::vector<int>> arboles(N+1, std::vector<int>(M+1, 0));	//Matriz que indica en qué posiciones hay un árbol
	arboles[0][0] = 1; arboles[N][M] = 1;
	int indice_origen = 0 * (M+1) + 0;
	int indice_destino = N * (M+1) + M;

	std::vector<std::pair<int, int>> arboles_talados(n);	//Posiciones de los árboles talados

	int f, c;
	for (int i = 0; i < n; ++i) {
		std::cin >> f >> c;
		std::pair<int, int> arbol = { f, c };
		arboles_talados.push_back(arbol);
	}

	bool found = false;
	std::pair<int, int> resultado = { -1,-1 };
	while (!arboles_talados.empty() && !found) {	//Mientras haya árboles talados por considerar, o no se haya encontrado el árbol buscado
		std::pair<int, int> arbol = arboles_talados.back();
		arboles_talados.pop_back();
		
		int indice_arbol = arbol.first*(M + 1) + arbol.second;

		//Recorrido de las casillas alcanzables
		for (int f = arbol.first - K; f <= arbol.first + K; f++) {
			for (int c = arbol.second - K; c <= arbol.second + K; c++) {

				int nf = (f - arbol.first);
				int nc = (c - arbol.second);

				//Si hay algún árbol que sea alcanzable desde el que estamos, se meten en el mismo conjunto
				if (sqrt(nf*nf + nc * nc) <= K) {
					if (f >= 0 && f <= N && c >= 0 && c <= M && arboles[f][c] == 1) {	
						int indice = f * (M + 1) + c;
						bosque.unir(indice, indice_arbol);
					}
				}
			}
		}

		arboles[arbol.first][arbol.second] = 1;

		if (bosque.unidos(indice_origen, indice_destino)) {
			found = true;
			resultado = arbol;
		}

	}

	if (!found) 
		std::cout << "NUNCA SE PUDO\n";
	else
		std::cout << resultado.first << " " << resultado.second << "\n";

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