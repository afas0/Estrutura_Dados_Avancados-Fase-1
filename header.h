#pragma once
/*****************************************************************//**
 * @file   header.h
 * @brief Declara��es das fun��es e estruturas
 *
 * @author Andre
 * @date   March 2024
 *********************************************************************/
#include <stdbool.h>

 /**
   * @brief Estrutura para representar um elemento da matriz
   */

typedef struct Elemento {
	int valor; ///< Valor do elemento
	struct Elemento* prox; ///< Ponteiro para o pr�ximo elemento na matriz
}Elemento;

/**
  * @brief Estrutura para representar uma matriz
  */

typedef struct Matriz {
	Elemento* inicio; ///< Ponteiro para o in�cio da matriz
	int numLinhas;  ///< N�mero de linhas na matriz
	int numColunas;  ///< N�mero de colunas na matriz
}Matriz;

#pragma region 

Matriz* lerFicheiro(char* ficheiroTxt);

void imprimirMatriz(Matriz* matriz);

Elemento* CriarElemento(int valor);

//Elemento* AlterarElemento(Elemento* ini, int* enderecoAntigo, int novoValor, bool* res);
Matriz* AlterarElemento(Matriz* inicio, int* enderecoAntigo, int novoValor);

//int* encontrarEnderecoPorCoordenadas(Elemento* inicio, int numLinhas, int numColunas, int linha, int coluna);
int* encontrarEnderecoPorCoordenadas(Matriz* matriz, int linha, int coluna);

//Elemento* RemoveElementosDaLinha(Elemento* inicio, int numColunas, int linhaRemover, bool* res);
void adicionarNovaLinha(Matriz* matriz);

void adicionarNovaColuna(Matriz* matriz);

void removerLinha(Matriz* matriz, int linha);

void removerColuna(Matriz* matriz, int coluna);

int encontrarMaiorElemento(Matriz* matriz);

void somaMatriz(Matriz* matriz, int posicao);

void freeMatriz(Matriz* matriz);

#pragma endregion