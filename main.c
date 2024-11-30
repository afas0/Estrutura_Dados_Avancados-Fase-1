/*****************************************************************//**
 * @file   main.c
 * @brief   Função principal do programa
 *
 * @author Andre
 * @date   March 2024
 *********************************************************************/

#include "header.h"
#include <stdio.h>
#include <string.h>
/**
 * @brief Função principal do programa
 *
 * Responsável por ler uma matriz a partir de um arquivo, realizar operações nessa matriz e calcular a maior soma máxima possível.
 *
 * @return Retorna 0 se o programa for executado com sucesso
 */
int main() {

    
    char* nomeFicheiro = "dados.txt";
    Matriz* matriz = lerFicheiro(nomeFicheiro);

    if (matriz->inicio == NULL) {
        printf("Erro ao ler a matriz do arquivo.\n");
        return 1;
    }
    printf("Matriz original:\n\n");
    imprimirMatriz(matriz);

    int* endereco = encontrarEnderecoPorCoordenadas(matriz, 1, 2);
    if (endereco != NULL) {
        AlterarElemento(matriz, endereco, 32);
    }
        
    printf("\nAlterar elemento da linha1/coluna2 por 32 :\n\n");
    imprimirMatriz(matriz);
    printf("\nAdicionar nova linha:\n\n");
    adicionarNovaLinha(matriz);
    imprimirMatriz(matriz);
    printf("\nAdicionar nova coluna:\n\n");
    adicionarNovaColuna(matriz);
    imprimirMatriz(matriz);
    printf("\nRemover linha n3:\n\n");
    removerLinha(matriz, 3);
    imprimirMatriz(matriz);
    printf("\nRemover Coluna n2:\n\n");
    removerColuna(matriz, 2);
    imprimirMatriz(matriz);
    
    //Libertar memória alocada para a matriz:
    freeMatriz(matriz);
    matriz = lerFicheiro(nomeFicheiro);
    if (matriz->inicio == NULL) {
        printf("Erro ao ler a matriz do arquivo.\n");
        return 1;
    }
    printf("\nMatriz original:\n\n");
    imprimirMatriz(matriz);
    int repeticoes = matriz->numColunas * matriz->numLinhas;
    int* somaResultado;
    somaResultado = malloc(repeticoes * sizeof(int));
    bool verificacao = false;
    int numero = 4;
    int* posicaoNum;
    posicaoNum = malloc(repeticoes * sizeof(int));
    //int* valorLista;
    //valorLista = malloc((repeticoes*matriz->numLinhas) * sizeof(int));

    for (int i = 0; i < repeticoes; i++) {
        int contador = i;
        int soma = 0;
        int valorMaiorPosicao;
        int valorMaior;
        int linha = 1;
        int* next = encontrarMaiorElemento(matriz);
        
        freeMatriz(matriz);
        matriz = lerFicheiro(nomeFicheiro);
        //imprimirMatriz(matriz);

        for (int i = 0; i < numero; i++) {

            if (i == 0 && verificacao) {
                soma = next[0] + soma;
                somaMatriz(matriz, next[1]);
                valorMaiorPosicao = next[1];
                valorMaior = next[0];
                int* posicao = encontrarMaiorElemento(matriz);
                soma = posicao[0] + soma;
                somaMatriz(matriz, posicao[1]);
                


            }
            
            else {
                int* posicao = encontrarMaiorElemento(matriz);
                soma = posicao[0] + soma;
                //printf("O maior elemento na matriz é: %d\n", posicao[0]);
                //printf("A posição do maior elemento na matriz é: %d\n", posicao[1]);
                somaMatriz(matriz, posicao[1]);
                if (i == 0) {
                    valorMaiorPosicao = posicao[1];
                    valorMaior = posicao[0];
                }
            }
            
        }
        posicaoNum[contador] = valorMaiorPosicao;
        //imprimirMatriz(matriz);
        int* ultimo = encontrarMaiorElemento(matriz);
        freeMatriz(matriz);
        matriz = lerFicheiro(nomeFicheiro);
        somaResultado[i] = ultimo[0] + soma;
        for (int i = 0; i <= contador; i++) {
            //printf("somaResultado%d\n", somaResultado[i]);
            //printf("n linhas:%d", matriz->numLinhas);
            //printf("n colunas:%d", matriz->numColunas);
            for (int i = matriz->numLinhas; i <= posicaoNum[i]; i += matriz->numLinhas) {
                linha++;
            }
            int coluna = (posicaoNum[i] - ((linha - 1) * matriz->numColunas)) + 1;
            //printf("\n\nValor linha:%d\n", linha);
            //printf("Valor coluna:%d\n\n", coluna);
            int* endereco = encontrarEnderecoPorCoordenadas(matriz, linha, coluna);
            if (endereco != NULL) {
                AlterarElemento(matriz, endereco, 0);
            }
        }
        verificacao = true;
        numero = 3;
        //imprimirMatriz(matriz);
    }
    int maiorSoma = 0;
    printf("\nLista:\n");
    for (int i = 0; i < repeticoes; i++) {
        printf("Soma maxima possivel[%d] = %d\n", i, somaResultado[i]);
        if (somaResultado[i] > maiorSoma) {
            maiorSoma = somaResultado[i]; 
        }
    }
    printf("\nResultado: ");
    printf("Maior soma maxima possivel = %d\n", maiorSoma);
    

    return 0;
}
