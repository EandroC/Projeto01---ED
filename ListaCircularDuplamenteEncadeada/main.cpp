#include <iostream>
#include <climits>
#include <vector>
#include "List.h";

#include <sstream>
#include <string>

using namespace std;

int main()
{
    std::cout<<"DIGITE:\n"<<
    "criar     - para criar uma nova lista\n"<<
    "add       - para adicionar um novo elemento no final da lista\n"<<
    "del       - para deletar o último elemento da lista\n"<<
    "insert    - para inserir um elemento na posição desejada da lista\n"<<
    "remove    - para remover a primeira ocorrência de um elemento na lista\n"<<
    "removeall - para remover todas as ocorrências de um elemento na lista\n"<<
    "print     - para exibir os elementos dentro de uma lista já criada\n"<<
    "reverse   - para exibir os elementos na ordem inversa de uma lista já criada\n"<<
    "empty     - verifica se a lista criada possui elementos\n"<<
    "size      - verifica o tamanho de uma lista\n"<<
    "clear     - esvazia uma lista\n"<<
    "concat    - passa os elementos de uma lista para outra lista, depois a esvazia\n"<<
    "copy      - copia os elementos de uma lista para uma nova lista\n"<<
    "addarray  - adiciona um sequência de elemnentos em uma lista já existente\n"<<
    "igual     - verifica se duas listas são iguais\n"<<
    "exit      - para terminar de manipular programa.\n"<<"\n";

    vector<List*> listas;

    while(true) {
		string cmd;
		getline(cin, cmd);

		// criar uma nova lista
		if(cmd == "criar") {
            List *l = new List;
			listas.push_back( l );
            if(l != nullptr) cout << "lista " <<  listas.size()-1 << " foi criada" << endl;
		}
        // adicionar um novo elemento no final da lista
        else if(cmd == "add") {
            std::cout<<"Lista que deseja adicionar o elemento:\n";
            int k;
			std::cin>>k;

			std::cout<<"elemento:\n";
			int x;
			std::cin>>x;

            if(k<=listas.size()-1){
                listas[k]->push_back(x);
                cout << x << " adicionado na lista " << k << endl;
			}
			else{
                cout << "lista "<<k<< " não foi encontrada."<< endl;
			}

		}
        // remove o último elemento da lista
		else if(cmd == "del") {

            std::cout<<"Lista que deseja deleta o último elemento:\n";
            int k;
			std::cin>>k;

			if(k<=listas.size()-1){
                int x=listas[k]->pop_back();
                if(x==INT_MIN){
                    cout << "lista não possui elementos para remover"<< endl;
                }else{
                    cout << x << " removido da lista " << k << endl;
                }
            }
            else{
                cout << "lista "<<k<< " não foi encontrada."<< endl;
			}
		}
		// adicionar um novo elemento no indice desejado da lista
		else if(cmd  == "insert") {
            std::cout<<"Lista que deseja adicionar o elemento:\n";
            int k;
			std::cin>>k;

			std::cout<<"elemento:\n";
			int x;
			std::cin>>x;

            std::cout<<"indice:\n";
            int i;
            std::cin>>i;

            if(k<=listas.size()-1){
                listas[k]->insertAfter(x,i);
            }
            else{
                  cout << "lista "<<k<< " não foi encontrada."<< endl;
			}
		}
		// remove a primeira ocorrência de um elemento na lista
		else if(cmd  == "remove") {
            std::cout<<"Lista que deseja remover o elemento:\n";
            int k;
			std::cin>>k;

			std::cout<<"elemento:\n";
			int x;
			std::cin>>x;

            if(k<=listas.size()-1){
                listas[k]->remove(x);
            }
            else{
                  cout << "lista "<<k<< " não foi encontrada."<< endl;
			}

		}
		// remove a todas as ocorrências de um elemento na lista
		else if(cmd  == "removeall") {
			std::cout<<"Lista que deseja remover o elemento:\n";
            int k;
			std::cin>>k;

			std::cout<<"elemento:\n";
			int x;
			std::cin>>x;

			if(k<=listas.size()-1){
                listas[k]->removeAll(x);
            }
            else{
                  cout << "lista "<<k<< " não foi encontrada."<< endl;
			}
		}
        // exibi os elementos dentro de uma lista
		else if(cmd  == "print") {
			std::cout<<"Lista que deseja exibir os elementos:\n";
            int k;
			std::cin>>k;

			if(k<=listas.size()-1){
                listas[k]->print();
            }
            else{
                cout << "lista "<<k<< " não foi encontrada."<< endl;
			}
		}
        // exibi os elemente na ordem reversa
		else if(cmd  == "reverse") {
            std::cout<<"Lista que deseja exibir os elementos:\n";
            int k;
			std::cin>>k;

			if(k<=listas.size()-1){
                listas[k]->printReverse();
            }
            else{
                  cout << "lista "<<k<< " não foi encontrada."<< endl;
			}
		}
		// empty [k]
		else if(cmd  == "empty") {
			std::cout<<"Lista que deseja verificar se esta vazia:\n";
            int k;
			std::cin>>k;

			if(k<=listas.size()-1){
                if(listas[k]->empty()) cout << "lista " << k << " esta vazia" << endl;
                else cout << "existem elementos na lista " << k << endl;
            }
            else{
                  cout << "lista "<<k<< " não foi encontrada."<< endl;
			}
		}
        // exibir o tamanho da lista
		else if(cmd  == "size") {
            std::cout<<"Lista que deseja verificar o tamanho:\n";
            int k;
			std::cin>>k;

			if(k<=listas.size()-1){
                cout << "cardinalidade da lista " << k << " é = " << listas[k]->size() << endl;
            }
            else{
                  cout << "lista "<<k<< " não foi encontrada."<< endl;
			}
		}
		//esvazia lista
		else if(cmd  == "clear") {
            std::cout<<"Lista que deseja esvaziar:\n";
            int k;
			std::cin>>k;

			if(k<=listas.size()-1){
                listas[k]->clear();
            }
            else{
                  cout << "lista "<<k<< " não foi encontrada."<< endl;
			}

		}
		// concatena uma lista dentro de outra
		else if(cmd  == "concat") {
            std::cout<<"Lista que deseja que receba os elementos:\n";
			int p;
			std::cin>>p;

			std::cout<<"Lista que deseja que seja concatenada na lista "<<p<<"\n";
            int q;
            std::cin>>q;

            if(p<=listas.size()-1 && q<=listas.size()-1){
               listas[p]->concat(listas[q]);
               cout << "elementos da lista " << q << " foram concatenados na lista " << p << endl;
            }
            else{
                if(p>listas.size()-1){
                    cout << "lista "<<p<< " não foi encontrada."<< endl;
                }
                if(q>listas.size()-1){
                    cout << "lista "<<q<< " não foi encontrada."<< endl;
                }
			}

		}
		// faz uma copia de uma lista
		else if(cmd  == "copy") {

            std::cout<<"Lista que deseja copiar:\n";
            int k;
			std::cin>>k;

			if(k<=listas.size()-1){
                List *cp = listas[k]->copy();
                listas.push_back(cp);
                cout << "uma copia da lista " << k <<
                    " foi criada, ela é a lista " << listas.size()-1 << endl;
            }
            else{
                  cout << "lista "<<k<< " não foi encontrada."<< endl;
			}

		}
		//copy array
        else if(cmd  == "addarray") {
            std::cout<<"Lista que deseja adicionar os novos elementos:\n";
            int k;
			std::cin>>k;

            std::cout<<"Digite a quantidade de elementos que deseja adicionar:\n";
			int n;
			std::cin>>n;

			int arr[n];

			for(int i = 0; i < n; i++) {
                std::cout<<"Digite o "<<i+1<<"º elemento\n";
				std::cin>>arr[i];
			}

			if(k<=listas.size()-1){
                listas[k]->copyArray(n,arr);
                cout << "array foi copiado para lista " << k << endl;
            }
            else{
                  cout << "lista "<<k<< " não foi encontrada."<< endl;
			}

		}
		// verifica se duas lista são iguais
		else if(cmd == "igual") {

			std::cout<<"Primeira lista que deseja comparar se é igual:\n";
			int p;
			std::cin>>p;

			std::cout<<"Segunda lista que deseja comparar se é igual:\n";
            int q;
            std::cin>>q;

            if(p<=listas.size()-1 && q<=listas.size()-1){
                bool iguais = listas[p]->equal(listas[q]);
                if(iguais) cout << "listas " << p << " e " << q << " sao iguais" << endl;
                else cout << "listas " << p << " e " << q << " sao diferentes" << endl;
            }
            else{
                if(p>listas.size()-1){
                    cout << "lista "<<p<< " não foi encontrada."<< endl;
                }
                if(q>listas.size()-1){
                    cout << "lista "<<q<< " não foi encontrada."<< endl;
                }
			}

		}
		else if(cmd == "exit") {
			for(int i = 0; i < listas.size(); ++i) {
				delete listas[i];
				listas[i] = nullptr;
			}
			listas.clear();
			break;
		}
    }

    return 0;
}
