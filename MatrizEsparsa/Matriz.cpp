#include "Matriz.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct Node{
    Node* direita;
    Node* abaixo;
    int linha;
    int coluna;
    double valor;
};

Matriz::Matriz(){
    head=new Node;
    head->direita=head;
    head->abaixo=head;
    head->linha=-1;
    head->coluna=-1;
}

Matriz::~Matriz(){

    Node *nodeLinha = head->abaixo;
    Node *nodeColuna = head->direita;
    //se a matriz não estiver vazia
    if(nodeColuna != head && nodeLinha != head){

        Node *aux;
        Node *t;
        //for vai funcionar enquanto l for menor ou igual ao total de linhas da matriz
        for(int l = 1; l <= linhas; l++){
            //movimenta a linha para direita
            aux = nodeLinha->direita;
            //for vai funcionar enquanto c for menor ou igual ao total de colunas da matriz
            for(int c = 1; c <= colunas; c++){
                //condição para achar as posições que possuem elementos e que estão no node
                if(aux->linha == l && aux->coluna == c){
                    delete aux;
                    aux = t;
                    t = aux->direita;
                }
            }
            nodeLinha = nodeLinha->abaixo;

        }
    }

    //após o processo apaga o head
    delete head;

    std::cout<<"Lista deletada\n";
}

void Matriz::criarMatriz(int l,int c){
    //definio tamanho da matriz
    this->linhas=l;
    this->colunas=c;

    Node *aux=head;
    //definir novos heads da linha
    for(int i=0;i<l;i++){
        Node *novo=new Node;
        novo->linha=-1;
        novo->coluna=i+1;
        aux->abaixo=novo;
        novo->direita=novo;
        novo->valor=-333;
        aux=novo;
    }
    aux->abaixo=head;

    aux=head;
    //definir novos heads da coluna
    for(int i=0;i<c;i++){
        Node *novo=new Node;
        novo->coluna=-1;
        novo->linha=i+1;
        aux->direita=novo;
        novo->abaixo=novo;
        novo->valor=-999;
        aux=novo;
    }

    aux->direita=head;

}

vector<string> splitString(const string& str, char virgula){

    //variavel que guardará temporariamente cada numero que será "quebrado" da linha
    string aux;

    //vector que receberá a  lista de elemento da linha
    vector<string> dados;
    stringstream valor(str);

    if(str == ""){
        return dados;
    }

    //laço que vai pegar cada elemento quebrado da linha do arquivo e inserir no vector dados
    while (getline(valor, aux, virgula)){
        dados.push_back(aux);
    }
    return dados;
}

void Matriz::lerMatriz(std::string DadosMatrizEsparsa){


    ifstream arquivo; //abre o arquivo para leitura
    arquivo.open("DadosMatrizEsparsa.txt");

    //se o arquivo for aberto
    if(arquivo.is_open()){

        string length;
        //ler a linha
        getline(arquivo,length);

        //variavéis que serão pegas durante a leitura da primeira linha do arquivo
        int linhaMatriz,colunaMatriz;

        //variavel que recebera dois elementos:linhaMatriz e colunaMatriz
        vector<string> dadosDaLinha= splitString(length,', ');

        //passa cada elemento de dadosDaLinha para sua variavel respectiva, usando stoi para remover a virgula
        linhaMatriz= std::stoi(dadosDaLinha.at(0));
        colunaMatriz= std::stoi(dadosDaLinha.at(1));

        //função que inicia a matriz
        criarMatriz(linhaMatriz,colunaMatriz);
        dadosDaLinha.clear();
        int indiceLinha,indiceColuna;
        double valor;

        //laço que executará enquanto houverem linhas para serem lidas
        while(!arquivo.eof()){

            string line = "";

            //ler a linha do arquivo
            getline(arquivo,line);

            if(line=="") break;
            //recebera tres elementos:indiceLinha, IndiceColuna e valor
            dadosDaLinha =splitString(line,', ');

            //passa cada elemento de dadosDaLinha para sua variavel respectiva, usando stoi para remover a virgula
            indiceLinha= std::stoi(dadosDaLinha.at(0));
            indiceColuna= std::stoi(dadosDaLinha.at(1));
            valor= std::stod(dadosDaLinha.at(2));

            this->insere(indiceLinha,indiceColuna,valor);

        }

        //fecha o arquivo
        arquivo.close();

        cout<<"Dados adicionados na matriz\n";

    }else{
        cout<<"Não foi possivel abrir o arquivo\n";
    }

}

void Matriz::insere( int i, int j, double value){
    //cria o um novo para colocar os valores i,j e value
    Node *novo = new Node;
    novo->linha = i;
    novo->coluna = j;
    novo->valor = value;

    Node *nodeLinha = head->abaixo;

    //cont será incrementado até que nodeLinha chegue na linha desejada
    int contador = 1;
    while(nodeLinha != head){
        if(contador == novo->linha){
        break;
        }
        contador++;
        nodeLinha = nodeLinha->abaixo;
    }

    //cont será incrementado até que nodecoluna chegue na coluna desejada
    Node *nodeColuna = head->direita;
    contador = 1;
    while(nodeColuna!=head){
        if(contador == novo->coluna){
            break;
        }
        contador++;
        nodeColuna = nodeColuna->direita;
    }

    Node *aux;
    //se a linha não  tiver nenhum elemento
    if(nodeLinha->direita == nodeLinha){
        nodeLinha->direita = novo;
        novo->direita = nodeLinha;
    }
    //se a linha tiver elementos
    else{

        aux = nodeLinha;
        //move a linha até posição desejada
        while(aux->direita != nodeLinha){
            //move o aux para a posição anterior a posição desejada
            if(aux->direita->coluna < novo->coluna){//aqui
                aux = aux->direita;
            }else{
                break;
            }
        }
        //processos de inserir na posição da linha
        //inserir no final da linha
        if(aux->direita == nodeLinha){
            aux->direita = novo;
            novo->direita = nodeLinha;
            //break;
        }
        //numa posição já inserida
        else if(aux->direita->linha==novo->linha&&aux->direita->coluna==novo->coluna){
            delete novo;
            return;
        }
        //inserir entre dois nos na linha
        else if(aux->direita->coluna > novo->coluna){
            Node* t = aux->direita;
            aux->direita = novo;
            novo->direita = t;
            //break
        }
    }
    //coluna não possuir elementos
    if(nodeColuna->abaixo == nodeColuna){
        nodeColuna->abaixo = novo;
        novo->abaixo = nodeColuna;
    }
    else{
        aux = nodeColuna;
        //move a coluna até a posição desejada
        while(aux->abaixo != nodeColuna){
            if(aux->abaixo->linha < novo->linha){
                aux = aux->abaixo;
            }else{
                break;
            }
        }
          //processos de inserir na posição da coluna
         //inserir no final da coluna
            if(aux->abaixo == nodeColuna){
                aux->abaixo = novo;
                novo->abaixo = nodeColuna;
                //break;
            }
            //numa posição já inserida
            else if(aux->direita->linha==novo->linha&&aux->direita->coluna==novo->coluna){
                delete novo;
                return;
            }
            //inserir entre dois nos na coluna
            else if (aux->abaixo->linha > novo->linha){
                Node *t = aux->abaixo;
                aux->abaixo = novo;
                novo->abaixo = t;
            }
        //}
    }
}
void Matriz::imprime(){
    Node *nodeLinha = head->abaixo;
    Node *nodeColuna = head->direita;
    //se a matriz não estiver vazia
    if(nodeColuna != head && nodeLinha != head){

        Node *aux;
        //for vai funcionar enquanto l for menor ou igual ao total de linhas da matriz
        for(int l = 1; l <= linhas; l++){
            //movimenta a linha para direita
            aux = nodeLinha->direita;
            //for vai funcionar enquanto c for menor ou igual ao total de colunas da matriz
            for(int c = 1; c <= colunas; c++){
                //condição para achar as posições que possuem elementos e que estão no node
                if(aux->linha == l && aux->coluna == c){
                    cout << aux->valor<<"\t";
                    aux = aux->direita;
                }
                else {
                    //caso não ache exibe 0
                    cout << 0 << "\t";
                }
            }

            nodeLinha = nodeLinha->abaixo;
            cout<<"\n";
        }
    }
}

Matriz *Matriz::multiplica(Matriz *B){
    Matriz novaMatriz;

    Node *nodeLinhaA = head->abaixo;
    Node *nodeColunaA = head->direita;

    Node *nodeLinhaB = B->head->abaixo;
    Node *nodeColunaB = B->head->direita;

    int i,j;

    if(this->linhas>=B->linhas){
        i=this->linhas;
    }else{
        i=B->linhas;
    }

    if(this->colunas>=B->colunas){
        j=this->colunas;
    }else{
        j=B->colunas;
    }

    novaMatriz.criarMatriz(i,j);


    if((nodeColunaA != head && nodeLinhaA != head)&&(nodeLinhaB != B->head && nodeLinhaB != B->head)){
        Node *auxA;
        Node *auxB;
        //for vai funcionar enquanto l for menor ou igual ao total de linhas da matriz
        for(int l = 1; l <= linhas&&l<=B->linhas; l++){
            //movimenta a linha para direita
            auxA = nodeLinhaA->direita;
            auxB = nodeLinhaB->direita;

            //for vai funcionar enquanto c for menor ou igual ao total de colunas da matriz
            for(int c = 1; c <= colunas&&c<=B->colunas; c++){
                //condição para achar as posições que possuem elementos e que estão no node
                if((auxA->linha == l && auxA->coluna == c) && (auxB->linha == l && auxB->coluna == c)){
                    double valor = auxA->valor*auxB->valor;
                    novaMatriz.insere(l,c,valor);
                }
            }
            nodeLinhaA = nodeLinhaA->abaixo;
            nodeLinhaB = nodeLinhaB->abaixo;
        }
    }
    cout<<"\n";
    novaMatriz.imprime();
}

Matriz *Matriz::soma(Matriz *B){
    Matriz novaMatriz;

    Node *nodeLinhaA = head->abaixo;
    Node *nodeColunaA = head->direita;

    Node *nodeLinhaB = B->head->abaixo;
    Node *nodeColunaB = B->head->direita;

    int i,j;

    if(this->linhas>=B->linhas){
        i=this->linhas;
    }else{
        i=B->linhas;
    }

    if(this->colunas>=B->colunas){
        j=this->colunas;
    }else{
        j=B->colunas;
    }

    novaMatriz.criarMatriz(i,j);


    if((nodeColunaA != head && nodeLinhaA != head)&&(nodeLinhaB != B->head && nodeLinhaB != B->head)){
        Node *auxA;
        Node *auxB;
        //for vai funcionar enquanto l for menor ou igual ao total de linhas da matriz
        for(int l = 1; l <= linhas&&l<=B->linhas; l++){
            //movimenta a linha para direita
            auxA = nodeLinhaA->direita;
            auxB = nodeLinhaB->direita;

            //for vai funcionar enquanto c for menor ou igual ao total de colunas da matriz
            for(int c = 1; c <= colunas&&c<=B->colunas; c++){
                //condição para achar as posições que possuem elementos e que estão no node
                if((auxA->linha == l && auxA->coluna == c) && (auxB->linha == l && auxB->coluna == c)){
                    double valor = auxA->valor+auxB->valor;
                    novaMatriz.insere(l,c,valor);
                }else{
                    if(auxA->linha == l && auxA->coluna == c){
                        double valor = auxA->valor+0;
                        novaMatriz.insere(l,c,valor);
                    }else{
                        double valor = auxB->valor+0;
                        novaMatriz.insere(l,c,valor);
                    }
                }
            }
            nodeLinhaA = nodeLinhaA->abaixo;
            nodeLinhaB = nodeLinhaB->abaixo;
        }
    }
    cout<<"\n";
    novaMatriz.imprime();
}
