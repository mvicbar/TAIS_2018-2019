//Grupo E, Mª Victoria Barylak Alcaraz

#include <iostream>
#include <fstream>
#include <functional>

#include "PriorityQueue.h"

typedef struct {
	int partituras;
	int musicos;
} Grupo;

/*Se calcula la prioridad de un grupo basándose en el número de músicos que se agrupan en las partituras*/
bool operator>(Grupo const& g1, Grupo const& g2) {
	int prio1, prio2;

	prio1 = g1.musicos / g1.partituras;
	if (g1.musicos % g1.partituras != 0)
		prio1++;

	prio2 = g2.musicos / g2.partituras;
	if (g2.musicos % g2.partituras != 0)
		prio2++;

	return prio1 > prio2;
}

//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
//Coste de la función: O(p * logn), siendo p el número de partituras por repartir, y n el número de grupos.
bool resuelveCaso() {
	int p, n, num;
	int sol;

	std::cin >> p >> n;

	if (!std::cin)
		return false;

	PriorityQueue<Grupo, std::greater<Grupo>> cola;
	Grupo grupo;

	p = p - n;	//Se reparte una partitura a cada grupo, y se restan del total

	for (int i = 0; i < n; ++i) {
		std::cin >> num;
		grupo = { 1, num };	//Cada grupo empieza con una partitura
		cola.push(grupo);
	}

	while (p > 0) {
		cola.pop(grupo);
		grupo.partituras++;
		cola.push(grupo);
		p--;
	}

	grupo = cola.top();

	sol = grupo.musicos / grupo.partituras;
	if (grupo.musicos%grupo.partituras != 0)
		sol++;

	std::cout << sol << "\n";

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