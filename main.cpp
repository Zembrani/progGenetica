#include "lib/lib.hpp"
#include <sys/time.h>

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec + (double) t.tv_usec / 1000000;
}

int main(int argc, char const* argv[]) {
  // FileOperator file;
  Solution solution;
  GetParameters parameters;
  double initialTime, finalTime;

  int population = parameters.getPopulation();
  int interactions = parameters.getInteractions();
  int mutationDegree = parameters.getMutation();
  int survival = parameters.getSurvival();
  int numberFile = parameters.getFile() - 1;
  int deep = parameters.getDeep();
  vector <string> funcs = parameters.getFunc();
  vector <string> terms = parameters.getTerm();
  parameters.print();

  // vector<myMap> data = file.read(file.fileName[numberFile]);
  // int qtNos = file.getNos();

  // parameters.print(qtNos);

  // Genetic genetic;
  // genetic.run(data, population, interactions, qtNos, mutationDegree, survival);
  
  solution.setFunc(funcs);
  solution.setTerm(terms);

  initialTime = wtime();
  solution.generate(deep);
  finalTime = wtime();

  solution.print();
  cout << "Time: " << finalTime - initialTime << endl;

  return 0;
}
