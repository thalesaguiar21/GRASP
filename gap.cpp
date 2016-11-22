#include "gap.h"
#include "ReaderWriter.h"
#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <chrono>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::vector;

Gap::Gap () {
	aNumAgts        = 0;
	aNumTasks       = 0;
	aMaxProfit      = 0;
	aVisitedNodes   = 0;
	apCosts         = NULL;
	apProfits       = NULL;
	apCapacity      = NULL;
	apAssign        = NULL;
}

Gap::~Gap () {
	for(int i=0; i<aNumAgts; i++)
		delete[] apCosts[i];
	delete[] apCosts;

	for(int i=0; i<aNumAgts; i++)
		delete[] apProfits[i];
	delete[] apProfits;

	delete[] apCapacity;
	delete[] apAssign;
}

int Gap::Open () { 
	int FAIL = 0;
	FAIL = ReadInput();
	if (0 == FAIL) {
		apAssign = new int[aNumTasks];
		for (int tsk=0; tsk<aNumTasks; tsk++) {
			apAssign[tsk] = -1;
		}
	}
	return FAIL; 
}

bool Gap::Allocate (int agnt, int task) {
	if (task < 0 || task > aNumTasks) {
		return false;
	} else if (agnt < 0 || agnt > aNumAgts) {
		return false;
	} else if (CntCapacity(agnt) + apCosts[agnt][task] > apCapacity[agnt]) {
		return false;
	} else 	return true;
}

int Gap::CntCapacity (int agt) {
	int total = 0;
	int aux_agt = 0;
	for (int tsk=0; tsk<aNumTasks; tsk++) {
		aux_agt = apAssign[tsk];
		if (aux_agt == agt) total += apCosts[aux_agt][tsk];
	}
	return total;
}

void Gap::ResetAssignments () {
	for (int tsk=0; tsk<aNumTasks; tsk++) {
		apAssign[tsk] = -1;
	}
}

int Gap::Grasp(int maxIteration){
	int *best_assign = NULL;
	int best_profit  = 0;
	int total_p      = 0;
	int mediana_p    = 0.0;
	int melhor_p     = 0;
	int pior_p       = 0;

	int total_t      = 0;
	int mediana_t    = 0.0;
	int melhor_t     = 0;
	int pior_t       = 0;
	struct timeval inicio, final;
    int tmili;
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	aRandGen.seed(seed1);

	for (int cnt_it=0; cnt_it < maxIteration; cnt_it++) {
		cout << cnt_it + 1 << "º iteration...\n";
		ResetAssignments();
		gettimeofday(&inicio, NULL);
		apAssign = GreedyRandomizedConstruction(0.1);
		gettimeofday(&final, NULL);
		tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
		/*LocalSearch();
		cout << "Neighbor profit: " << TotalProfit(apAssign) << endl;
		int profit_aux = TotalProfit(apAssign);
		if(profit_aux > best_profit) {
			best_profit = profit_aux;
			best_assign = GetAssign();
		}
		cout << "Best profit: " << TotalProfit(best_assign) << endl;
		cout << "Best assignment: ";
		cout << "(";
		for (int task=0; task<aNumTasks; task++) {
			cout << best_assign[task] << ( (task == (aNumTasks-1) ) ? "" : ", " );
		}
		cout << ")\n\n";*/
		int tmp = TotalProfit(apAssign);
		total_p += TotalProfit();
		if (melhor_p == 0) {
			melhor_p = tmp;
			pior_p = tmp;
		} else {
			if (melhor_p < tmp) {
				melhor_p = tmp;
			} 
			if (pior_p > tmp) {
				pior_p = tmp;
			}
		}

		total_t += tmili;
		if (melhor_t == 0) {
			melhor_t = tmili;
			pior_t = tmili;
		} else {
			if (melhor_t > tmili) {
				melhor_t = tmili;
			} 
			if (pior_t < tmili) {
				pior_t = tmili;
			}
		}
		if (cnt_it == 5) {
			mediana_p = tmp;
			mediana_t = tmili;
		}
	}

	cout << "     \t\tMelhor Media Mediana Pior\n";
	cout << "Tempo\t\t" << melhor_t << " " << total_t / 15.0 << " " << mediana_t << " " << pior_t << endl;
	cout << "Lucro\t\t" << melhor_p << " " << total_p / 15.0 << " " << mediana_p << " " << pior_p << endl;

	return 0;
}

int* Gap::GreedyRandomizedConstruction (float alpha) {
	vector<int> lrc;
	vector<int> cdt;
	int sel          = 0;
	int task         = 0;
	int c_min        = 0;
	int c_max        = 0;
	float threshold  = 0;
	
	while (!IsASolution(apAssign)) {
		task = 0;
		cdt  = FindCandidates(0);
		ResetAssignments();
		while (cdt.size() > 0 && task < aNumTasks) {
			c_min = apProfits[0][task];
			c_max = apProfits[0][task];
			for (int i=1; i<cdt.size(); i++) {
				if (apProfits[cdt[i]][task] < c_min) {
					c_min = apProfits[cdt[i]][task];
				}
				if (apProfits[cdt[i]][task] > c_max) {
					c_max = apProfits[cdt[i]][task];
				} 
			}
			threshold = c_min + alpha*(c_max - c_min);
			for (int e=0; e<cdt.size(); e++) {
				if (apProfits[cdt[e]][task] >= threshold) {
					lrc.push_back(cdt[e]);
				}
			}
			if (0 == lrc.size()) break;
 			sel = aRandGen() % lrc.size();
			apAssign[task] = lrc[sel];

			task++;
			cdt.clear();
			lrc.clear();
			cdt = FindCandidates(task);
		}
		cdt.clear();
		lrc.clear();
	}
	return apAssign;
}

vector<int> Gap::FindCandidates (int task) {
	vector<int> candidates;
	for (int agnt=0; agnt<aNumAgts; agnt++) {
		if(Allocate(agnt, task)) candidates.push_back(agnt);
	}
	return candidates; 
}

int Gap::AgentCapacity (int agnt) {
	if (agnt < 0 || agnt > aNumAgts) {
		cerr << "Invalid agent number!\n";
	} else  return apCapacity[agnt];
	return 1;
}

void Gap::LocalSearch () {
	vector<int*> neighbors;
	for (int tsk=0; tsk<aNumTasks; tsk++) {
		neighbors = Neighbor(tsk);

		for (int i=0; i<neighbors.size(); i++) {
			int neighSol = TotalProfit(neighbors[i]);
			if (neighSol > TotalProfit(apAssign)) {
				for (int t=0; t<aNumTasks; t++) {
					apAssign[t] = neighbors[i][t];
				}
			}
		}
		for (int i=0; i<neighbors.size(); i++) {
			delete[] neighbors[i];
		}
		neighbors.clear();
	}
	return;
}

vector<int*> Gap::Neighbor (int task) {
	vector<int*> neighbor;
	vector<int> candidates;
	int opt1 = apAssign[task];
	int neig = 0;
	apAssign[task] = -1;

	for (int agnt=0; agnt<aNumAgts; agnt++) {
		if (Allocate(agnt, task) && agnt != opt1) {
			neighbor.push_back(GetAssign());
			neighbor[neig][task] = agnt;
			neig++;
		}
	}

	apAssign[task] = opt1;
	return neighbor;
}

void Gap::ShowAssign () {
	cout << "(";
	for (int task=0; task<aNumTasks; task++) {
		cout << apAssign[task] << ( (task == (aNumTasks-1) ) ? "":", " );
	}
	cout << ")\n";
}

int Gap::TotalProfit () {
	int total = 0;
	for(int tsk=0; tsk<aNumTasks; tsk++){
		if(apAssign[tsk] != -1)
			total += apProfits[apAssign[tsk]][tsk];
	}
	return total;
}

int Gap::TotalProfit (int *assignment) {
	int total = 0;
	for (int tsk=0; tsk<aNumTasks; tsk++) {
		if (assignment[tsk] != -1) {
			total += apProfits[assignment[tsk]][tsk];
		}
	}
	return total;
}

int Gap::GetNumAgts () {
	return aNumAgts;
}

int Gap::GetNumTasks () {
	return aNumTasks;
}

int Gap::GetMaxProfit () {
	return aMaxProfit;
}

int Gap::GetVisitedNodes () {
	return aVisitedNodes;
}

int* Gap::GetAssign () {
	int *assign_cp = new int[aNumTasks];
	for (int tsk=0; tsk<aNumTasks; tsk++) {
		assign_cp[tsk] = apAssign[tsk];
	}
	return assign_cp;
}

int* Gap::GetCapacities () {
	int *capacity_cp = new int[aNumAgts];
	for (int agnt=0; agnt<aNumAgts; agnt++) {
		capacity_cp[agnt] = apCapacity[agnt];
	}
	return capacity_cp;
}

int** Gap::GetCosts () {
	int **costs_cp = new int*[aNumAgts];
	for (int agnt=0; agnt<aNumAgts; agnt++) {
		costs_cp[agnt] = new int[aNumTasks];
		for (int tsk=0; tsk<aNumTasks; tsk++) {
			costs_cp[agnt][tsk] = apCosts[agnt][tsk];
		}
	}
	return costs_cp;
}

int** Gap::GetProfits () {
	int **profits_cp = new int*[aNumAgts];
	for (int agnt=0; agnt<aNumAgts; agnt++) {
		profits_cp[agnt] = new int[aNumTasks];
		for (int tsk=0; tsk<aNumTasks; tsk++) {
			profits_cp[agnt][tsk] = apProfits[agnt][tsk];
		}
	}
	return profits_cp;
}

bool Gap::IsASolution (int *assignment) {
	for (int task=0; task<aNumTasks; task++) {
		if(apAssign[task] == -1) return false;
	}
	for (int agnt=0; agnt<aNumAgts; agnt++) {
		if (CntCapacity(agnt) > apCapacity[agnt]) return false;
	}
	return true;
}

int Gap::ReadInput () {
	const char *file   = NULL;
	string file_name   = "";

	cout << "Type in the file name: ";
	cin >> file_name;
	file = file_name.c_str();

	apCosts = readResource<int> (file, aNumAgts, aNumTasks);
	apProfits = readCost<int> (file, aNumAgts, aNumTasks);
	apCapacity = readAgentsCap<int> (file, aNumAgts, aNumTasks);
	if (!apCosts || !apProfits || !apCapacity) {
		cerr << "Could not read the file!\n";
		return 1;
	} else return 0;
}