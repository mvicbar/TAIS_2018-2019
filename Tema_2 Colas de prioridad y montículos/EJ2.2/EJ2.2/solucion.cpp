//Grupo E, Mª Victoria Barylak Alcaraz


#include <iostream>
#include <fstream>
#include <string>

#include "PriorityQueue.h"

typedef struct {
	std::string nombre;
	int gravedad;
	int llegada;
}Registro;

bool operator> (Registro const& p1, Registro const& p2) {
	return p1.gravedad > p2.gravedad || (p1.gravedad == p2.gravedad && p1.llegada < p2.llegada);
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
//Coste de la funcion: O(IlogN), siendo I el numero de pacientes que llegan a la consulta, y n el numero de pacientes que ya estaban en la consulta. 
bool resuelveCaso() {
	int eventos, hora = 0, gravedad;
	std::string nombre;
	char tipo;
	Registro p;

	std::cin >> eventos;

	if (eventos == 0)
		return false;

	PriorityQueue<Registro, std::greater<Registro>> cola;

	while (eventos > 0) {
		std::cin >> tipo;

		switch (tipo) {
		case 'I':
			std::cin >> nombre >> gravedad;
			p.nombre = nombre; p.gravedad = gravedad; p.llegada = hora;
			cola.push(p);
			++hora;
			break;
		case 'A':
			std::cout << cola.top().nombre << "\n";
			cola.pop();
			break;
		}

		eventos--;
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