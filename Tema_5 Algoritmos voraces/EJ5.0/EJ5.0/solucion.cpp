//Grupo E, Mª Victoria Barylak Alcaraz

//	Para representar los agujeros de la mangueras se tiene un vector de enteros, en el que cada entero representa la posición donde se encuentra el agujero en la
//	manguera. Se tiene un entero que indica el primer agujero que tapa el último parche colocado.

//	Siempre se empieza con un parche, para tapar al menos el primer agujero. A continuación, se recorren el resto de agujeros y se comprueba si están al alcance
//	del parche ya colocado, comparando su posición con la suma de la longitud del parche y la posición del primer agujero que tapa. Si su posición está dentro
//	de ese alcance, no hace falta añadir otro parche; si no está al alcance, se añade un nuevo parche y se actualiza el entero del inicio del último parche
//	colocado.

#include <iostream>
#include <fstream>
#include <vector>


//	Coste de la función: O(N), siendo N el número de agujeros de la manguera.
int manguera(std::vector<int> const& agujeros, const int& L) {
	int parches = 1, 
		inicio_parche = agujeros[0];	//Primer agujero que tapa el último parche colocado

	for (int a = 1; a < agujeros.size(); a++) {
		if (agujeros[a] > L + inicio_parche) {	//	si el agujero a tapar está fuera del alcance del parche
			parches = parches + 1;									//	se añade un parche más
			inicio_parche = agujeros[a];		//	y se actualiza el primer agujero del último parche
		}
	}

	return parches;
}


//Resuelve un caso de prueba, leyendo de la entrada
//la configuracion y escribiendo la respuesta
bool resuelveCaso() {
	int N, L;

	std::cin >> N >> L;

	if (!std::cin)
		return false;

	std::vector<int> agujeros(N);

	for (int i = 0; i < N; ++i) {
		int agujero;
		std::cin >> agujero;
		agujeros[i] = agujero;
	}

	std::cout << manguera(agujeros, L) << "\n";
	
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