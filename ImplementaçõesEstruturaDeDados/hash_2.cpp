/* Nome: Gustavo Cesar Bento Laurindo
   RA: 821402
   TRABALHO 2 AED2: HASH TABLE */

//PARTE B
//Obs: Para todos os casos considerei h'(k) = k mod m

/*A ideia é fazer um array de struct como hash table, em que tem ponteiro para a chave, para que
em caso de remoção bastaria colocar como nullptr. */

#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct hash_b{
    int *key; 
    hash_b(){ 
        key = nullptr;
    }
}hash_b;

//As 3 funções já englobam os 3 tipos de sondagem, por meio do uso do switch para probing.
/* Os possíveis valores de probing são:
1- linear probing
2- quadratic probing
3- double hashing */

//Insere uma chave na hash table.
void hash_insert(hash_b *z, int key, int const m, int const probing){
    int aux = key % m; // aux = h'(k) = h1(k)
    int aux2 = 1 + (key % 1013); //aux2 = h2(k)
    int position; //position = h(k,i)
    for(int i = 0; i < m; i++){
        switch (probing){ //Calcula a posição de acordo com o tipo de sondagem.
            case 1:
                position = (aux + i) % m;
                break;
            case 2:
                position = (aux + 3*i + 5*i*i) % m;
                break;
            case 3:
                position = (aux + (i * aux2)) % m;
                break;
        }
        if(z[position].key == nullptr){ //Se estiver vazio na posição calculada, a chave é inserida.
            z[position].key = new int;
            *(z[position].key) = key;
            break;
        }
    }
}

//Busca uma chave na hash table.
int hash_search(hash_b *z, int key, int const m, int const probing, int *acesso){
    int aux = key % m; // aux = h'(k) = h(k)
    int aux2 = 1 + (key % 1013); //aux2 = h2(k)
    int position; //position = h(k,i)
    *acesso = 0;
    for(int i = 0; i < m; i++){
        switch (probing){ //Calcula a posição de acordo com o tipo de sondagem.
            case 1:
                position = (aux + i) % m;
                break;
            case 2:
                position = (aux + 3*i + 5*i*i) % m;
                break;
            case 3:
                position = (aux + (i * aux2)) % m;
                break;
        }
        *acesso += 1;
        if(z[position].key != nullptr){ 
            if(*(z[position].key) == key){ //Verifica se a chave procurada está na posição calculada.
                return position;
            }
        }
        else{
            break;
        }
    }
    return -1; //Retorna -1 caso key não pertença à hash table.
}

//Realiza remoção de uma chave em uma hash table.
void hash_delete(hash_b *z, int key, int const m, int const probing){
    int acesso; //Apenas para preencher a função, não será usada no hash_delete.
    int position = hash_search(z, key, m, probing, &acesso); //Procura a chave.
    if(position == -1){
        cout << "Chave não encontrada" << "\n";
        return; //Caso a chave não seja encontrada, encerra a função.
    }
    delete z[position].key; //Caso a chave pertença a hash table, remove e declara o ponteiro nulo.
    z[position].key = nullptr; 
} 

//Insere as 500 chaves.
void insert_500_keys(hash_b *z, int m, int const probing){
    int contador = 0;
    int key;
    int aux;
    int acesso; //Apenas para preencher a função, não será usada no hash_delete.
    while(contador < 500){
        key = rand() % 2000 + 1;
        aux = hash_search(z, key, m, probing, &acesso);
        if(aux == -1){ //Se a chave não pertencer a hash table, insere a chave e incrementa o contador. Com isso, evita-se repetição.
            contador++;
            hash_insert(z, key, m, probing);
        }
    }
}

//Imprime todas as chaves.
void print_all(hash_b *z, int const m){
    for(int i = 0; i < m; i++){
        cout << "Posição " << i << ": ";
        if(z[i].key == nullptr){
            cout << "NIL";
        }
        else{
            cout << *(z[i].key);
        }
        cout << "\n";
    }
}

//Busca as 10 chaves que estão na hash table e as que não estão também
//vet1 é para 10 chaves que estão ou não estão na hash table.
void search_10_keys(hash_b *z, int const m, int vet1[], int probing){
    int acesso = 0; //Nessa função será usada o acesso.
    int position;
    int total = 0;
    for(int i = 0; i < 10; i++){
        position = hash_search(z, vet1[i], m, probing, &acesso);
        cout << "Chave " << vet1[i] << ": " << acesso << " acessos" << "\n";
        total += acesso;
    }
    cout << "A média dos acessos é de: " << total/10.0 << "\n";
}


int main()
{
    int const m = 1019;
    
    //i) Linear Probing
    hash_b *z = new hash_b[m];
    //Inserção das 500 chaves.
    insert_500_keys(z, m, 1);
    //print_all(z, m); //A função foi usada para achar as chaves que pertencem a hash table e está marcada como comentario devido ao tamanho da hash table.
    cout << "PARTE I: LINEAR PROBING" << "\n";
    cout << "Busca por 10 chaves que pertencem à hash table: " << "\n";
    int vet[10] = { 970, 1040, 1088, 1096, 118, 128, 1203, 190 , 260, 1513};
    search_10_keys(z, m, vet, 1);
    cout << "\n" << "Busca por 10 chaves que não pertencem à hash table: " << "\n";
    int vet2[10] = { 2010, 2020, 2030, 2040, 2050, 2060, 2070, 2080, 2090, 2100 };
    search_10_keys(z, m, vet2, 1);
    cout << "\n";
   
    //ii) Quadratic Probing
    hash_b *b = new hash_b[m];
    //Inserção das 500 chaves.
    insert_500_keys(b, m, 2);
    //print_all(b, m); //A função foi usada para achar as chaves que pertencem a hash table e está marcada como comentario devido ao tamanho da hash table.
    cout << "PARTE II: QUADRATIC PROBING" << "\n";
    cout << "Busca por 10 chaves que pertencem à hash table: " << "\n";
    int vet3[10] = { 1960, 1955, 1905, 1859, 837, 790, 1760, 1711, 1463, 1362};
    search_10_keys(b, m, vet3, 2);
    cout << "\n" << "Busca por 10 chaves que não pertencem à hash table: " << "\n";
    int vet4[10] = { 2030, 2040, 2050, 3040, 4050, 5060, 6070, 8080, 7090, 3100 };
    search_10_keys(b, m, vet4, 2);
    cout << "\n";
    
    //iii) Double Hashing
    hash_b *a = new hash_b[m];
    //Inserção das 500 chaves.
    insert_500_keys(a, m, 3);
    //print_all(a, m); //A função foi usada para achar as chaves que pertencem a hash table e está marcada como comentario devido ao tamanho da hash table.
    cout << "PARTE III: DOUBLE HASHING" << "\n";
    cout << "Busca por 10 chaves que pertencem à hash table: " << "\n";
    int vet5[10] = { 1983, 958, 1931, 1054, 1058, 1135, 1184, 1280, 1333, 1419};
    search_10_keys(a, m, vet5, 3);
    cout << "\n" << "Busca por 10 chaves que não pertencem à hash table: " << "\n";
    int vet6[10] = { 5030, 6040, 12050, 30340, 132050, 5342060, 6450, 132080, 4090, 5100 };
    search_10_keys(a, m, vet6, 3);
    cout << "\n";
    

    return 0;
}