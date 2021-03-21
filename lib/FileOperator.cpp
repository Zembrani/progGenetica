#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

#if !defined(FILEOPERATOR)
#define FILEOPERATOR

struct FileOperator {
  vector<string> fileName = {"trainning1.txt", "trainning2.txt"};
  ifstream myFile;

  void listOptions(void) {
    long unsigned int i;
    for (i = 0; i < fileName.size(); i++) {
      cout << fileName[i] << endl;
    }
  };

// Faz a leitura do arquivo e retorna o vetor de dados
  void read(string fileName) {
    myFile.open(fileName);

    if (!myFile.is_open())
      exit(1);

    myFile.close();
    }

  // Imprime o vetor com os nós
    void printData() {
    }

};
#endif // FILEOPERATOR