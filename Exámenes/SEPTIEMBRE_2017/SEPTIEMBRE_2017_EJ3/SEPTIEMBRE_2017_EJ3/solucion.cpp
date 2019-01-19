//	M� Victoria Barylak Alcaraz

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "Matriz.h"

//	Definici�n de la funci�n:
//		aiofobia(i, j) = n�mero m�nimo de letras que hacen falta para formar un pal�ndromo con las letras de la i a la j

//	Definici�n recursiva:
//		aiofobia(i, j) = min(aiofobia(i, j - 1), aiofobia(i + 1, j)) + 1; si letra[i] != letra[j]
//					   = min(aiofobia(i, j - 1), aiofobia(i + 1, j)) - 1; si letra[i] == letra[j]

//	Caso base:
//		aiofobia(i, i) = 0;

//	Coste de la funci�n: O((N*N)/2), en tiempo, ya que s�lo se recorre la mitad de la matriz; y O(N*N) en espacio, siendo N la longitud de la palabra.
int aibofobia(std::string const& palabra) {
	int n = palabra.size();
	Matriz<int> palindromo(n + 1, n + 1, 0);

	for (int d = 1; d <= n; d++) {
		for (int i = 1; i <= n - d; ++i) {
			int j = i + d;

			if (palabra[i - 1] == palabra[j - 1])
				palindromo[i][j] = std::min(palindromo[i][j - 1], palindromo[i + 1][j]) - 1;
			else
				palindromo[i][j] = std::min(palindromo[i][j - 1], palindromo[i + 1][j]) + 1;
			
		}
	}

	return palindromo[1][n];
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	std::string palabra;

	std::cin >> palabra;

	if (!std::cin)
		return false;

	int letras = aibofobia(palabra);

	std::cout << letras << "\n";

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