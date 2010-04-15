/********************************************/
/*  Estatística.h                           */
/*  Autor: Antonio Ribeiro Alves Junior     */
/*  Matricula: 13305                        */
/*  Data: Abril/2010                        */
/********************************************/


#ifndef _ESTATISTICA_H
#define _ESTATISTICA_H

#include "ConjuntoDados.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
using namespace std;


class Estatistica{
public:
    int amplitudeInterQuartil(){
        return terceiroQuartil() - primeiroQuartil();
    }
    ConjuntoDados *cd;
    Estatistica(){
        cd = new ConjuntoDados();
        Node n;
        n.peso = 99;        
    }    
    float media(){
        int tam = cd->quantidadeDados;
        if(tam == 0) return 0.0;
        int soma = 0;
        cd->resetIterator();
        do{ 
            soma += cd->retornaAtual();
        }while(cd->incrementaIterator() == 0);
        return (float)soma/(float)tam;
    }

    int mediana(){
	cd->resetIterator();
        if(cd->quantidadeDados == 0) 
            return 0;
        int halfTam = cd->quantidadeDados/2;
        for(int i = 0; i < halfTam; i++)
            cd->incrementaIterator();
        return cd->retornaAtual();
    }

    int max(){
        return (cd->retornaMax());
    }
    int min(){
        return cd->retornaMin();
    }
    float variancia(){
        if(cd->quantidadeDados == 0)
            return 0;
        int _media = media();
        int var, acumulado = 0;
        cd->resetIterator();
        do{
            var = cd->retornaAtual();
            var = var-_media;
            var = var*var;
            acumulado += var;
        }while(cd->incrementaIterator() == 0);
        
        return (float)acumulado/(float)cd->quantidadeDados;        
    }

    float desvioPadrao(){
        return sqrt(variancia());
    }

    int primeiroQuartil(){
	cd->resetIterator();
        if(cd->quantidadeDados == 0) 
            return 0;
        int halfTam = cd->quantidadeDados/4;
        for(int i = 0; i < halfTam; i++)
            cd->incrementaIterator();
        return cd->retornaAtual();
    }

    int terceiroQuartil(){
        cd->resetIterator();
        if(cd->quantidadeDados == 0) 
            return 0;
        int halfTam = cd->quantidadeDados/4*3;
        for(int i = 0; i < halfTam; i++)
            cd->incrementaIterator();
        return cd->retornaAtual();
    }

    int moda(){	
	int preModa = 0;
	int contPreModa = 0;
	int contModaAtual = 0;
	int valorAtual = 0;	
	
	if(cd->quantidadeDados == 0)
	    return 0;
	cd->resetIterator();	
	
	do{	    
	    if(valorAtual == cd->retornaAtual()){
		contModaAtual ++;
	    }
	    else{
		if(contModaAtual >= contPreModa){
		    contPreModa = contModaAtual;
		    preModa = valorAtual;	
		    contModaAtual = 0;
		}
		valorAtual = cd->retornaAtual();	
	    }	    	    
	}while(cd->incrementaIterator() == 0);
	if(contModaAtual >= contPreModa){
	    contPreModa = contModaAtual;
	    preModa = valorAtual;
	}
	return preModa;
    }

    float desvioMedio(){
        int _media;
        float acumulado = 0;
        _media = media();
        cd->resetIterator();

        do{
            acumulado += (float)abs(cd->retornaAtual() - _media);
        }while(cd->incrementaIterator() == 0);
        acumulado /= (float)cd->quantidadeDados;
        return acumulado;
    }
    int amplitude(){
        return cd->retornaMax() - cd->retornaMin();
    }
    float coeficienteVariacao(){
        return desvioMedio() / media();
    }

    int sturges(){      //retorna a quantidade de grupos a se dividir
        float k;
        k = 1 + 3.3*log10(cd->quantidadeDados);        
        k += 0.5;
        return (int)k;
    }

    int *histo(){
        return histo(sturges());
    }
    int *histo(int k){
        int *vetor = new int[k];
        int contador = 0;
        int indiceVetor = 0;
        int contadorGeral = 0;
        int ceil;

        ceil = cd->getFinal()->peso+1;
        
        cd->resetIterator();
        do{            
            if((float)cd->retornaAtual() <= ((float)ceil/(float)k * (float)(indiceVetor + 1))){
                contador ++;
                contadorGeral ++;
                cd->incrementaIterator();
            }
            else{
                vetor[indiceVetor] = contador;
                indiceVetor ++;
                contador = 0;
            }                                    
            if(contadorGeral >= cd->quantidadeDados){
                vetor[k-1] = contador;
                break;
            }
        }while(cd->getIterator() != NULL);
        return vetor;
    }
    int *acumulado(){
        return acumulado(sturges());
    }
    int *acumulado(int k){
        int *_histo, *vetor;

        _histo = histo(k);
        vetor = acumulado(_histo, k);
        
        delete _histo;
        return vetor;
    }

    int *acumulado(int* _histo, int tam){
        int i, _acumulado;
        int *vetor;
        _acumulado = 0;
        vetor = new int[tam];

        for(i = 0; i < tam; i++){
            _acumulado += _histo[i];
            vetor[i] = _acumulado;
        }       
        return vetor;
    }

    void outliers(float mult){
        float min, max;
        int debug = 0;
        min = primeiroQuartil() - mult * amplitudeInterQuartil();
        max = terceiroQuartil() + mult * amplitudeInterQuartil();
        cd->resetIterator();
        do{
            
            if(cd->retornaAtual() > max || cd->retornaAtual() < min){
                cout << "Retirado: " << cd->retornaAtual() << endl;
                cd->retiraDado(cd->getIterator());
                //cd->resetIterator();
            }
            if(cd->getIterator() == NULL)
                break;
        }while(cd->incrementaIterator() == 0);
        
    }

    void outliersModerado(){
        outliers(1.5);
    }
    void outliersExtremo(){
        outliers(3.0);
    }
    string *conjuntoHisto(){
        return conjuntoHisto(sturges());
    }
    string *conjuntoHisto(int k){
        string *conjunto = new string();
        char buffer[10];        
        int indiceVetor = 0;
        int contadorGeral = 0;
        int ceil;

        ceil = cd->getFinal()->peso+1;

        cd->resetIterator();
        do{
            if((float)cd->retornaAtual() <= ((float)ceil/(float)k * (float)(indiceVetor + 1))){
                contadorGeral ++;
                sprintf(buffer,"%d ",cd->retornaAtual());
                conjunto->append(buffer);
                cd->incrementaIterator();
            }
            else{
                conjunto->append("\n");
                indiceVetor++;
            }
            if(contadorGeral >= cd->quantidadeDados){
                break;
            }
        }while(cd->getIterator() != NULL);
        return conjunto;
    }
};//class Estatistica

#endif
