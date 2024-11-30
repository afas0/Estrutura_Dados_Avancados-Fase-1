# Manipulação de Matrizes em C

## Descrição

Este projeto implementa um conjunto de funções em C para manipulação de matrizes utilizando uma estrutura de dados ligada. O foco principal é proporcionar operações básicas e eficientes para leitura, alteração e manipulação de elementos em matrizes.

## Funcionalidades

- Leitura de dados de matriz a partir de um ficheiro de texto
- Impressão da matriz
- Alteração de elementos individuais
- Localização de elementos por coordenadas
- Adição e remoção de linhas/colunas

## Estrutura do Projeto

O projeto é composto por três arquivos principais:

1. `header.h`: Contém as declarações de estruturas e funções.
2. `source.c`: Implementa as funções declaradas no header.
3. `main.c`: Programa principal que utiliza as funções implementadas.

## Estrutura de Dados

A matriz é representada por uma lista ligada, onde cada nó (elemento) contém:
- Um valor
- Ponteiros para elementos adjacentes na mesma linha
