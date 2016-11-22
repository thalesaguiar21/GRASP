#ifndef GAP_H
#define GAP_H

#include <vector>
#include <random>

using std::vector;

class Gap{

public:

	Gap ();
	~Gap ();
	int           Open();
	int*          Grasp (int maxIteration, float alpha);
	int*          GreedyRandomizedConstruction (float alpha);	
	void          LocalSearch ();
	vector<int*>  Neighbor (int task);
	void          ShowAssign ();
	int           TotalProfit ();
	int           TotalProfit (int *assignment);

	int    GetNumAgts ();
	int    GetNumTasks ();
	int    GetMaxProfit ();
	int    GetVisitedNodes ();
	int*   GetAssign ();
	int*   GetCapacities ();
	int**  GetCosts ();
	int**  GetProfits ();

private:

	int  aNumAgts;
	int  aNumTasks;
	int  aMaxProfit;
	int  aVisitedNodes;
	int  **apCosts;
	int  **apProfits;
	int  *apCapacity;
	int  *apAssign;
	std::mt19937 aRandGen;

	int           ReadInput ();
	bool          IsASolution (int *assignment);
	vector<int>   FindCandidates (int task);
	int           AgentCapacity (int agnt);
	bool          Allocate (int agnt, int task);
	int           CntCapacity (int agt);
	void          ResetAssignments ();
};

#endif