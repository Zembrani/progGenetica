#include "lib/lib.hpp"
#include <sys/time.h>

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec + (double) t.tv_usec / 1000000;
}

int main(int argc, char const* argv[]) {
  Genetic genetic;
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

  initialTime = wtime();
  genetic.run(population, interactions,mutationDegree, survival, deep, funcs, terms, numberFile);
  finalTime = wtime();

  cout << "Time: " << finalTime - initialTime << endl;

  return 0;
}
