#include"lista.h"
#define TAM 15

void ImprimeHeap(no *lista){
    no *aux=lista->prox;
    int indiceatual=0;
    printf(".................HEAP.................\n\n");
    while(aux!=lista){
        if(aux->prox!=lista && (aux->elemento.indice==aux->prox->elemento.indice)){
            aux=aux->prox;
        }
        for(int i=0;i<aux->elemento.qtd;i++){
            if(aux->elemento.variavel=='\n'){
                printf("[  %d  ]",indiceatual);
            }else{
                printf("[//%d//]",indiceatual);
            }
            indiceatual++;
        }
        aux=aux->prox;
    }
    printf("\n\n\n\n");
}

void FirstFit(no *lista,char ID,int Qtd){
    no *aux=lista->prox; //primeiro elemento da lista de índices do heap
    pos PosOc; // cria nó de posição ocupada
    int ctr=1;
    while( aux!=lista && ctr==1 ){  // percorre a lista de índices do vetor
        if(aux->elemento.variavel=='\n' && aux->elemento.qtd>=Qtd){ // posição vazia com espaço suficiente
            ctr=0;  // para
        }else{ // se não for
            aux=aux->prox; // olha o próximo nó
        }
    }
    if(aux!=lista){ // não percorreu até o fim
        PosOc.indice=aux->elemento.indice; // índice
        PosOc.qtd=Qtd; // espaço requisitado
        PosOc.variavel=ID; // associa a "ID"
        Remover(lista,PosOc.indice); // remove o nó antigo(associado a um espaço vazio no vetor)
        InsereOrdem(lista,PosOc); // insere na lista de índices do vetor
        ArrumaLista(lista,TAM);
    }
}

void NextFit(no *lista,char ID,int Qtd,int *IndiceUltimaAreaOcupada){
    no *inicioBusca=BuscaIndice(lista,*(IndiceUltimaAreaOcupada)); // inicioBusca aponta pro nó de indice UIO
    pos PosOc;
    int ctr=1;
    if(inicioBusca!=lista){ // se esse indice existe na lista
        no *aux=inicioBusca->ant;
        while(inicioBusca!=aux && ctr==1){ // enquanto não der a volta completa na lista
            if(inicioBusca->prox==lista&&(inicioBusca->elemento.indice=='\n'&&inicioBusca->elemento.qtd>=Qtd)){ // se a próxima posição é o sentinela
                inicioBusca=lista->prox;
            }
            if(inicioBusca->elemento.variavel=='\n' && inicioBusca->elemento.qtd>=Qtd){ // posição vazia com espaço suficiente
                ctr=0;  // para
            }else{ // se não for
                inicioBusca=inicioBusca->prox; // olha o próximo nó
            }
        }
        if(inicioBusca!=aux){ // não percorreu até o fim
            PosOc.indice=inicioBusca->elemento.indice; // índice
            PosOc.qtd=Qtd; // espaço requisitado
            PosOc.variavel=ID; // associa a "ID"
            Remover(lista,PosOc.indice); // remove o nó antigo(associado a um espaço vazio no vetor)
            InsereOrdem(lista,PosOc); // insere na lista de índices do vetor
            *(IndiceUltimaAreaOcupada)=PosOc.indice;
            ArrumaLista(lista,TAM);
            printf("..uio: %d\n",*(IndiceUltimaAreaOcupada));
        }
    }
}

void BestFit(no *lista,char ID,int Qtd){
    no *melhorPos=lista->prox; // inicio da lista
    pos PosOc;
    int ctr=1;
    while(melhorPos!=lista && ctr==1){
        if(melhorPos->elemento.variavel=='\n'&&melhorPos->elemento.qtd>=Qtd){ //primeira posição vazia com espaço suficiente
            ctr=0;
        }else{
            melhorPos=melhorPos->prox;
        }
    }
    if(melhorPos!=lista){ // se tiver encontrado alguma posição livre que caiba
        if(melhorPos->elemento.qtd!=Qtd){ // caso a primeira posição livre encontrada tenha o espaço exato
            no *aux=melhorPos->prox;
            int ctr=1;
            while(aux!=lista && ctr==1){
                if(aux->elemento.variavel=='\n' && (aux->elemento.qtd==Qtd)){
                    melhorPos=aux;
                    ctr=0;
                }else{
                    if(aux->elemento.variavel=='\n' && (aux->elemento.qtd < melhorPos->elemento.qtd)){
                        melhorPos=aux;
                    }
                    aux=aux->prox;
                }
            }
        }
        PosOc.indice=melhorPos->elemento.indice;
        PosOc.qtd=Qtd;
        PosOc.variavel=ID;
        Remover(lista,PosOc.indice);
        InsereOrdem(lista,PosOc);
        ArrumaLista(lista,TAM);
    }
}

void WorstFit(no *lista,char ID,int Qtd){
    no *melhorPos=lista->prox; //primeiro indice
    pos PosOc;
    int ctr=1;
    while(melhorPos!=lista && ctr==1){
        if(melhorPos->elemento.variavel=='\n'&&melhorPos->elemento.qtd>=Qtd){ //primeira posição vazia com espaço suficiente
            ctr=0; //para
        }else{
            melhorPos=melhorPos->prox;
        }
    }
    if(melhorPos!=lista){ // se tiver encontrado alguma posição vazia com espaço
        if(melhorPos->elemento.qtd!=Qtd){ // se a primeira posição encontrada não for a "posição perfeita"
            no *aux=melhorPos->ant; // posição seguinte da primeira encontrada
            int ctr=1;
            while(aux!=lista && ctr==1){ // até o fim da lista ou encoontrar uma "posição perfeita"
                if(aux->elemento.variavel=='\n' && (aux->elemento.qtd==Qtd)){ // "posição perfeita"
                    melhorPos=aux;
                    ctr=0; // para
                }else{
                    if(aux->elemento.variavel=='\n' && (aux->elemento.qtd > melhorPos->elemento.qtd)){ //posição com mais espaço do que a encontrada anterior
                        melhorPos=aux;
                    }
                    aux=aux->prox;
                }
            }
        }
        PosOc.indice=melhorPos->elemento.indice;
        PosOc.qtd=Qtd;
        PosOc.variavel=ID;
        Remover(lista,PosOc.indice);
        InsereOrdem(lista,PosOc);
        ArrumaLista(lista,TAM);
    }
}

void InsereHeap(no *lista,int *TipoHeap,char ID,int Qtd,int *IndiceUltimaPosOc){
    int caso= *(TipoHeap);
    switch(caso){
    case 1:
        FirstFit(lista,ID,Qtd);
        break;
    case 2:
        NextFit(lista,ID,Qtd,IndiceUltimaPosOc);
        break;
    case 3:
        BestFit(lista,ID,Qtd);
        break;
    case 4:
        WorstFit(lista,ID,Qtd);
        break;
    }
}

void RemoveHeap(no *lista,char ID){
    no *aux;
    pos a1;
    a1.qtd=1;
    aux=lista->prox;
    int ctr=1;
    while(aux!=lista && ctr==1){  // percorre a lista de índices do vetor
        if(aux->elemento.variavel==ID){ // posição ocupada associada a "ID"
            if(aux->ant!=lista&&aux->ant->elemento.variavel=='\n'){  // se não for o primeiro índice e o próximo indice é uma posição vazia
                aux->ant->elemento.qtd+=aux->elemento.qtd; // incrementa o espaço livre (seguinte ao indice) com a quantidade que vai ser liberada
                Remover(lista,aux->elemento.indice);
                ArrumaLista(lista,TAM);
            }else if(aux->prox!=lista&&aux->prox->elemento.variavel=='\n'){ // se não for o último índice e o índice anterior é uma posição vazia
                aux->prox->elemento.qtd+=aux->elemento.qtd; // incrementa o espaço livre (anterior ao indice) com a quantidade que vai ser liberada
                Remover(lista,aux->elemento.indice);
                ArrumaLista(lista,TAM);
            }else{ // se for o primeiro ou o último índice
                aux->elemento.variavel='\n';  // só substitui por uma posição vazia
            }
            ctr=0;
        }else{
            aux=aux->prox;
        }
    }
    ArrumaLista(lista,TAM);
}

void Atribui(no *lista,no *listaAtribuicoes,char id1,char id2){
    no *aux2=BuscaID(lista,id2);
    pos a1;
    if(aux2!=lista){
        a1.variavel=id1;
        a1.indice=aux2->elemento.indice;
        a1.qtd=aux2->elemento.qtd;
        InserirInicio(listaAtribuicoes,a1);
    }
    AjustaOver(lista,TAM);
}

void ProcessaInstrucao(char *s,no *lista,int *TipoHeap,no *listaAtribuicoes,int *UltimoIndiceOcupado){

    if(strncmp(s,"heap",4)==0){ /// <set_heap> ::= 'heap { 'first | 'best | 'worst | 'next }
        char letra;
        letra=s[5];
        switch(letra){
        case 'f':
            *(TipoHeap)=1;
            break;
        case 'n':
            *(TipoHeap)=2;
            break;
        case 'b':
            *(TipoHeap)=3;
            break;
        case 'w':
            *(TipoHeap)=4;
            break;
        }

    }else if(strncmp(s,"new",3)==0){ /// <new> ::= 'new <id> <number>
        char id;
        int numero, tamSubstring;
        char subs[5],num[1];
        tamSubstring=OrdemNum(s)+1;
        id=s[4];
        if(tamSubstring>1){ //Se no <number> for maior que 9
             memcpy(subs,s+6,sizeof(char)*tamSubstring);
             numero=atoi(subs);
        }else{ //
            num[0]=s[6];
            numero=atoi(num);
        }
        if(PosSuficiente(lista,TAM,numero)==1){
            InsereHeap(lista,TipoHeap,id,numero,UltimoIndiceOcupado);
            *(UltimoIndiceOcupado)=IndicePorID(lista,id);
        }

    }else if(strncmp(s,"del",3)==0){ /// <del> ::= 'del <id>
        char id;
        id=s[4];
        RemoveHeap(lista,id);

    }else if(strncmp(s,"exibe",5)==0){ /// <exibe> ::= 'exibe
        ImprimeHeap(lista);

    }else{ ///<atribui> ::= <id> '= <id>
        char id1, id2;
        id1=s[0];
        id2=s[4];
        Atribui(lista,listaAtribuicoes,id1,id2);
    }
}

int menu(){
    int resp;
    printf("[0] Sair\n[1] Abrir arquivo com instrucoes\n\nDigite: ");
    scanf("%d",&resp);
    return resp;
}

int main(){
    no *lista, *listaAtribuicoes;
    pos Elm;
    char string[11],nomeArq[20];
    int arqlidos=0, resp, tipoHeap=0, UIO, linhaArq=1;
    do{
        lista=CriaLista();
        listaAtribuicoes=CriaLista();
        Elm.indice=0;
        Elm.qtd=TAM;
        Elm.variavel='\n';
        InserirInicio(lista,Elm);
        ImprimirLista(lista);
        UIO=0;
        resp=menu();
        switch(resp){
            case 1:
                printf("Digite o nome do arquivo: ");
                scanf("%s",nomeArq);
                FILE *arq=fopen(nomeArq,"rt");
                if(arq==NULL){
                    printf("Arquivo nao encontrado.\n");
                }else{
                    arqlidos++;
                    while(feof(arq)==0){
                        fgets(string,15,arq);
                        printf("(linha: %d) \tInstrucao: %s\n\n",linhaArq,string);
                        ProcessaInstrucao(string,lista,&tipoHeap,listaAtribuicoes,&UIO);
                        linhaArq++;
                    }
                }
                fclose(arq);
                ImprimirLista(lista);
                lista=DestruirLista(lista);
                printf(".......\n");
                ImprimirLista(listaAtribuicoes);
                listaAtribuicoes=DestruirLista(listaAtribuicoes);
                linhaArq=1;
                break;
        }
    }while(resp!=0);
    if(arqlidos>0){
        lista=DestruirLista(lista);
        listaAtribuicoes=DestruirLista(listaAtribuicoes);
    }
    return 0;
}
