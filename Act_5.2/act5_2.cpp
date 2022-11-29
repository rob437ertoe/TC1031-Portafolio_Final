//Integrantes del equipo
//Samantha Benítez Rentería
//Felipe de Jesús González Acosta
//Jonathan Eliud Fernández Zamora
//Roberto Eduardo Cardona Luis
//Ariadna Daniela Medina García
//Luis Fernando Cabral


#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

//Declaración de objetos para la manipulación de datos 

struct tryIP {
    string IP;
    float floatIP;
    int numTry; 

    tryIP();
    tryIP(string, float);
};

tryIP::tryIP() {
    this->IP = "0.0.0.0";
    this->floatIP = 0;
    this->numTry = 0;    
}

tryIP::tryIP(string IP_, float floatIP_) {
    this->IP = IP_;
    this->floatIP = floatIP_;
}


struct objIP {
    float floatIP;
    string strIP;
    vector<tryIP> accessAttempt;

    objIP();
    objIP(float, string);
    int findAccessAttempt(float);
};

objIP::objIP() {
    this->strIP = "0.0.0.0";
    this->floatIP = 0;
}

objIP::objIP(float floatIP_, string strIP_) {
    this->strIP = strIP_;
    this->floatIP = floatIP_;
}

int objIP::findAccessAttempt(float key) {
    int find = 0;

    for(int c = 0; c < accessAttempt.size(); c++) {
        if (accessAttempt[c].floatIP == key)
        {   find = 1;
            return c; 
        }
    }

    if (find == 0)
    {   return -1;  }
}

// Metodos de HASH 

int hash1(int key, int N)
{   return key%N;   }

int hash2(int key)
{   return 13367 - (key%13367); }


int doubleHashing(float key, int i, int N) {
    int value = hash1(key, N) + i*hash2(key);   
    return value;
}

// Declaración de objetos para el Hash Table

class Element {
    public:
        int numKey;
        float key;
        string strKey;
        bool taken;
        objIP value;

        Element ()
        {
            taken = false;
            strKey = "";
        }

        void printInfo();
};

void Element::printInfo() {
    cout << "IP: " << strKey << endl;
    cout <<"\tIPs que intentaron acceder: " << endl;

    for(int c = 0; c < value.accessAttempt.size(); c++) 
    {   cout << "\tIP: " << value.accessAttempt[c].IP << "\tIntentos: " << value.accessAttempt[c].numTry << endl;   }
}

class Hash {
    public:
        int colisionCounter = 0;
        int max_size = 0;
        int current_size = 0;
        int i;

        Element **table;

        Hash(int size)
        {
            max_size = size;
            table = new Element*[max_size];

            for (i = 0; i < max_size; i++)
            {   table[i] = new Element();   }
        }

        void insert(float, objIP);
        int find(float);
        void printInfoHash();
};

void Hash::insert(float raw, objIP newVal) {
    int index, key;
    int found = 0;
    colisionCounter = 0;

    if (current_size < this->max_size) 
    {
        int intRaw = floor(raw);
        index = hash1(intRaw, max_size);

        while (found == 0)
        {   
            if (table[index]->taken == false)
            {
                table[index]-> key = newVal.floatIP;
                table[index]-> numKey = index;
                table[index]-> value = newVal;
                table[index]-> taken = true;
                table[index]-> strKey = newVal.strIP;

                current_size++;
                found = 1;
            }
            else 
            { 
                colisionCounter++;
                index = doubleHashing(raw, colisionCounter, max_size)%max_size;
            }
        }
    }
    else 
    {   cout << "Error: tabla llena" << endl;}

}

int Hash::find(float raw) {

    int intRaw = floor(raw);
    int index = intRaw % max_size;
    int c = 0;
    colisionCounter = 0;
    int key = index;

    while (c < current_size)
    {   if (table[index]->value.floatIP == raw)
        {   return index;   }
        else
        {   colisionCounter++;
            index = doubleHashing(raw, colisionCounter, max_size)%max_size;    
        }
        c++;
    }
    return -1;
}

void Hash::printInfoHash() {
    cout << "Lista completa IP" << endl;

    for (int c = 0; c < max_size; c++)
    {   table[c]->printInfo();   }
}

// Función para ingresar las IP que intentaron acceder

void insertAccessAttempt(tryIP access, float accessed, Hash hashTable) {
    int index = hashTable.find(accessed);

    if (index != -1) 
    {   int indexAttempt = hashTable.table[index]->value.findAccessAttempt(access.floatIP);
        
        if (indexAttempt != -1)
        {   hashTable.table[index]->value.accessAttempt[indexAttempt].numTry++;    }
        else
        {   access.numTry++;
            hashTable.table[index]->value.accessAttempt.push_back(access);
        }
    }
}

float str2floIP(string IP){
    IP.erase(remove(IP.begin(), IP.end(), '.'), IP.end());
    float floIP = stof(IP);
    floIP *= 0.001;
    return floIP;
}

Hash readFile() {

    Hash htable(13381);

    //	C++
	string sline, line, aux; //Definimos las variables a utilizar
	int index, auxIndex;

	ifstream inFile("bitacoraHash.txt"); 	    //  input file stream
	//ofstream outFile("salida2.txt");		//	output file stream	
	
	//	Verifica que los archivos se hayan abierto correctamente
	int i = 0;
	int N, E;
	if (inFile.is_open() )	 //Abrimos el archivo de bitacora 	
	{	//	Lee liniea a linea
		while ( getline(inFile, sline) ) { //Mientras que se lea el archivo haremos lo siguiente
            if (i == 0){    //si el valor de i es igual a 0 se hara lo siguiente
                //cout << sline << endl;

				line = sline;
				index = line.find(" ");  //Encontraremos el valor de la linea del grafo
				aux = line.substr(0, index);
				N = stoi(aux);

				line = line.substr(index+1);
				index = line.find(" ");  

				line = line.substr(index+1);
				index = line.find(" ");
				aux = line.substr(0, index);
				E = stoi(aux);

				cout << "N: "<< N << endl; //Obtenemos el numero de nodos que hay en el grafo
				cout << "E: "<< E << endl; //Obtenemos el numero de aristas que hay en el grafo
                
            }
            else if(i > 0 && i <= N){ //Si el valor de i no es igual a 0 haremos lo siguiente
                string strIP = sline; //En la variable ip obtendremos el valor de sline
                string tempIP = strIP; //String temporal para cambiar la IP a float
            
                float floIP = str2floIP(tempIP);

                objIP IP(floIP, strIP);
                htable.insert(IP.floatIP, IP);
            }
            else{
                // Se obtiene el mes:
                string line = sline;
                index = line.find(" "); 
                //string month = line.substr(0, index);
                auxIndex = index+1;
                
                // Obtiene el día
                line = sline.substr(auxIndex);
                index = line.find(" ");
                //string day = line.substr(0, index);
                auxIndex += index+1;

                // Obtiene la hora
                line = sline.substr(auxIndex);
                index = line.find(" ");
                //string hour = line.substr(0, index);
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

                // Obtiene la IP
                line = sline.substr(auxIndex);
                index = line.find(":");
                string IP2 = line.substr(0, index);
                auxIndex += index+1;

                // Obtiene el puerto
                line = sline.substr(auxIndex);
                index = line.find(" ");
                string port2 = line.substr(0, index);
                auxIndex += index+1;

                // Obtiene el puerto
                line = sline.substr(auxIndex);
                index = line.find(" ");
                //string peso = line.substr(0, index);
                auxIndex += index+1;

                string tempIP1 = IP; //String temporal para cambiar la IP de intento a float
                float floIP1 = str2floIP(tempIP1);

                tryIP access(IP, floIP1);

                string tempIP2 = IP2; //String temporal para cambiar la IP de intento a float
                float accessed = str2floIP(tempIP2);

                insertAccessAttempt(access, accessed, htable);
            }
            i++;
            //outFile.close();
        }
    }
    inFile.close();

    return htable;
}

void writeOutputfile( Hash hTable ) {
    cout << "\nCreando TXT con la información de la HASH table\n" << endl;

    ofstream outputFile("bitacoraFinal.txt", std::ofstream::out);
    if (outputFile.is_open())
    {
        for (int c = 0; c < hTable.max_size; c++)
        { 
            outputFile << "IP: " << hTable.table[c]->strKey << endl;
            outputFile <<"\tIPs que intentaron acceder: " << endl; 
            for(int j = 0; j < hTable.table[c]->value.accessAttempt.size(); j++) 
            {   outputFile << "\t\tIP: " << hTable.table[c]->value.accessAttempt[j].IP << "\tIntentos: " << hTable.table[c]->value.accessAttempt[j].numTry << endl;   }
        }
        outputFile << "\n\n" << endl;
    }
}

int main()
{
    Hash hTable = readFile(); // Crea la tabla hash con la infromación leida

    writeOutputfile( hTable );

    string IPBuscada;
    cout << "Ingresa la IP para conocer los intentos de acceso que tiene" << endl;
    cout << "Utiliza el formato 1.1.1.1" << endl;
    cout << "Ingresa aquí la IP: ";
    cin >> IPBuscada;

    float floIPB = str2floIP(IPBuscada);
    int indexIPBuscada = hTable.find(floIPB);

    cout << "\nInformación de la IP buscada: \n" << endl;
    hTable.table[indexIPBuscada]->printInfo();
}