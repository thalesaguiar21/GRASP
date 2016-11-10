#ifndef GAP_H
#define GAP_H


class Gap{

public:

	Gap ();
	~Gap ();
	int    Open();
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
	void   SetNumTasks (int numAgts);
	void   SetCosts (int **costs);
	void   SetProfits (int **profits);
	void   SetCapacity (int *caps);

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
	int    CntCapacity (int agt);
};

#endif