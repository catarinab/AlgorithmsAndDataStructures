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
#include <stdio.h>
#include "struct.h"
#include "equipa.h"
#include "jogo.h"
#include "interface.h"

/*
* A funcao inicializarHT inicializa as Hashtables de jogos e de equipas e a Lista de Jogos.
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* listaJogo: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
*/
void inicializarHT(ItemFirstHT ** headsJogo, lista * listaJogo, ItemSecondHT ** headsEquipa, 
                                    int capacidadeJ, int capacidadeE){
    HTInitFirst(headsJogo, listaJogo, capacidadeJ);
    InitSecondHT(headsEquipa, capacidadeE);
}

/*A funcao hash realiza o hashing de uma string 
* key: key do elemento a que é feito o hashing
* capacidade: tamanho da HashTable
*/
int hash(char * key, int capacidade){
    int h, a = 31415, b = 27183;
    for (h = 0; *key != '\0'; key++, a = a * b % (capacidade - 1))
        h = (a * h + *key) % capacidade;
    return h;
}

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
void adicionarEquipa(ItemSecondHT ** headsEquipa, int capacidadeE, int linha){
    char nomeEquipa[MAXNOME];
    scanf(" %[^\n]", nomeEquipa);
    if(HTInserirElementoS(nomeEquipa, headsEquipa, capacidadeE) == FALSE)
        printf("%d Equipa existente.\n", linha);
}

/*
* A funcao procurarMelhoresEquipas chama a funcao que procura na Hashtable de equipas as
* equipas com mais vitorias.
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
* linha: variavel que armazena a linha do input que originou esse comando
*/
void procurarMelhoresEquipas(ItemSecondHT ** headsEquipa, int capacidadeE, int linha){
    HTencontraEquipasVencedoras(headsEquipa, capacidadeE, linha);
}

/* 
* A funcao imprimirEquipa imprime da forma pedida no enunciado uma equipa.
* eq: equipa a ser impressa
*/
void imprimirEquipa(equipa * eq){
    printf("%s %d\n", eq->nome, eq->vitorias);
}

/* 
* A funcao procurarEquipa verifica se a equipa de nome nomeEquipa existe, e caso exista imprime a 
* equipa da forma dita no enunciado. Caso a equipa nao exista, imprime essa informacao.
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
* linha: variavel que armazena a linha do input que originou esse comando
*/
void procurarEquipa(ItemSecondHT ** headsEquipa, int capacidadeE, int linha){
    char nomeEquipa[MAXNOME];
    equipa * e;
    scanf(" %[^\n]", nomeEquipa);
    e = HTProcurarElementoS(nomeEquipa, headsEquipa, capacidadeE);
    if(e == NULL)
        printf("%d Equipa inexistente.\n", linha);
    else{
        printf("%d ", linha);
        imprimirEquipa(e);
    }
}

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
                                     int capacidadeE, int capacidadeJ, int linha){
    int s1, s2;
    equipa *e1, *e2;
    char nomeJogo[MAXNOME], nomeEquipa[MAXNOME], nomeEquipa2[MAXNOME];
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nomeJogo, nomeEquipa, nomeEquipa2, &s1, &s2);
    if (HTProcurarElementoF(nomeJogo, capacidadeJ, headsJogo) != NULL) /* o jogo ja existe*/
        printf("%d Jogo existente.\n", linha);
    else if ((e1 = HTProcurarElementoS(nomeEquipa, headsEquipa, capacidadeE)) == NULL ||
        (e2 = HTProcurarElementoS(nomeEquipa2, headsEquipa, capacidadeE)) == NULL)
        printf("%d Equipa inexistente.\n", linha);
    else HTInserirElementoF(nomeJogo, s1, s2, capacidadeJ, headsJogo, listaJogo, e1, e2);
        
}

/* 
* A funcao encontrarJogo verifica se o jogo de nome nomeJogo existe, e caso exista imprime o 
* jogo da forma dita no enunciado. Caso o jogo nao exista, imprime essa informacao.
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* linha: variavel que armazena a linha do input que originou esse comando
*/
void encontrarJogo(int capacidadeJ, ItemFirstHT ** headsJogo, int linha){
    char nomeJogo[MAXNOME];
    jogo * pJogo;
    scanf(" %[^\n]", nomeJogo);
    pJogo = HTProcurarElementoF(nomeJogo, capacidadeJ, headsJogo);
    if( pJogo == NULL)
        printf("%d Jogo inexistente.\n", linha);
    else
        imprimirJogo(pJogo, linha);
}

/* 
* A funcao imprimirJogo imprime um jogo da forma mencionada no enunciado.
* jogo: jogo a ser impresso
* linha: linha do input que originou este comando
*/
void imprimirJogo(jogo * jogo, int linha){
    printf("%d %s %s %s %d %d\n", linha, jogo->nome, jogo->pEquipa->nome, jogo->sEquipa->nome, 
    jogo->pScore, jogo->sScore);
}

/* A funcao listarJogos chama a funcao que lista os jogos ordenados pela ordem de insercao.
* listaJogo: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* linha: variavel que armazena a linha do input que originou esse comando*/
void listarJogos(lista* listaJogo, int linha){
    HTListarElementos(linha, listaJogo);
}

/* 
* A funcao alterarPontucao chama a funcao que altera a pontuacao do jogo de nomeJogo caso 
* exista e altera as vitorias das equipas caso isso seja necessario.
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* linha: variavel que armazena a linha do input que originou esse comando
*/
void alterarPontuacao(int capacidadeJ, ItemFirstHT ** headsJogo, int linha){
    int s1, s2, i;
    char nomeJogo[MAXNOME];
    scanf(" %[^:\n]:%d:%d", nomeJogo, &s1, &s2);
    i = HTAlterarPontuacao(nomeJogo, s1, s2, capacidadeJ, headsJogo);
    if(i == FALSE)
        printf("%d Jogo inexistente.\n", linha);
}

/* 
* A funcao removerJogo remove um jogo do sistema (da Hashtable e da Lista de Jogos) caso o 
* jogo exista.
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* listaJogo: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* linha: variavel que armazena a linha do input que originou esse comando
*/
void removerJogo(ItemFirstHT ** headsJogo, int capacidadeJ, lista* listaJogo, int linha){
    int i;
    char nomeJogo[MAXNOME];
    scanf(" %[^\n]", nomeJogo);
    if ((i = HTRemoverElemento(headsJogo, capacidadeJ, nomeJogo, listaJogo)) == FALSE){
        printf("%d Jogo inexistente.\n", linha);
    }
}

/* A funcao freeAll da free a toda a memoria alocada durante o funcionamento do programa.
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* listaJogo: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
*/
void freeAll(ItemFirstHT ** headsJogo, ItemSecondHT ** headsEquipa, lista * listaJogo, 
                        int capacidadeE, int capacidadeJ){
    freeAllEquipa(headsEquipa, capacidadeE);
    freeAllJogo(headsJogo, capacidadeJ, listaJogo);
}