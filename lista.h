#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Posicao{
    int indice;     ///Indice do vetor que representa o heap.
    int qtd;       /// Posições Subsequentes ao Indice.
    char variavel;///  Id associado a área do heap.
}pos;

typedef struct no{
    struct Posicao elemento;
    struct no *ant, *prox;
}no;

no *CriaLista(){
    no *sentinela=(no*)malloc(sizeof(no));
    sentinela->ant=sentinela;
    sentinela->prox=sentinela;
    return sentinela;
}

no *CriaElemento(pos Elemento){
    no *novo=(no*)malloc(sizeof(no));
    novo->elemento=Elemento;
    novo->ant=NULL;
    novo->prox=NULL;
    return novo;
}

void InserirInicio(no *lista,pos Elemento){
    no *novo=(no*)malloc(sizeof(no)); /// posição livre
    novo->elemento=Elemento;
    novo->ant=lista;
    novo->prox=lista->prox;
    lista->prox->ant=novo;
    lista->prox=novo;
}

void InserirFim(no *lista,pos Elemento){
    no *novo=(no*)malloc(sizeof(no));  ///Posição ocupada
    novo->elemento=Elemento;
    novo->ant=lista->ant;
    novo->prox=lista;
    lista->ant->prox=novo;
    lista->ant=novo;
}

void InsereOrdem(no *lista,pos Elemento){
    no *aux=lista->prox;
    no *novo=CriaElemento(Elemento);
    while(aux!=lista && Elemento.indice>aux->elemento.indice){
        aux=aux->prox;
    }
    novo->prox=aux;
    novo->ant=aux->ant;
    aux->ant->prox=novo;
    aux->ant=novo;
}

no *BuscaID(no *lista,char ID){
    no *aux=lista->prox;
    int ctr=1;
    while((aux!=lista) && ctr==1){
        if(aux->elemento.variavel==ID){
            ctr=0;
        }else{
            aux=aux->prox;
        }
    }
    return aux;
}

void RemoverPorID(no *lista,char ID){
    no *aux=BuscaID(lista,ID);
    if(aux!=NULL){
        aux->prox->ant=aux->ant;
        aux->ant->prox=aux->prox;
        free(aux);
    }
}

no *BuscaIndice(no *lista,int Indice){
    no *aux=lista->prox;
    int ctr=1;
    while(aux!=lista && ctr==1){
        if(aux->elemento.indice==Indice){
            ctr=0;
        }else{
            aux=aux->prox;
        }
    }
    return aux;
}

void Remover(no *lista,int Indice){
    no *aux=BuscaIndice(lista,Indice);
    if(aux!=NULL){
        aux->prox->ant=aux->ant;
        aux->ant->prox=aux->prox;
        free(aux);
    }
}

no *DestruirLista(no *lista){
    if(lista!=NULL){
        no *aux=lista;
        lista->ant->prox=NULL;
        while(aux!=NULL){
            lista=lista->prox;
            free(aux);
            aux=lista;
        }
    }
    return NULL;
}

void ImprimirLista(no *lista){
    no *aux=lista->prox;
    while(aux!=lista){
        if(aux->elemento.variavel=='\n'){
            printf("Indice: %d\nPosicoes Subsequentes: %d\n\n",aux->elemento.indice,aux->elemento.qtd);
        }else{
            printf("ID: %c\nIndice: %d\nPosicoes Subsequentes: %d\n\n",aux->elemento.variavel,aux->elemento.indice,aux->elemento.qtd);
        }
        aux=aux->prox;
    }printf("\n\n");
}

void AjustaOver(no *lista,int maxtam){
    no *aux=lista->ant;
    int cont;
    cont=aux->elemento.indice+aux->elemento.qtd;
    if(cont>maxtam){
        aux->elemento.qtd-=(cont-maxtam);
    }
}

void JuntaPosVaziasContiguas(no *lista){
    no *aux=lista->prox;
    while(aux!=lista){
        if(aux->prox!=lista){
            if(aux->elemento.variavel=='\n' && aux->prox->elemento.variavel=='\n'){
                aux->elemento.qtd+=aux->prox->elemento.qtd;
                Remover(lista,aux->prox->elemento.indice);
            }
        }
        aux=aux->prox;
    }
}

void ArrumaLista(no *lista,int MAXtam){
    no *aux=lista->prox;
    pos a1;
    while(aux!=lista){
        if((aux->elemento.indice+aux->elemento.qtd != aux->prox->elemento.indice) && aux->prox!=lista){
            a1.indice=aux->elemento.indice+aux->elemento.qtd;
            a1.qtd=aux->prox->elemento.indice-a1.indice;
            a1.variavel='\n';
            InsereOrdem(lista,a1);
        }
        JuntaPosVaziasContiguas(lista);
        aux=aux->prox;
    }
    if(aux->ant->elemento.variavel!='\n'){
        a1.indice=aux->ant->elemento.indice+aux->ant->elemento.qtd;
        a1.qtd=MAXtam-a1.indice;
        a1.variavel='\n';
        InsereOrdem(lista,a1);
    }
    aux=lista->prox;
    while(aux!=lista){
        if(aux->elemento.qtd<=0||(aux->elemento.variavel=='\n'&&(aux->elemento.indice==aux->prox->elemento.indice))){
            Remover(lista,aux->elemento.indice);
        }
        aux=aux->prox;
    }
}

int PosSuficiente(no *lista,int tamMAX,int Qtd){
    no *aux=lista->prox;
    int resp=-1;
    while(aux!=lista){
        if(aux->elemento.variavel=='\n'&&aux->elemento.qtd>=Qtd){
            return 1;
        }
        aux=aux->prox;
    }
    return 0;
}

int IndicePorID(no *lista,char ID){
    no *aux=lista->prox;
    while(aux!=lista){
        if(aux->elemento.variavel==ID){
            return aux->elemento.indice;
        }
        aux=aux->prox;
    }
    return -1;
}

int OrdemNum(char *str){
    int n=0;
    while(str[7+n]!='\n'){
        n++;
    }
    return n;
}

#endif // LISTA_H_INCLUDED
