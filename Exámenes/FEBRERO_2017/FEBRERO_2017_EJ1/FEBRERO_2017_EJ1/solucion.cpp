//	M� Victoria Barylak Alcaraz

//	Se introduce el n�mero de aficionados de cada equipo en una cola de prioridad, ordenados de menor a mayor. Se van considerando los equipos
//	de dos en dos, simulando los partidos. Al contador de gorras se le suman los aficionados de ambos equipos, y se vuelve a introducir en la
//	cola la suma de los aficionados de los dos equipos que han jugado (simulando as� la victoria de uno y la conversi�n de las aficionados
//	del equipo perdedor en aficionados del equipo ganador).

//	Los "partidos" siempre se juegan entre los dos equipos que menos aficionados tienen; y el bucle se repite hasta que s�lo quede un equipo en la cola.

//	El coste de la funci�n es de O(N*logN), siendo N el n�mero de equipos, ya que por cada equipo se realiza un acceso al elemento m�s prioritario
//	y una inserci�n.

#include <iostream>
#include <fstream>

#include "PriorityQueue.h"


int competicion(PriorityQueue<int>& equipos) {
	int gorras = 0;

	while (equipos.size() > 1) {
		int e1 = equipos.top(); equipos.pop();
		int e2 = equipos.top(); equipos.pop();

		gorras = gorras + e1 + e2;

		equipos.push(e1 + e2);
	}

	return gorras;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N;

	std::cin >> N;

	if (N == 0)
		return false;

	PriorityQueue<int> equipos;

	int aficionados;
	for (int i = 0; i < N; ++i) {
		std::cin >> aficionados;
		equipos.push(aficionados);
	}

	int gorras = competicion(equipos);

	std::cout << gorras << "\n";

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