// Grupo E, Mª Victoria Barylak Alcaraz

// Para saber cuántas ovejas blancas hay en la foto, contamos manchas blancas.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


const std::vector<std::pair<int, int>> dirs = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 } };

//Recorrido en profundidad de la foto.
//Coste de la función: O(C * F), siendo C el número de columnas y F el número de filas de la foto.
void DFS(std::vector<std::string> const& foto, int i, int j, std::vector<std::vector<bool>>& marked, const int& columnas, const int& filas) {
	marked[i][j] = true;

	for (auto d : dirs) {
		int ni = i + d.first, nj = j + d.second;
		if (0 <= ni && ni < filas && 0 <= nj && nj < columnas && foto[ni][nj] != 'X' && !marked[ni][nj]) {
			DFS(foto, ni, nj, marked, columnas, filas);
		}
	}

}


int ovejas(std::vector<std::string> const& foto, const int columnas, const int filas) {
	int blancas = 0;
	std::vector<std::vector<bool>> marked(filas, std::vector<bool>(columnas, false));

	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {

			if (foto[i][j] != 'X' && !marked[i][j]) {
				blancas++;
				DFS(foto, i, j, marked, columnas, filas);
			}

		}
	}

	blancas--;	//Al final se resta uno al número de manchas blancas, ya que también se cuenta el fondo blanco de la foto como una mancha blanca.

	return blancas;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int columnas, filas;
	std::string marca;

	std::cin >> columnas >> filas;

	if (!std::cin)
		return false;

	std::vector<std::string> foto(filas);

	for (int i = 0; i < filas; ++i) {
		std::cin >> marca;
		foto[i] = marca;
	}

	std::cout << ovejas(foto, columnas, filas) << "\n";

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
