
// Jesus Granizo Egido y Mª Victoria Barylak Alcaraz

// Se tiene una cola de prioridades ordenada por tiempos. Mientras queden cajas libres y lleguen clientes, se asignan
// clientes a las cajas, y se actualiza el tiempo total transcurrido para el siguiente cliente.

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

typedef struct {
	int caja;
	int seg;
}tCliente;

bool operator< (tCliente const& c1, tCliente const& c2) {
	return c1.seg < c2.seg || (c1.seg == c2.seg) && c1.caja < c2.caja;
}

//Coste: O(C logN) siendo C el número de clientes, y N el número de cajas.
bool resuelveCaso() {
	int N, C;
	cin >> N >> C;

	if (N == 0)
		return false;

	int auxCaja = 1;
	int tiempo = 0, seg;
	tCliente c;
	PriorityQueue<tCliente> filaUnica;

	while (C > 0) {
		cin >> seg;
		c.seg = seg + tiempo; //Actualizacion de tiempo

		if (N > 0) { //Mientras queden cajas
			c.caja = auxCaja;
			filaUnica.push(c);
			auxCaja++;
			N--;
		}

		if (N == 0) { //Cuando no quedan cajas
			auxCaja = filaUnica.top().caja;
			tiempo = filaUnica.top().seg;
			filaUnica.pop();
			N++;
		}

		C--;
	}

	cout << auxCaja << "\n";

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
