/* Nome: Gustavo Cesar Bento Laurindo
   RA: 821402
   Questão 2: Radixsort
*/

#include <iostream>
using namespace std;
int i = 0;

//Função que ordena o elemento de acordo com cada posição do dígito(unidade, dezena, centena, etc...)
void countingsort_R(int L[], int n, int d){
    int *S = new int[n]();
    int m = (L[0] / d) % 10;
    for(i = 1; i < n; i++){
        if((L[i]/d) % 10 > m){
            m = (L[i]/d) % 10; //Encontra o maior número da posição do dígito.
        }
    }
    int *C = new int[m+1];
    for(i = 0; i < n; i++){
        C[(L[i]/d) % 10] += 1; //Histograma.
    }
    for(i = 1; i < m + 1; i++){
        C[i] += C[i-1]; //Soma acumulada.
    }
    for(i = n-1; i >= 0; i--){
        C[(L[i]/d) % 10] -= 1; //Encontra o índice ideal do elemento da lista.
        S[C[(L[i]/d) % 10]] = L[i]; //Coloca o elemento da lista na posição idel para ordenação.
    }
    for(i = 0; i < n; i++){
        L[i] = S[i]; //Atualiza a lista.
    }
}

//Busca o maior elemento da lista.
int maior(int L[], int n){
    int maior = L[0];
    for(i = 1; i < n; i++){
        if(L[i] > maior){
            maior = L[i];
        }
    }
    return maior;
}

//A função countingsort_R é realizada de acordo com a quantidade de dígitos que o maior número da lista possui.
void radixsort(int L[], int n){
    int m = maior(L, n);
    int d = 1;
    while(m/d > 0){
        countingsort_R(L, n, d);
        d = d * 10; // Ordena em unidades, depois dezena, centena, etc.
    }
}

//Imprime o vetor.
void imprime(int L[], int n){
    for(i = 0; i < n; i++){
        cout << L[i] << " ";
    }
    cout << endl;
}



int main()
{
    int n = 20;
    int L[] = { 29, 125, 391, 74, 213, 178, 43, 19, 424, 131, 120, 158, 105, 92, 169, 81, 1, 143, 210, 51 };
    cout << "Antes:" << endl;
    imprime(L, n);
    radixsort(L, n);
    cout << "Depois:" << endl;
    imprime(L, n);
    
    
    
    return 0;
}