#ifndef GAP_H
#define GAP_H

#include <vector>
#include <random>

using std::vector;

class Gap{

public:

	Gap ();
	~Gap ();
	/*
	 * Método para inicialização da leitura dos dados e criação segura de obje
	 * tos.
	 *
	 * INPUT: 
	 * OUTPUT:
	 */
	int           Open();
	/*
	 * Meta heurística de GRASP reativo para resolução do Problema de Alocação
	 * Generalizada. Composto por duas etapas: construção e otimização. A fase
	 * de construção é feita pelo método GreedyRandomizedConstruction enquanto
	 * a otimização é feita pelo LocalSearch. O método consiste em criar vária
	 * s soluções iniciais de maneira gulosa, aleatória e adaptativa e otimizá
	 * -las usando uma busca local e ao final tomar a melhor como ótima.
	 *
	 * INPUT: int maxIteration - número máximo de iterações ou soluções gerada
	 *        s.
	 *        float alpha - Valor inicial para restrição de seleção para a LRC.
	 * OUTPUT: int* - Um vetor contendo a melhor solução encontrada dentre tod
	 *         as as iterações.
	 */
	int*          ReactiveGrasp (int maxIteration, float alpha);

	/*
	 * Constrói uma solução inicial para uma instância do Problema de Alocação
	 * Generalizada. Cria uma lista de candidatos com todos os agentes que pod
	 * em ser alocados à uma dada tarefa sem exceder sua capacidade. Seleciona
	 * dessa lista um grupo restrito por uma faixa determinada pelo parâmetro 
	 * alpha e adiciona aleatoriamente um agente do grupo restrito a solução. 
	 * Caso a lista de candidatos se esvazie e a solução não seja completa, a 
	 * característica aleatória da construção é enfatizada. Caso contrário, de
	 * três em três inserções a característica gulosa é enfatizada.
	 *
	 * INPUT: float alpha - Valor inicial para restrição de seleção para a LRC. 
	 * OUTPUT:
	 */
	void          GreedyRandomizedConstruction (float alpha);

	/*
     * Otimiza a solução inicial contruída pela fase anterior. Busca pelos pos
     * síveis agentes que podem ser trocados em cada tarefa. Dessa forma crian
     * do uma vizinhança e selecionando a melhor dentre a vizinhança inteira.
	 *
	 * INPUT: 
	 * OUTPUT:
	 */
	void          LocalSearch ();

	/*
	 * Identifica quais tarefas possuem mais de uma possibilidade de alocação 
	 * e cria uma permutação ao trocar a alocação dessa tarefa. Ao final, reto
	 * rna um vetor contendo todas as permutações possíveis para uma tarefa.
	 *
	 * INPUT: 
	 * OUTPUT:
	 */
	vector<int*>  Neighbor (int task);
	/*
	 * Imprime na tela a alocação de tarefas atual do objeto.
	 *
	 * INPUT: 
	 * OUTPUT:
	 */
	void          ShowAssign ();

	/*
     * Percorre o vetor de alocações do objeto e calcula a quantidade total de
     * lucro obtido por essa permutação.
	 *
	 * INPUT: 
	 * OUTPUT:
	 */
	int           TotalProfit ();

	/*
     * Dado um vetor com tamanho igual ao número de tarefas da intância do Pro
     * blema de Alocação Generalizada passada ao objeto. Os valores dos lucros
     * de cada alocação são obtidos da matriz de lucros lida pela instância ao
     * executar o método Open().
	 *
	 * INPUT: 
	 * OUTPUT:
	 */
	int           TotalProfit (int *assignment);

	int    GetNumAgts ();
	int    GetNumTasks ();
	int    GetMaxProfit ();

	/*
     * Cria uma cópia do vetor de alocações atual da instância.
	 *
	 * INPUT: 
	 * OUTPUT: int* - A cópia contruída.
	 */
	int*   GetAssign ();

	/*
     * Cria uma cópia do vetor que contém as capacidades dos agentes.
	 *
	 * INPUT: 
	 * OUTPUT: int* - A cópia contruída. 
	 */
	int*   GetCapacities ();

	/*
	 * Cria uma cópia da matriz que contém os valores dos custos de alocar 
	 * um agente à uma tarefa. 
	 *
	 * INPUT: 
	 * OUTPUT: int** - A cópia contruída.
	 */
	int**  GetCosts ();

	/*
	 * Cria uma cópia da matriz que contém os valores dos lucros de alocar 
	 * um agente à uma tarefa. 
	 *
	 * INPUT: 
	 * OUTPUT: int** - A cópia contruída.
	 */
	int**  GetProfits ();

private:

    
	int  aNumAgts;           // Quantidade de agentes da instância
	int  aNumTasks;          // Quantidade de tarefas da instância
	int  aMaxProfit;         // Maior lucro encontrado para uma permutação
	int  **apCosts;          // Matriz de custos de alocação
	int  **apProfits;        // Matriz de lucros de alocação
	int  *apCapacity;        // Vetor com as capacidades de cada agente
	int  *apAssign;          // Vetor com a alocação de tarefas atual
	std::mt19937 aRandGen;   // Gerador de números aleatórios

    /*
     * Lê uma string do teclado que representa o caminho para um arquivo. Tent
     * ler o arquivo que deverá conter a quantidade de agentes, quantidade de
     * tarefas, matrizes de custo e lucro e vetor com as capacidades de cada a
     * gente. O padrão do arquivo deve seguir o mesmo usado pelos arquivos da 
     * OR Library, com exceção da separação das instâncias, ou seja, um arquiv
     * o por instância e não cinco em um mesmo arquivo.
	 *
	 * INPUT: 
	 * OUTPUT: int - Valor que representa a ocorrência ou não de erro na leitu
	           ra do arquivo. Sendo 1 para erro e 0 caso contrário.
     */
	int           ReadInput ();

	/*
     * Verifica se um vetor, com tamanho igual ao número de tarefas da instânc
     * ia, é uma soluão completa e factível. Nesse caso, todas as tarefas deve
     * m estar alocadas e nenhum agente deve exceder a sua capacidade. 
	 *
	 * INPUT:  int *assignment - Vetor representando uma alocação para a instâ
	 *         ncia.
	 * OUTPUT: bool - Verdadeiro caso a alocação seja uma solução, falso caso 
	 *         contrário.
	 */
	bool          IsASolution (int *assignment);

	/*
	 * Dado uma tarefa, esse método busca por todos os agentes que podem ser a
	 * locados à ela sem torná-la infactível e os armazena em um vetor o qual 
	 * é retornado como resultado.
	 *
	 * INPUT:  int task - Um número entre 0 e a quantidade de tarefas da instâ
	 *         ncia.
	 * OUTPUT: vector<int> - Contendo todos os outros agentes que podem ser al
	 *         ocados à tarefa.
	 */
	vector<int>   FindCandidates (int task);

	/*
	 * Retorna a capacidade de um agente.
	 *
	 * INPUT:  int agnt - Um número entre 0 e a quantidade de agentes da instâ
	 *         ncia.
	 * OUTPUT: int - Capacidade total de um agente.
	 */
	int           AgentCapacity (int agnt);

	/*
     * Verifica se é possível alocar um agente à uma tarefa com base na alocaç
     * ão atual.
	 *
	 * INPUT:  int agnt - Um número entre 0 e a quantidade de agentes da instâ
	 *         ncia.
	 *         int task - Um número entre 0 e a quantidade de tarefas da instâ
	 *         ncia.
	 * OUTPUT: bool - Verdadeiro caso seja possível alocar o agente à tarefa e
	 *         falso caso contrário.
	 */
	bool          Allocate (int agnt, int task);

	/*
	 * Retorna a quantidade atual consumida da capacidade de um agente com bas
	 * e na alocação atual.
	 *
	 * INPUT:  int agnt - Um número entre 0 e a quantidade de agentes da instâ
	 *         ncia
	 * OUTPUT: int - QUantidade total consumida da capacidade de um agente.
	 */
	int           CntCapacity (int agt);

	/*
	 * Atribui -1 a todas as tarefas do vetor de alocações da instância, o que
	 * significa que nenhuma tarefa possui um agente designado para ela.
	 *
	 * INPUT: 
	 * OUTPUT:
	 */
	void          ResetAssignments ();
};

#endif