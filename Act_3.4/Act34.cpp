//Integrantes del equipo
//Samantha Benítez Rentería
//Felipe de Jesús González Acosta
//Jonathan Eliud Fernández Zamora
//Roberto Eduardo Cardona Luis
//Ariadna Daniela Medina García
//Luis Fernando Cabral

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <algorithm>

using namespace std;

struct info{
    string month;
    string time;
    string ip;
    string port;
    string text;
    float IP;
    int access;
    int day;
    info();
    info(string month, string time, int day, string ip, float IP, string port, string text, int access);
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

//Separamos y determinados el contenido de cada linea del archivo
// O(n)
//Parámetros de entrada: String con los datos
info::info(string month, string time, int day, string ip, float IP, string port, string text, int access) {
    this->IP = IP;
    this->month = month;
    this->time = time;
    this->day = day;
    this->ip = ip;
    this->port = port;
    this->text = text;
    this->access = access;

}

//Convierte los valores int en valores string
string info::toString(){
    string line = month + " " + to_string(day) + " " + time + " " + ip + ":" + port + " " + text;
    return line;

}

//Creamos un objeto que guarde los datos 
struct accessList {

    int id; //Guarda como ID el número de accesso
    vector<info> data; //Guarda todos los datos de tipo info con la el mismo access no.
    int length; // Guarda la cantidad de datos que tiene el objeto

    accessList();
    accessList(int ID);
    void insertInfo(info value);
};


accessList::accessList(){

    this->id = 0;
    this->length = 0;

}

accessList::accessList(int ID){

    this->id = ID;
    this->length = 0;

}

void accessList::insertInfo(info value){

    this->length++;
    this->data.push_back(value);

}

// Esta clase es parte de la creación del árbol binario 
//Tiene los atributos de nodo, izquierdo, derecho y Up (el padre)
//Complejidad de log2(n)
// template<class T>
class NodoTree //Creamos la clase en donde declaramos los constructores y los metodos a utilizar 
{ 
    public:
        accessList data;
        int value;
		int level, hL, hR, fBal;
		NodoTree *left, *right, *up;

	
	//Creamos el constructor el cual nos solicitara un valor que este valor sera agregado al nodo
	//Parametros de entrada: el valor a ingresar
	//Parametros de salida: ninguno
	//Complejidad de O(1)
        NodoTree(accessList data)
        {	this->data = data;
            this->value = data.length;
            this->left = NULL;
            this->right = NULL;
            this->up = NULL;
            this->level = 0;
            this->hL = level;
            this->hR = level;
            this->fBal = hR - hL;
        }
	
	//Creamos los valores que vamos a utilizar en el programa
        NodoTree(accessList data, NodoTree *left, NodoTree *right, NodoTree *up) {
            this->data = data;
            this->value = data.length;
            this->left = nullptr;
            this->right = nullptr;
            this->up = nullptr;
        }

        accessList getData(){//Creamos la funcion para obtener los datos
            return data;
        }

        NodoTree* getLeft(){//Funcion para obtener la izquierda
            return left;
        }

        NodoTree* getRight(){//Funcion para obtener la derecha
            return right;
        }

        NodoTree* getUp(){
            return right;
        }

        void setData(accessList data) { //Funcion para establecer los datos
            this->data = data;
        }

        // Modificar el apuntador al subarbol izquierdo
        void setLeft(NodoTree *left) {
            this->left = left;
        }

        // Modificar el apuntador al subarbol derecho
        void setRight(NodoTree *right) {
            this->right = right;
        }

        void setUp(NodoTree *up) {
            this->up = up;
        }

};

enum Traversal
{   factorBalanceo,
    ppreorder,
    pinorder,
    ppostorder,
    plevelbylevel
};

//template <class T>
class AVLTree {//Creamos la clase que utilizaremos para los diferentes datos a utilizar
    public:

        NodoTree *root;

        AVLTree();
		AVLTree(accessList value) 
        {   root = new NodoTree ( value );  }
        ~AVLTree();
        NodoTree* search(accessList data);
        NodoTree* insert(accessList data);
        bool isEmpty() const;
        NodoTree* deleted (NodoTree *, accessList value);
        int getSize() const;
        void print(Traversal traversal) const;

        int height(NodoTree *);
        int getFBal(NodoTree *);

        void balanceTree(NodoTree *);
        int countChildren(NodoTree *);

        NodoTree *rotaRight(NodoTree *);
        NodoTree *rotaLeft(NodoTree *);
        NodoTree *updateFB(NodoTree *parent, NodoTree *child);

    private:
        int size;//
        void destroyTree(NodoTree *root);
        int countChildren(NodoTree *node) const;
        void preorder(NodoTree *tree) const;
        void inorder(NodoTree *tree) const;
        void postorder(NodoTree *tree) const;
		void levelorder(queue<NodoTree*> levels) const;

};

//Árbol AVL con complejidad de O(log n) y complejidad de busqueda de O(n)
// template<class T>
AVLTree::AVLTree(){
	root = nullptr;
	size = 0;
}

// template<class T>
AVLTree::~AVLTree() {
    destroyTree(root);
}

// template<class T>
void AVLTree::destroyTree(NodoTree *root) { //Funcion para destruir el arbol
    if (root != nullptr) { //Si el valor es diferente a nulo se efectua la accion
        destroyTree(root->getLeft());
        destroyTree(root->getRight());
        delete root;//Elimina el arbol
        root = nullptr; //Toma el valor nulo
    }
}

// template<class T>
NodoTree* AVLTree::search(accessList value)//Funcion utilizada para buscar algun balor en el arbol y regresar en donde se encuentra este nodo
{	NodoTree *aux = this->root;

	cout << "Buscando " << to_string(value.length) << endl;//Inicia la busqueda del nodo

	while ( aux != NULL )//Creamos un ciclo para cuando el valor a buscar sea diferente a nulo
	{	if (value.length < aux-> getData().length )//Si el valor es menor que el auxiliar imprimira que esta en la izquierda y seguira avanzando
		{	cout << " left " << endl;
			aux = aux->getLeft();
		}
		else if(value.length > aux->getData().length )//Si es valor mayor a auxiliar seguira a la derecha
		{	cout << " right " << endl;
			aux = aux->getRight();
		}
		else//Si el valor no es mayor ni menor, esto significa que el nodo se encontro y regresara donde está
		{	cout << " Se encontro " << to_string(value.length) << endl;
			return aux;
		}
	}

	cout << " Aún no existe " << to_string(value.length) << endl;//Si no se encuentra nada imprime al usurio que no existe y regresara un valor nulo
	return NULL;
}

// template<class T>
int AVLTree::getSize() const {//Funcion para obtener el tamaño del arbol
    return size;//Regresa el valor del tamaño del arbol
}

// template<class T>
NodoTree* AVLTree::insert(accessList value)//Funcion para insertar un nodo
{	NodoTree *aux = this->root;

	NodoTree *leaf = new NodoTree(value);

	if ( search(value) == NULL )//Si el valor no existe en el nodo lo insertara en el arbol
	{	cout << " Insertando numero " << to_string(value.length) << endl;

		if ( root == NULL )//Si el valor de root es nulo va a insertar el numero como raiz 
		{	cout << " Insertado numero " << to_string(value.length) << " como raiz" << endl;
			root = leaf;
			return aux;
		}

		while ( aux != NULL)//Creamos un ciclo para cuando el valor de auxiliar sea diferente a nulo 
		{	if (leaf->data.length < aux->data.length)
			{	if (aux->left == NULL )//Si es valor de la izquierda es nulo pondra el numero comohijo izquiero
				{	cout << " Numero insertado: " << to_string(value.length) << " como hijo izquierdo de " << to_string(aux->data.length) << endl;
					aux->left = leaf;
					leaf->up = aux;
					return aux;
				}
				else//Si no el valor se pondra en la izquierda
				{	aux = aux->left;	}
			}
			else
			{	if (aux->right == NULL )//Si es valor de la izquierda es nulo pondra el numero comohijo derecho
				{	cout << " Numero insertado: " << to_string(value.length) << " como hijo derecho de " << to_string(aux->data.length) << endl;
					aux->right = leaf;
					leaf->up = aux;
					return aux;
				}
				else//Si no se insertara en la derecha
				{	aux = aux->right;	}
			}

		}

        // Ajuste del insert para AVL

        leaf->level = aux->level + 1;
        leaf->hL = leaf->level;
        leaf->hR = leaf->level;
        leaf->fBal = leaf->hR - leaf->hL;
        NodoTree *Z = updateFB(aux, leaf);
        Z->level = 1 + max(height(Z->left), height(Z->right));
        balanceTree(Z);
	}
	else
	{	cout << " Error: ya existente " << to_string(value.length) << endl; }//Si ya existe el valor va a imprimir un error

    return NULL;

}


// template<class T>
bool AVLTree::isEmpty() const {//Si el arbol esta vacio regresa que el tamaño que es 0
    return size == 0;
}

// template<class T>
int AVLTree::countChildren(NodoTree *nodo) const{//Esta funcion cuenta los nodos hijos que existen en el arbol
	int children = 0;//Empezamos el contador en 0
	if (nodo->getLeft() != nullptr)
        children++;//Aumentamos el valor del contador
    if (nodo->getRight() != nullptr)//Cuando el nodo sea diferente a nulo avanza a la derecha
        children++;//Aumentamos el valor del contador
    return children;

}

// template<class T>
NodoTree* AVLTree::deleted (NodoTree *root, accessList value) {//Funcion creada para eliminar nodos que queramos
    
    // Buscar el nodo que se va a eliminar
    NodoTree *parent = nullptr;
    NodoTree *node = root;

    if (root != nullptr) {

        while (node != nullptr && value.length != node->getData().length) {//Creamos un ciclo para cuando el nodo sea indiferente a nulo y el valor diferente al valor tomado del nodo
            parent = node;
            if (value.length < node->getData().length)
                node = node->getLeft();
            else
                node = node->getRight();
        }
        if (node == nullptr) //Si el dato no se encuentra
            return root;
        // remover de acuerdo a la cantidad de hijos del nodo a borrar
        NodoTree *grandchild;
        switch (countChildren(node)) {
        case 0: // nodo hoja
            if (parent == nullptr) // Eliminar el nodo raíz
                root = nullptr;
            else // Quitar el hijo adecuado
                if (value.length < parent->getData().length)
                    parent->setLeft(nullptr);
                else
                    parent->setRight(nullptr);
            delete node;
            size--;
            break;
        case 1:  // nodo interior con 1 hijo
            grandchild = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();
            if (parent == nullptr) // eliminar el nodo raíz
                root = grandchild;
            else // cortar el hijo adecuado
                if (value.length < parent->getData().length)
                    parent->setLeft(grandchild);
                else
                    parent->setRight(grandchild);
            delete node;
            size--;
            break;
        case 2: // nodo interior con 2 hijos
            // obtiene el predecesor
            NodoTree *pred = node->getLeft();
            while (pred->getRight() != nullptr)
                pred = pred->getRight();
            accessList predData = pred->getData();
            deleted(root->right, predData);
            node->setData(predData);
            break;
        }
    }

    if (node == nullptr) //Si el dato no se encuentra
    {   return node;   }

    root->level = 1 + max(height(root->left), height(root->right));

    balanceTree(root);

    return root;

}

// template<class T>
int AVLTree::countChildren(NodoTree *node) {//Creamos un ciclo para contar los hijos del arbol

    int ch = 0;//Creamos una variable para el contador

    if (node->left != nullptr)//Si hay hijos en la izquierda  aumentaremos el contador
    {   ch++;   }
    if (node->right != nullptr)//Si hay hijos en la derecha  aumentaremos el contador
    {   ch++;   }
    return ch;

}

// template<class T>
NodoTree* AVLTree::updateFB(NodoTree *parent, NodoTree *child) {

    if (parent == NULL)
    {   return NULL;    }
    if (parent->left == child)
    {   parent->hL = max(child->hL, child->hR);   }
    else 
    {   parent->hR = max(child->hL, child->hR); }

    parent->fBal = parent->hR - parent->hL;

    if (parent->fBal < -1 || parent->fBal > 1)
    {
        cout << "desbalanceado" << parent->data.length << endl;
        return parent;
    }
    else
    {   updateFB(parent->up, parent);   }
    
    return NULL;

}

// template<class T>
void AVLTree::inorder(NodoTree *auxRoot) const{
	if(auxRoot == NULL){
		return;
	}
	inorder(auxRoot->right);//Acomodara a la izquierda el valor aux
	cout << auxRoot->data.length << "\t";
    cout << "Acceso número: " << to_string(auxRoot->data.id) << endl;

    for (int c = 0; c < auxRoot->data.data.size(); c++){
        cout << auxRoot->data.data[c].toString() << endl;
    }

	inorder(auxRoot->left);//Acomodara a la derecha el valor de auz
}

// template<class T>
void AVLTree::postorder(NodoTree *auxRoot) const{//Funcion creada para tener un orden al final
	if(auxRoot == NULL){//Si el valor de aux es nulo no hara nada
		return;
	}
	postorder(auxRoot->left);//Acomodara a la izquierda el valor de aux
	postorder(auxRoot->right);//Acomodara a la derecha el valor de aux
	cout << auxRoot->data.length << "\t";
}

// template<class T>
void AVLTree::preorder(NodoTree *auxRoot) const{//Funcion creada para hacer un orden anteriormente
	if(auxRoot == NULL){//Si el valor de aux es nulo no hara nada
		return;
	}
	cout << auxRoot->data.length << "\t";
	preorder(auxRoot->left);//Acomodara a la izquierda el valor de aux
	preorder(auxRoot->right);//Acomodara a la derecha el valor de aux
}

// template<class T>
void AVLTree::levelorder(queue<NodoTree*> levels) const {//Funcion creada para ordenar los niveles
    while (! levels.empty()) {  //Creamos un ciclo para ordenas los niveles
        NodoTree *node = levels.front();
        cout << " " << node->getData().length; 
        NodoTree *child = node->getLeft(); 
        if (child != nullptr) levels.push(child);
        child = node->getRight();
        if (child != nullptr) levels.push(child);
        levels.pop();
    }
}

// template<class T>
void AVLTree::print(Traversal traversal) const //Funcion utilizada para imprimir la lista
{
    cout << "Recorrido en ";
    switch (traversal) {
        case ppreorder://Si el caso es con preorden activara la funcion de preorder
            cout << "preorden:";
            preorder(root);
        break;
        case pinorder://Si el caso es con pinorden activara la funcion de pinorder
            cout << "inorden: \n";
            inorder(root);
        break;
        case ppostorder://Si el caso es con ppostorden activara la funcion de ppostorden
            cout << "postorden:";
            postorder(root);
        break;
        case plevelbylevel://Si el caso es con plevelbylevel activara la funcion de plevelbylevel
            cout << "nivel x nivel:";
            if (! isEmpty()) {
                queue<NodoTree*> levels;
                levels.push(root);
                levelorder(levels);
           }
         break;
    }
    cout << endl;
}

// template<class T>
void AVLTree::balanceTree(NodoTree *Z)
{

    // Insertamos la rotacion

    if (Z != NULL)
    {
        // Comprobar  que Z sea mayor que 1 o menor que -1
        int factorBalanceo = getFBal(Z);
        // Left Left Case
        if (factorBalanceo > 1 && Z->data.length < Z->left->data.length)
        {
            rotaRight(Z);
            return;
        }

        // Right Right Case
        if (factorBalanceo < -1 && Z->data.length > Z->right->data.length)
        {
            rotaLeft(Z);
            return;
        }

        // Left Right Case
        if (factorBalanceo > 1 && Z->data.length > Z->left->data.length)
        {
            Z->left = rotaLeft(Z->left);
            rotaRight(Z);
            return;
        }

        // Right Left Case
        if (factorBalanceo < -1 && Z->data.length < Z->right->data.length)
        {
            Z->right = rotaRight(Z->right);
            rotaLeft(Z);
            return;
        }
    }
}


// template<class T>
int AVLTree::getFBal(NodoTree *node)
{
    if (node != NULL)
        return (height(node->right) - height(node->left));
    else
        return 3;
}

// Nuevas funciones para el AVL
// template<class T>
int AVLTree::height(NodoTree *node) {//Funcion creada para obtener la altura del arbol

    if (node == NULL) //Si es nula regresaremos un -1
    {   return -1;   }
    else { //Si no 

        int lheight = height(node->left); //Creamos variables para cada uno de los lados del arbol
        int rheight = height(node->right);

        if (lheight > rheight) //Realizamos calculos para conocer la altura del arbol
        {   return (lheight+1);    } 
        else 
        {   return (rheight +1);    }

    }

}

//template<class T>
NodoTree* AVLTree::rotaRight(NodoTree *Y) {//Funcion creada para realizar rotaciones a la derecha 

    NodoTree *X = Y->left;
    NodoTree *T2 = X->right;
//Tomamos el nodo que queremos modificar 
    X->right = Y;
    Y->left = T2;
    X->up = NULL; 
    Y->level = max(height(Y->left), height(Y->right)) + 1;
    X->level = max(height(X->left), height(X->right)) + 1;

    return X; //Regresamos el valor del nodo ya modificado

}

//template<class T>
NodoTree* AVLTree::rotaLeft(NodoTree *X) {//Funcion creada para realizar rotaciona a la izquierda

    NodoTree *Y = X->left;
    NodoTree *T2 = Y->right;
    //Tomamos el nodo ingresado por el usuario el cual moveremos a la izquiera
    Y->right = X;
    X->left = T2;
    Y->up = NULL; 
    X->level = max(height(X->left), height(X->right)) + 1;
    Y->level = max(height(Y->left), height(Y->right)) + 1;

    return Y;//Regresamos el valor del nodo en la ubicacion deseada
}

// template<class T>
NodoTree* minValNodo(NodoTree *node){//Funcion creada para devolver el valor minimo del nodo que exista en el arbol AVL

    NodoTree *current = node;//Tomamos el nodo como apuntador

    while (current->left != NULL)//Creamos un ciclo para cuando el nodo sea diferente a nulo
    {   current = current->left;   } 

}

void addinfo(vector<accessList> &accList, info data){//creamos una funcion en la cual nosotros podremos agregar informacion al archivo

    bool exist = false;

    for (int i = 0; i < accList.size(); i++){ //Creamos un ciclo for  para acceder a lista cuando el valor de i sea menor al tamaño de la lista de acceso

        if (accList[i].id == data.access) //Creamos un ciclo if si el access list es igual al data access
        {   
            accList[i].insertInfo(data); //Insertamos la nueva info
            exist = true; 
            break; //Rompemos el ciclo
        }

    }

    if (exist == false) {
        accessList newAccList(data.access);
        accList.push_back(newAccList);
    }

}

int main(){
    ifstream file; //Decimos que utilizaremos un archivo de datos
    ifstream archivo("bitacora_ip_ordenada.txt");//Declaramos en que archivo o programa estan lso datos
    string sline;
    int index;
    int auxIndex;

    vector<info> data;//Lista de datos 
    vector<float> dataIP; //Lista con todos los IP
    vector<info> lookedData; //Lista con las IP necesitadas por el usuario
    vector<accessList> allAccess; //Vector con todos los vectores por ID
    AVLTree InfoTree;

    file.open("bitacora.txt"); //Abrimos el archivo que utilizaremos en donde tenemos los datos

    while ( getline(archivo, sline) )	{//Creamos un ciclo para obtener la informacion de la fecha con los datos

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

        // Obtiene la calve de acceso de la IP
        index = IP.find(".");
        string accessStr = IP.substr(0, index);
        int access = stoi(accessStr);

        //cout << "Mes: "<< month <<" Dia: " << day << " Hora: " << hour << " IP: " << IP << " Puerto: " << port << " Error: " << msg << " Access:" << accessStr << endl;
        info info(month, hour, stoi(day), IP, floIP, port, msg, access);

        addinfo(allAccess, info);
        dataIP.push_back(floIP);
        data.push_back(info);
    }

    for(int i = 0; i < allAccess.size()-1;i++){
        InfoTree.insert(allAccess[i]);
    }

    int count = 0;
    vector<info>infoAccesos;
    int a = 0;
	//Consigue las 5 direcciones ip con más accesos
    while(a<5){
	    //Recorre todo allAccess para encontrar cual ip tiene más accesos
        for(int i = 0; i <= allAccess.size()-1;i++){
            if(allAccess[i].length > count){
               count = allAccess[i].length; 
            }
        }
        for(int i = 0; i <= allAccess.size()-1;i++){
            if(allAccess[i].length == count){
               infoAccesos = allAccess[i].data;
               allAccess[i].length = 0;
            }
        }

        cout << "Numero total de accesos: " << count << endl;
	
	    //Imprime todas las ip y sus accesos
        for(int i = 0; i <= infoAccesos.size() - 1;i++){
            cout << "The ip is: " << infoAccesos[i].ip << " Número de acceso: " << i+1 << endl;            
        }
        a++;
        count = 0;
    }
	//Imprime el arbol ordenado por el número de accesos, de mayor a menor
    InfoTree.print(pinorder);


}