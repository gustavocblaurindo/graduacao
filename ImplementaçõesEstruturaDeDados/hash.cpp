/* Nome: Gustavo Cesar Bento Laurindo
   RA: 821402
   TRABALHO 2 AED2: HASH TABLE */

//PARTE A 

/*A ideia é fazer um vetor de structs, contendo lista em cada posição que deve ser mapeada pela função hash, 
e em caso de colisão basta realizar o encadeamento lógico.*/

//A primeira parte é fazer as operações de lista encadeada, assim possibilitando o encadeamento lógico.

#include <iostream>
#include <cstdlib>
using namespace std;

//Struct nó, que possui ponteiros que apontam para a esquerda e direita.
typedef struct Node{
    int key;
    struct Node *right;
    struct Node *left;
    Node(){ //Inicialização do nó
        right = nullptr;
        left = nullptr;
    }
}Node;

//Lista é um array de nós
typedef struct List{
    Node *head;
    int size; 
    List(){ //Inicialização da lista
        head = nullptr;
        size = 0;
    }
}List;

//Insere um nó na lista.
void insert_node(List *x, int key){
    x->size++; //Incrementa o tamanho. 
    if(x->head == nullptr){
        x->head = new Node; 
        x->head->key = key;
        return;
    }
    Node *aux = new Node; //A ideia é chegar até o último nó da lista e inserir o nó novo contendo a chave.
    aux = x->head;
    while(aux->right != nullptr){
        aux = aux->right;
    }
    Node *insert = new Node;
    insert->key = key;
    aux->right = insert;
    insert->right = nullptr;
    insert->left = aux;
}

//Remove um nó da lista.
void delete_node(List *x, int key){
    Node *aux;
    if(x->head == nullptr){
        return; //Se a lista não possui nós, então não tem nada a ser deletado.
    }
    aux = x->head;
    while(aux->key != key && aux != nullptr){
        aux = aux->right;
    }
    if(aux == nullptr){
        return;
    }
    //Reorganizando a lista para possibilitar a remoção do nó
    if(aux->left != nullptr){
        aux->left->right = aux->right; 
    }
    else{
        x->head = aux->right;
    }
    if(aux->right != nullptr){
        aux->right->left = aux->left;
    }
    aux->right = nullptr;
    aux->left = nullptr;
    delete aux;
    x->size--;
}

//Parte A: tabela hash com encadeamento lógico

//Vetor de struct que contém lista, em que cada posição do vetor deve ser mapeado.
typedef struct hash_a{
    List *list; 
    hash_a(){
        list = new List; //Todas as listas estão alocadas.
    }
}hash_a;

//Calcula a função hash da parte A.
int calculate(int key, int m){
    return key % m;
}

//Procura uma chave por meio do uso de hash table.
Node *search_key_a(hash_a z[], int key, int m, int *acesso){
    int position = calculate(key, m);
    *acesso = 0; //Irá realizar a contagem da quantidade de acessos a cada chave
    Node *aux = z[position].list->head;
    while(aux != nullptr && aux->key != key){
        aux = aux->right;
        (*acesso)++;
    }
    if(aux != nullptr){
        (*acesso)++;
    }
    
    return aux;
}

//Insere uma chave na hash table.
void insert_a(hash_a z[], int key, int m){
    int position = calculate(key, m);
    insert_node(z[position].list, key);
}

//Remove uma chave na hash table.
void delete_a(hash_a *z, int key, int m){
    int position = calculate(key, m);
    delete_node(z[position].list, key);
}

//Imprime o tamanho de cada lista e calcula a média.
void print_sizelist(hash_a *z, int m){
    int total = 0;
    for(int i = 0; i < m; i++){
        cout << "Na posição " << i << ", o tamanho é: " << z[i].list->size << "\n";
        total += z[i].list->size;
    }
    cout << "\n" << "A média do tamanho de cada uma das listas encadeadas é de: " << total/(1.0*m) << "\n";
}

//Imprime a tabela toda.
void print_keys(hash_a *z, int m){
    for(int i = 0; i < m; i++){
        cout << "Posição " << i << ": ";
        Node *aux;
        aux = z[i].list->head;
        while(aux != nullptr){
            cout << aux->key << " ";
            aux = aux->right;
        }
        cout << "\n";
    }
}

//Insere as chaves entre 1 a 2000, sem repetição.
void insert_500_keys(hash_a *z, int m){
    int contador = 0;
    int key;
    int acesso; //Apenas para preencher a função, a parte acesso deverá ser utilizado apenas na função seguinte.
    Node *aux;
    while(contador < 500){
        key = rand() % 2000 + 1; //Chave gerada aleatoriamente.
        aux = search_key_a(z, key, m, &acesso); //Caso a chave não esteja na hash table, é inserida e o contador é incrementado, assim evitando a repetição.
        if(aux == nullptr){ 
            contador++;
            insert_a(z, key, m);
        }
    }
}

//Procura 3 chaves presentes na hash table e 3 não pertencentes a hash table.
void search_3_keys(hash_a *z, int m){
    int acesso;
    int is_at_hash_table[] = { 1803, 341, 83 }; //Estão na hash table.
    for(int i = 0; i < 3; i++){
        search_key_a(z, is_at_hash_table[i], m, &acesso);
        cout << "Para o número " << is_at_hash_table[i] << " foram necessários " << acesso << " acessos." << "\n";
    }
    int isnt_at_hash_table[] = { 100, 200, 3000 }; //Não estão na hash table;
    for(int i = 0; i < 3; i++){
        search_key_a(z, isnt_at_hash_table[i], m, &acesso);
        cout << "Para o número não presente na hash table " << isnt_at_hash_table[i] << " foram necessários " << acesso << " acessos " << "para finalizar a busca." << "\n";
    }
    
}

int main()
{
    int m = 43;
    hash_a *z = new hash_a[m];
    
    //Item 1: Inserção de 500 chaves.
    insert_500_keys(z, m);
    
    //Impressão de todas as chaves em uma hash table.-
    //cout << "Todas as chaves: " << "\n";
    //print_keys(z, m); // Está marcado como comentário, pois a impressão no terminal fica muito grande.
    
    //Item 2: Impressão de cada uma das listas encadeadas dos slots e cálculo da média.
    cout << "\n" << "\n" << "Tamanhos de cada lista em uma hash table: " << "\n";
    print_sizelist(z, m);
    cout << "\n" << "\n";
    
    //Item 3 e 4: busca de 3 chaves que estejam presentes na hash table e 3 chaves que não pertencem à hash table.
    search_3_keys(z, m);

    return 0;
}