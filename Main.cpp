/********************************************/
/*  Programa de teste da classe Estatística */
/*  Autor: Antonio Ribeiro Alves Junior     */
/*  Matricula: 13305                        */
/*  Data: Abril/2010                        */
/********************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estatistica.h"
#include "Node.h"

int main(){
    Estatistica *e = new Estatistica();
    int data, tam;    
    
    scanf("%i",&tam);
    
    for(int i = 0; i < tam; i++){
        scanf("%i",&data);
        e->cd->insereOrdenado(data);
    }

    e->outliersModerado();
    //e->outliersExtremo();
    e->cd->resetIterator();
/*    data = 0;
    do{
        data++;
	    printf("%i\n",e->cd->retornaAtual());
    }while(e->cd->incrementaIterator()==0);
*/
    printf("Tamanho do Conjunto--> %i\n",e->cd->quantidadeDados);
    printf("Maximo---------------> %i\n",e->max());
    printf("Minimo---------------> %i\n",e->min());
    printf("Media----------------> %f\n",e->media());
    printf("Mediana--------------> %i\n",e->mediana());
    printf("Primeiro Quartil-----> %i\n",e->primeiroQuartil());
    printf("Terceiro Quartil-----> %i\n",e->terceiroQuartil());
    printf("Amplitude Inter Qrt--> %i\n",e->amplitudeInterQuartil());
    printf("Variancia------------> %f\n",e->variancia());
    printf("Desv. Padrao---------> %f\n",e->desvioPadrao());
    printf("Moda-----------------> %i\n",e->moda());
    printf("Desvio Medio---------> %f\n",e->desvioMedio());
    printf("Amplitude------------> %i\n",e->amplitude());
    printf("Coeficiente Variação-> %f\n",e->coeficienteVariacao());
    printf("Sturges--------------> %i\n",e->sturges());


    printf("Histograma-----------> ");
    int* vetor = e->histo();
    for(int i = 0; i < e->sturges(); i++)//e->sturges(); i++)
        cout << vetor[i] << " ";
    cout << endl;

    printf("Acumulado------------> ");
    vetor = e->acumulado();
    for(int i = 0; i < e->sturges(); i++)
        cout << vetor[i] << " ";
    cout << endl;

    printf("Conjunto Dados-------> \n");
    string *texto = e->conjuntoHisto();
    cout << *(texto);
    cout << endl;



    printf("\n");
}


