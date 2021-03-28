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
    vector <Solution> sucessLevel;
    vector <Solution> nextGeneration;
    int survivalBackup = survivals;

    FileOperator file;
    file.read(file.fileName[numberFile]);
    file.printData();
    vector <int> input = file.getInput();
    vector <int> output = file.getOutput();

   //Criando a população inicial
    for (int i = 0; i < population; i++) {
        solution.generate(deep);
        solutions.push_back(solution);
    }

    int i = 0;
    vector <double> probabilityArray;

    while (i < interactions) {
        if (nextGeneration.size() != 0) solutions = nextGeneration;

        //Avaliação das soluções
        vector <Solution> aux;
        for (int j = 0; j < population; j++) {
            Solution temp = solutions[j];
            aux.push_back(sucessAmount(temp, input, output));
        }
        solutions = aux;

        // Ordenacao do vetor de solucoes
        if ((int)nextGeneration.size() > 1) {
            solutions = mergeSort(solutions);
        }

        // if (i%10 == 0) {
            cout << "******* Geração " << i << " *******" << endl;
            printVectorDouble(solutions);
            cout << "*********************" << endl;
        // }

        // Conta a quantidade de elementos otimos e faz eles persistirem
        survivals = survivalBackup;
        for (int j = 0; j < (int)solutions.size(); j++) {
            // cout << "sucess Level - " << solutions[j].sucessLevel << endl;
            survivals += solutions[j].sucessLevel == 0 ? 1 : 0;
        }
        // cout << "survivals " << survivals << endl;
        // cout << "-----------------------------" << endl;

        i++;
        nextGeneration = createNextGeneration(solutions, mutationDegree, survivals);

        // probabilityArray = probability(nextGeneration);
        //   nextGeneration = removeWorst(nextGeneration, (int)nextGeneration.size(), probabilityArray);
    }
  }

    //Função que verifica a qualidade da solução
    Solution sucessAmount(Solution solution, vector <int> input, vector <int> output) {
        Solution original = solution;
        vector <int> xindex = findAllX(solution);
        int sizeX = (int)xindex.size();
        vector<double> results;

        if (sizeX > 0) {
            for (int i = 0; i < (int)input.size(); i++) {
                solution = original;
                for (int j = 0; j < sizeX; j++) {
                    solution.solution[xindex[j]] = to_string(input[i]);
                }
                solution = findOperator(solution);
                results.push_back(stod(solution.solution[0]));
            }
        } else {
            for (int i = 0; i < (int)input.size(); i++) {
                solution = findOperator(solution);
                results.push_back(stod(solution.solution[0]));
            }
        }
        // solution.print(solution.solution);
        solution = original;
        solution.sucessLevel = calculateDiff(results, output);
        return solution;
    };

    // Encontra todas as variaveis x na funcao
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

    // Calcula a diferença sobre cada ponto da funcao gerada com os da funcao esperada, retorna a soma da diferenca desses pontos
    double calculateDiff(vector <double> resultsObtained, vector <int> resultExpected) {
        double sum = 0;
        for (int i = 0; i < (int)resultExpected.size(); i++) {
            // cout << resultsObtained[i] << " - " << resultExpected[i] << " = " << abs(resultsObtained[i] - resultExpected[i]) << endl;
            sum += abs(resultsObtained[i] - resultExpected[i]);
        }
        return sum;
    }

    void printVectorDouble(vector<Solution> vec) {
        for (auto&& it : vec) {
            it.print(it.solution);
            cout << "Sucess Level - " << it.sucessLevel << endl;
        }
    }

    // Ordena o vetor de resultados
    vector <Solution> mergeSort(vector <Solution> results) {
        int size = (int)results.size();
        //Fim da chamada recursiva
        if (size <= 1) return results;

        vector <Solution> merge1;
        vector <Solution> merge2;
        vector <Solution> result;

        // Divisão do vetor em duas partes
        int k;
        for (k = 0; k < size/2; k++) {
        merge1.push_back(results[k]);
        }
        for (; k < size; k++) {
        merge2.push_back(results[k]);
        }

        // Chamada recursiva
        merge1 = mergeSort(merge1);
        merge2 = mergeSort(merge2);

        int merge1Size = (int)merge1.size();
        int merge2Size = (int)merge2.size();
        int i = 0; int j = 0;

        while (i < merge1Size && j < merge2Size) {
            if (merge1[i].sucessLevel < merge2[j].sucessLevel) {
                result.push_back(merge1[i]);
                i++;
            } else {
                result.push_back(merge2[j]);
                j++;
            }
        }
        if (i < merge1Size) {
            for (; i < merge1Size; i++) {
                result.push_back(merge1[i]);
            }
        }
        if (j < merge2Size) {
            for (; j < merge2Size; j++) {
                result.push_back(merge2[j]);
            }
        }
        return result;
    }

    //Realiza a seleção probabilistica e gera um novo vetor com as soluções modificadas
    vector <Solution> createNextGeneration(vector <Solution> solution, int mutationDegree, int survivals) {
        vector <Solution> newSolutions;
        vector <double> probabilityArray;

        int size = (int)solution.size();

        probabilityArray = probability(solution);

        


        //Isto é para propagar os melhores sobreviventes sem alterações
        int i = 0;
        for (; i < survivals; i++) {
            newSolutions.push_back(solution[i]);
        }

        

        for (; i < size; i++) {
            // Seleciona o melhor entre dois aleatorios para fazer o crossover
            Solution toCrossOver = selectBestOfTwo(size, solution);
            toCrossOver.crossover(selectBestOfTwo(size, solution));

            newSolutions.push_back(toCrossOver);
            
            // int teste;
            // cin >> teste;
            //int mutateIndex = select(size, probabilityArray);
            
            //Realiza mutação com modify e modifyV2
            //Solution temp = solution[mutateIndex];
            //temp.mutate(mutationDegree);
            

            //newSolutions.push_back(temp);
        }

        return newSolutions;
    }

    //Função que gera o vetor com as probabilidades de cada solução
    vector <double> probability(vector <Solution> solution) {
        vector <double> probability;
        int sum = 0;
        double value  = 0.0;
        int size = (int)solution.size();

        for (int i = 0; i < size; i++) {
        sum += solution[i].sucessLevel;
        }

        for (int i = 0; i < size; i++) {
        value += probabilityValue(solution[i].sucessLevel, sum);
        probability.push_back(value);
        }
        return probability;
    }

    //Gera um valor double entre 0.1 e 10 de acordo o sucessLevel
    double probabilityValue(int sucessLevel, int sum) {
        double result = (sucessLevel * 1.0 / sum * 1.0) * 10;
        return sucessLevel != 0 ? result : 0;
    }

    //Função para selecionar probabilisticamente uma solução
    int select(int size, vector <double> probability) {
        //Rambom para gera um double aletatório
        random_device rd;
        default_random_engine gen(rd());
        uniform_real_distribution<double> distrib(0.1, size);

        double item = distrib(gen);

        for (int i = 0; i < size; i++) {
          if (item < probability[i]) return i;
        }
        return size-1;
    }

    //Função para selecionar a melhor entre duas solucoes selecionadas aleatoriamente
    Solution selectBestOfTwo(int size, vector <Solution> solution) {
        //Rambom para gera um double aletatório
        random_device rd;
        default_random_engine gen(rd());
        uniform_real_distribution<double> distrib(0, size);

        double first = distrib(gen);
        double second = distrib(gen);

        return solution[first].sucessLevel < solution[second].sucessLevel ? solution[first] : solution[second];
    }
};
#endif