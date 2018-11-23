//Grupo E, Mª Victoria Barylak Alcaraz


#include <iostream>
#include <fstream>

#include "PriorityQueue.h"

typedef struct {
	int momento;	//momento en el que le toca
	int id;			//identificador del paciente
	int periodo;	//tiempo entre envios de informacion
} Registro;

bool operator<(Registro const& paciente1, Registro const& paciente2) {
	return paciente1.momento < paciente2.momento || (paciente1.momento == paciente2.momento && paciente1.id < paciente2.id);
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
//Coste de la funcion: O(n*logn + k*logn), donde n es el numero de pacientes y k el numero de consultas.
bool resuelveCaso() {
	int pacientes, consultas;
	PriorityQueue<Registro> cola;

	std::cin >> pacientes;

	if (pacientes == 0)
		return false;

	for (int i = 0; i < pacientes; i++) {
		Registro p;
		std::cin >> p.id;
		std::cin >> p.periodo;
		p.momento = p.periodo;

		cola.push(p);
	}

	std::cin >> consultas;
	
	while (consultas > 0) {
		Registro p;
		cola.pop(p);
		std::cout << p.id << "\n";
		p.momento += p.periodo;
		cola.push(p);
		consultas--;
	}

	std::cout << "----" << "\n";

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