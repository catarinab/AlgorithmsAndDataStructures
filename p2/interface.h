/*
 * Ficheiro:  hashtable.h
 * Autor: Catarina Soares da Costa Bento
 * Numero: 93230
 * Curso: LEIC-A
 * Descricao: este ficheiro serve de interface entre a funcao main e as hashtables e listas. Tem
 * tambem as funcoes comuns a todas as hashtables, por exemplo a funcao de hashing.
 */

#include <stdio.h>
#include "struct.h"

#define MAXNOME 1024
#define CAPACIDADEJ 1000
#define CAPACIDADEE 1000

/*
 * Ficheiro:  hashtable.c
 * Autor: Catarina Soares da Costa Bento
 * Numero: 93230
 * Curso: LEIC-A
 * Descricao: este ficheiro serve de interface entre a funcao main e as hashtables e listas. Tem
 *                     tambem as funcoes comuns a todas as hashtables, por exemplo a funcao de hashing.
 */

/*****************************************************************************************************
 * Bibliotecas e Ficheiros 
*****************************************************************************************************/
#include "struct.h"

/*
* A funcao inicializarHT inicializa as Hashtables de jogos e de equipas e a Lista de Jogos.
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* listaJogo: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
*/
void inicializarHT(ItemFirstHT ** headsJogo, lista * listaJogo, ItemSecondHT ** headsEquipa, 
                                    int capacidadeJ, int capacidadeE);

/*A funcao hash realiza o hashing de uma string 
* key: key do elemento a que é feito o hashing
* capacidade: tamanho da HashTable
*/
int hash(char * key, int capacidade);

/*****************************************************************************************************
 * Equipas
*****************************************************************************************************/

/*
* A funcao adicionarEquipa verifica se a equipa com o nome dado ja existe, e caso nao exista 
* adiciona a equipa a HashTable de equipas.
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
* linha: variavel que armazena a linha do input que originou esse comando
*/
void adicionarEquipa(ItemSecondHT ** headsEquipa, int capacidadeE, int linha);

/*
* A funcao procurarMelhoresEquipas chama a funcao que procura na Hashtable de equipas as
* equipas com mais vitorias.
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
* linha: variavel que armazena a linha do input que originou esse comando
*/
void procurarMelhoresEquipas(ItemSecondHT **headsEquipa, int capacidadeE, int linha);

/* 
* A funcao imprimirEquipa imprime da forma pedida no enunciado uma equipa.
* eq: equipa a ser impressa
*/
void imprimirEquipa(equipa * eq);

/* 
* A funcao procurarEquipa verifica se a equipa de nome nomeEquipa existe, e caso exista imprime a 
* equipa da forma dita no enunciado. Caso a equipa nao exista, imprime essa informacao.
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
* linha: variavel que armazena a linha do input que originou esse comando
*/
void procurarEquipa(ItemSecondHT ** headsEquipa, int capacidadeE, int linha);

/*****************************************************************************************************
 * Jogos
*****************************************************************************************************/

/*
* A funcao adicionarJogo verifica se o jogo com o nome dado ja existe e se as equipas adicionadas
* existem, e caso o jogo nao exista e as equipas existam, adiciona o jogo a HashTable e Lista de 
* equipas. Caso ocorra algum erro imprime o erro.
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* listaJogo: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* linha: variavel que armazena a linha do input que originou esse comando
*/
void adicionarJogo(ItemFirstHT ** headsJogo, lista* listaJogo, ItemSecondHT ** headsEquipa,
                                     int capacidadeE, int capacidadeJ, int linha);

/* 
* A funcao encontrarJogo verifica se o jogo de nome nomeJogo existe, e caso exista imprime o 
* jogo da forma dita no enunciado. Caso o jogo nao exista, imprime essa informacao.
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* linha: variavel que armazena a linha do input que originou esse comando
*/
void encontrarJogo(int capacidadeJ, ItemFirstHT **headsJogo, int linha);

/* 
* A funcao imprimirJogo imprime um jogo da forma mencionada no enunciado.
* jogo: jogo a ser impresso
* linha: linha do input que originou este comando
*/
void imprimirJogo(jogo *jogo, int linha);

/* A funcao listarJogos chama a funcao que lista os jogos ordenados pela ordem de insercao.
* listaJogo: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* linha: variavel que armazena a linha do input que originou esse comando*/
void listarJogos(lista *listaJogo, int linha);

/* 
* A funcao alterarPontucao chama a funcao que altera a pontuacao do jogo de nomeJogo caso 
* exista e altera as vitorias das equipas caso isso seja necessario.
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* linha: variavel que armazena a linha do input que originou esse comando
*/
void alterarPontuacao(int capacidadeJ, ItemFirstHT **headsJogo, int linha);

/* 
* A funcao removerJogo remove um jogo do sistema (da Hashtable e da Lista de Jogos) caso o 
* jogo exista.
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* listaJogo: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* linha: variavel que armazena a linha do input que originou esse comando
*/
void removerJogo(ItemFirstHT ** headsJogo, int capacidadeJ, lista* listaJogo, int linha);

/* A funcao freeAll da free a toda a memoria alocada durante o funcionamento do programa.
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* listaJogo: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
*/
void freeAll(ItemFirstHT ** headsJogo, ItemSecondHT ** headsEquipa, lista * listaJogo, 
                        int capacidadeE, int capacidadeJ);
