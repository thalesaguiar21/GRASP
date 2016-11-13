#ifndef GAP_H
#define GAP_H

#include <vector>

using std::vector;

class Gap{

public:

	Gap ();
	~Gap ();
	int           Open();
	int           Grasp (int maxIteration, int seed);
	int*          GreedyRandomizedConstruction (float alpha, int seed);	
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

	int           ReadInput ();
	bool          IsASolution (int *assignment);
	vector<int>   FindCandidates (int task);
	int           AgentCapacity (int agnt);
	bool          Allocate (int agnt, int task);
	int           CntCapacity (int agt);
	void          ResetAssignments ();
};

#endif