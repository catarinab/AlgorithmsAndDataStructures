/*
 * Ficheiro:  jogo.h
 * Autor: Catarina Soares da Costa Bento
 * Numero: 93230
 * Curso: LEIC-A
 * Descricao: este ficheiro contem as funcoes especificas a manipulacao da Hashtable e da Lista de
 *                      Jogos.
 */


/*****************************************************************************************************
 * Bibliotecas e Ficheiros 
*****************************************************************************************************/
#include "struct.h"

/*****************************************************************************************************
 * Abstracoes dos Jogos 
*****************************************************************************************************/
#define elementHTS(ItemFirstHT) ItemFirstHT->jogo
#define keyHTS(ItemFirstHT) ItemFirstHT->jogo->nome
#define fElementHTS(ItemFirstHT) ItemFirstHT->jogo->pEquipa
#define sElementHTS(ItemFirstHT) ItemFirstHT->jogo->sEquipa
#define fDescHTS(ItemFirstHT) ItemFirstHT->jogo->pScore
#define sDescHTS(ItemFirstHT) ItemFirstHT->jogo->sScore
#define elementList(ItemList) ItemList->jogo

/* 
* A funcao HTInitFirst inicializa a HashTable e lista de Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
*/
void HTInitFirst(ItemFirstHT **headsJogo, lista *listaJogo, int capacidadeJ);

/* 
* A funcao HTInserirElementoF insere uma novo Jogo na lista duplamente ligada de Jogos e na
* HashTable de jogos.
* nome: nome do Item
* score1 e score2: score do Jogo
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* e1 e e2: equipas pertencentes ao jogo
*/
void HTInserirElementoF(char *nome, int score1, int score2, int capacidadeJ, ItemFirstHT ** headsJogo, 
                        lista* listaJogo,  equipa * e1, equipa * e2);

/* 
* Esta funcao chama a funcao que procura um jogo na HashTable de Jogos. Caso o Jogo exista
* retorna o jogo. Se o jogo nao existir, retorna nulo.
* key: elemento pelo qual o jogo sera procurado.
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
*/
jogo *HTProcurarElementoF(char *v, int capacidadeJ, ItemFirstHT **headsJogo);

/*
* A funcao HTListarJogos percorre a lista ligada de Jogos e chama a funcao que imprime jogos para
* cada no da lista (sendo que cada uma contem um jogo).
* linha: variavel que armazena a linha do input que originou este comando
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
*/
void HTListarElementos(int linha, lista *listaJogo);

/* 
* As seguintes tres funcoes sao auxiliares a funcao HTAlterarPontuacao, que alteram as vitorias de 
* cada equipa de acordo com o vencedor do jogo ou se tiver sido um empate (antes de se alterar
* a pontuacao do jogo)
* nJogo: jogo ao qual sera alterado a pontuacao
* score1 e score2: nova pontuacao do jogo 
*/
int HTAlterarPontuacao(char * nomeJogo, int score1, int score2, int capacidadeJ, 
                                            ItemFirstHT ** headsJogo);

/*
* A funcao HTRemoverJogo chama a funcao que encontra o jogo com nome "nomeJogo" e caso ele 
* exista, remove-o da HashTable e da Lista de Jogos, dando free aos elementos.
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* nomeJogo: nome do Item
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
*/
int HTRemoverElemento(ItemFirstHT ** headsJogo, int capacidadeJ, char * nomeJogo, lista* listaJ);
/* 
* A funcao freeAllJogo da free aos elementos da HashTable de jogos, dos proprias jogos
* nessa HashTable e da lista de Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos.
*/

void freeAllJogo(ItemFirstHT ** headsJogo, int capacidadeJ,lista* listaJogo);

/* 
* A funcao freeJogo da free aos elementos do Jogo recebido e do proprio jogo
* fJogo: jogo a ser libertado
*/
void freeJogo(jogo *fJogo);