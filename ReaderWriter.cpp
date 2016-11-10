#include "ReaderWriter.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;

template<typename T> void printMat(T **matriz, int linha, int coluna){

	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			cout << matriz[i][j] << std::setw(3);
		}
		cout << "\n";
	}
	cout << "\n";
}
template void printMat<int>(int **matriz, int linha, int coluna);
template void printMat<double>(double **matriz, int linha, int coluna);

	
template<typename T> T** readCost(const char *fileName, int &linha, int &coluna){

	T **matriz;
	ifstream myFile(fileName);

	if(!myFile){
		return NULL;
	}

	myFile >> linha; 
	myFile >> coluna;

	matriz = new T*[linha];
	for(int i=0; i<linha; i++){
		matriz[i] = new T[coluna];
		for(int j=0; j<coluna; j++){
			myFile >> matriz[i][j];
		}
	}

	myFile.close();

	return matriz;
}
template int** readCost<int>(const char *fileName, int &linha, int &coluna);
template double** readCost<double>(const char *fileName, int &linha, int &coluna);


template<typename T> T** readResource(const char *fileName, int &linha, int &coluna){
	
	T **matriz;
	T dummy;

	ifstream myFile(fileName);

	if(!myFile){
		return NULL;
	}

	myFile >> linha; 
	myFile >> coluna;

	//Jump the first matrix
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			myFile >> dummy;
		}
	}

	matriz = new T*[linha];
	for(int i=0; i<linha; i++){
		matriz[i] = new T[coluna];
		for(int j=0; j<coluna; j++){
			myFile >> matriz[i][j];
		}
	}

	myFile.close();

	return matriz;
}
template int** readResource<int>(const char *fileName, int &linha, int &coluna);
template double** readResource<double>(const char *fileName, int &linha, int &coluna);


template<typename T> T* readAgentsCap(const char *fileName, int &linha, int &coluna){
	
	T *array;
	T dummy;

	ifstream myFile(fileName);

	if(!myFile){
		return NULL;
	}

	myFile >> linha; 
	myFile >> coluna;

	//Jump the first matrix
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			myFile >> dummy;
		}
	}

	//Jump the second matrix
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			myFile >> dummy;
		}
	}

	array = new T[linha];
	for(int i=0; i<linha; i++){
		myFile >>array[i];
	}

	myFile.close();

	return array;
}
template int* readAgentsCap<int>(const char *fileName, int &linha, int &coluna);
template double* readAgentsCap<double>(const char *fileName, int &linha, int &coluna);