#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "gap.h"
#include "ReaderWriter.h"

using std::cout;
using std::cin;
using std::endl;

int main () {
	Gap *gap = new Gap();
	if (0 != gap->Open()) exit(1);

	cout << "\nAgents: " << gap->GetNumAgts() << endl;
	cout << "\nTarefas: " << gap->GetNumTasks() << endl;
	cout << "\nCosts: \n";
	printMat<int>(gap->GetCosts(), gap->GetNumAgts(), gap->GetNumTasks());
	cout << "\nProfits: \n";
	printMat<int>(gap->GetProfits(), gap->GetNumAgts(), gap->GetNumTasks());
	cout << "\nAgents capacity:\n";
	int *aux = gap->GetCapacities();
	for(int i=0; i<gap->GetNumAgts(); i++){
		cout << aux[i] << " ";
	}
	cout << "\n\n";

	gap->GreedyRandomizedConstruction (0.3, std::time(0));
	cout << "Total: " << gap->TotalProfit() << endl;

	delete gap;
	delete[] aux;
	return 0;
}