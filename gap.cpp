#include "gap.h"
#include "ReaderWriter.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::srand;
using std::rand;

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

int Gap::TotalProfit () {
	int total = 0;
	for(int tsk=0; tsk<aNumTasks; tsk++){
		if(apAssign[tsk] != -1)
			total += apProfits[apAssign[tsk]][tsk];
	}
	return total;
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

void Gap::ShowAssign () {
	cout << "(";
	for (int task=0; task<aNumTasks; task++) {
		cout << apAssign[task] << ( (task == (aNumTasks-1) ) ? "":", " );
	}
	cout << ")\n";
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

void Gap::SetNumAgts (int numAgts) {
	if (numAgts <= 0) {
		cerr << "Invalid argument!" <<
					" There must be a positive number of agents.\n";
	} else {
		aNumAgts = numAgts;
	}
}

void Gap::SetNumTasks (int numTasks){
	if (numTasks <= 0) {
		cerr << "Invalid argument!" <<
					"There must be a positive number of tasks.\n";
	} else aNumTasks = numTasks;
}

void Gap::SetMaxProfit (int maxProfit){
	if (maxProfit < 0) {
		cerr << "Invalid argument!" <<
					" Can't have a negative solution.\n";
	} else aMaxProfit = maxProfit;
}

void Gap::SetCosts (int **costs) {
	if (costs == NULL) {
		cerr << "Invalid argument!" <<
					" Can't set the costs to NULL\n";
	} else {
		for (int agnt=0; agnt<aNumAgts; agnt++) {
			for (int tsk=0; tsk<aNumTasks; tsk++) {
				if (apProfits[agnt][tsk] < 0) {
					cerr << "Invalid argument!" <<
								" Can't set negative costs.\n";
					return;
				}
				apCosts[agnt][tsk] = costs[agnt][tsk];
			}
		}
	}
	
}

void Gap::SetProfits (int **profits) {
	if (profits == NULL) {
		cerr << "Invalid argument!" <<
					" Can't set the profits to NULL\n";
	} else {
		for (int agnt=0; agnt<aNumAgts; agnt++) {
			for (int tsk=0; tsk<aNumTasks; tsk++) {
				if (profits[agnt][tsk] < 0) {
					cerr << "Invalid argument!" <<
								" Can't set negative profits.\n";
					return;
				}
				profits[agnt][tsk] = apProfits[agnt][tsk];
			}
		}
	}
}

void Gap::SetCapacity (int *caps) {
	if (caps == NULL) {
		cerr << "Invalid argument!" <<
					" Can't set the capcities to NULL\n";
	} else {
		for (int agnt=0; agnt<aNumAgts; agnt++) {
			if (caps[agnt] < 0) {
				cerr << "Invalid argument!" <<
							" Can't set negative capacities.\n";
				return;
			}
			apCapacity[agnt] = caps[agnt];
		}
	}
}

void Gap::SetAssign (int *assign) {
	if(assign == NULL) {
		cerr << "Invalid argument!" <<
					" Can't set the capcities to NULL\n";
	} else {
		for (int tsk=0; tsk<aNumTasks; tsk++) {
			if(assign[tsk] < 0 || assign[tsk] >= aNumAgts) {
				cerr << "Invalid assignment!\n";
				return;
			}
		}
		apAssign = assign;
	}
}

int Gap::AssignCost (int agnt, int task) {
	if (task < 0 || task > aNumTasks) {
		cerr << "Invalid task number!\n";
	} else if (agnt < 0 || agnt > aNumAgts) {
		cerr << "Invalid agent number!\n";
	} else  return apCosts[agnt][task];
	return 1;
}

int Gap::AgentCapacity (int agnt) {
	if (agnt < 0 || agnt > aNumAgts) {
		cerr << "Invalid agent number!\n";
	} else  return apCapacity[agnt];
	return 1;
}

bool Gap::Allocate (int agnt, int task) {
	if (task < 0 || task > aNumTasks) {
		//cerr << "Invalid task number!\n";
		return false;
	} else if (agnt < 0 || agnt > aNumAgts) {
		//cerr << "Invalid agent number!\n";
		return false;
	} else if (CntCapacity(agnt) + apCosts[agnt][task] > apCapacity[agnt]) {
		//cerr << "Agent " << agnt+1 << " can't exceed its capacity!\n";
		return false;
	} else 	return true;
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

vector<int> Gap::GetCandidates (int task) {
	vector<int> candidates;
	for (int agnt=0; agnt<aNumAgts; agnt++) {
		if(Allocate(agnt, task)) candidates.push_back(agnt);
	}
	return candidates; 
}

vector<float> Gap::EvaluateCandidates (int task, vector<int> cand) {
	vector<float> values;
	int tot   = TotalProfit();
	float val = 0;
	for (int i=0; i < cand.size(); i++) {
		values.push_back(apProfits[cand[i]][task]);
	}
	return values; 
}

void Gap::ResetAssignments () {
	for (int tsk=0; tsk<aNumTasks; tsk++) {
			apAssign[tsk] = -1;
	}
}

int* Gap::GreedyRandomizedConstruction (float alpha, int seed) {
	vector<int> lrc;
	vector<int> cdt;
	int sel          = 0;
	int task         = 0;
	float threshold  = 0;
	int c_min        = 0;
	int c_max        = 0;
	srand(seed);
	cout << "Building a solution...\n";
	// Avaliação de custos dos elementos
	while (!IsASolution(apAssign)) {
		task = 0;
		ResetAssignments();
		cdt = GetCandidates(0);
		while (cdt.size() > 0 && task < aNumTasks) {
			// Calculating maximum and minimum costs
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
			// Calculating the threshold
			threshold = c_min + alpha*(c_max - c_min);
			// Add all candidates that are subject to
			// inc_val(e) >= threshold
			for (int e=0; e<cdt.size(); e++) {
				if (apProfits[cdt[e]][task] >= threshold) {
					lrc.push_back(cdt[e]);
				}
			}
			// Select a pseudo-random element form LRC
			if(0 == lrc.size()) break;
 			sel = rand() % lrc.size();
			if (sel < 0) sel = (-1)*sel;
			// Update solution
			apAssign[task] = lrc[sel];
			// Update candidate list
			task++;
			cdt.clear();
			lrc.clear();
			cdt = GetCandidates(task);
		}
	}
	cout << "Assignments: ";
	ShowAssign();
	cout << "Capacities: ";
	for (int i=0; i<aNumAgts; i++) {
		cout << CntCapacity(i) << " ";
	}
	cout << "\n\n";
	return apAssign;
}

vector<int*> Gap::Neighbor (int *assignment, int task) {
	srand(std::time(NULL));
	vector<int*> neighbor;
	vector<int> candidates;
	int opt1 = assignment[task] ;
	assignment[task] = -1;

	for (int agnt=0; agnt<aNumAgts; agnt++) {
		if (Allocate(agnt, task) && agnt != opt1) {
			candidates.push_back(agnt);
		}
	}
	
	for (int i=0; i<candidates.size(); i++) {
		neighbor.push_back(GetAssign());
		neighbor[i][task] = candidates[i];
	}

	assignment[task] = opt1;
	return neighbor;
}

int* Gap::LocalSearch (int *assignment) {
	srand(std::time(NULL));
	bool proceed             = true;
	int local_min            = 0;
	int task                 = rand() % aNumTasks;
	vector<int*> my_neighbor = Neighbor(assignment, task);
	return NULL;
}

int Gap::Grasp(int maxIteration, int seed){
	for (int cnt_it=0; cnt_it < maxIteration; cnt_it++) {
		apAssign = GreedyRandomizedConstruction(0.5, seed);
		apAssign = LocalSearch(apAssign);
		if(TotalProfit() > aMaxProfit) SetMaxProfit(TotalProfit());
	}
	return 0;
}