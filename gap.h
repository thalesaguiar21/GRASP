#ifndef GAP_H
#define GAP_H

#include <vector>

using std::vector;

class Gap{

public:

	Gap ();
	~Gap ();
	int           Open();
	bool          Allocate (int agnt, int task);
	int           CntCapacity (int agt);
	int           AssignCost (int agnt, int task);
	void          ResetAssignments ();
	vector<float> EvaluateCandidates (int task, vector<int> cand);
	int           Grasp (int maxIteration, int seed);
	int*          GreedyRandomizedConstruction (float alpha, int seed);
	void          UpdateSolution (int localSolution, int bestSolution);
	int           AgentCapacity (int agnt);
	vector<int>   GetCandidates (int task);
	int           TotalProfit ();
	int           TotalProfit (int *assignment);
	void          ShowAssign ();
	int*          LocalSearch (int *assignment);
	vector<int*>  Neighbor (int *assignment, int task);

	int    GetNumAgts ();
	int    GetNumTasks ();
	int    GetMaxProfit ();
	int    GetVisitedNodes ();
	int*   GetAssign ();
	int*   GetCapacities ();
	int**  GetCosts ();
	int**  GetProfits ();
	void   SetNumAgts (int numAgts);
	void   SetNumTasks (int numTasks);
	void   SetMaxProfit (int maxProfit);
	void   SetCosts (int **costs);
	void   SetProfits (int **profits);
	void   SetCapacity (int *caps);
	void   SetAssign (int *assign);

private:

	int  aNumAgts;
	int  aNumTasks;
	int  aMaxProfit;
	int  aVisitedNodes;
	int  **apCosts;
	int  **apProfits;
	int  *apCapacity;
	int  *apAssign;

	int    ReadInput ();
	bool   IsASolution (int *assignment);
};

#endif