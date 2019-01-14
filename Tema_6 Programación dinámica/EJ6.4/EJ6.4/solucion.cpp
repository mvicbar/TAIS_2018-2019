//Grupo E, Mª Victoria Barylak Alcaraz


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "Matriz.h"


//	patindromo(i, j) = longitud del palíndromo más grande que se puede conseguir teniendo en cuenta las letras de la i a la j

//	patindromo(i, j) = patindromo(i + 1, j - 1) + 2; si letra(i) = letra(j)
//					   max(patindromo(i + 1, j), patindromo(i, j - 1)); si letra(i) != letra(j)

//	patindromo(i, j) = 1; cuando i = j

//	Coste: O(n*n) en espacio, y O(n*n/2)en tiempo, ya que se recorre sólo la mitad de la matriz

std::string construirPalindromo(Matriz<int>& patindromo, const int tam, std::string const& patos) {
	int longitudPalindromo = patindromo[1][tam];
	std::string palindromo(longitudPalindromo + 1, ' ');
	int p = 1, q = tam;	//índices para las letras de la palabra
	int v = 1, w = longitudPalindromo;	//índices para las letras del palíndromo

	while (longitudPalindromo > 0) {

		if (patos[p] == patos[q]) {
			palindromo[v] = patos[p];
			palindromo[w] = patos[q];
			longitudPalindromo = longitudPalindromo - 2;

			p++; q--;
			v++; w--;
		}
		else if (longitudPalindromo == 1) {
			palindromo[v] = patos[q];
			longitudPalindromo--;
		}
		else {
			if (patindromo[p][q - 1] > patindromo[p + 1][q])
				q--;
			else
				p++;
		}
	}

	std::string res = palindromo.substr(1, palindromo.size() - 1);

	return res;
}


std::string patindromo(std::string const& patos) {
	int n = patos.size() - 1;
	Matriz<int> patindromo(n + 1, n + 1, 0);

	for (int d = 1; d <= n - 1; d++)
		patindromo[d][d] = 1;	//la diagonal principal se inicializa a 1

	for (int diag = 1; diag <= n - 1; diag++) {	//bucle que recorre las diagonales de la matriz
		for (int i = 1; i <= n - diag; i++) {	//bucle que recorre los elementos de las matrices
			int j = i + diag;

			if (patos[i] == patos[j])
				patindromo[i][j] = patindromo[i + 1][j - 1] + 2;
			else if (patos[i] != patos[j])
				patindromo[i][j] = std::max(patindromo[i + 1][j], patindromo[i][j - 1]);

		}
	}

	std::string palindromo = construirPalindromo(patindromo, n, patos);

	return palindromo;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	std::string patos;

	std::cin >> patos;
	patos = " " + patos;

	if (!std::cin)
		return false;

	std::string palindromo = patindromo(patos);

	std::cout << palindromo << "\n";

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