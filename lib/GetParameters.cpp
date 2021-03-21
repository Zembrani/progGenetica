#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#if !defined(GETPARAMETERS)
#define GETPARAMETERS

struct GetParameters {
    string fileName = "parameters.txt";
    ifstream myFile;
    int qtPopulation;
    int qtInteractions;
    int mutation;
    int survival;
    int file;
    int deep;
    vector <string> func;
    vector <string> term;

    void read(string fileName) {
        myFile.open(fileName);
        int i = 0;

        if (!myFile.is_open())
            exit(1);

        myFile >> qtPopulation;
        myFile >> qtInteractions;
        myFile >> mutation;
        myFile >> survival;
        myFile >> file;
        myFile >> deep;

        myFile >> i;
        for(int j = 0; j < i; j++) {
            string aux;
            myFile >> aux;
            func.push_back(aux);
        }
        myFile >> i;
        for(int j = 0; j < i; j++) {
            string aux;
            myFile >> aux;
            term.push_back(aux);
        }
        myFile.close();
    }

    GetParameters() {
        read(fileName);
    }

    void print() {
        cout << "*****  Parametros  ***** " << endl;
        cout << "\tProfundidade : " << qtInteractions << endl;
        cout << "\tPopulação : " << qtPopulation << endl;
        cout << "\tNós para mutação : " << mutation << endl;
        cout << "\tQt de sobreviventes : " << survival << endl;
        cout << "\tArquivo : trainning" << file << ".txt" << endl;
        cout << "\tProfundidade : " << deep << endl;
        cout << "\tSet de funções : "; printSet(func);
        cout << "\tSet de termos : "; printSet(term);
        cout << "**************************" << endl;
    }

    void printSet(vector <string> set) {
        for (auto&& it : set) {
            cout << it << " ";
        }
        cout << endl;
    }

    int getDeep() {
        return deep;
    }

    vector <string> getFunc() {
        return func;
    }

    vector <string> getTerm() {
        return term;
    }

    int getPopulation() {
        return qtPopulation;
    }
    
    int getInteractions() {
        return qtInteractions;
    }

    int getMutation() {
        return mutation;
    }

    int getSurvival() {
        return survival;
    }

    int getFile() {
        return file;
    }
};
#endif