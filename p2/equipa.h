/*
 * Ficheiro:  equipa.c
 * Autor: Catarina Soares da Costa Bento
 * Numero: 93230
 * Curso: LEIC-A
 * Descricao: este ficheiro contem as funcoes especificas a manipulacao da Hashtable das Equipas.
 */

#ifndef hashtableEquipa
#define hashtableEquipa

/*****************************************************************************************************
 * Bibliotecas e Ficheiros 
*****************************************************************************************************/
#include "struct.h"

/*****************************************************************************************************
 * Abstracoes das Equipas 
*****************************************************************************************************/
#define elementHT(ItemSecondHT) ItemSecondHT->equipa
#define keyHT(ItemFirstHT) ItemFirstHT->equipa->nome
#define descHT(ItemFirstHT) ItemFirstHT->equipa->vitorias

/*A funcao InitSecondHT inicializa a hashTable de Equipas
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
*/
void InitSecondHT(ItemSecondHT **headsEquipa, int capacidadeE);

/* 
* Esta funcao verifica se ja existe uma equipa com nome "nome", e se nao existir adiciona uma 
* equipa com esse nome. Se ja existir, retorna FALSE, se conseguir adicionar a equipa retorna TRUE.
* nome: nome do item
* headsEquipa: variavel que armazena as heads da HT de Encademento Externo das Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
*/
int HTInserirElementoS(char *nome, ItemSecondHT **headsEquipa, int capacidadeE);

/* 
* Esta funcao procura uma equipa na HashTable de equipas. Caso a equipa exista, retorna a equipa.
* Se a equipa nao existir, retorna nulo.
* nome: nome do item.
* headsEquipa: variavel que armazena as heads da HT de Encademento Externo das Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
*/
equipa * HTProcurarElementoS(char *v, ItemSecondHT **headsEquipa, int capacidadeE);

/* 
* A funcao HTEncontraEquipasVencedoras encontra as equipas com mais vitorias de todas as 
* equipas e chama a funcao que as ordena por ordem lexicografica e as imprime.
* headsEquipa: variavel que armazena as heads da HT de Encademento Externo das Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
* linha: variavel que armazena a linha do input que originou este comando.
*/
void HTencontraEquipasVencedoras(ItemSecondHT **headsEquipa, int capacidadeE, int linha);

/* 
* A funcao freeAllEquipa da free aos elementos da HashTable de equipas e das proprias equipas
* nessa HashTable.
* headsEquipa: variavel que armazena as heads da HT de Encademento Externo das Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
*/
void freeAllEquipa(ItemSecondHT **headsEquipa, int capacidadeE);

#endif