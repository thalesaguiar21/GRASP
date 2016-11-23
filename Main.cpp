#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <random>
#include <sys/time.h>
#include "gap.h"
#include "ReaderWriter.h"

using std::cout;
using std::cin;
using std::endl;

int main () {
	Gap *gap = new Gap();
	int *result;
	if (0 != gap->Open()) exit(1);
	struct timeval inicio, final;
    int tmili;
    float tempoMin = 0.0;
    float solMin = 0.0;
    float tempoMax = 0.0;
    float solMax = 0.0;
    float tempoTotal = 0.0;
    float solTotal = 0.0;

	cout << "\nAgents: " << gap->GetNumAgts() << endl;
	cout << "\nTasks: " << gap->GetNumTasks() << endl;
	cout << "\nCosts: \n";
	printMat<int>(gap->GetCosts(), gap->GetNumAgts(), gap->GetNumTasks());
	cout << "\nProfits: \n";
	printMat<int>(gap->GetProfits(), gap->GetNumAgts(), gap->GetNumTasks());
	cout << "\nAgents capacity:\n";
	int *aux = gap->GetCapacities();
	for(int i=0; i<gap->GetNumAgts(); i++){
		cout << std::setfill(' ') << std::setw(3) << aux[i];
	}
	cout << "\n\n";

	for (int i=0; i<10; i++) {
		gettimeofday(&inicio, NULL);
		result = gap->ReactiveGrasp (37, 1.0);
		gettimeofday(&final, NULL);
		tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
		int cnt_sol = gap->TotalProfit(result);
		if (tmili > tempoMax) tempoMax = tmili;
		if (tempoMin == 0.0) tempoMin = tmili;
		else if (tmili < tempoMin) tempoMin = tmili;
		if (cnt_sol > solMax) solMax = cnt_sol;
		if (solMin == 0.0) solMin = cnt_sol;
		else if (cnt_sol < solMin) solMin = cnt_sol;
		solTotal += cnt_sol;
		tempoTotal += tmili;
	}
	cout << "Solução máxima, Solução média, Solução mínima, Tempo máximo, Tempo médio, Tempo mínimo.\n";
	cout << solMax;
	cout << "," << solTotal / 10.0;
	cout << "," << solMin;
	cout << "," << tempoMax;
	cout << "," << tempoTotal / 10.0;
	cout << "," << tempoMin << endl;

	delete[] result;
	delete gap;
	delete[] aux;
	return 0;
}