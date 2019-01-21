//	Mª Victoria Barylak Alcaraz

//	Se interpreta la matriz de la entrada como un grafo implícito, en el que las casillas son los vértices, y las conexiones de arriba, abajo,
//	izquierda y derecha son las aristas.

//	Para contar el número de manchas, se realiza un recorrido en profundidad, sumando uno al contador de manchas cada vez que se inicia un 
//	nuevo recorrido. Para contar el tamaño de la mancha más grande, se utiliza el mismo recorrido en profundida, sumando uno cada vez que se
//	llama con una nueva casilla.

//	El coste de la función es de O(E + V), siendo E el número de aristas y V el número de vértices.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

const std::vector<std::pair<int, int>> dirs = { {0,1}, {1,0}, {0,-1}, {-1,0} };


void DFS(std::vector<std::string> const& bitmap, std::vector<std::vector<bool>>& marked, const int F, const int C, int f, int c, int& tam) {
	marked[f][c] = true;

	for (auto d : dirs) {
		int nf = f + d.first, nc = c + d.second;
		if (0 <= nf && nf < F && 0 <= nc && nc < C && !marked[nf][nc] && bitmap[nf][nc] == '#') {
			tam++;
			DFS(bitmap, marked, F, C, nf, nc, tam);
		}
	}


}


int manchas_negras(std::vector<std::string> const& bitmap, const int F, const int C, int& num_manchas) {
	std::vector<std::vector<bool>> marked(F, std::vector<bool>(C, false));
	int max_tam = 0;

	for (int f = 0; f < F; ++f) {
		for (int c = 0; c < C; ++c) {
			if (!marked[f][c] && bitmap[f][c] == '#') {
				int tam = 1; num_manchas++;
				DFS(bitmap, marked, F, C, f, c, tam);
				max_tam = std::max(max_tam, tam);
			}
		}
	}

	return max_tam;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int F, C;

	std::cin >> F >> C;

	if (!std::cin)
		return false;

	std::vector<std::string> bitmap(F);
	int num_manchas = 0;

	for (int i = 0; i < F; ++i)
		std::cin >> bitmap[i];

	int mayor_mancha = manchas_negras(bitmap, F, C, num_manchas);

	std::cout << num_manchas << " " << mayor_mancha << "\n";

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