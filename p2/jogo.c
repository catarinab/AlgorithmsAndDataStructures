/*
 * Ficheiro:  jogo.c
 * Autor: Catarina Soares da Costa Bento
 * Numero: 93230
 * Curso: LEIC-A
 * Descricao: este ficheiro contem as funcoes especificas a manipulacao da Hashtable e da Lista de
 *                      Jogos.
 */

/*****************************************************************************************************
 * Bibliotecas e Ficheiros 
*****************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jogo.h"
#include "struct.h"
#include "interface.h"

/* 
* A funcao HTInitFirst inicializa a HashTable e lista de Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
*/
void HTInitFirst(ItemFirstHT **headsJogo, lista *listaJ, int capacidadeJ){
    int i;
    listaJ->head = NULL;
    listaJ->last = NULL;
    for (i = 0; i < capacidadeJ; i++)
        headsJogo[i] = NULL;
}

/* 
* A funcao adicionarUltimoLista adiciona um jogo ao fim da Lista de Jogos
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* nJogo: jogo a inserir na listaJ
*/
void adicionarUltimoLista(lista* listaJ, jogo * nJogo){
    ItemList *no = malloc(sizeof(ItemList));
    if(listaJ->head == NULL){   /* Ou seja, e o primeiro Item da Lista*/
        listaJ->head = no;
        no ->previous = NULL;
    }
    else{
        no->previous = listaJ->last;
        listaJ->last->next = no;
    }
    no->next = NULL;
    no->jogo = nJogo;
    listaJ->last = no;
}

/* 
* A funcao inicializarItem aloca memoria e inicializa os campos do novo ItemFirstHT.
* nome: nome do Item
* e1 e e2: equipas pertencentes ao jogo
* s1 e s2: score do Jogo
*/
ItemFirstHT * inicializarItem(char *nome, equipa * e1, equipa * e2, int s1, int s2){
    ItemFirstHT *temporario = (ItemFirstHT *)malloc(sizeof(ItemFirstHT));
    elementHTS(temporario) = (jogo *)malloc(sizeof(jogo));
    keyHTS(temporario) = (char *)malloc((strlen(nome) + 1) * sizeof(char));
    strcpy(keyHTS(temporario), nome);
    fElementHTS(temporario) = e1;
    sElementHTS(temporario) = e2;
    fDescHTS(temporario) = s1;
    sDescHTS(temporario) = s2;
    temporario->previous = NULL;  /* Pois o item e inserido no inicio da lista*/
    return temporario;
}

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
                        lista* listaJ,  equipa * e1, equipa * e2){
    int i = hash(nome, capacidadeJ);
    ItemFirstHT *temporario = inicializarItem(nome, e1, e2, score1, score2);
    adicionarUltimoLista(listaJ, elementHTS(temporario));
    if (score1 > score2) 
        e1->vitorias +=1;
    else if (score1 < score2)
        e2->vitorias +=1;
    temporario->next = headsJogo[i];
    if (headsJogo[i] != NULL) /* Ou seja, se nao for o primeiro Item da Lista de encadeamento e.*/
        headsJogo[i]->previous = temporario;
    headsJogo[i] = temporario;
}




/* 
* A funcao procurarElemento procura um jogo de nome "nome" na HashTable de equipas e 
* retorna o link da HashTable com esse jogo caso ele exista. Se nao existir, retorna nulo.
* head:ponteiro para posicao no array da HT da lista de encadeamento externo a que o item pertence.
* key: nome do item (chave de procura).
*/
ItemFirstHT * procurarElemento(ItemFirstHT * head, char * key){
    while(head != NULL){
        if(strcmp(keyHTS(head), key) == 0){
            return head;
        }
        head = head->next;
    }
    return NULL;
}

/* 
* Esta funcao chama a funcao que procura um jogo na HashTable de Jogos. Caso o Jogo exista
* retorna o jogo. Se o jogo nao existir, retorna nulo.
* key: elemento pelo qual o jogo sera procurado.
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
*/
jogo * HTProcurarElementoF(char *key, int capacidadeJ, ItemFirstHT ** headsJogo){
    ItemFirstHT *head;
    int i = hash(key, capacidadeJ);
    head = procurarElemento(headsJogo[i], key);
    if (head == NULL)
        return NULL;
    return elementHTS(head);
}

/*
* A funcao HTListarElementos percorre a lista ligada de Jogos e chama a funcao que imprime jogos para
* cada no da lista (sendo que cada uma contem um jogo).
* linha: variavel que armazena a linha do input que originou este comando
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
*/
void HTListarElementos(int linha, lista* listaJ){
    ItemList * head = listaJ->head;
    while (head != NULL){
        imprimirJogo(elementList(head), linha);
        head = head->next;
    }
}

/* 
* As seguintes tres funcoes sao auxiliares a funcao HTAlterarPontuacao, que alteram as vitorias de 
* cada equipa de acordo com o vencedor do jogo ou se tiver sido um empate (antes de se alterar
* a pontuacao do jogo)
* nJogo: jogo ao qual sera alterado a pontuacao
* score1 e score2: nova pontuacao do jogo 
*/
void alterarPontuacaoIgual(jogo * nJogo, int score1, int score2){
    if (score1 == score2 && nJogo->pScore > nJogo->sScore)
        nJogo->pEquipa->vitorias -= 1;
    else if (score1 == score2 && nJogo->pScore < nJogo->sScore)
        nJogo->sEquipa->vitorias -= 1;
}

void alterarPontuacaoP(jogo * nJogo, int score1, int score2){
    if (score1 < score2 && nJogo->pScore > nJogo->sScore){
        nJogo->pEquipa->vitorias -= 1;
        nJogo->sEquipa->vitorias += 1;
    }
    else if (score1 < score2 && nJogo->pScore == nJogo->sScore)
        nJogo->sEquipa->vitorias += 1;
}

void alterarPontuacaoS(jogo * nJogo, int score1, int score2){
    if(score1 > score2 && nJogo->pScore < nJogo->sScore){
        nJogo->pEquipa->vitorias += 1;
        nJogo->sEquipa->vitorias -= 1;
    }
    else if (score1 > score2 && nJogo->pScore == nJogo->sScore)
        nJogo->pEquipa->vitorias += 1;
}

/*
* A funcao HTAlterarPontuacao chama as funcoes auxiliares que alteram as vitorias de cada equipa
* do jogo de acordo com a nova pontuacao e altera o score do jogo. 
* nomeJogo: nome do Item
* score1 e score2: score do Jogo
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
*/
int HTAlterarPontuacao(char * nomeJogo, int score1, int score2, int capacidadeJ, 
                                            ItemFirstHT ** headsJogo){
    jogo * nJogo = HTProcurarElementoF(nomeJogo, capacidadeJ, headsJogo);
    if (nJogo == NULL)
        return FALSE;
    alterarPontuacaoP(nJogo, score1, score2);
    alterarPontuacaoS(nJogo, score1, score2);
    alterarPontuacaoIgual(nJogo, score1, score2);
    nJogo->pScore = score1;
    nJogo->sScore = score2;
    return TRUE;
}

/*
* A funcao removerElementoHT remove o jogo da HashTable de acordo com a sua posicao na lista de 
* encadeamento externo da HashTable, cuja cabeca e head.
* head:ponteiro para posicao no array da HT da lista de encadeamento externo a que o item pertence.
* pos:  posicao no array da HT da lista de encadeamento externo a que o item pertence.
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* i: posicao da
*/
void removerElementoHT(ItemFirstHT * head, int pos, ItemFirstHT ** headsJogo){
    if(head->next == NULL && head->previous == NULL)
        headsJogo[pos] = NULL;
    else if (head->next == NULL){
        head->previous->next = NULL;
    }
    else if (head->previous == NULL){
        headsJogo[pos] = head->next;
        head->next->previous = NULL;
    }
    else{
        head->previous->next = head->next;
        head->next->previous = head->previous;
        }
}

/*
* A funcao removerElementoLista procura o jogo j na lista listaJ e remove-o de acordo com a sua 
* posicao na lista de Jogos.
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
* jogo: jogo a ser removido da lista
*/
void removerElementoLista(lista* listaJ, jogo * jogo){
    ItemList * head = listaJ->head;
    while(head != NULL){
        if(elementList(head) == jogo){
            if(head->next == NULL && head->previous == NULL) {
                listaJ->head = NULL;
            }
            else if(head->next == NULL){
                head->previous->next = NULL;
                listaJ->last = head->previous;
            }
            else if(head->previous == NULL){
                listaJ->head = head->next;
                head->next->previous = NULL;
            }
            else{
                head->previous->next = head->next;
                head->next->previous = head->previous;
            }
            freeJogo(elementList(head));
            free(head);
            head = NULL;
            break;
        }
       head = head->next;
    }
}

/*
* A funcao HTRemoverElemento chama a funcao que encontra o jogo com nome "nomeJogo" e caso
* ele exista, remove-o da HashTable e da Lista de Jogos, dando free aos elementos.
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* nomeJogo: nome do Item
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
*/
int HTRemoverElemento(ItemFirstHT ** headsJogo, int capacidadeJ, char * nomeJogo, lista* listaJ){
    int i = hash(nomeJogo, capacidadeJ);
    ItemFirstHT * head = procurarElemento(headsJogo[i], nomeJogo);
    if(head != NULL){
        /* Alterar as vitorias das equipas*/
        if (fDescHTS(head) > sDescHTS(head))
            head->jogo->pEquipa->vitorias -= 1;
        else if (fDescHTS(head) < sDescHTS(head))
            head->jogo->sEquipa->vitorias -= 1;
        
        removerElementoHT(head, i, headsJogo);
        removerElementoLista(listaJ, head->jogo);
        free(head);
        head = NULL;
        return TRUE;
    }
    return FALSE;
}

/* 
* A funcao freeLista da free aos nos da lista de Jogos
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos
*/
void freeLista(lista* listaJ){
    ItemList * head = listaJ->head, * temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    free(listaJ);
}

/* 
* A funcao freeJogo da free aos elementos do Jogo recebido e do proprio jogo
* fJogo: jogo a ser libertado
*/
void freeJogo(jogo * fJogo){
    free(fJogo->nome);
    free(fJogo);
}

/* 
* A funcao freeAllJogo da free aos elementos da HashTable de jogos, dos proprias jogos
* nessa HashTable e da lista de Jogos
* headsJogo: variavel que armazena as heads da HashTable de Jogos
* capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
* listaJ: variavel que armazena ponteiros para o primeiro e ultimo elemento da lista de Jogos.
*/
void freeAllJogo(ItemFirstHT ** headsJogo, int capacidadeJ, lista* listaJ){
    ItemFirstHT *temp;
    int i;
    freeLista(listaJ);
    for (i = 0; i < capacidadeJ; i++){
        while (headsJogo[i] != NULL){
            temp = headsJogo[i];
            freeJogo(elementHTS(temp));
            headsJogo[i] = headsJogo[i]->next;
            free(temp);
        }
    }
    free(headsJogo);
}
