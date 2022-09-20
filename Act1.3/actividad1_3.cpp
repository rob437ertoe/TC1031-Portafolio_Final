//Integrantes:
//Roberto Eduardo Cardona Luis A00833365
//Jonathan Eliud Fernández Zamora A01571108
//Felipe de Jesús González Acosta A01275536
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct info{
    string month;
    string time;
    string ip;
    string text;
    string datesearch;
    int day;
    string key;
    info(string month, string time, int day, string ip, string text);
    bool operator<(info data);
};

info::info(string month, string time, int day, string ip, string text){
    string monthval;
    int monthday;
    this->month = month;
    this->time = time;
    this->day = day;
    this->ip = ip;
    this->text = text;

    if (month == "Jan"){
            monthday = 100 + day; 
            monthval = "0" + to_string(monthday);
        }
        else if (month == "Feb"){
            monthday = 200 + day; 
            monthval = "0" + to_string(monthday);
        }
        else if (month == "Mar"){
            monthday = 300 + day; 
            monthval = "0" + to_string(monthday);
        }
        else if (month == "Apr"){
            monthday = 400 + day; 
            monthval = "0" + to_string(monthday);
        }
        else if (month == "May"){
            monthday = 500 + day; 
            monthval = "0" + to_string(monthday);
        }
        else if (month == "Jun"){
            monthday = 600 + day; 
            monthval = "0" + to_string(monthday);
        }
        else if (month == "Jul"){
            monthday = 700 + day; 
            monthval = "0" + to_string(monthday);
        }
        else if (month == "Aug"){
            monthday = 800 + day; 
            monthval = "0" + to_string(monthday);
        }
        else if (month == "Sep"){
            monthday = 900 + day;
            monthval = "0" + to_string(monthday);
        }
        else if (month == "Oct"){
            monthday = 1000 + day;
            monthval = to_string(monthday);
        }
        else if (month == "Nov"){
            monthday = 1100 + day;
            monthval = to_string(monthday);
        }
        else if (month == "Dec"){
            monthday = 1200 + day;
            monthval = to_string(monthday);
        }

    this->key = monthval+"-"+time;
    this->datesearch = monthval;

}

bool info::operator<(info data){
    return this->key < data.key;
}

vector<info> sequentialSearch(vector<info> list, string datestart, string dateend)
{
    vector<info> datesearchlist;
    int a = 0;
    for (int i = 0;i<list.size();i++){
        if (list[i].datesearch >= datestart && list[i].datesearch <= dateend){
            datesearchlist.push_back(list[i]);
        }
    }
    return datesearchlist;
}

void merge(vector<info> &list, int inf, int mid, int sup)
{
    vector<info> left;
    for (int i = inf; i <= mid; i++)
    {
        left.push_back(list[i]);
    }
    vector<info> right;
    for (int i = mid + 1; i <= sup; i++)
    {
        right.push_back(list[i]);
    }
    int idxLeft = 0;
    int idxRight = 0;
    int idx = inf;
    while (idxLeft < left.size() && idxRight < right.size())
    {
        if (left[idxLeft] < right[idxRight])
        {
            list[idx] = left[idxLeft];
            idx++;
            idxLeft++;
        }
        else
        {
            list[idx] = right[idxRight];
            idx++;
            idxRight++;
        }
    }
    while (idxLeft < left.size())
    {
        list[idx] = left[idxLeft];
        idx++;
        idxLeft++;
    }
    while (idxRight < right.size())
    {
        list[idx] = right[idxRight];
        idx++;
        idxRight++;
    }
}

void mergeSort(vector<info> &list, int inf, int sup)
{
    if (inf < sup)
    {
        int mid = (inf + sup) / 2;
        mergeSort(list, inf, mid);
        mergeSort(list, mid + 1, sup);

        merge(list, inf, mid, sup);
    }
}

int main(){
    ifstream file;
    ifstream inputFile("bitacora.txt");
    vector<info> data;
    vector<info> datelistsearch;
    string line;
    string datestart, dateend;
    
    file.open("bitacora.txt");

    while (getline(inputFile, line)){
        istringstream ss(line);
        string month, time, monthval, ip, text;
        int day, monthday;
        ss >> month >> day >> time >> ip >> text;
        if (ip.size() == 17)
            text = line.substr(33, line.size()-1);
        else if (ip.size() == 16)
            text = line.substr(32, line.size()-1);
        else
            text = line.substr(35, line.size()-1);
        info info(month, time, day, ip, text);
        data.push_back(info);
    }

    inputFile.close();

    mergeSort(data, 0, data.size()-1);



    cout << "Introduzca la fecha de inicio de búsqueda"<< endl<< "Número de Mes y Día (MMDD)  Ejemplo: 0912"<<endl;
    cin>>datestart;

    cout << endl <<  "Introduzca la fecha de fin de búsqueda: " << endl<< "Número Mes y Día (MMDD) Ejemplo: 1118"<<endl;
    cin>>dateend;

    datelistsearch = sequentialSearch(data, datestart, dateend);

    cout<<endl;
    for(int i = 0; i < datelistsearch.size()-1; i++){
        cout<<"Date/Time: " << datelistsearch[i].month << " " << datelistsearch[i].day << " " << datelistsearch[i].time << " IP adress: " << datelistsearch[i].ip << " Message: " << datelistsearch[i].text << endl;
    }

    ofstream outputFile("bitacora_ordenada.txt", std::ofstream::out);

    if (outputFile.is_open())
    {
        for (int i = 0; i < data.size(); i++) {
            string finalLineStr = "";

            finalLineStr = finalLineStr + data[i].month + " " + to_string(data[i].day) + " " + data[i].time + " " + data[i].ip + " " + data[i].text;

            outputFile << finalLineStr << endl;
        }
        outputFile.close();
    }
    else cout << "Problem with opening file";

    return 0;

}