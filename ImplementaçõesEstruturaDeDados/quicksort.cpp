/* Nome: Gustavo Cesar Bento Laurindo
   RA: 821402
   AA1 - exercício 5( implementação algoritmo Quicksort )*/

#include <iostream>
using namespace std;

void imprime(int L[], int n){ //Função que imprime o vetor.
    for(int i = 0; i < n; i++){ 
        cout << L[i] << " ";
    }
}

void troca(int &A, int &B){ // Função que realiza a troca de elementos de um vetor.
    int aux = A; // Utiliza uma variável auxiliar para guardar o valor de um elemento, e assim, realizar a troca.
    A = B; 
    B = aux; 
}

int particao(int L[], int low, int high){
    int x;
    x = L[high]; // O pivô é o último elemento do vetor.
    int i;
    i = low - 1; // O i particiona elementos menores que o pivô
    for(int j=low;j<high;j++){
        if(L[j]<=x){ // O j particiona elementos maiores que o pivô, sempre ficando na frente do pivô
            i=i+1;
            troca(L[i], L[j]);
        }
    }
    troca(L[high], L[i+1]); // O pivô fica na posição certa, em que elementos particionados por i ficam atrás e particionados por j ficam na frente.
    return i + 1; // Retorna a posição do pivô
}

void Quicksort(int L[], int low, int high){ // Quicksort é basicamente o particionamento feito sucessivas vezes até ordenar.
    int a;
    if(low < high){ // É a condição de parada quando o vetor(todo ou particionado) já está ordenado.
        a = particao(L, low, high);
        Quicksort(L, low, a-1); 
        Quicksort(L, a+1, high); //Usa-se recursão para particionar sucessivas vezes até ficar ordenado.
    }
}

int main()
{
    int L[] = {29, 12, 3, 7, 2, 17, 4, 19, 42, 31, 20, 15, 10, 9, 16, 8, 1, 13, 21, 5};
    int n = 20; // Quantidade de elementos do vetor L.
    cout << "Antes da ordenação:" << endl;
    imprime(L, n);
    cout << endl;
    cout << "Depois da ordenação:" << endl;
    int high = n - 1; 
    int low = 0;
    Quicksort(L, low, high); // Função chamada para ordenar os elementos do vetor L.
    imprime(L, n);

    return 0;
}

