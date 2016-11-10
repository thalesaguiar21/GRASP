#ifndef GAP_H
#define GAP_H


class Gap{

public:

	Gap ();
	~Gap ();
	int    Open();
	bool   Allocate (int agnt, int task);
	int    CntCapacity (int agt);
	int    AssignCost (int agnt, int task);
	int    Grasp (int maxIteration, int seed);
	int*   GreedyRandomizedConstruction (int seed);
	int*   LocalSearch (int *assignment);
	void   UpdateSolution (int localSolution, int bestSolution);
	int    AgentCapacity (int agnt);
	void   ShowAssign ();

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
	int    TotalProfit ();
};

#endif