//Grupo E, Mª Victoria Barylak Alcaraz	

#include <iostream>
#include <fstream>

#include "PriorityQueue.h"

typedef struct {
	int ini;
	int fin;
	int periodo;
}Tarea;

bool operator<(Tarea const& t1, Tarea const& t2) {
	return t1.ini < t2.ini || (t1.ini == t2.ini && t1.fin < t2.fin);
}


bool resuelveCaso() {
	int unicas, periodicas, T;

	std::cin >> unicas >> periodicas >> T;

	if (!std::cin)
		return false;

	int c, f, p;
	bool solapa = false;
	bool fin = false;

	PriorityQueue<Tarea> cola;
	Tarea t1;

	/*Lectura de las tareas unicas*/
	for (int i = 0; i < unicas; ++i) {
		std::cin >> c >> f;
		cola.push({ c, f, 0 });
	}

	/*Lectura de las tareas periodicas*/
	for (int j = 0; j < periodicas; ++j) {
		std::cin >> c >> f >> p;
		cola.push({ c, f, p });
	}


	if (cola.size() > 1) {
		cola.pop(t1);

		/*Si de momento no solapan tareas y sigo en el intervalo de tiempo [0..T)*/
		while (!solapa && (t1.fin < T || cola.top().ini < T) && !fin) {

			solapa = t1.fin > cola.top().ini;

			if (t1.periodo != 0) {
				cola.push({ t1.ini + t1.periodo, t1.fin + t1.periodo, t1.periodo });
			}

			if (cola.size() > 1)
				cola.pop(t1);
			else
				fin = true; //Si la cola tiene un único elemento, se sale del bucle
		}
	}


	if (solapa)
		std::cout << "SI\n";
	else
		std::cout << "NO\n";


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