#ifndef GEN_ASSIGN_H
#define GEN_ASSIGN_H

/********************************************************************************
*																				*
*	Classe criada para representar o Problema de Alocação Generalizada(GAP).	*
*	Proposto como trabalho para obtenção de nota parcial na disciplina de 		*
*	Algoritmos Avançados(DIM0406).												*
*																				*
*	Esse problema consiste em dados um conjunto de agentes que possuem uma c 	*
*	apacidade máxima, um conjunto de tarefas, um conjunto de custos de aloca 	*
*	ção e a quantidade de recursos consumidos fazer uma alocação tal que cad 	*
*	a tarefa seja designada a exatamente um agente de forma que a soma dos c 	*
*	ustos de alocação não exceda a capacidade máxima de cada agente e que o  	*
*	recurso total gasto seja máximo. 											*
*																				*
*	Instruções para execuçãopodem ser encontradas no README.md 					*
*																				*
*																				*
*	AUTHOR:	Thales Aguiar de Lima												*
*	DATE:	05 of October 2016													*
*																				*
*********************************************************************************/

#include <queue>

class GenAssign
{
private:

	int nAgts;			/* Número de agentes da instância */
	int nTasks;			/* Número de tarefas da instância */
	int maxProfit;		/* Candidato de solução para  a instância */
	int visitedNodes;	/* Quantidade de nós visitados */
	int **costs;		/* Custo de alocar o agente i à tarefa j, com
						   0<=i<= nAgts e 0<=j<= nTasks */
	int **profits;		/* Recurso consumido ao alocar o agente i à t
						   arefa j, com 0<=i<= nAgts e 0<=j<= nTasks */
	int *capacity;		/* Capacidade dos agentes */
	int *assign;		/* Alocações realizadas */
	int *colMaximum;	/* Somatórios dos maiores valores de '**profits'
						   a partir da coluna j, 0<=j<= nTasks  */

	/*
		Função privada chamada pela função pública 'solve()'.
		Executa o Branch and Bound para resolver a instância
		lida atualmente.

		INPUT: 	Tarefa para iniciar a busca, inicializada por 
				padrão com '0' pela função 'solve()'.
	*/
	void solve(int task);

	/*
		Verifica se o agente 'agt' é promissor para a tarefa
		'task'. Seu objetivo é eliminar a visita à nós irrel
		evantes, como nós que excedem a capacidade, ou nós q
		ue ao somar os recursos até aquele momento com os ma
		ores recursos possíveis futuramente(colMaximum['task+1'])
		não apresentar uma possíve solução melhor que a já e
		ncontrada.

		INPUT: 	Agente 'agt', com 0<=agt<=nAgts e uma tarefa
				'task' com 0<=task<=nTasks.
		OUTPUT:	true se 'agt' é promissor, e false caso cont
				rário.
	*/
	bool promising(int agt, int task);

	/*
		Calcula a soma dos custos atuais para um dado agente
		'agt', baseado na alocação atual '*assign'.

		INPUT:	Um agente 'agt', com 0<=agt<=nAgts.
		OUTPUT:	Um inteiro representando o custo total do ag
				ente.
	*/
	int actualCap(int agt);

	/*
		Calcula o lucro, ou recursos consumido, até o momento
		Para isso, usa o vetor '*assign' e a matriz '**profit
		s'.

		INPUT:	None
		OUTPUT:	Total de recursos consumidos com a alocação a
				tual.
	*/
	int totalProfit();

	/*
		Soma os maiores valores por coluna de '**profits' a p
		artir de uma coluna 'strtTask'.

		INPUT:	Coluna inicial.
		OUTPUT:	Soma dos maiores valores por coluna a partir 
				de 'strttask'.
	*/
	int colLimit(int strtTask);

	/*
        Lê os dados contido no arquivo denome "fileName" e inic
        ializa os atributos do problema.

        INPUT:   Nome do arquivo que contém a instância.
        OUTPUT:  None

	*/
	void readInstance(const char *fileName);

	/*
        Calcula uma solução inicial para a instância dada.
        Adiciona os agentes que possuem o melhor custo-benefício
        para uma determinada tarefa.

        INPUT:   None
        OUTPUT:  "Profit" calculado.

	*/
	int initialSolution();

public:

	/*
		Cria um novo objeto GenAssign. Inicializa a instância c
		om a leitura do arquivo descrito em 'ReaderWriter.cpp'.
		Nenhum erro será lançado caso não seja possível ler o a
		rquivo, entretanto será lançado um erro de segmentação 
		ao tentar resolver o problema com o método 'solve()'.
		
		INPUT:	Nome do arquivo com instância do problema.
		OUTPUT:	Uma nova instância de GenAssign.
	*/
	GenAssign(const char *fileName);

	/*
		Destrutor da classe GenAssign, responsável por fazer a
		desalocação de memória.

		INPUT:	None
		OUTPUT:	None
	*/
	~GenAssign();

	int** getCosts();
	int** getProfits();
	int* getCapacity();
	int getNumAgts();
	int getNumTasks();
	int getMaxProfit();
	int getNumVisitedNodes();
	void solve();

	/*
		Exibe a alocação atual dos agentes/tarefas
	*/
	void showAssign();

};

#endif