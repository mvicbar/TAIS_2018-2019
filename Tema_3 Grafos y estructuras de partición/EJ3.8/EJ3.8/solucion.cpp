//	Grupo: E; Mª Victoria Barylak Alcaraz

//	Se representa la web como un grafo dirigido valorado donde los nodos son las páginas web, las aristas son los enlaces que conectan dos páginas distintas, y el valor
//	de las aristas es el tiempo que se tarda en encontrar el enlace dentro de la página origen y pulsarlo para ir a la página destino.
//	Se tiene también un vector con los tiempos de carga de todas las páginas.

//	Sobre el grafo, se realiza el algoritmo de Dijkstra para encontrar los caminos mínimos desde el origen a todos los demás vértices. Una vez finalizado el algoritmo,
//	se comprueba si se ha llegado a la última página (comprobando si la distancia hasta ella es distinta a infinito). Si no llega ninguna arista, se muestra por pantalla; si llega
//	alguna arista, se recorren las páginas desde la última hasta la primera acumulando los tiempos de carga de todas las páginas y los tiempos que se tarda en encontrar
//	los enlaces.

//	El coste del algoritmo de Dijkstra es de O(M * log N), siendo M el número de enlaces entre las páginas de la web, y N el número de páginas. Este coste se debe a que 
//	cada enlace se recorre una única vez (O(M)), y por cada enlacec se pueden realizar actualizaciones sobre una cola de prioridades variables que contiene las
//	páginas ordenadas (O(log N)).


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

const int INFINITO = 1000000000;

//Coste: O(E * log V), siendo E el número de aristas de grafo, y V el número de vértices
void relajar(AristaDirigida<int>& a, std::vector<int>& distTo, std::vector<AristaDirigida<int>>& edgeTo, IndexPQ<int>& pq) {
	int v = a.from();
	int w = a.to();

	if (distTo[w] > distTo[v] + a.valor()) {
		distTo[w] = distTo[v] + a.valor();
		edgeTo[w] = a;
		pq.update(w, distTo[w]);
	}
}


void navegar(GrafoDirigidoValorado<int> const& web, std::vector<int> const& tiempoCarga) {
	std::vector<int> distTo(web.V(), INFINITO);
	std::vector<AristaDirigida<int>> edgeTo(web.V());
	IndexPQ<int> pq(web.V());

	distTo[0] = 0;
	pq.push(0, 0);

	while (!pq.empty()) {
		int v = pq.top().elem; pq.pop();
		for (AristaDirigida<int> a : web.ady(v))
			relajar(a, distTo, edgeTo, pq);
	}

	int tiempoAcumulado = 0;
	int ultimo = web.V() - 1;

	/*Si la distancia a la última página es infinito, es porque no se ha podido llegar a ella*/
	if (distTo[ultimo] == INFINITO)
		std::cout << "IMPOSIBLE\n";
	else {
		tiempoAcumulado = distTo[ultimo] + tiempoCarga[0];
		std::cout << tiempoAcumulado << "\n";
	}
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, M;

	std::cin >> N;	//número de páginas

	if (N == 0)
		return false;

	std::vector<int> tiempoCarga(N);

	/*Vector de tiempos de carga de las páginas*/
	for (int t = 0; t < N; t++)
		std::cin >> tiempoCarga[t];

	std::cin >> M;	//númro de enlaces entre páginas

	/*Construcción del grafo de la web*/
	GrafoDirigidoValorado<int> web(N);
	for (int p = 0; p < M; p++) {
		int origen, destino, tiempo;
		std::cin >> origen >> destino >> tiempo;

		web.ponArista({ origen - 1, destino - 1, tiempo + tiempoCarga[destino - 1] });
	}

	navegar(web, tiempoCarga);

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