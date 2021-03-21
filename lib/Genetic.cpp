#include "Solution.cpp"
#include "FileOperator.cpp"
#include<bits/stdc++.h>

#if !defined(GENETIC)
#define GENETIC

struct Genetic {
  void run(int population, int interactions, int mutationDegree, int survivals, int deep, vector <string> funcs, vector <string> terms, int numberFile) {
    
    vector <Solution> solutions;
    Solution solution;
    solution.setFunc(funcs);
    solution.setTerm(terms);
    solution.generate(deep);
    solution.print();

    FileOperator file;
    file.read(file.fileName[numberFile]);
    file.printData();
    

    //Criando a população inicial
    // for (int i = 0; i < population; i++) {
    //     solution.generate(deep);
    //     solutions.push_back(solution);
    // }
    cout << "sucesso : " << sucessAmount(solution) << endl;
    //Avaliação das soluções
    // for (int i = 0; i < population; i++) {
    //   Solution temp = solutions[i];
    //   sucessAmount(temp);
    // }


    //Ordenação do vetor de resultados
    // if (sucessSolution.size() > 1) {
    //   sucessSolution = mergeSort(sucessSolution);
    // }

    // cout << "Geração 0" << endl;
    // print(sucessSolution);

    // int i = 0;
    // vector <double> probabilityArray;

    // while ( i < interactions) {
    //   //cout << "Geração " << i << endl;
    //   i++;
    //   if (nextGeneration.size() != 0) sucessSolution = nextGeneration;

    //   nextGeneration = createNextGeneration(sucessSolution, mutationDegree, survivals);
      
    //   //Avaliação das soluções
    //   vector < ObjectSolution > aux;
    //   for (int i = 0; i < population; i++) {
    //     Solution temp = nextGeneration[i].solution;
    //     aux.push_back(sucessAmount(data, temp, qtNos));
    //   }
    //   nextGeneration = aux;

    //   probabilityArray = probability(nextGeneration);
    //   nextGeneration = removeWorst(nextGeneration, (int)nextGeneration.size(), probabilityArray);
      // cout << "geração " << i << endl;
      // print(nextGeneration);
      // cout << "------------------" << endl;
    }

    //Função que verifica a qualidade da solução
    int sucessAmount(Solution solution) {
        int size = solution.solution.size();
        vector <string> funcSet = solution.getFuncs();
        int i;
        int sum = 0;

        // Encontra o ultimo operador
        for (i = size-1; i >= 0; i--) {
            auto it = find(funcSet.begin(), funcSet.end(), solution.solution[i]);
            if (it != funcSet.end()) {
                calc(solution, i, funcSet);
            }
        }
        return sum;
    };

    void calc(Solution solution, int index, vector <string> funcSet) {
        cout << "solution[index] " << solution.solution[index] << endl;
        switch ((char)solution.solution[index]) {
            case funcSet[0]:
                cout << "Faz soma " << endl;
                break;
            case funcSet[1]:
                cout << "Faz subtração " << endl;
                break;
            case funcSet[2]:
                cout << "Faz multiplicação " << endl;
                break;
            case funcSet[3]:
                cout << "Faz divisão " << endl;
                break;
            default:
                break;
        }
    }
};
#endif