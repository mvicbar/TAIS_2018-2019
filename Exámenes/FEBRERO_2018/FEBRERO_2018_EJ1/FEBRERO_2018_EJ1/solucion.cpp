//	Mª Victoria Barylak Alcaraz

//	Se representan las tareas como una estructura con tres enteros, el tiempo de inicio de la tarea, el tiempo de finalización de la tarea, y
//	la perioricidad con la que se repiten. Las tareas únicas siempre tendrán una periodicidad de 0.

//	Se ordenan las tareas en una cola de prioridades ordenadas de menor a mayor tiempo de inicio y, mientras queden tareas en la agenda, no se haya
//	pasado el tiempo T, y no haya habido ningún conflicto hasta ese momento, se comparan las dos tareas más prioritarias; si el tiempo de finalización de la
//	primera tarea es menor o igual que el inicio de la segunda, no hay conflicto. En caso contrario, hay conflicto.

//	El coste de la función es de O(T * logN), siendo N el número de tareas que hay en la cola, y T el periodo de tiempo, ya que por cada paso de tiempo
//	se hace una inserción en la cola y un acceso a la tarea más prioritaria.

#include <iostream>
#include <fstream>

#include "PriorityQueue.h"

typedef struct {
	int ini, fin;
	int repeticion;
}Tarea;

bool operator<(Tarea const& t1, Tarea const& t2) {
	return t1.ini < t2.ini;
}


bool agenda(PriorityQueue<Tarea>& tareas, const int& T) {
	Tarea t1 = tareas.top();
	tareas.pop();
	bool conflicto = false;

	while (!tareas.empty() && tareas.top().ini <= T && !conflicto) {

		conflicto = t1.fin > tareas.top().ini;

		if (t1.repeticion != 0)
			tareas.push({ t1.ini + t1.repeticion, t1.fin + t1.repeticion, t1.repeticion });

		t1 = tareas.top();
		tareas.pop();

	}

	return conflicto;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N, M, T;

	std::cin >> N >> M >> T;

	if (!std::cin)
		return false;

	PriorityQueue<Tarea> tareas;

	for (int n = 0; n < N; ++n) {
		int inicio, fin;
		std::cin >> inicio >> fin;

		tareas.push({ inicio, fin, 0 });
	}

	for (int m = 0; m < M; ++m) {
		int inicio, fin, periodo;
		std::cin >> inicio >> fin >> periodo;

		tareas.push({ inicio, fin, periodo });
	}

	int conflicto = agenda(tareas, T);

	if (!conflicto)
		std::cout << "NO\n";
	else
		std::cout << "SI\n";

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