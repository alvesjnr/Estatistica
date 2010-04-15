/********************************************/
/*  ConjuntoDados.h                         */
/*  Autor: Antonio Ribeiro Alves Junior     */
/*  Matricula: 13305                        */
/*  Data: Abril/2010                        */
/********************************************/


#ifndef _CONJUNTO_DADOS_H
#define _CONJUNTO_DADOS_H

#include <stdlib.h>
#include "Node.h"

typedef int DADO;

class ConjuntoDados{
public:
    int quantidadeDados;
private:
	Node *primeiro;
	Node *ultimo;
	Node *iterator;

	void insereFim(Node *novo){
	    ultimo->proximo = novo;	    	    
	    ultimo = novo;
	}

	void insereInicio(Node *novo){
	    novo->proximo = primeiro;
	    primeiro = novo;
	}

	void insereMeio(Node *novo){
	    Node *trash,*aux;
	    trash = primeiro;
	    aux = trash->proximo;
	    while(aux->peso < novo->peso){
		trash = aux;
		aux = aux->proximo;
	    }					//retorna [trash]->[aux]
	    trash->proximo = novo;
	    novo->proximo = aux;
	}

public:
    ConjuntoDados(){
	primeiro = NULL;
	ultimo = NULL;
	quantidadeDados = 0;
        iterator = NULL;
    }
    int insereOrdenado(int i){
        Node *novo = new Node;
        novo->peso = i;
        if(quantidadeDados==0){
    	    primeiro = ultimo = novo;
	    ultimo->proximo = NULL;
         }else{
            if(primeiro->peso > novo->peso)
                insereInicio(novo);
            else if(ultimo->peso <= novo->peso)
                insereFim(novo);
            else
                insereMeio(novo);
        }
        return ++quantidadeDados;
    }

    int retiraDado(Node* ptr){
        Node* it = primeiro;
        int valor;
        if(it == ptr){   //retirar o primeiro
            primeiro = primeiro->proximo;
            valor = it->peso;
            iterator = primeiro;
            quantidadeDados--;
            delete ptr;
            return valor;
        }
        else{           //retirar enésimo
            while(it->proximo != ptr)
                it = it->proximo;       //aponta pro mesmo que ptr

            it->proximo = ptr->proximo;
            valor = ptr->peso;
            delete ptr;            
        }
        if(quantidadeDados > 1)
            iterator = it;
        else
            iterator = primeiro;
        if(it->proximo == NULL)
            ultimo = it;
        quantidadeDados--;
        return valor;
    }

    int retornaAtual(){
        return iterator->peso;
    }

    int incrementaIterator(){
        if(iterator->proximo != NULL){
            iterator = iterator->proximo;
            return 0;		//tem proximo
	}else
	    return 1;		//nao tem
    }

    int resetIterator(){
	iterator = primeiro;
    }

    int hasNext(){
	if(iterator == ultimo)
            return 0;		//não tem proximo
	else
            return 1;		//tem proximo
    }

    int retornaMax(){
        if(ultimo == NULL)
            return 0;
        return ultimo->peso;
    }

    int retornaMin(){
        if(primeiro == NULL)
            return 0;
        return primeiro->peso;
    }

    Node* getIterator(){
	return iterator;
    }
    Node* getInicio(){
        return primeiro;
    }
    Node* getFinal(){
        return ultimo;
    }

};

#endif
