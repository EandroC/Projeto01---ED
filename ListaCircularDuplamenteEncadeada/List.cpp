#include <iostream>
#include <climits>

#include "List.h"


struct node{
    int valor;
    node* proximo;
    node* anterior;
};

List::List(){
    //inicializa o head e faz ele apontar para ele mesmo
    head = new node;
    head->proximo=head;
    head->anterior=head;
}

List::~List(){
    //verifica se a lista esta vazia
    if(!this->empty()){

        node* aux = head->proximo;
        node* t = aux->anterior;

        //deleta node por node
        while(aux!=head){
            delete aux;
            aux = t;
            t = aux->anterior;
        }
    }

    //após o processo apaga o head
    delete head;

    std::cout<<"Lista deletada\n";
}

void List::push_back(int key){
    //é criado um novo node com valor igual a key passada
    node* novo = new node;
    novo->valor = key;

    //um node auxiliar é criado para ajudar na alocação na lista
    node* aux = head->anterior;

    //alocação do novo node na lista
    aux->proximo = novo;
    head->anterior = novo;
    novo->proximo = head;
    novo->anterior = aux;
}

int List::pop_back(){
    if(!this->empty()){
        //dois nodes são criados um pegando o ultimo node e outro o penultimo
        node* ultimo = head->anterior;
        node* penultimo = ultimo->anterior;

        //variavel que irá armazenar o valor removido
        int valorRemovido = ultimo->valor;

        //ultimo node e consequentemente ultimo valor é removido
        delete ultimo;

        //faz o penultimo apontar para head e manter o circulo
        penultimo->proximo=head;
        head->anterior=penultimo;

        //retorna o valor removido
        return valorRemovido;
    }
    //retorna o menor valor possivel se a lista estiver vazia
    return INT_MIN;
}

void List::insertAfter(int key, int k){
   //variavel que se movimentará no laço
   int i=0;
   //node que navegar até o indice desejado
   node* aux = head;

    //condição para saber se o indice esa correto
    if(k >=0 && k<=size()){

        //laço
        while(i<=k){
            aux=aux->proximo;
            i++;
        }

        //novo node com a key
        node* novo = new node;
        novo->valor = key;

        //node auxiliar que ajudará na conexão dos nodes
        node* aux2 = aux->anterior;

        //conexão dos nodes
        aux2->proximo = novo;
        aux->anterior = novo;
        novo->proximo = aux;
        novo->anterior = aux2;

        std::cout << key << " adicionado no indice "<<k<<"\n";

    }else{
        std::cout<<"indice incorreto\n";
    }
}

void List::remove(int key){
    //verifica se a lista esta vazia
    if(!empty()){

        //node que irá se movimentar e fazer a nova conexão
        node* aux= head->proximo;

        while(aux != head){
            //condição para achar o elemento que precisa ser excluido
            if(aux->valor==key){
                //refaz a conexão
                aux->anterior->proximo=aux->proximo;
                aux->proximo->anterior=aux->anterior;
                free(aux);
                aux=head;

                std::cout<<key<<" foi removido\n";
                //quebra o laço ápós achar o elemento
                break;
            }
            aux= aux->proximo;
        }
        //executado quando o elemento foi achado na lista
        std::cout<<"elemento não encontrado dentro da lista\n";

    }else{
        std::cout<<"Lista esta vazia";
    }
}

void List::removeAll(int key){
    //variavel que irá informar ser o elemento estava ou não na lista
    bool verifica=false;
    //verifica se a lista esta vazia
    if(!this->empty()){
        //node que irá percorrer
        node *aux = head->proximo;
        while(aux!=head){
            //condição para achar o elemento dentro da lista
            if(aux->valor == key){
                aux->anterior->proximo=aux->proximo;
                aux->proximo->anterior=aux->anterior;
                free(aux);
                aux=head;
                verifica=true;
            }
            aux=aux->proximo;
       }
       //informa se o elemento foi removido ou não
       if(verifica==true){
            std::cout<<key<<" foi removido\n";
       }else{
            std::cout<<"elemento não encontrado dentro da lista\n";
       }
    }else{
        std::cout<<"Lista esta vazia";
    }
}

void List::print(){

    std::cout<<"[";
    //se estiver vazia vai print somente:[]
    if(!empty()){
        //node que irá percorrer
        node* aux= head->proximo;
        while(aux != head){
            //exibe o valor e vai para o proximo valor
            std::cout<<aux->valor;
            aux= aux->proximo;
            //condição para o aparecimento da virgula
            if(aux!=head){
                std::cout<<",";
            }
        }
    }
    std::cout<<"]\n";
}

void List::printReverse(){

    std::cout<<"[";
    //se estiver vazia vai print somente:[]
    if(!empty()){
        //node que irá percorrer
        node* aux= head;
        //percorre até o último elemento da lista
        while(aux->proximo!=head){
            aux=aux->proximo;
        }
        //percorre e exibe inversamente até o primeiro elemento
        while(aux!= head){
            std::cout<<aux->valor;
            aux= aux->anterior;
            //condição para exibir a virgula
            if(aux!=head){
                std::cout<<",";
            }
        }
    }
    std::cout<<"]\n";
}

bool List::empty(){
    //retorna true se o proximo elemento for o head, caso contrario o retorno é false
    return head->proximo==head;
}

int List::size(){
    //verifica se a lista esta vazia
    if(!this->empty()){
        //contador que irá aumentar conforme percorre a lista
        int count= 0;
        //node que irá percorrer a lista
        node *aux = head->proximo;
        //lista é percorrido e o contador incrementado
        while(aux!=head){
            count++;
            aux=aux->proximo;

        }
        //retorna o count
        return count;
    }
    return 0;
}

void List::clear(){
    //verifica se a lista esta vazia
    if(!this->empty()){
        //cria dois nodes um para ir apagando e outro para receber o anterior
        node* aux = head->proximo;
        node* t = aux->anterior;
        //processo de remoção dos nodes
        while(aux!=head){
            delete aux;
            aux = t;
            t = aux->anterior;
        }
    //faz o head apontar para ele mesmo
        head->proximo=head;
        head->anterior=head;

        std::cout << "lista foi esvaziada\n";

    }else{
        std::cout<<"lista já estava vazia\n";
    }
}

void List::concat(List *lst){
    //node que irá percorrer até o ultimo valor da matriz que irá receber os elementos
    node* aux = head->proximo;

    while(aux!=head){
        aux=aux->proximo;
    }

    //chama a função copy para fazer uma copia da função da lista que irá ser concatenada
    List *cp = lst->copy();

    //cria um node que irá receber os dados da copia
    node* t = cp->head;

    //processo para inserir a copia na lista desejada
	t->proximo->anterior = aux->anterior;
    aux->anterior->proximo = t->proximo;
    t->proximo = aux;
    aux->anterior = t;

    //chama uma função que irá remover o head da copia que também foi passado no processo
    auxConcat();

    //limpa a lista que foi concatenada
    lst->clear();
}

void List::auxConcat(){
    //função similar a função de remover, ela terá a função de retirar o head da copia
    if(!this->empty()){
        node* ult = head->anterior;
        node* pen = ult->anterior;

        delete ult;

        pen->proximo=head;
        head->anterior=pen;
    }
}

List *List::copy(){
    //cria uma nova lista
    List *novaLista = new List;

    //node que irá percorrer a lista que irá ser copiada
    node* aux=head->proximo;

    //percorrer a lista que irá se copiada e add o elementos dela na nova lista
    while(aux!=head){
        novaLista->push_back(aux->valor);
        aux=aux->proximo;
    }
    //retorna a nova lista criada
    return novaLista;
}

void List::copyArray(int n, int arr[]){
    //i será incrementado até que chegue no tamanho do array
    for(int i=0;i<n;i++){
        //função que adiciona elemento no final da lista
        push_back(arr[i]);
    }
}

bool List::equal(List *lst){
    //se as duas possuirem o mesmo tamanho continua a verificar
    if(this->size() == lst->size()){
        //criar dois nodes para fazer a comparação
        node* aux= head->proximo;
        node* t = lst->head->proximo;
        //irá percorrer e comparar os elementos dentro de cada uma
        while(aux!=head && t!=head){
            if(t->valor!=aux->valor){
                return false;
            }
            t = t->proximo;
            aux= aux->proximo;
        }
    }else{
        return false;
    }
    //se não tudo sem retornar false é pq é igual então retorna true
        return true;
}

