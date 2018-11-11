//Grupo E, Mª Victoria Barylak Alcaraz

//	Se representa la comarca como un grafo dirigido valorado donde las casas son vértices, los caminos aristas, y el esfuerzo de recorrer un camino el valor de la 
//	arista. Se introducen las casas a las que hay que enviar un paquete en un vector.

//	Para calcular el esfuerzo de enviar los paquetes a las distintas casas, se ejecuta el algoritmo de Dijkstra sobre el grafo, y se suman las distancias de las 
//	distintas casas a la oficina. Para calcular el esfuerzo de volver de las casas a la oficina, se invierte el grafo y se hace lo mismo. Si en algún momento la
//	distancia a alguna casa es igual a infinito, quiere decir que no exite un camino que conecte la oficina con la casa, ya sea de ida o de vuelta y, por lo tanto,
//	es imposible realizar la entrega.

//	El coste del algoritmo de Dijkstra es de O(C * log N), siendo C el número de calles, y N el número de casas. Este coste se debe a que cada calle se recorre 
//	una única vez (O(C)), y por cada calle se pueden realizar actualizaciones sobre una cola de prioridades variables que contiene las casa ordenadas (O(log N)).

#include <iostream>
#include <fstream>
#include <vector>

#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

const int INFINITO = 1000000000;


void relajar(AristaDirigida<int>& a, std::vector<AristaDirigida<int>>& edgeTo, std::vector<int>& distTo, IndexPQ<int>& pq) {
	int v = a.from(), w = a.to();

	if (distTo[w] > distTo[v] + a.valor()) {
		distTo[w] = distTo[v] + a.valor();
		edgeTo[w] = a;
		pq.update(w, distTo[w]);
	}
}


int SP(GrafoDirigidoValorado<int> const& comarca, const int& oficina, std::vector<int> const& clientes) {
	std::vector<AristaDirigida<int>> edgeTo(comarca.V());
	std::vector<int> distTo(comarca.V(), INFINITO);
	IndexPQ<int> pq(comarca.V());
	int esfuerzoTotal = 0;

	distTo[oficina] = 0;
	pq.push(oficina, 0);
	while (!pq.empty()) {
		int v = pq.top().elem; pq.pop();

		for (AristaDirigida<int> a : comarca.ady(v))
			relajar(a, edgeTo, distTo, pq);
	}

	int casa = 0;
	while (casa < clientes.size() && distTo[clientes[casa]] != INFINITO) {
		esfuerzoTotal += distTo[clientes[casa]];
		casa++;
	}

	if (casa < clientes.size() && distTo[clientes[casa]] == INFINITO)
		esfuerzoTotal = -1;
	

	return esfuerzoTotal;
}


void oficinaDeTransportes(GrafoDirigidoValorado<int> const& comarca, const int& oficina, std::vector<int> const& clientes) {
	int esfuerzoIdas = 0, esfuerzoVueltas = 0;

	esfuerzoIdas = SP(comarca, oficina, clientes);

	if (esfuerzoIdas == -1)
		std::cout << "Imposible\n";
	else {
		//Al invertir el grafo, se obtienen los caminos de vuelta a la oficina
		GrafoDirigidoValorado<int> comarcaInvertida = comarca.inverso();
		esfuerzoVueltas = SP(comarcaInvertida, oficina, clientes);

		if (esfuerzoVueltas == -1)
			std::cout << "Imposible\n";
		else
			std::cout << esfuerzoIdas + esfuerzoVueltas << "\n";
	}
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N, C;

	std::cin >> N;

	if (!std::cin)
		return false;

	GrafoDirigidoValorado<int> comarca(N);

	std::cin >> C;

	/*Construcción del grafo*/
	for (int i = 0; i < C; ++i) {
		int origen, destino, esfuerzo;
		std::cin >> origen >> destino >> esfuerzo;
		comarca.ponArista({ origen - 1, destino - 1, esfuerzo });
	}

	int oficina, paquetes;

	std::cin >> oficina >> paquetes;

	std::vector<int> clientes;
	
	/*Lectura de las casas a las que hay que enviar un paquete*/
	for (int j = 0; j < paquetes; ++j) {
		int pedido;
		std::cin >> pedido;
		clientes.push_back(pedido - 1);
	}

	oficinaDeTransportes(comarca, oficina - 1, clientes);

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