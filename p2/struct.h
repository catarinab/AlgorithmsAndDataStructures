/*
 * Ficheiro:  struct.h
 * Autor: Catarina Soares da Costa Bento
 * Numero: 93230
 * Curso: LEIC-A
 * Descricao: este ficheiro contem as estruturas e constantes necessarias ao funcionamento de todo
 *                      o programa.
 */

#ifndef hashtableJogo
#define hashtableJogo

/*****************************************************************************************************
* Constantes
*****************************************************************************************************/
#define TRUE 1
#define FALSE 0
#define STRIGUAL 0

/*****************************************************************************************************
 * Estruturas
*****************************************************************************************************/

/*
 * Tipo que descreve uma Equipa
 * vitorias: o numero de vitorias total da equipa 
*/
typedef struct{
    char *nome;
    int vitorias;
} equipa;

/*
 * Tipo que descreve o link de cada encadeamento externo da Hashtable de equipas
*/
typedef struct linkE{
    equipa * equipa;
    struct linkE * next;
} linkEquipa;

/*
 * Tipo que descreve um Jogo
 * contem duas equipas, e dois inteiros, sendo o primeiro inteiro a pontuacao da pEquipa e o segundo
 * inteiro a pontuacao da sEquipa.
*/
typedef struct{
    char *nome;
    equipa *pEquipa;
    equipa *sEquipa;
    int pScore;
    int sScore;
} jogo;

/*
 * Tipo que descreve o link de cada encadeamento externo da Hashtable de jogos
*/
typedef struct linkJ{
    jogo *jogo;
    struct linkJ *next, * previous;
} linkJogo;

/*
 * Tipo que descreve um node de uma lista duplamente ligada de Jogos.
*/
typedef struct str_node{
    struct str_node *next, *previous;
    jogo * jogo;
} node;

/*
* Tipo que contem ponteiros para o primeiro e ultimo no da lista duplamente ligada.
*/
typedef struct{
    struct str_node *head, *last;
} lista;

/*****************************************************************************************************
 * Abstracoes de Itens 
*****************************************************************************************************/
typedef linkJogo ItemFirstHT;

typedef node ItemList;

typedef linkEquipa ItemSecondHT;

#endif