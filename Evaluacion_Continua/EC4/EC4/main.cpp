
//	Pablo López Veleiro y Mª Victoria Barylak Alcaraz

//	Para minimizar el número de equipaciones nuevas que hay que comprar para la temporada, ordenamos tanto las
//	tallas de los jugadores como las tallas de las equipacines de menor a mayor. A continuación, recorremos ambos
//	vectores de tallas, cada uno con un índice distinto. Si el jugador puede llevar la equipación (tiene la misma
//	talla o una más), se avanzan ambos índices; si el jugador es mucho más pequeño, se avanza el índice de los 
//	jugadores y se suma uno a las equipaciones nuevas; si el jugador es más grande, se avanza el índice de las equipaciones.

//	El coste de la función es O(max(N, M)), siendo N el número de jugadores y M el número de
//	equipaciones.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


bool resuelveCaso() {
	int N, M;
	cin >> N >> M;

	if (!cin)
		return false;

	std::vector<int> jugadores(N);
	std::vector <int> equipaciones(M);

	for (int i = 0; i < N; i++)
		cin >> jugadores[i];

	for (int j = 0; j < M; j++)
		cin >> equipaciones[j];

	sort(jugadores.begin(), jugadores.end()); //O(N * logN)
	sort(equipaciones.begin(), equipaciones.end());	//O(M * logM)

	int j = 0, e = 0;
	int equipaciones_nuevas = 0;
	while (j < N && e < M) {	//O(max(N, M))
		if (jugadores[j] - equipaciones[e] == -1 || jugadores[j] - equipaciones[e] == 0) {	//el jugador puede llevar la equipación
			j++; e++;
		}
		else {
			if (jugadores[j] < equipaciones[e] + 1) {	//el jugador es muy pequeño, se necesita una equipación
				equipaciones_nuevas++;
				j++;
			}
			else {	//el jugador es muy grande para la equipación, hay que buscarle otra talla mayor
				e++;
			}
		}
	}

	if (j < N)	//O(1)
		equipaciones_nuevas += N - j;

	cout << equipaciones_nuevas << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
