//	Mª Victoria Barylak Alcaraz

//	Para representar a los usuarios que se registran en el sistema se utiliza una estructura con tres enteros: el id del usuario,
//	el periodo con el que se tienen que realizar los envíos, y los momentos en los que se tienen que realizar (acumulación de 
//	periodos).

//	Se introducen los usuarios en una cola de prioridad, y se ordenan de menor a mayor momento de envío y, en caso de ser estos
//	iguales, de menor a mayor id.

//	El coste de la función es de O(k * log N), siendo k en número de envíos que se quieren realizar, y N en número de usuarios
//	registrados en el sistema; ya que para cada envío se realiza un acceso al elemento más prioritario, y una inserción.

#include <iostream>
#include <fstream>

#include "PriorityQueue.h"

typedef struct {
	int ID;
	int periodo, momento;
}Usuario;

bool operator<(Usuario const& u1, Usuario const& u2) {
	return u1.momento < u2.momento || u1.momento == u2.momento && u1.ID < u2.ID;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N;

	std::cin >> N;

	if (N == 0)
		return false;

	PriorityQueue<Usuario> UCM;
	int tiempo = 0;

	for (int i = 0; i < N; ++i) {
		int id, periodo;
		std::cin >> id >> periodo;

		UCM.push({ id, periodo, periodo });
	}

	int envios;

	std::cin >> envios;
	for (int e = 0; e < envios; ++e) {
		Usuario usuario = UCM.top();
		UCM.pop();

		std::cout << usuario.ID << "\n";

		UCM.push({ usuario.ID, usuario.periodo, usuario.momento + usuario.periodo });
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