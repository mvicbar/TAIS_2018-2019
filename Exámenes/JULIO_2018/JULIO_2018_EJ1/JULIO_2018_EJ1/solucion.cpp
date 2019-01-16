//	Mª Victoria Barylak Alcaraz

//	Se representa a los pacientes con una estructura que contiene su nombre, su gravedad, y el momento de llegada (que se asigna con un contador
//	que se actualiza con cada llegada nueva de un paciente).
//	Para representar la cola de urgencias se usa una cola de prioridad de pacientes, en la que los pacientes están ordenados de mayor a menor gravedad y, en
//	el caso de que las gravedades sean iguales, de menor a mayor tiempo de llegada.
//	Cuando llega un nuevo paciente, se mete en la cola, y cuando se atiende a un paciente, se devuelve el nombre del primer elemento de la cola, y se 
//	elimina de la misma.

//	El coste de la función es de O(I*logN + A*logN), siendo N el número de pacientes que se encuentran en la cola, ya que se realizan I inserciones
//	de complejidad O(logN), y A accesos al elemento más prioritario de complejidad O(logN).

#include <iostream>
#include <fstream>
#include <string>

#include "PriorityQueue.h"

typedef struct {
	std::string nombre;
	int gravedad, llegada;
}Paciente;


bool operator<(Paciente const& p1, Paciente const& p2) {
	if (p1.gravedad == p2.gravedad)
		return p1.llegada < p2.llegada;
	else 
		return p1.gravedad > p2.gravedad;
}

//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N, tiempo = 1;
	char evento;
	Paciente p;

	std::cin >> N;

	if (N == 0)
		return false;

	PriorityQueue<Paciente> urgencias;

	for (int i = 0; i < N; ++i) {
		std::cin >> evento;

		if (evento == 'I') {
			std::cin >> p.nombre;
			std::cin >> p.gravedad;
			p.llegada = tiempo;
			tiempo++;

			urgencias.push(p);
		}

		if (evento == 'A') {
			Paciente atendido = urgencias.top();
			urgencias.pop();

			std::cout << atendido.nombre << "\n";
		}
	}

	std::cout << "----\n";

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