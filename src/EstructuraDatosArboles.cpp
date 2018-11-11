;//============================================================================
// Name        : EstructuraDatosArboles.cpp
// Author      : Jose Gutierrez
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdexcept>

using namespace std;

struct nodoArbol {

	int valor;

	struct nodoArbol * izquierda, * derecha, * padre;

};

struct nodoArbol * raiz;

class Utility {

public:

	int putNumber(std::string askString, std::string notanumString, int min = 0, int max = 100000000) {

		std::string errorRange("Error, el valor debe estar entre $num1 y $num2");

		bool isNumber = false;

		bool inRange = false;

		std::string id;

		do {

			std::cout << askString << " \n";

			std::cin >> id;

			isNumber = this->isNumber(id);

			if (!isNumber)

				std::cout << notanumString << " \n";

			if (stringToInteger(id) < min || stringToInteger(id) > max) {

				replace(errorRange, "$num1", std::to_string(min));

				replace(errorRange, "$num2", std::to_string(max));

				std::cout << errorRange << " \n";

			} else {

				inRange = true;
			}

		} while (isNumber == false || inRange == false);

		return stringToInteger(id);
	}

private:

	bool replace(std::string& str, const std::string& from,
			const std::string& to) {

		size_t start_pos = str.find(from);

		if (start_pos == std::string::npos)

			return false;

		str.replace(start_pos, from.length(), to);

		return true;
	}

	int stringToInteger(std::string num) {

		int toReturn = 0;

		try {

			toReturn = atoi(num.c_str());

		} catch (int param) {

			std::cout << " ...Exception";

		}

		return toReturn;
	}

	bool isNumber(const std::string& s) {

		std::string::const_iterator it = s.begin();

		while (it != s.end() && std::isdigit(*it)) {

			++it;
		}

		return (!s.empty() && it == s.end()) ? true : false;
	}

};

class Arbol {

public:

	void insertarNodo() {

		Utility utility;

		int valor = utility.putNumber("Ingrese el valor del Nodo:", "Error, no es un número valido", 1, 1000);

		this->insertarEnArbol(raiz, valor);
	}

	void imprimirArbol() {

		this->pintarArbol(raiz);
	}

	void buscarNodo(){

		Utility utility;

		int valor = utility.putNumber("Ingrese el valor del Nodo a buscar:", "Error, no es un número valido", 1, 1000);

		this->nodoEncontrado = false;

		this->buscarEnArbol(raiz, valor);

		if (this->nodoEncontrado == true){

			cout << "El valor fue encontrado.\n";

		}else{

			cout << "El valor NO fue encontrado.\n";

		}

	}

	void eliminarNodoMenu (){

		Utility utility;

		int valor = utility.putNumber("Ingrese el valor del Nodo a eliminar:", "Error, no es un número valido", 1, 1000);

		this->eliminar (raiz, valor);
	}

private:

	bool nodoEncontrado = false;

	void destruirNodo (nodoArbol * nodo){

		nodo->izquierda = NULL;

		nodo->derecha = NULL;

		delete nodo;

	}

	nodoArbol * minimo (nodoArbol * nodo){

		if (nodo == NULL){

			return NULL;

		}

		if (nodo->izquierda){

			return minimo(nodo->izquierda);

		}else{

			return nodo;
		}

	}

	void eliminarNodo (nodoArbol * nodo){

		if (nodo->derecha != NULL && nodo->izquierda != NULL){ // Si un nodo tiene dos hijos, se recorre el hijo a la derecha y despues el ultimo a la izquierda.

			nodoArbol * menor = this->minimo(nodo->derecha);

			nodo->valor = menor->valor;

			eliminarNodo(menor);

		}else if (nodo->izquierda != NULL){ // Si bien tiene uno solo hijo, sea izquierdo

			nodo->izquierda->padre = nodo->padre;

			nodo->padre->izquierda = nodo->izquierda;

			destruirNodo(nodo);

		}else if (nodo->derecha != NULL){// Si bien tiene uno solo hijo, sea derecho

			nodo->derecha->padre = nodo->padre;

			nodo->padre->derecha = nodo->derecha;

			destruirNodo(nodo);

		}else{ // Si un nodo no tiene hijos

			if ((nodo->padre->derecha != NULL) && (nodo->padre->derecha->valor == nodo->valor)){

				nodo->padre->derecha = NULL;
			}

			if ((nodo->padre->izquierda != NULL) && (nodo->padre->izquierda->valor == nodo->valor)){

				nodo->padre->izquierda = NULL;
			}

			destruirNodo(nodo);

		}

	}

	// Se busca el elemento que se desea eluminar, para eso se recorre el arbol recursivamente
	void eliminar (nodoArbol * nodo, int valor){

		if (nodo == NULL){

			return;

		}else if (valor < nodo->valor){

			eliminar(nodo->izquierda, valor);


		}else if (valor > nodo->valor){

			eliminar(nodo->derecha, valor);

		}else{

			cout << "Se encontró el elemento a eliminar... \n";

			eliminarNodo(nodo);

		}

	}

	void buscarEnArbol (nodoArbol * nodo, int valor, bool encontro = false){

		if (nodo->valor == valor){

			this->nodoEncontrado = true;

		}else{

			if (nodo->izquierda != NULL){

				this->buscarEnArbol(nodo->izquierda, valor, encontro);

			}

			if (nodo->derecha != NULL){

				this->buscarEnArbol(nodo->derecha, valor, encontro);

			}

		}

	}

	nodoArbol * crearNodo() {

		nodoArbol * temp = new nodoArbol();

		return temp;
	}

	nodoArbol * actualizarNodo(nodoArbol * nodoArbol) {

		cout << "Ingrese el valor del nodo: ";

		cin >> nodoArbol->valor;

		return nodoArbol;
	}

	void pintarArbol (nodoArbol * nodo, int contador = 1, int mode = 0){

		if (nodo != NULL){

			if (nodo->derecha != NULL){

				pintarArbol(nodo->derecha, contador+1, 1);
			}

			if (nodo != raiz){

				for (int i = 0; i < contador; i ++){

					if (mode == 1){

						if (i == contador-1)

							cout << "   / ";

						else

							cout << "     ";

					}else{

						if (i == contador-1)

							cout << "   \\ ";

						else

							cout << "     ";
					}

				}

			}else

				cout << "    ";

			cout << nodo->valor << "\n";

			if (nodo->izquierda != NULL){

				pintarArbol(nodo->izquierda, contador+1, 2);

			}

		}

	}

	void insertarEnArbol(nodoArbol * nodo, int valor) {

		if (nodo == NULL){

			nodoArbol * nuevo = this->crearNodo();

			nuevo->valor = valor;

			nuevo->padre = NULL;

			raiz = nuevo;

			cout << "El valor " << valor << " fue asignado a la raiz.";

		}else{

			if (valor < nodo->valor){

				if (nodo->izquierda == NULL){

					nodoArbol * nuevo = this->crearNodo();

					nuevo->valor = valor;

					nuevo->padre = nodo;

					nodo->izquierda = nuevo;

					cout << "Nodo insertado cuyo valor es (" << valor << ") a la IZQUIERDA de " << nodo->valor << " \n";

				}else{

					insertarEnArbol(nodo->izquierda, valor);

				}

			}else if (nodo->valor < valor){

				if (nodo->derecha == NULL){

					nodoArbol * nuevo = this->crearNodo();

					nuevo->valor = valor;

					nuevo->padre = nodo;

					nodo->derecha = nuevo;

					cout << "Nodo insertado cuyo valor es (" << valor << ") a la DERERCHA de " << nodo->valor << " \n";

				}else{

					insertarEnArbol(nodo->derecha, valor);
				}

			}else{

				cout << "Error, el valor ya está asignado a un nodo. \n" ;

			}

		}

	}

};

class Menu {

public:

	void mostrarMenu() {

		Utility utility;

		int opcion = 0;

		do {

			cout << "Menú Principal" << "\n";

			cout << "1. Insertar nodo" << "\n";

			cout << "2. Buscar nodo" << "\n";

			cout << "3. Eliminar nodo" << "\n";

			cout << "4. Imprimir arbol (IN-ORDEN)" << "\n";

			opcion = utility.putNumber("Digite la opción...", "No es número", 1, 5);

			switch (opcion) {

			case 1:
				arbolObject.insertarNodo();
				break;
			case 2:
				arbolObject.buscarNodo();
				break;
			case 3:
				arbolObject.eliminarNodoMenu();
				break;
			case 4:
				arbolObject.imprimirArbol();
				break;
			}

		} while (opcion != 5);

	}

	Menu(Arbol arbol);

private:

	Arbol arbolObject;

};

Menu::Menu(Arbol arbol) {

	this->arbolObject = arbol;

}

int main() {

	Arbol arbol;

	Menu menu(arbol);

	menu.mostrarMenu();

	return 0;
}

