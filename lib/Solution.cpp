#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

#if !defined(SOLUTION)
#define SOLUTION

struct Solution {
  int qtInstances = 0;
  vector<string> solution;
  bool wasModified = false;
  vector <string> termSet;
  vector <string> funcSet;
  int deepMax;

// Gera uma solucao aleatoria
  void generate(int deep) {
    deepMax = deep;
    solution = gerNextExpr(0);
  }

  //Gera os proximos valores da arvore
  vector<string> gerNextExpr(int deep) {
    vector<string> nextExpre;
    vector<string> aux;
    bool lastIsFunc = false;
    double item = itemRandom();

    if (deep <= deepMax) {
      if ((deep == 0 || item > getProbability()) && !(deep == deepMax)) {
        // Adiciona os operadores
        int element = elementRandom(funcSet.size());
        nextExpre.push_back(funcSet[element]);
        lastIsFunc = true;
      } else 
        if (deep == deepMax || item < getProbability()) {
        // Adiciona elementos utilizados nas operacoes
        int element = elementRandom(termSet.size());
        nextExpre.push_back(termSet[element]);
        lastIsFunc = false;
      }
    }
    // Faz a chamada recursiva se o ultimo elemento adicionado for uma funcao
    if (lastIsFunc) {
      for(int i = 0; i < 2; i++) {
        aux = gerNextExpr(deep+1);
        for (auto&& it : aux) {
          nextExpre.push_back(it);
        }
      }
    }
    return nextExpre;
  }

  // Gera um valor para a probabilidade entre a quantidade de operadores e de termos
  double getProbability() {
    return (double)termSet.size() / (termSet.size() + funcSet.size());
  }

  // Retorna um double aleatório entre 0.1 e 1.0
  double itemRandom() {
    random_device rd;
    default_random_engine gen(rd());
    uniform_real_distribution<double> distrib(0.1, 1.0);
    return distrib(gen);
  }

  // Retorna um int aleatório entre 0 e size
  int elementRandom(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, size - 1);
    return distrib(gen);
  }

  void print() {
    for (auto&& literal : solution) {
      cout << literal << " ";
    }
     cout << endl;
  }

  void setTerm(vector <string> terms) {
    termSet = terms;
  }

  void setFunc(vector <string> funcs) {
    funcSet = funcs;
  }

  vector <string> getFuncs() {
    return funcSet;
  }
};

#endif