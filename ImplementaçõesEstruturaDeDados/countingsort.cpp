/* Nome: Gustavo Cesar Bento Laurindo
   RA: 821402
   Questão 1: Countingsort
*/


#include <iostream>
using namespace std;
int i = 0;

//Encontra o maior valor da lista
int max(int L[], int n){
    int maior = L[0];
    for(i = 1; i < n; i++){
        if(L[i] > maior){
            maior = L[i];
        }
    }
    return maior;
}

//Realiza a ordenação do tipo countingsort, que consiste em achar cada indice correto dos elementos da lista.
int* countingsort(int L[], int n){
    int maior = max(L, n);
    int *C = new int[maior+1]();
    int *S = new int[n]();
    for(i = 0; i < n; i++){
        C[L[i]] += 1;  //Realiza histograma.
    }
    for(i = 1; i < maior + 1; i++){
        C[i] += C[i-1]; //Realiza soma acumulada.
    }
    for(i = 0; i < n; i++){
        C[L[i]] -= 1; //Índice do vetor.
        S[C[L[i]]] = L[i]; //Armazena o elemento no índice correto do vetor, ordenando.
    }
    delete[] C;
    return S;
}

//Imprime o vetor.
void printVetor(int L[], int n){
    for(i = 0; i < n; i++){
        cout << L[i] << " ";
    }
    cout << endl;
}


int main()
{
    int n = 20;
    int vet[] = {29, 12, 3, 7, 2, 17, 4, 19, 42, 31, 20, 15, 10, 9, 16, 8, 1, 13, 21, 5};
    int *resultado = countingsort(vet, n);
    cout << "Antes: " << endl;
    printVetor(vet, n);
    cout << "Depois: " << endl;
    printVetor(resultado, n);
    delete[] resultado;

    return 0;
}