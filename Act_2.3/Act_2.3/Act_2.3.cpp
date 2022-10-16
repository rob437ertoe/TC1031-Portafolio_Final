//Integrantes:
//Roberto Eduardo Cardona Luis A00833365
//Jonathan Eliud Fernández Zamora A01571108
//Felipe de Jesús González Acosta A01275536

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

struct info{
    string month;
    string time;
    string ip;
    string port;
    string text;
    float IP;
    int day;
    info();
    info(string month, string time, int day, string ip, float IP, string port, string text);
    string toString();
};

//Declarar los valores de info
info::info(){
    this->month = "N/A";
    this->time = "00:00:00";
    this->ip = "000.000.000.00";
    this->port = "0000";
    this-> text = "N/A";
}

info::info(string month, string time, int day, string ip, float IP, string port, string text) {
    this->IP = IP;
    this->month = month;
    this->time = time;
    this->day = day;
    this->ip = ip;
    this->port =  port;
    this->text = text;

}

//Convierte los valores int en valores string
string info::toString(){
    string line = month + " " + to_string(day) + " " + time + " " + ip + ":" + port + " " + text;
    return line;

}

// class node: un valor y un puntero a otro nodo
template<class T>
class Node
{	public:

		T value;//ponemos que valor es un numero entero
		Node<T> *next;
        Node<T> *prev;
	
		Node(T value){	
			this->value = value;
			this->next = NULL;
            this->prev = NULL;
		}

};

//  Clase lista enlazada simple: 
//	puntero al primer nodo y tamaño total
template<class T>
class List
{	Node<T> *first;   // puntero al primer nodo
    Node<T> *last;   // puntero al ultimo nodo
	int size; //creamos la variable tamaño

	public: //Añadimos los valores publicos
		List() 
		{	first = NULL; 
            last = NULL;
			size = 0;
		}
		
		int getSize(){ return size; }
		void showList();  //Creamos los void para las funciones a realizar

		Node<T>* find(T); 

		void insertLast(T);	 
		void insertFirst(T);  

		void deleteFirst(); 
		void deleteLast(); 

        Node<T>* getFirst();
        Node<T>* getLast();
};

//borrar el primer elemento
template<class T>
void List<T>::deleteFirst(){
	Node<T> *aux = this->first; // Crea un Nodo auxiliar para liberar el primer nodo
	this->first = aux->next; // Guarda la info del segundo nodo en el primer nodo
	delete aux; // Borra el nodo auxiliar
	this->size--; // Reduce el valor del tamaño de la lista en 1
}

//Borrar el ultimo elemento
template<class T>
void List<T>::deleteLast(){
	Node<T> *aux = this->first; // Crea un Nodo auxiliar para guardar la información de los nodos
	while(aux -> next -> next != NULL){ //Recorre todos los nodos hasta encontrar el nodo final
		aux = aux -> next; //Recorre la información de los nodos guardandolos temporalmente en aux
	}
	delete aux -> next; // Elimna el auxiliar que contiene ya el nodo final
	aux -> next = NULL; // Cambia la propiedad next del auxiliar mostrando que es el final
	this -> size--; // Reduce el valor del tamaño de la lista en 1
}

//Encontrar un valor
template<class T>
Node<T>* List<T>::find(T value){
	Node<T> *aux = this->first; // Crea un Nodo auxiliar para guardar la información de los nodos
	while(aux != NULL){
		if(aux -> value == value){ //Si el valor que buscamos es igual al valor encontrado en la lista regresamos el valor de aux
			return aux;
		}
		aux = aux -> next;
	}
	return NULL; // Si el valor no es encontrado regressa NULL
}

//Insertar al inicio
template<class T>
void List<T>::insertFirst(T newVal)
{	Node<T> *node = new Node<T>(newVal); //Insertamos en el primer lugar de la lista un numero seleccionado
    Node<T> *secondNode = this->first;

	node->next = this->first;
	this->first = node;
	
    if (this->size == 0)
    {   this->last = node;  }
    else 
    {   secondNode->prev = node;    }

    this->size++; //Aumentamos el tamaño de la lista

}

//Insertar al final
template<class T>
void List<T>::insertLast(T newVal)
{	Node<T> *node = new Node<T>(newVal);
	Node<T> *aux;

	if (this->size == 0)
	{	this->insertFirst(newVal);  }
	else
	{	aux = this->first;

		//  Recorrer la lista hasta llegar al ultimo elemento, O(n)
		while ( aux->next != NULL )
		{ aux = aux->next;  }

		aux->next = node;		//	el ultimo apuntara hacia el nodo nuevo
		this->size++;			//	numero de elementos habra aumentado
	}
}	


//Mostrar la lista
template<class T>
void List<T>::showList() //Mostramos la lista que nosotros vayamos a crear en la funcion de main
{	Node<T> *aux = this->first; // Crea un Nodo auxiliar para guardar la información de los nodos

	cout<< "Size: " << this->size << endl; // Muestra el tamaño de la lista

	while ( aux != NULL ) // Muestra el valor de cada nodo en la lista, separa con Tabs
	{	cout << aux->value.toString() << endl;
		aux = aux->next;
	}
}

//Regresa el primer valor de la lista
template<class T>
Node<T>* List<T>::getFirst()
{   return this->first;  }

//Regresa el ultimo valor de la lista
template<class T>
Node<T>* List<T>::getLast()
{   return this->last;  }

// Swap 
//Intercambia el valor de a con el valor de b
void swap (info* a, info* b) {
    info aux = *a;
    *a = *b;
    *b = aux;
}

// Partition

template <class T>//Empezaremos con la particion del nodo
Node<T>* partition(Node<T>* L, Node<T>* R) {
    
    float pivot = R->value.IP;//creamos un variable para pivot con el valor de la Ip registrada en R

    Node<T> *i = L->prev; 

    for (Node<T> *j = L; j != R; j = j->next) {//creamos un ciclo for que aumentara el vamor de J cada ves que se realice un ciclo
        if (j->value.IP <= pivot) { //si el valor de j es menor o igual pivot se activara el ciclo if

            if (i == NULL)//donde si el valor de i es nulo tomara el valor de L
            {   i = L;  }
            else
            {   i = i->next;   }//si no avanzara de nodo

            swap(&(i->value), &(j->value)); //cambiaremos los valores de i y j

        }
    }

    if (i == NULL) //si no se cumple la condicion del if anterior realizarenos no mismo que dentro de aquel
    {   i = L;  }
    else
    {   i = i->next;   }

    swap(&(i->value), &(R->value));//cambiaremos el valor de i y R

    return i;//Regresamos el valor de i

}

// Quicksort
template <class T>
void quickSort(Node<T>* L, Node<T>* R) { //Ciclo para quickSort

    if (R != NULL && L != R && L != R->next) { //creamos un if con las condiciones de R y L
        Node<T> *pivot = partition(L, R); 

        quickSort(L, pivot->prev); //tomaremos el valor anterior de L
        quickSort(pivot->next, R);// tomaremos el valor despues de R
    }

}

// Search 
//Busca los todos las direcciones IP que entren dentro del rango que se introduze 
template <class T>
List<T> search(List<T> data, float firstIP, float lastIP) {

    List<T> finalList; //Se crea una nueva lista para devolver con las direcciones IP que cumplan la condicion
    Node<T> *aux = data.getFirst();

    while (aux != NULL)  //si el valor del aux es indiferente a nulo haremos el sig ciclo
    {
        if ((aux->value.IP >= firstIP) && (aux->value.IP <= lastIP)) //Si el valor del ip es mayor a first IP y menor a lastIP se inserta el valor en la lista
        {
            finalList.insertFirst(aux->value);//insertamos el valor de aux
        }
        aux = aux->next;//cambiaremos el valor de aux
    }

    return finalList; //Regresa la lista con todas las IP que cumplan la condicion

}

int main() {

    ifstream file; //Decimos que utilizaremos un archivo de datos
    ifstream inputFile("bitacora.txt");//Declaramos en que archivo o programa estan lso datos
    string sline;
    int index;
    int auxIndex;

    List<info> data;//Lista de datos 
    List<float> dataIP; //Lista con todos los IP
    List<info> lookedData; //Lista con las IP necesitadas por el usuario

    file.open("bitacora.txt"); //Abrimos el archivo que utilizaremos en donde tenemos los datos

    while ( getline(inputFile, sline) )	{//Creamos un ciclo para obtener la informacion de la fecha con los datos
	    

        // Se obtiene el mes:
        string line = sline;
        index = line.find(" "); 
        string month = line.substr(0, index);
        auxIndex = index+1;
        
        // Obtiene el día
        line = sline.substr(auxIndex);
        index = line.find(" ");
        string day = line.substr(0, index);
        auxIndex += index+1;

        // Obtiene la hora
        line = sline.substr(auxIndex);
        index = line.find(" ");
        string hour = line.substr(0, index);
        auxIndex += index+1;

        // Obtiene la IP
        line = sline.substr(auxIndex);
        index = line.find(":");
        string IP = line.substr(0, index);
        auxIndex += index+1;

        // Obtiene el puerto
        line = sline.substr(auxIndex);
        index = line.find(" ");
        string port = line.substr(0, index);
        auxIndex += index+1;
        
        // Obtiene el mensaje de error
        string msg = sline.substr(auxIndex);

        // cout << "Mes: "<< month <<" Dia: " << day << " Hora: " << hour << " IP: " << IP << " Puerto: " << port << " Error: " << msg << endl;


        //Hacemos la IP un int
        
        string strIP = IP;

        strIP.erase(remove(strIP.begin(), strIP.end(), '.'), strIP.end());

        float floIP = stof(strIP);

        info info(month, hour, stoi(day), IP, floIP, port, msg);

        dataIP.insertFirst(floIP);
        data.insertFirst(info);
    }

    //data.showList();
    quickSort(data.getFirst(), data.getLast());
    //data.showList();

    
    string strInitialIP, strFinalIP; 
    bool repeat = true;
    float InitialIP;
    float FinalIP;

    do {   
        
        cout << "Inserte la IP de inicio a buscar: "; 
        cin >> strInitialIP;
        strInitialIP.erase(remove(strInitialIP.begin(), strInitialIP.end(), '.'), strInitialIP.end());
        InitialIP = stof(strInitialIP);
        if(dataIP.find(InitialIP) != NULL)
        {   
            cout << "IP encontrada! " << endl;
            repeat = false;
        }
        else 
        {   
            cout << "IP inválida " << endl;
            repeat = true;  
        }
        
    } while ( repeat );

    do {   
        
        cout << "Inserte la IP de final a buscar: "; 
        cin >> strFinalIP;
        strFinalIP.erase(remove(strFinalIP.begin(), strFinalIP.end(), '.'), strFinalIP.end());
        FinalIP = stof(strFinalIP);
        if(dataIP.find(FinalIP) != NULL)
        {   
            cout << "IP encontrada! " << endl;
            repeat = false;
        } 
        else 
        {   
            cout << "IP inválida " << endl;
            repeat = true;  
        }
        if (FinalIP < InitialIP) 
        {
            cout << "IP menor que la IP incial \nIntroduzca otra IP válida " << endl;
            repeat = true;  
        } 
        else {
            repeat = false;
        }
        
    } while ( repeat );

    // Metodo de busqueda
    lookedData = search(data, InitialIP, FinalIP);
    quickSort(lookedData.getFirst(), lookedData.getLast());
    lookedData.showList();

    // Escribe en el programa
    ofstream outputFile("bitacora_ip_ordenada.txt", std::ofstream::out);
    if (outputFile.is_open())
    {
        Node<info> *auxWrite = lookedData.getFirst();
        string writeStr;

        while ( auxWrite != NULL ) 
        {
            writeStr = auxWrite->value.toString();
            outputFile << writeStr << endl;
            auxWrite = auxWrite->next;
        }
        outputFile.close();
    }
    else cout << "Problem with opening file";

    cout << "TXT creado" << endl;

}
