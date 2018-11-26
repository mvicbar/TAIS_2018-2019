//Grupo E, M� Victoria Barylak Alcaraz

//	Para conseguir asistir a todas las conferencias con el menor n�mero de amigos primero se ordenan las conferencias por orden creciente de hora de inicio.
//	Se tiene tambi�n una cola de prioridades donde se guardan, de menor a mayor, las horas a las que finalizan las conferencias en las que hay alguien (yo o uno
//	de mis amigos). Esta cola se inicializa con la hora de finalizaci�n de la primera conferencia, a la que asisto yo. A continuaci�n, se recorren las dem�s
//	conferencias; si el inicio de la conferencia es menor que el final de la conferencia que antes acaba, se necesita un amigo m�s (se suma 1 al n�mero de 
//	amigos, y se introduce en la cola la hora a la que finaliza su conferencia), en caso contrario, no se necesita un amigo, se saca de la cola la conferencia
//	que ya ha terminado, y se introduce el final de la nueva conferencia a la que se asiste.

//	EL coste de la funci�n es el coste de ordenar la conferencias por orden creciente de hora de inicio, es decir, O(N *logN), siendo N el n�mero de conferencias.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

#include "PriorityQueue.h"


bool operator< (std::pair<int, int>& c1, std::pair<int, int>& c2) {
	return c1.first < c2.first;
}


//	Coste: O(N * logN), siendo N el n�mero de conferencias
int semana_de_la_informatica(std::vector <std::pair<int, int>>& conferencias, PriorityQueue<int>& finales) {
	std::sort(conferencias.begin(), conferencias.end());
	int amigos = 0;
	finales.push(conferencias[0].second);

	for (int i = 1; i < conferencias.size(); ++i) {
		if (conferencias[i].first < finales.top()) {	//se necesita un amigo
			amigos++;
			finales.push(conferencias[i].second);
		}
		else {	//no se necesita amigo, se actualiza la hora a la que finaliza la conferencia en la que estoy
			finales.pop();
			finales.push(conferencias[i].second);
		}
	}

	return amigos;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N;

	std::cin >> N;

	if (N == 0)
		return false;

	std::vector<std::pair<int, int>> conferencias(N);

	for (int i = 0; i < N; ++i)
		std::cin >> conferencias[i].first >> conferencias[i].second;

	PriorityQueue<int> finales;

	std::cout << semana_de_la_informatica(conferencias, finales) << "\n";

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