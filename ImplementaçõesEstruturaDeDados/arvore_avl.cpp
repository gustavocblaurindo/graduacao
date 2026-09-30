/******************************************************************************
TRABALHO 1: ÁRVORE AVL 
NOME: Gustavo Cesar Bento Laurindo
RA: 821402

*******************************************************************************/

#include <iostream>
using namespace std;

//Struct da árvore AVL
typedef struct tree_avl{
    struct tree_avl *p; //árvore pai
    int key; //chave
    int b; //fator de balanço
    struct tree_avl *left; //nó esquerdo
    struct tree_avl *right; //nó direito
    tree_avl(){ //Construtor da árvore
        key = 0;
        b = 0;
        left = nullptr;
        right = nullptr;
        p = nullptr;
    } 
} tree_avl;

//Todas as operações de rotação retorna o elemento que está na posição em que o nó rotacionado estava. 

//Rotação à esquerda.
tree_avl *left_rotate(tree_avl *x){
    tree_avl *y = x->right; 
    tree_avl *z = y->left;
    x->right = z;
    if(z != nullptr){ 
        z->p = x;
    }
    y->left = x;
    y->p = x->p;
    x->p = y;
    if (y->p != nullptr) {
        if (y->p->left == x) {
            y->p->left = y;
        } 
        else {
            y->p->right = y;
        }
    }
    return y; 
}

//Rotação à direita.
tree_avl *right_rotate(tree_avl *y){
    tree_avl *x = y->left;
    tree_avl *z = x->right;
    y->left = z;
    if(z != nullptr){
        z->p = y;
    }
    x->right = y;
    x->p = y->p;
    y->p = x;
    if (x->p != nullptr) {
        if (x->p->left == y) {
            x->p->left = x;
        } 
        else {
            x->p->right = x;
        }
    }
    return x;
}


//Rotação direita-esquerda.
tree_avl *leftRightRotate(tree_avl *z){
    tree_avl *x = z->left;
    tree_avl *y = left_rotate(x);
    tree_avl *w = right_rotate(z);
    return w;
}

//Rotação esquerda-direita.
tree_avl *rightLeftRotate(tree_avl *z){
    tree_avl *x = z->right;
    tree_avl *y = right_rotate(x);
    tree_avl *w = left_rotate(z);
    return w;
}

//Busca a menor chave da árvore.
tree_avl *tree_Minimum(tree_avl *x){
    while(x->left != nullptr){
        x = x->left;
    }
    return x;
}

//Função que procura um possível sucessor para o nó da árvore, baseado no menor elemento à direita do nó.
tree_avl *successor(tree_avl *x){
    if(x != nullptr){
        return tree_Minimum(x->right);
    }
    else{
        tree_avl *y = x->p;
        while(y != nullptr and x == y->right){
            x = y;
            y = y->p;
        }
        return y;
    }
}

//Busca a chave da árvore.
tree_avl *search_key(tree_avl *z, int key){
    tree_avl *y = z;
    if(y == nullptr){
        return nullptr;
    }
    if(y->key > key){
        return search_key(y->left, key);
    }
    else{
        if(y->key < key){
            return search_key(y->right, key);   
        }
    }
    return y;
}

//Calcula a altura de um nó da árvore.
int height(tree_avl *x){
    if(x == nullptr){
        return 0;
    }
    int left = height(x->left);
    int right = height(x->right);
    if(left > right){
        return 1 + left;
    }
    else{
        return 1 + right;
    }
}

//Calcula o fator de balanço de um nó da árvore.
int balance(tree_avl *x){
    int left = height(x->left);
    int right = height(x->right);
    return left-right;
}

//Balanceia e equilibra todos os nós da árvore, verificando se o nó inserido number desbalanceou ou não.
void balance_all(tree_avl *z){
    if(z != nullptr){
        z->b = balance(z);
        balance_all(z->left);
        balance_all(z->right);
    }
}

//Verifica após inserção/remoção se a árvore está desbalanceada. Caso positivo, realiza operações de rotação.
void fixup(tree_avl **t, tree_avl *x){
    while (x->p != nullptr){
        x = x->p; // Percorre pai, avô... de x.
        x->b = balance(x);
        if (x->b > 1){
            if (x->left->b >= 0){ //A operação deve ser right_rotate, a diferença é o nó que está substituindo a posição do x.
                if (x->p == nullptr){ //x é a própria raíz da árvore.
                    *t = right_rotate(x); // A função retorna a nova raíz, então t tem que apontar para a nova raíz.
                } 
                else{ //x não é raíz da árvore.
                    if (x->p->left == x){
                        x->p->left = right_rotate(x); 
                    } 
                    else{ 
                        x->p->right = right_rotate(x);
                    }
                }
            } 
            else{ //A operação deverá ser leftRightRotate, a diferença é o nó que está substituindo a posição do x.
                if (x->p == nullptr){ 
                    *t = leftRightRotate(x);
                } 
                else{ 
                    if (x->p->left == x){
                        x->p->left = leftRightRotate(x);
                    } 
                    else{
                        x->p->right = leftRightRotate(x);
                    }
                }
            }
            break;
        } 
        else{ //Caso simétrico do x->b > 1.
            if (x->b < -1){
                if (x->right->b <= 0){
                    if (x->p == nullptr){
                        *t = left_rotate(x);
                    } 
                    else{ 
                        if (x->p->left == x){
                            x->p->left = left_rotate(x);
                        } 
                        else{
                            x->p->right = left_rotate(x);
                        }
                    }
                } 
                else{
                    if (x->p == nullptr){
                        *t = rightLeftRotate(x);
                    } 
                    else{ 
                        if (x->p->left == x){
                            x->p->left = rightLeftRotate(x);
                        } 
                        else{
                            x->p->right = rightLeftRotate(x);
                        }
                    }
                }
                break;
            }
        }
        balance_all(*t);
    }
    balance_all(*t);
}

//Realiza inserção da árvore de busca binária.
void insert(tree_avl **z, tree_avl *number){
    tree_avl *x = *z;
    tree_avl *y = nullptr;
    while(x != nullptr){
        y = x;
        if(number->key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    number->p = y;
    if(y == nullptr){
        *z = number;
    }
    else{
        if(number->key < y->key){
            y->left = number;
        }
        else{
            y->right = number;
        }
    }
    balance_all(*z);
}

// Insere um nó da árvore AVL e verifica se está desbalanceado. Caso esteja, realiza rotações.
void insert_fixup(tree_avl** t, tree_avl* number){
    insert(t, number);
    tree_avl *x = number;
    fixup(t, x);
}

// Substitui uma subárvore por outra subárvore.
void transplant(tree_avl** root, tree_avl* u, tree_avl* v) {
    if (u->p == nullptr){
        *root = v;
    } 
    else{ 
        if (u == u->p->left){
            u->p->left = v;
        } 
        else{
            u->p->right = v;
        }
        if (v != nullptr){
            v->p = u->p;
            u->p = nullptr;
        }
    }
}

// Realiza a remoção de um nó da árvore de busca binária.
tree_avl* deleted(tree_avl** t, int key) {
    tree_avl *y = search_key(*t, key);
    tree_avl *x;
    if (y->left == nullptr) {
        transplant(t, y, y->right);
    } 
    else{ 
        if (y->right == nullptr) {
            transplant(t, y, y->left);
        } 
        else {
            tree_avl* z = tree_Minimum(y->right);
            if (z != y->right) {
                transplant(t, z, z->right);
                z->right = y->right;
                y->right->p = z;
            }
            transplant(t, y, z);
            z->left = y->left;
            if (z->left != nullptr) {
                z->left->p = z;
            }
        }
    }
    balance_all(*t);
    return y;
}

// Remove um nó da árvore AVL e verifica se está desbalanceado. Caso esteja, realiza rotações.
void delete_fixup(tree_avl **t, int key) {
    tree_avl *y = deleted(t, key);
    tree_avl *x = y;
    fixup(t, x);
}

//Realiza o percurso inorder e imprime os valores em ordem crescente, sendo o número entre colchetes o fator de balanceamento do nó. 
void inorder(tree_avl *x){
    if(x != nullptr){
        inorder(x->left);
        cout << x->key << "[" << x->b << "]" << " ";
        inorder(x->right);
    }
}

//Insere os nós proposto no item 1 do trabalho.
void code_test_insert(tree_avl **x, int vector[]){
    for(int i = 0; i < 20; i++){
        tree_avl *aux = new tree_avl;
        aux->key = vector[i];
        insert_fixup(x, aux);
    }
}

//Remove os nós proposto no item 4 do trabalho.
void code_test_delet(tree_avl **x, int vector[]){
    for(int i = 0; i < 3; i++){
        delete_fixup(x, vector[i]);
    }
}

int main()
{
    tree_avl *x = nullptr;
    int vector_insert[] = { 11, 12, 13, 14, 15, 20, 19, 18, 17, 16, 5, 4, 3, 2, 1, 6, 7, 8, 9, 10 }; //Todos os números que devem ser inseridos na árvore;
    cout << "Árvore após todas as inserções:" << endl;
    code_test_insert(&x, vector_insert);
    inorder(x); //O número entre colchete é o fator de balanceamento do nó.
    cout << endl;
    int vector_delet[] = { 5, 10, 15 }; //Os números que devem ser deletados da árvore.
    cout << "Árvore após as 3 remoções:" << endl;
    code_test_delet(&x, vector_delet);
    inorder(x);
    return 0;
}