//	Mª Victoria Barylak Alcaraz

//	La foto de las ovejas se representa mediante una matriz. Sobre dicha matriz, que se interpreta como un grafo implícito, se lleva a cabo
//	una búsqueda en profundidad. Se cuentan las manchas blancas que aparecen en la foto, y al final se devuelve ese número menos 1, ya
//	que el fondo de la foto es siempre blanco.

//	El coste de la función es el coste de la búsqueda en profundidad, es decir, O(V + E), siendo V el número de vértices y E el número de aristas.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const std::vector<std::pair<int, int>> dirs = { {1,0}, {0,1}, {-1,0}, {0,-1} };

void DFS(std::vector<std::string> const& foto, int& i, int& j, const int& F, const int& C, std::vector<std::vector<bool>>& marked) {
	marked[i][j] = true;

	for (auto d : dirs) {
		int ni = i + d.first, nj = j + d.second;
		if (0 <= ni && ni < F && 0 <= nj && nj < C && foto[ni][nj] == '.' && !marked[ni][nj])
			DFS(foto, ni, nj, F, C, marked);
	}
}

int ovejas_blancas(std::vector<std::string> const& foto, const int& F, const int& C) {
	std::vector<std::vector<bool>> marked(F, std::vector<bool>(C, false));
	int blancas = 0;

	for (int i = 0; i < F; ++i) {
		for (int j = 0; j < C; ++j) {
			if (foto[i][j] == '.' && !marked[i][j]) {
				blancas++;
				DFS(foto, i, j, F, C, marked);
			}
		}
	}

	return blancas - 1;
}

//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int ANCHO, ALTO;

	std::cin >> ANCHO >> ALTO;

	if (!std::cin)
		return false;

	std::vector<std::string> foto(ALTO);

	for (int i = 0; i < ALTO; ++i)
		std::cin >> foto[i];

	int num_ovejas = ovejas_blancas(foto, ALTO, ANCHO);

	std::cout << num_ovejas << "\n";

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