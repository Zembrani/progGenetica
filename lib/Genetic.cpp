#include "Solution.cpp"
#include "FileOperator.cpp"
#include <bits/stdc++.h>

#if !defined(GENETIC)
#define GENETIC

struct Genetic {
  void run(int population, int interactions, int mutationDegree, int survivals, int deep, vector <string> funcs, vector <string> terms, int numberFile) {
    
    vector <Solution> solutions;
    Solution solution;
    solution.setFunc(funcs);
    solution.setTerm(terms);
    solution.generate(deep);
    solution.print(solution.solution);

    FileOperator file;
    file.read(file.fileName[numberFile]);
    file.printData();
    vector <int> input = file.getInput();
    vector <int> output = file.getOutput();

   //Criando a população inicial
    // for (int i = 0; i < population; i++) {
    //     solution.generate(deep);
    //     solutions.push_back(solution);
    // }
    cout << sucessAmount(solution, input, output) << endl;
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
    int sucessAmount(Solution solution, vector <int> input, vector <int> output) {
        int sum = 0;
        Solution original = solution;
        vector <int> xindex = findAllX(solution);
        int sizeX = (int)xindex.size();
        if (sizeX > 0) {
            for (int i = 0; i < (int)input.size(); i++) {
                solution = original;
                for (int j = 0; j < sizeX; j++) {
                    solution.solution[xindex[j]] = to_string(input[i]);
                }
                solution.print(solution.solution);
                cin >> sum;
                solution = findOperator(solution);
                cout << "resultado : ";
                solution.print(solution.solution);
            }
        } else {
            solution = findOperator(solution);
        }

        solution.print(solution.solution);
        return sum;
    };

    vector <int> findAllX(Solution solution) {
        vector <int> xindexs;
        for (int i = 0; i < (int)solution.solution.size(); i++) {
            if (solution.solution[i] == "x") {
                xindexs.push_back(i);
            }
        }
        return xindexs;
    }
    // Encontra os operadores e realiza os calculos ate obter o resultado final da funcao
    Solution findOperator(Solution solution) {
        vector <string> funcSet = solution.getFuncs();
        int i;
        int size = solution.solution.size();
        for (i = size-1; i >= 0; i--) {
            auto it = find(funcSet.begin(), funcSet.end(), solution.solution[i]);
            if (it != funcSet.end()) {
                double value = calc(solution, i, funcSet);
                solution.solution[i] = to_string(value);
                solution = removeElement(solution, i+1, (int)solution.solution.size());
            }
        }
        return solution;
    }

    // Verifica as operacoes e realiza o calculo de acordo, retorna o resultado dessa operacao
    double calc(Solution solution, int index, vector <string> funcSet) {

        double result = 0.0;

        if (solution.solution[index] == "+") {
            result = stod(solution.solution[index + 1]) + stod(solution.solution[index + 2]);
            return result;
        }
        if (solution.solution[index] == "-") {
            result = stod(solution.solution[index + 1]) - stod(solution.solution[index + 2]);
            return result;
        }
        if (solution.solution[index] == "*") {
            result = stod(solution.solution[index + 1]) * stod(solution.solution[index + 2]);
            return result;
        }
        if (solution.solution[index] == "/") {
            if (stod(solution.solution[index + 2]) == 0) {
                return 0;
            }
            result = stod(solution.solution[index + 1]) / stod(solution.solution[index + 2]);
            return result;
        }
        return result;
    }

    // Puxa os elementos do vetor duas casas para frente e retorna o novo vetor
    Solution removeElement(Solution solution, int index, int size) {
        for(int i = index; i < size - 2; i++) {
            solution.solution[i] = solution.solution[i+2];
        }
        solution.solution[size-2]={};
        solution.solution[size-1]={};
        
        return solution;
    }
};
#endif