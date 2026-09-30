/* Nome: Gustavo Cesar Bento Laurindo
   RA: 821402
   AA1 - exercício 6( implementação algoritmo Shellsort )*/

#include <iostream>
using namespace std;

void troca(int L[], int i, int j){ // Função que realiza a troca de elementos de um vetor.
    int aux = L[i]; // Utiliza uma variável auxiliar para guardar o valor de um elemento, e assim, realizar a troca.
    L[i] = L[j]; 
    L[j] = aux; 
}

void Shellshort(int L[], int n){ //Função que deverá executar o algoritmo Shellsort.
    int h;
    h = n / 2; // Divisão inteira utilizada para sequência de Shell.
    while(h>0){ // Esse loop é para executar cada número da sequência de Shell até chegar em 1, que ao ser dividido inteiramente por 2 dá 0.
        for(int i=0;i < n;i=i+h){ // Esse loop é utilizado para reduzir conjuntos de elementos a serem organizados e assim ordená-los primeiro, e assim se repete.
            int aux = i; // O aux é utilizado para não fazer operação sobre i e assim dar erro.
            while(aux >= h && L[aux-h] > L[aux]){ // Compara o elemento pivô com o elemento anterior do conjunto reduzido de elementos. 
                troca(L, aux-h, aux); // Se o elemento anterior for maior que o pivô, faz a troca.
                aux = aux - h; // O elemento anterior vira pivô se for possível.
            }
        }
        h = h / 2; // Realiza novamente a divisão inteira até h for igual a zero.
    }
}

void imprime(int L[], int n){ //Função que imprime o vetor.
    for(int i = 0; i < n; i++){ 
        cout << L[i] << " ";
    }
}





int main()
{
    int L[] = { 29, 12, 3, 7, 2, 17, 4, 19, 42, 31, 20, 15, 10, 9, 16, 8, 1, 13, 21, 5 }; //  O vetor descrito pelo exercício.
    int n = 20; // Quantidade de elementos do vetor L.
    cout << "Antes da ordenação:" << endl;
    imprime(L, n);
    cout << endl;
    cout << "Depois da ordenação:" << endl;
    Shellshort(L, n); // Função chamada para ordenar os elementos do vetor L.
    imprime(L, n);
    

    return 0;
}