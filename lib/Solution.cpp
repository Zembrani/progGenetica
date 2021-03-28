#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

#if !defined(SOLUTION)
#define SOLUTION

struct Solution {
  vector <string> solution;
  vector <string> termSet;
  vector <string> funcSet;
  double sucessLevel;
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

  // Funcao que concatena ou substitui uma subarvore derivada de outra solucao, na solucao atual
  void crossover(Solution solution2) {
    vector <int> indexes;
    vector <int> indexes2;
    vector <string> subTree;
    int deepSubTree;
    int deepSolutionSubTree;
    int index;
    int teste;

    indexes = operatorCount(solution2.solution);
    cout << "Solucao PAI" << endl;
    print(solution);
    cout << "Solucao MAE" << endl;
    print(solution2.solution);

    random_device rd;
    mt19937 gen(rd());

    if (indexes.size() > 1) {
      uniform_int_distribution<> distrib(0, (int)indexes.size() -1);
      index = distrib(gen);
      cout << "**** Arvore de entrada *****"<< endl;
      print(solution2.solution);
      cout << "valor do index " << indexes[index] << endl;
      subTree = returnSubTree(solution2.solution, indexes[index]);
      cout << "**** Arvore de Saida *****"<< endl;
      print(subTree);
    } else {
      subTree = solution2.solution;
    }
    // cout << " Arvore de saida " << endl;
    // print(subTree);
  // Fazer a função que retorna a profundidade da subtree ou a subtree em tal profundidade

    deepSubTree = deepCount(subTree);
    cout << "Profundidade da subtree " << deepSubTree << endl;
    cout << "Subtree " << endl;
    print(subTree);
  
    // cout << "indexes " << endl;
    // for (auto&& it : indexes) cout << " " << it;
    // cout << endl;
    // cout << "subTree " << endl;
    // print(subTree);
    // cout << "Solucao " << endl;
    // print(solution);
    indexes2 = operatorCount(solution);
    cout << "vetor de indexes " << endl;
    for (auto&& it : indexes2) cout << it << " ";
    cout << endl;

    // Se o indexes for menor que 1, significa que so existe um operador
    if (indexes2.size() > 1) {
      cout << "Entrou no if " << endl;
      uniform_int_distribution<> distrib(0, (int)indexes2.size() -1);
      // index eh onde inicia a subTree que sera substituida
      index = distrib(gen);
      deepSolutionSubTree = deepCount(solution, index);
      int teste2;
      while (deepSubTree + (deepMax - deepSolutionSubTree) <= deepMax + 1) {
        cout << "Comparando " << deepSubTree + (deepMax - deepSolutionSubTree) << " <= " << deepMax + 1 << endl;
        cin >> teste2;
        index = distrib(gen);
        deepSolutionSubTree = deepCount(solution, indexes2[index]);
      }
      cout << "Chama mergeTree com index =  " << indexes2[index] << endl;
      mergeTree(subTree, indexes2[index]);
    } else {
      cout << "Entrou no else " << endl;
      uniform_int_distribution<> distrib(1, 2);
      index = distrib(gen);
      // cout << "index = " << index << endl;
      cout << "Chama mergeTree com index =  " << index << endl;
      mergeTree(subTree, index, index);
    }
    cout << "Solucao de retorno" << endl;
    print(solution);
    cin >> teste;

  }

  // Faz o merge entre a subTree de outra solucao com a solucao atual, substituindo uma subarvore da solucao atual
  void mergeTree(vector <string> subTree, int indexInit, int indexFin = 0) {
    vector <string> newSolution;
    if (indexFin == 0) {
      cout << "Solucao do merge" << endl;
      print(solution);
      cout << "Index inicial " << indexInit << endl;
      vector <string> aux = returnSubTree(solution, indexInit);
      cout << "Parte a ser removida" << endl;
      print(aux);
      indexFin = aux.size();
    }
    int i = 0;
    for(; i < indexInit; i++) {
      newSolution.push_back(solution[i]);
    }
    for(int j = 0; j < (int)subTree.size(); j++) {
      newSolution.push_back(subTree[j]);
    }
    for(i += indexFin; i < (int)solution.size(); i++) {
      newSolution.push_back(solution[i]);
    }
    solution = newSolution;
  }

  // Percorre a arvore e conta a quantidade de operadores
  vector <int> operatorCount(vector <string> vec) {
    vector <int> indexes;
    int size = (int)vec.size()-1;

    for (int i = 1; i < size; i++){
      auto it = find(funcSet.begin(), funcSet.end(), vec[i]);
      if (it != funcSet.end()) {
        indexes.push_back(i);
      }
    }

    return indexes;
  }

  // Retorna uma subArvore
  vector <string> returnSubTree(vector <string> tree, int index) {
    vector <string> newTree;
    newTree.push_back(tree[index]);

    // Se começar por um termo retorna somente ele
    auto it = find(termSet.begin(), termSet.end(), tree[index]);
    if (it != termSet.end()) return newTree;

    index++;
    for (int i = 0; i < 2; i++) {
      auto itF = find(funcSet.begin(), funcSet.end(), tree[index]);
      auto itT = find(termSet.begin(), termSet.end(), tree[index]);
      if (itF != funcSet.end()) {
        vector <string> aux = returnSubTree(tree, index);
        for (auto&& it : aux) {
          newTree.push_back(it);
          index++;
        }
      } else if (itT != termSet.end()) {
        newTree.push_back(tree[index]);
        index++;
      }
    }
    return newTree;
  }

  int deepCount(vector <string> tree, int index = 0) {
    int deep = 0;
    int aux;
    auto it = find(funcSet.begin(), funcSet.end(), tree[index]);
    while (it != funcSet.end()) {
      index++;
      aux = deepCount(tree, index);
      index += aux;
      deep += aux;
      aux = 0;
      it = find(funcSet.begin(), funcSet.end(), tree[index]);
    }
    return deep + 1;
  }

  //Realiza amountOfChanges alterações, cada alteração consiste em alterar algum termo ou funcao.
  void mutate(int amountOfChanges) {
    // Random functions 
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, (int)solution.size()-1);
    uniform_int_distribution<> distribT(0, (int)termSet.size()-1);
    uniform_int_distribution<> distribF(0, (int)funcSet.size()-1);

    for (int i = 0; i < amountOfChanges; i++){
      int index = distrib(gen);
      auto it = find(funcSet.begin(), funcSet.end(), solution[index]);
      if (it != funcSet.end()) {
        while(flipF(index, distribF(gen)));
      }
      it = find(termSet.begin(), termSet.end(), solution[index]);
      if (it != termSet.end()) {
        while(flipT(index, distribT(gen)));
      }
    }
  }

  // Faz a alteracao do operador por outro diferente
  int flipF(int index1, int index2) {
    if (solution[index1] == funcSet[index2]) return 1;
    solution[index1] = funcSet[index2];
    return 0;
  }

  // Faz a alteracao de termo por outro diferente
  int flipT(int index1, int index2) {
    if (solution[index1] == termSet[index2]) return 1;
    solution[index1] = termSet[index2];
    return 0;
  }

  void print(vector <string> vec) {
    for (auto&& literal : vec) {
      cout << literal << " ";
    }
     cout << endl;
  }

  void printAll() {
    cout << "Solution" << endl;
    print(solution);
    cout << "Set de funcoes" << endl;
    print(funcSet);
    cout << "Set de termos" << endl;
    print(termSet);
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