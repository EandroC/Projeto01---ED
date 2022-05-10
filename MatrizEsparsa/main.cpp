#include "Matriz.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
std::cout<<"DIGITE:\n"<<
    "lerarquivo    - cria uma matriz com os indices e elementos passados por um arquivo\n"<<
    "criar         - para criar uma nova matriz\n"<<
    "add           - para adicionar um novo elemento dentro da matriz\n"<<
    "imprimir      - para exibir os elementos dentro de uma matriz já criada\n"<<
    "multiplica    - para multiplicar duas matrizes e exibir em outra matriz\n"<<
    "soma          - para somar duas matrizes e exibir em outra matriz\n"<<
    "exit          - para terminar de manipular programa.\n"<<"\n";

    vector<Matriz*> listaMatrizes;

    while(true) {
		string cmd;
		getline(cin, cmd);
		//cria e ler os elementos de uma nova matriz
        if(cmd == "lerarquivo") {
            Matriz *M = new Matriz;
			listaMatrizes.push_back( M );

            if(M != nullptr) cout << "Matriz " <<  listaMatrizes.size()-1 << " foi criada" << endl;

            int k= listaMatrizes.size()-1;

            listaMatrizes[k]->lerMatriz("DadosMatrizEsparsa.txt");
		}
		// criar uma nova matriz
		if(cmd == "criar") {
            Matriz *M = new Matriz;
			listaMatrizes.push_back( M );

            std::cout<<"Quantidade de linhas da matriz:\n";
            int i;
			std::cin>>i;

            std::cout<<"Quantidade de colunas da matriz:\n";
            int j;
			std::cin>>j;

			int k= listaMatrizes.size()-1;
			listaMatrizes[k]->criarMatriz(i,j);
            if(M != nullptr) cout << "Matriz " <<  listaMatrizes.size()-1 << " foi criada" << endl;
		}
		//adionar elementos em uma matriz
         else if(cmd == "add") {
            std::cout<<"A matriz que deseja adicionar o elemento:\n";
            int k;
			std::cin>>k;

			std::cout<<"Indice da linha:\n";
			int i;
			std::cin>>i;

			std::cout<<"Indice da coluna:\n";
			int j;
			std::cin>>j;

			std::cout<<"Valor:\n";
			int v;
			std::cin>>v;

            if(k<=listaMatrizes.size()-1){
                listaMatrizes[k]->insere(i,j,v);
                cout << v << " adicionado na Matriz " << k << endl;
			}
			else{
                cout << "Matriz "<<k<< " não foi encontrada."<< endl;
			}
		}
		//imprimir duas matrizes
		else if(cmd == "imprimir") {

            std::cout<<"A matriz que deseja exibir:\n";
            int k;
			std::cin>>k;

			if(k<=listaMatrizes.size()-1){
                listaMatrizes[k]->imprime();
			}
			else{
                cout << "Matriz "<<k<< " não foi encontrada."<< endl;
			}
		}
		//multiplica duas matrizes
        else if(cmd  == "multiplica") {
            std::cout<<"Primeira matriz:\n";
			int p;
			std::cin>>p;

			std::cout<<"Segunda matriz:\n";
            int q;
            std::cin>>q;

            if(p<=listaMatrizes.size()-1 && q<=listaMatrizes.size()-1){
               listaMatrizes[p]->multiplica(listaMatrizes[q]);
            }
            else{
                if(p>listaMatrizes.size()-1){
                    cout << "Matriz "<<p<< " não foi encontrada."<< endl;
                }
                if(q>listaMatrizes.size()-1){
                    cout << "Matriz "<<q<< " não foi encontrada."<< endl;
                }
			}

		}
		//soma duas matrizes
		 else if(cmd  == "soma") {
            std::cout<<"Primeira matriz:\n";
			int p;
			std::cin>>p;

			std::cout<<"Segunda matriz:\n";
            int q;
            std::cin>>q;

            if(p<=listaMatrizes.size()-1 && q<=listaMatrizes.size()-1){
               listaMatrizes[p]->soma(listaMatrizes[q]);
            }
            else{
                if(p>listaMatrizes.size()-1){
                    cout << "Matriz "<<p<< " não foi encontrada."<< endl;
                }
                if(q>listaMatrizes.size()-1){
                    cout << "Matriz "<<q<< " não foi encontrada."<< endl;
                }
			}
        //finaliza o programa
		}else if(cmd == "exit") {
			for(int i = 0; i < listaMatrizes.size(); ++i) {
				delete listaMatrizes[i];
				listaMatrizes[i] = nullptr;
			}
			listaMatrizes.clear();
			break;
		}
    }

}
