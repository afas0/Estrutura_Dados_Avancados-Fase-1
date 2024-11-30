/*****************************************************************//**
 * @file   source.c
 * @brief  Implementação de funções que manipulam uma Matriz
 *
 * @author Andre
 * @date   March 2024
 *********************************************************************/
#include "header.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#pragma warning (disable:4996)


 /**
   * @brief Cria um novo elemento da matriz
   *
   * @param valor Valor do novo elemento
   * @return Ponteiro para o novo elemento
   */

Elemento* CriarElemento(int valor) {
	Elemento* aux = (Elemento*)malloc(sizeof(Elemento));
	if (aux == NULL) return NULL;
	aux->valor = valor;
	aux->prox;
	return aux;
}

/**
 * @brief Lê os dados de um ficheiro de texto e cria uma matriz a partir deles
 *
 * @param ficheiroTxt Nome do ficheiro de texto
 * @return Ponteiro para o início da matriz
 */

Matriz* lerFicheiro(char* ficheiroTxt) {
	Matriz* novaMatriz = (Matriz*)malloc(sizeof(Matriz));
	novaMatriz->inicio = NULL;
	novaMatriz->numLinhas = 1; ///< Em baixo no \n avanca 1 linha
	novaMatriz->numColunas = 0;

	FILE* ficheiro = fopen(ficheiroTxt, "r");
	if (ficheiro == NULL) {
		printf("Erro ao ler ficheiro");
		return novaMatriz;
	}

	Elemento* ultimoElemento = NULL;
	int numColunas = 0;
	int valor;
	char delimitador;

	while (fscanf(ficheiro, "%d%c", &valor, &delimitador) > 0) {
		Elemento* novoElemento = CriarElemento(valor);

		if (novaMatriz->inicio == NULL) {
			novaMatriz->inicio = novoElemento;
		}
		else {
			ultimoElemento->prox = novoElemento;
		}

		ultimoElemento = novoElemento;
		numColunas++;

		if (delimitador == '\n') {
			novaMatriz->numLinhas++;
			if (novaMatriz->numColunas == 0) {
				novaMatriz->numColunas = numColunas;
			}
			//else if (numColunas != novaMatriz->numColunas)					
			numColunas = 0;
		}
	}
	if (ultimoElemento != NULL) {
		ultimoElemento->prox = NULL;
	}

	fclose(ficheiro);
	return novaMatriz;
}

/**
 * @brief Imprime os dados da matriz
 *
 * @param matriz Ponteiro para a matriz a ser impressa
 */

void imprimirMatriz(Matriz* matriz) {
	Elemento* atual = matriz->inicio;
	int linhaAtual = 1;
	int colunaAtual = 0;
	int valorMax = matriz->numColunas  * matriz->numLinhas;
	//printf("Numero de Linhas: %d\n", matriz->numLinhas);
	//printf("Numero de Colunas: %d\n\n", matriz->numColunas);	
	int contador=0;
	while (atual != NULL && contador < valorMax) {
		if (atual != NULL) { 
			printf("%d ", atual->valor);
		}

		colunaAtual++;
		if (colunaAtual == matriz->numColunas) {
			printf("\n"); ///<  Nova linha depois de imprimir uma linha completa
			//linhaAtual++;
			colunaAtual = 0;
		}

		atual = atual->prox;
		contador++;
	}

}
/**
 * @brief Altera o valor de um elemento da matriz
 *
 * @param inicio Ponteiro para o início da matriz
 * @param enderecoAntigo Ponteiro para o endereço do valor do elemento a ser alterado
 * @param novoValor Novo valor a ser atribuído ao elemento
 * @return Ponteiro para o início da matriz
 */

Matriz* AlterarElemento(Matriz* inicio, int* enderecoAntigo, int novoValor) {
	if (inicio == NULL) {
		return inicio;
	}
		
	Elemento* aux = inicio->inicio; 
	while (aux != NULL && &(aux->valor) != enderecoAntigo) {
		aux = aux->prox;
	}

	
	if (aux != NULL && &(aux->valor) == enderecoAntigo) {  ///< Se o elemento com o endereço de memória fornecido for encontrado, altera o valor
		aux->valor = novoValor;
	}

	return inicio;
}

/**
 * @brief Encontra o endereço de memória de um elemento da matriz com base em suas coordenadas
 *
 * @param matriz Ponteiro para a matriz
 * @param linha Linha do elemento desejado
 * @param coluna Coluna do elemento desejado
 * @return Ponteiro para o endereço de memória do valor do elemento, ou NULL se não encontrado
 */


int* encontrarEnderecoPorCoordenadas(Matriz* matriz, int linha, int coluna) {

	
	int posicao = ((matriz->numColunas * (linha - 1)) + coluna) - 1; ///< Calcula a posição do elemento na lista ligada com base nas coordenadas

	Elemento* atual = matriz->inicio;  ///< Percorre a lista ligada até a posição do elemento desejado
	for (int i = 0; i < posicao && atual != NULL; i++) {
		atual = atual->prox;
	}

	if (atual != NULL) {
		
		return &(atual->valor); ///< Retorna o endereço de memória do valor do elemento encontrado
	}
	else {
		
		return NULL;
	}
}

/**
 * @brief Adiciona uma nova linha à matriz
 *
 * @param matriz Ponteiro para a matriz
 */

void adicionarNovaLinha(Matriz* matriz) {
	
	int numNovosElementos = matriz->numColunas;  ///<  Cria uma nova linha dependendo do tamanho da numColunas

	Elemento* atual = matriz->inicio;
	while (atual->prox != NULL) {
		atual = atual->prox; ///<  Vai para o último elemento da matriz
	}

	
	for (int i = 0; i < numNovosElementos; i++) {  ///< Adiciona novos elementos no final da matriz
		atual->prox = CriarElemento(0); ///< Cria um novo elemento com valor 0
		atual = atual->prox;
	}

	matriz->numLinhas++; 
}

/**
 * @brief Adiciona uma nova coluna à matriz
 *
 * @param matriz Ponteiro para a matriz
 */
void adicionarNovaColuna(Matriz* matriz) {
	Elemento* atual = matriz->inicio;
	int contador = 1; ///< Contador para acompanhar a posição atual
	int tamanhoColunas = matriz->numColunas;
	int valorMax = matriz->numColunas * (matriz->numLinhas);

	while (atual != NULL && contador <= valorMax) {
		
		if (contador % tamanhoColunas == 0) {
			Elemento* novoElemento = CriarElemento(0); ///< Cria um novo elemento com valor '0'
			novoElemento->prox = atual->prox;
			atual->prox = novoElemento;

			atual = novoElemento->prox; ///< Avança para o próximo elemento após o novo elemento adicionado
		}
		else {
			atual = atual->prox;  ///<Avança para o próximo elemento
		}
		contador++;
	}

	matriz->numColunas++; 
}

/**
 * @brief Remove uma linha específica da matriz
 *
 * @param matriz Ponteiro para a matriz
 * @param linha Número da linha a ser removida
 */
void removerLinha(Matriz* matriz, int linha) {
	
	Elemento* anterior = NULL;
	Elemento* atual = matriz->inicio;
	int posicaoAtual = 0;
	int posicaoIni = matriz->numColunas * (linha-1);
	int posicaoFim = posicaoIni + matriz->numColunas -1;
	bool ultimaLinha = true;
	if (linha == matriz->numColunas) {
		ultimaLinha = false;
	}
	
	while (atual != NULL && posicaoAtual < posicaoIni) {  ///< Encontra a linha a ser removida
		anterior = atual;
		atual = atual->prox;
		posicaoAtual++;
	}

	while (atual != NULL && posicaoAtual < posicaoFim) {
		Elemento* temp = atual;
		atual = atual->prox;
		free(temp); ///< Liberta a memória do elemento removido
		posicaoAtual++;
	}

	
	if (anterior != NULL) {
		anterior->prox = atual->prox;   ///< Remove os elementos da linha
	}
	else {
		matriz->inicio = atual->prox;
	}

	matriz->numLinhas--; 
}

/**
 * @brief Remove uma coluna da matriz
 *
 * @param matriz Ponteiro para a matriz da qual remover a coluna
 * @param coluna Índice da coluna a ser removida
 */
void removerColuna(Matriz* matriz, int coluna) {

	bool loop=false;	
	int posicao = coluna - 1;
	Elemento* anterior = NULL;
	Elemento* atual = matriz->inicio;
	int valorMax = (matriz->numColunas -1 ) * matriz->numLinhas;
	int contador = 0;


	while (atual != NULL && contador < valorMax) {
		
		if (posicao == 0) {
			if (!loop) {
				Elemento* temp = atual;
				matriz->inicio = atual->prox;
				free(temp);
				atual = matriz->inicio;
				contador++;
				loop = true;
			}
			else {
				Elemento* temp = atual;
				anterior->prox = atual->prox;
				free(temp);
				atual = anterior->prox;
			}
		}
		else {
			if (loop) {
				posicao = 1;
			}
			for (int i = 0; i < posicao; i++) {
				anterior = atual;
				atual = atual->prox;
				contador++;
				loop = true;
			}

			Elemento* temp = atual;
			if (anterior != NULL) {
				anterior->prox = atual->prox;
			}

			else {
				matriz->inicio = atual->prox;
			}
			free(temp); ///< Liberta a memória do elemento removido
			atual = anterior;
		}
		
		
		
		for (int i = 0; i < matriz->numColunas - 1; i++) {   ///< Avança para o próximo elemento na mesma coluna
			anterior = atual;
			atual = atual->prox;
			contador++;
		}
	}

	matriz->numColunas--; 
}


/**
 * @brief Encontra o maior elemento na matriz
 *
 * @param matriz Ponteiro para a matriz na qual encontrar o maior elemento
 * @return Array com dois elementos: o maior valor encontrado e a sua posição na matriz
 */

int encontrarMaiorElemento(Matriz* matriz) {

	int valorMax = matriz->numColunas  * matriz->numLinhas;
	Elemento* atual = matriz->inicio;
	int maior = atual->valor;
	int posicao = 0;
	int posicaoMax = 0;
	static int resultado[2];

	while (atual != NULL && posicao < valorMax) {
		if (atual->valor > maior) {
			maior = atual->valor;
			posicaoMax = posicao;
		}

		atual = atual->prox;
		posicao++;
	}
	resultado[0] = maior;
	resultado[1] = posicaoMax;
	return resultado;
}

/**
 * @brief Soma os elementos da matriz até uma determinada posição e remove a linha e a coluna do maior elemento
 *
 * @param matriz Ponteiro para a matriz na qual realizar a soma e remover os elementos
 * @param posicao Posição até à qual realizar a soma e remover os elementos
 */
void somaMatriz(Matriz* matriz, int posicao) {

	int linha = matriz->numLinhas;
	int coluna = matriz->numColunas;
	int contador = 1; // vai ser sempre +1 

	for (int i = linha; i <= posicao; i+= linha) {
		contador++;
	}
	coluna = (posicao - ((contador-1) * coluna))+1;
	//printf("\n\nValor linha:%d\n", contador);
	//printf("Valor coluna:%d\n\n", coluna);

	removerLinha(matriz,contador);
	//printf("\nREMOVER LINHA:\n");
	//imprimirMatriz(matriz);
	removerColuna(matriz,coluna);
	//printf("\nREMOVER Coluna:\n");
	//printf("\nMatriz Alterada:\n\n");
	//imprimirMatriz(matriz);
	

}
/**
 * @brief Liberta a memória alocada para a matriz
 *
 * @param matriz Ponteiro para a matriz a ser libertada
 */
void freeMatriz(Matriz* matriz) {
	if (matriz == NULL) {
		return; 
	}
	int contador = 0;
	int maxValor = matriz->numColunas * matriz->numLinhas;
	Elemento* atual = matriz->inicio;
	while (atual != NULL&& contador < maxValor) {
		Elemento* temp = atual; ///< Guarda o ponteiro atual
		atual = atual->prox; ///< Move para o próximo elemento
		free(temp); ///< Liberta a memória do elemento temp
		contador++;
	}

	free(matriz); ///< Liberta a memória da estrutura da matriz
}