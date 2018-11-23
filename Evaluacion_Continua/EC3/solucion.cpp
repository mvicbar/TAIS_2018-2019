
// TAIS15; Mª Victoria Barylak ALcaraz y Gonzalo Rivas Fernández

//	Representamos el laberinto como un grafo dirigido valorado en el que los vértices son las celdas y las aristas los pasadizos que las conectan. 
//	Como todos los ratones tienen que llegar a la misma celda desde todas las demás, invertimos el grafo y aplicamos el algoritmo de Dijkstra para
//	obetener el tiempo mínimo desde la salida a todos las celdas de inicio. Si el tiempo es menor o igual al tiempo de cronómetro, el ratón ha llegado
//	y se le cuenta, si no, no se le cuenta.

//	Es un problema de camino mínimo, convirtiendo distancias en tiempos.

#include <iostream>
#include <fstream>
#include <vector>

#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

using namespace std;

const int INFINITO = 1000000000;

void relajar(AristaDirigida<int>& a, std::vector<AristaDirigida<int>>& edgeTo, std::vector<int>& distTo, IndexPQ<int>& pq) {
	int v = a.from(), w = a.to();

	if (distTo[w] > distTo[v] + a.valor()) {
		distTo[w] = distTo[v] + a.valor();
		edgeTo[w] = a;
		pq.update(w, distTo[w]);
	}
}

// Coste: O(P * log N), siendo P el número de pasadizos y N el número de celdas
void experimento(GrafoDirigidoValorado<int> const& laberinto, int& salida, int& tiempo) {
	std::vector<AristaDirigida<int>> edgeTo(laberinto.V());	
	std::vector<int> distTo(laberinto.V(), INFINITO);
	IndexPQ<int> pq(laberinto.V());

	distTo[salida] = 0;
	pq.push(salida, 0);
	while (!pq.empty()) {
		int v = pq.top().elem; pq.pop();
		for (AristaDirigida<int> a : laberinto.ady(v))
			relajar(a, edgeTo, distTo, pq);
	}

	int ratones = 0;

	for (int i = 0; i < distTo.size(); i++) {
		if (i != salida && distTo[i] <= tiempo)
			ratones++;
	}

	std::cout << ratones << "\n";
}

bool resuelveCaso() {
	int N, //número de celdas
		S, //salida
		T, //tiempo de cronómetro
		P; //número de pasadizos

	cin >> N >> S >> T >> P;

	if (!cin)
		return false;

	GrafoDirigidoValorado<int> laberinto(N);

	//Construcción del grafo
	for (int i = 0; i < P; i++) {
		int a, b, segundos;

		cin >> a >> b >> segundos;
		laberinto.ponArista({ a - 1, b - 1, segundos });
	}

	S = S - 1;

	// Coste de invertir el grafo: O(P + N), siendo P el número de pasadizos y N el número de celdas; porque cada celda se recorre sólo una vez
	// y por cada celda se recorren sus celdas adyacentes sólo una vez.
	experimento(laberinto.inverso(), S, T);

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
