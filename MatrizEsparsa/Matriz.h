#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#include <iostream>
#include <string>

struct Node;

class Matriz {
private:

  Node *head;

  int linhas;
  int colunas;

//double** M;
public:
   // Construtor
    Matriz();

    ~Matriz();

    void lerMatriz(std::string DadosMatrizEsparsa);

    void criarMatriz(int l,int c);

    void imprime();

    void insere(int i, int j, double v);

    Matriz *soma(Matriz *B);

    Matriz *multiplica(Matriz *B);


};

#endif // MATRIZ_H_INCLUDED
