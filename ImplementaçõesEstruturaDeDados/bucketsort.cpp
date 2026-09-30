/* Nome: Gustavo Cesar Bento Laurindo
   RA: 821402
   Disciplina: AED2
   Implementação do Bucketsort */

#include <iostream>
using namespace std;
int i=0;

//Cada struct possui low e high para realizar quicksort e um balde. A ideia é fazer n matrizes para n baldes.
typedef struct{
    int *balde = nullptr; //O balde é um vetor.
    int low = 0;
    int high = 0;
} Matriz;

void troca(int &A, int &B){ // Função que realiza a troca de elementos de um vetor.
    int aux = A; // Utiliza uma variável auxiliar para guardar o valor de um elemento, e assim, realizar a troca.
    A = B; 
    B = aux; 
}

//Procura maior valor da lista
float maior(int L[], int n){
    float m = L[0];
    for(i = 1;i < n; i++){
        if(L[i] > m){
            m = L[i];
        }
    }
    return m;
}

//Procura menor valor da lista
float menor(int L[], int n){
    float m = L[0];
    for(i = 1;i < n; i++){
        if(L[i] < m){
            m = L[i];
        }
    }
    return m;
}

int particao(int L[], int low, int high){
    int x;
    x = L[high]; // O pivô é o último elemento do vetor.
    int i;
    i = low - 1; // O i particiona elementos menores que o pivô
    for(int j = low;j < high; j++){
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

//Insere cada elemento no final do balde.
void insere(Matriz &matriz, int numero){
    if(matriz.high == 0){
        matriz.balde = new int[1];
        matriz.balde[matriz.high] = numero;
        matriz.high++;
    }
    else{
        int *aux = new int[matriz.high + 1]; //Para alocação dinâmica utiliza-se um auxiliar e no final atribui balde = aux;
        for(int i=0;i<matriz.high;i++){
            aux[i] = matriz.balde[i];
        }
        aux[matriz.high] = numero;
        matriz.high++;
        delete[] matriz.balde;
        matriz.balde = aux;
    }
}

//Realiza a ordenação, inserindo cada elemento em cada balde, ordenando cada balde e por fim, concatenando os baldes.
void bucketsort(int vet[], int n){
    float index = 0;
    float a = maior(vet, n); 
    float b = menor(vet, n);
    int index_int;
    Matriz *matriz = new Matriz[n]; //Aloca n quantidade de baldes.
    for(int i = 0;i < n; i++){
        index = (vet[i]-b)/(a-b); //Calcula a posição do balde.
        index_int = index; //Converte em inteiro a posição.
        insere(matriz[index_int], vet[i]);
    }
    int aux = 0;
    for(int i=0;i<n;i++){
        if(matriz[i].high>0){
            Quicksort(matriz[i].balde, matriz[i].low, matriz[i].high - 1); //Realiza quicksort em cada balde.
            for(int j=0;j<matriz[i].high;j++){
                vet[aux] = matriz[i].balde[j]; //Concatena todos os baldes.
                aux++;
            }
        }
    }
}

//Imprime o vetor.
void imprime(int vet[], int n){
    for(int i=0;i<n;i++){
        cout << vet[i] << " ";
    }
    cout << endl;
}

int main()
{
    int vet[] = {29, 12, 3, 7, 2, 17, 4, 19, 42, 31, 20, 15, 10, 9, 16, 8, 1, 13, 21, 5};
    cout << "Antes:" << endl;
    imprime(vet, 20);
    bucketsort(vet, 20);
    cout << "Depois:" << endl;
    imprime(vet, 20);

    return 0;
}