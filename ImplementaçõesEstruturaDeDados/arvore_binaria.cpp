/*Jogo: Adivinhe o time do Brasileirão série A
  Aplicação: É utilizada a estrutura de dados árvore
*/

#include <iostream>
#include <string>

using namespace std;

//É a estrutura árvore;
struct node{
    string info;
    string dica;
    int codigo;
    struct node *dir;
    struct node *esq;
    
    node(){
        esq=nullptr;
        dir=nullptr;
    };
};

typedef struct node *arvore;

//Verifica se a árvore está vazia
bool vazia(arvore a){
    if(a==nullptr){
        return true;
    }
    else{
        return false;
    }
}

//Insere um elemento na árvore de times.
void insere(arvore &a, string nome, string dica, int cod){
    arvore aux;
    if(vazia(a)){
        aux = new node;
        aux->info = nome;
        aux->dica = dica;
        aux->codigo = cod;
        aux->dir = nullptr;
        aux->esq = nullptr;
        a = aux;
        aux = nullptr;
        delete aux;
    }
    else{
        if(cod > a->codigo){
            insere(a->dir, nome, dica, cod);
        }
        else{
            insere(a->esq, nome, dica, cod);
        }
    }
}

//Apresenta a tela do jogo com o título "ADIVINHE O TIME DA SÉRIE A".
void menu(){
    cout << "▂▃▄▅▆▇█▓▒░ADIVINHE O SEU TIME░▒▓█▇▆▅▄▃▂"

    << endl;
}

//Imprime as opções iniciais do jogo.
void imprime(){
    cout<< "[1] JOGAR"<< endl;
    cout<< "[2] AJUDA"<< endl;
    cout<< "[3] INFORMAÇÕES"<< endl;
    cout<< "Caso deseje encerrar o programa, digite -1"<< endl;
}

void info(){
    cout << "Esse é um jogo desenvolvido com fins de aplicação da estrutura de dados árvore." << endl;
}
//Pega a informação da árvore a ser impressa.
string getArvore(arvore times){
    return times->info;
}

//Cria a árvore para o quiz de times.
void CriaQuizTime(arvore &times){
    insere(times, "O seu time é da região Sudeste?", "Os times da série A que são da Região Sudeste são: Palmeiras, São Paulo, Corinthians, Bragantino, Flamengo, Vasco, Botafogo, Atlético/MG, Cruzeiro e Fluminense. \n", 2000);
    insere(times, "O seu time tem pelo menos um título do Brasileirão?", "Ranking títulos brasileiros: \n 12 - Palmeiras \n 8 - Flamengo \n 8 - Santos \n 7 - Corinthians \n 6 - São Paulo \n 4 - Cruzeiro \n 4 - Fluminense \n 4 - Vasco \n 3 - Internacional \n 2 - Bahia \n 2- Botafogo \n 3 - Atlético/MG \n 1 - Athletico/PR \n 1 - Coritiba \n 1- Guarani \n 1- Sport " ,1000);
    insere(times, "O seu time tem 2 ou mais libertadores?", "Times que têm libertadores: \n 3 - Flamengo, Palmeiras, Grêmio, Santos e São Paulo \n 2 - Cruzeiro e Internacional \n 1- Atlético/MG, Corinthians, Fluminense e Vasco \n" ,3000);
    insere(times, "O seu time é do estado de Rio de Janeiro?", "Os times da série A que são do RJ são: Flamengo, Vasco, Botafogo e Fluminense \n", 2500);
    insere(times, "O seu time é do estado de São Paulo?", "Os times da série A que são do estado de SP são: Palmeiras, Corinthians, Bragantino e São Paulo \n" ,4000);
    insere(times, "O seu time é da região Sul?", "Os times da série A que são da região Sul são: Grêmio, Internacional, Criciúma e Juventude \n", 1100);
    insere(times, "O seu time é da região Nordeste?", "Os times da série A que são da região Nordeste são: Bahia, Fortaleza e Vitória" , 900);
    insere(times, "O seu time é do estado de São Paulo?","Os times da série A que são do estado de SP são: Palmeiras, Corinthians, Bragantino e São Paulo \n" ,2250);
    insere(times, "O seu time já caiu 4 vezes para segunda divisão do Brasileirão?", "O único time da série A que já caiu 4 vezes é o Vasco \n", 2750);
    insere(times, "O seu time é o maior campeão da Copa do Brasil?", "O maior campeão da copa do Brasil é o Cruzeiro \n", 3500);
    insere(times, "O seu time é o atual campeão do Brasileirão?", "O atual campeão do Brasileirão é Palmeiras \n" ,5000);
    insere(times, "O seu time tem libertadores?", "Times que têm libertadores: \n 3 - Flamengo, Palmeiras, Grêmio, Santos e São Paulo \n 2 - Cruzeiro e Internacional \n 1- Atlético/MG, Corinthians, Fluminense e Vasco \n", 1200);
    insere(times, "O seu time é Bahia.", "" ,1050);
    insere(times, "O seu time é o atual vice-campeão da Sulamericana?", "O atual vice-campeão da Sulamericana é o Fortaleza. \n", 950);
    insere(times, "O seu time tem pelo menos uma copa do Brasil?","Os times que têm copas do Brasil são: 6 - Cruzeiro, 5 - Grêmio, 4 - Palmeiras e Flamengo, 3 - Corinthians, 2 - Atlético/MG, 1 - Criciúma, Fluminense, Internacional, Juventude, Paulista, Santo André, Santos, Sport, Vasco, Athletico/PR e São Paulo \n", 800);
    insere(times, "O seu time é do estado do Mato Grosso?", "O único time da série A que é do estado do Mato Grosso é o Cuiabá \n", 700);
    insere(times, "O treinador Luiz Felipe Scolari, mais conhecido como Felipão, já treinou o seu time?", "Felipão já treinou CSA, Juventude, Brasil de Pelotas, Grêmio, Goiás, Coritiba, Criciúma, Palmeiras, Cruzeiro e Athletico/PR. É o atual treinador do Atlético/MG.", 850);
    insere(times, "O seu time é Vitória.", "", 925);
    insere(times, "O seu time é Fortaleza.","", 975);
    insere(times, "O seu time é Atlético/MG.","", 2200);
    insere(times, "O seu time tem mundial?","", 2300);
    insere(times, "O seu time teve a melhor campanha do primeiro turno do Brasileirão na história dos pontos corridos?", "O time que teve tal campanha histórica é o Botafogo \n", 2625);
    insere(times, "O seu time é Vasco.","", 2800);
    insere(times, "O seu time é Flamengo.","", 3250);
    insere(times, "O seu time é Cruzeiro.","", 3750);
    insere(times, "O seu time é São Paulo.","", 4500);
    insere(times, "O seu time é Palmeiras.","", 6000);
    insere(times, "O seu time é Atlético/GO.","", 600);
    insere(times, "O seu time é Cuiabá.","", 750);    
    insere(times, "O seu time é Juventude.", "", 825);
    insere(times, "O seu time é Criciúma.", "", 875);
    insere(times, "O seu time é Bragantino.", "", 2275);
    insere(times, "O seu time é Corinthians.", "", 2325);
    insere(times, "O seu time é Fluminense.", "", 2600);
    insere(times, "O seu time é Botafogo.", "", 2650);
    insere(times, "O seu time é Athletico/PR.", "", 1175);
    insere(times, "O escudo do seu time tem cor azul?", "Os times que tem cor azul no escudo são Cruzeiro, Fortaleza e Grêmio", 1300);
    insere(times, "O seu time é Grêmio.", "", 1400);
    insere(times, "O seu time é Internacional.","", 1250);    
}

//Joga o quiz.
void jogar(arvore &times){
    string num;
    arvore aux;
    aux = times;
    while(aux!=nullptr){
        cout << aux->info << endl;
        if(aux->dir != nullptr && aux->esq != nullptr){
            cout << "[1] SIM | [2] NÃO | [3] DICA" << endl;
            cin >> num;  
            cout << endl;
        }
        
        while(num=="3" && aux->dir != nullptr && aux->esq != nullptr){
            cout << endl << aux->dica << endl << endl;
            cout << endl << aux->info << endl;
            cout << "[1] SIM | [2] NÃO | [3] DICA" << endl;
            cin >> num;
            cout << endl;
                           
        }
        while(num!="1" && num!="2" && num!="3"){
            cout << "Número inválido, tente novamente." << endl;
            cin >> num;
            cout << endl;
        }
        if(num=="1"){
            aux = aux->dir;
        }
        else{
            aux = aux->esq;
        }
    }
}

//Explica o funcionamento do jogo.
void ajuda(){
    cout << "Para jogar esse jogo, você deverá pensar em um time que está no Brasileirão Série A." << endl;
    cout << "Feito isso, observe as perguntas na tela e para responder digite 1 para sim, 2 para não e 3 para dica." << endl;
    cout << "Após responder as perguntas necessárias, irá aparecer o time que você pensou." << endl;
}

// É a interface do jogo.
void interface(){
    arvore times = nullptr;
    CriaQuizTime(times);
    int num;
    menu();
    imprime();
    cin>>num;
    while(num!=-1){
        switch (num){
            case -1:
                break;
            case 1:
                cout << endl;
                jogar(times);
                break;
            case 2:
                cout << endl;
                ajuda();
                break;
            case 3:
                cout << endl;
                info();
                break;
            default:
                cout<<"Número inválido. Tente novamente"<<endl;
        }
        cout << endl << endl;
        imprime();
        cin>>num;
    }
    
    cout << "Programa encerrado." << endl;
}

int main()
{
    interface();

    return 0;
}