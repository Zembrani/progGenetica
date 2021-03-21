#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#if !defined(FILEOPERATOR)
#define FILEOPERATOR

struct FileOperator {
  vector<string> fileName = {"trainning1.txt", "trainning2.txt"};
  ifstream myFile;
  vector <int> input;
  vector <int> output;

  void listOptions(void) {
    int i;
    for (i = 0; i < (int)fileName.size(); i++) {
      cout << fileName[i] << endl;
    }
  };

// Faz a leitura do arquivo e retorna o vetor de dados
  void read(string fileName) {
    myFile.open(fileName);
    int count;
    int aux;

    if (!myFile.is_open()) {
      cout << "Arquivo não encontrado" << endl;
      exit(1);
    }

  // Leitura dos valores de entrada da funcao
    myFile >> count;

    for (int i = 0; i < count; i++) {
      myFile >> aux;
      input.push_back(aux);
    }

  // Leitura dos valores de saida da funcao
    myFile >> count;

    for (int i = 0; i < count; i++) {
      myFile >> aux;
      output.push_back(aux);
    }
    myFile.close();
    }

  // Imprime o vetor com os nós
  void printData() {
    cout << "vetor de entrada" << endl;
    print(input);
    cout << "vetor de saida" << endl;
    print(output);
  }

  void print(vector <int> vec) {
    for (auto&& it : vec) {
      cout << it << " ";
    }
    cout << endl;
  }

  vector <int> getInput() {
    return input;
  }

  vector <int> getOutput() {
    return output;
  }
};
#endif // FILEOPERATOR