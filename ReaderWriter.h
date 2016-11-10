#ifndef READERWRITER_H
#define READERWRITER_H

#include <string>

/************************************************************
*															*
* 	Conjunto de funções para leitura e escrita de matrizes.	*
*															*
*	Os arquivos devem seguir o formato abaixo				*
*															*
*	LINHA COLUNA 											*
*	MATRIZ DE CUSTOS 										*
*	MATRIZ DE RECURSOS 										*
*	LISTA DE CAPACIDADES									*
*															*
*	Por exemplo, 											*
*	2 3 													*
*	1 2 3 													*
*	4 5 6													*
*	1 2 3													*
*	6 7 8													*
*	10 15													*
*															*
************************************************************/


/*
	Imprime a matriz '**matriz', de ordem 'linha'X'coluna'
*/
template<typename T>
extern void printMat(T **matriz, int linha, int coluna);

/*
	Lê a matriz de custos do arquivo e armazena o tamanho,
	do problema em 'linha' e 'coluna'.
*/
template<typename T> 
extern T** readCost(const char *fileName, int &linha, int &coluna);

/*
	Lê a matriz de recursos do arquivo e armazena o tamanh
	o, do problema em 'linha' e 'coluna'.
*/
template<typename T> 
extern T** readResource(const char *fileName, int &linha, int &coluna);

/*
	Lê a lista de capacidades do arquivo e armazena o taman
	ho, do problema em 'linha' e 'coluna'.
*/
template<typename T>
extern T* readAgentsCap(const char *fileName, int &linha, int &coluna);


#endif