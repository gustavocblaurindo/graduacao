/* É o código-fonte do jogo, em que envolve a estrutura de dados pilha, controle do pássaro principal e a troca de cenários. */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class principalcontrola : MonoBehaviour
{
    [SerializeField] private string nomeDoLevelDeJogo; //É a tela que ganhou o jogo
    [SerializeField] private string nomeDoLevelDeJogo2; //É a tela que perdeu o jogo
    [SerializeField] private string nomeDoLevelDeJogo3; //É o menu do jogo, basta apertar esc

    //Controla a velocidade do passaro.
    private float vel = 2.5f;
    
    //armazenamentoPassaro é o conjunto de 4 pássaros que deverão ser colocadas aleatoriamente numa pilha que deverá ser formada no jogo.
    public GameObject[] armazenamentoPassaro;

    //armazenamento da pilha de pássaros
    public GameObject[] empilhar;
    
    //São as posições do armazenamentoPassaro pré-definida no jogo para colocar em uma pilha, a fim de gerar sempre uma pilha aleatória ao iniciar o jogo, sem ficar com a mesma pilha.
    int Pilhaaleatoria;
    
    //É a posição do topo da pilha.
    int posicaoPilha = 0;
    
    //É um objeto invisível no qual ao empilhar, um novo passaro deve aparecer na posição desse objeto invisivel, que fica em cima de outro pássaro.
    public GameObject TopoPassaro;

    //É a pilha que vai sendo formada ao longo do jogo.
    public GameObject[] pilhaFormada = new GameObject[7];
    
    //É o valor da comparação entre duas pilhas de pássaro, a ser formada no jogo para ganhar e a que está se formando, retornando false se for diferente.
    bool valor;

    //É a pilha aleatória gerada que deve ser formada no jogo.
    private GameObject[] PilhaPassaroPrincipal = new GameObject[6];

    //Deverá aparecer nos blocos invisíveis, cada um, a pilha de pássaros a ser formada.
    public GameObject[] interfacePassaro;

    //Movimenta o pássaro em cima ou em baixo.
    void inputTeclado()
    {
        if (Input.GetKey(KeyCode.UpArrow))
        {
            transform.Translate(new Vector3 (0, vel * Time.deltaTime, 0));
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            transform.Translate(new Vector3(0, -vel * Time.deltaTime, 0));
        }
    }

    //Verifica se a pilha está vazia.
    bool vaziaPilha(GameObject[] pilhas)
    {
        if(pilhas == null)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //Verifica se a pilha está cheia.
    bool cheiaPilha(GameObject[] pilhas, int posicao)
    {
        if(posicao >= pilhas.Length)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //Gera um numero da posicao do armazenamento de passaros que deverá ser colocada numa pilha aleatória que deve ser formada no jogo, a partir da pilha pré-definida.
    void geranumeroPilhaPassaro()
    {
        Pilhaaleatoria = Random.Range(0, armazenamentoPassaro.Length);
    }
    
    //Vai empilhar a pilha que deve ser formada no jogo.
    void geraPilhaAleatoria()
    {
        for(int i = 0;i < 6;i++)
        {
            geranumeroPilhaPassaro();
            PilhaPassaroPrincipal[i] = armazenamentoPassaro[Pilhaaleatoria];
            Instantiate(PilhaPassaroPrincipal[i], interfacePassaro[i].transform.position, interfacePassaro[i].transform.rotation);
        }
    }

    //Empilha o passaro
    void EmpilhaPassaro(GameObject[] pilhas, ref int posicao, ref Collision2D empilha)
    {
        GameObject novoPassaro;
        if (!cheiaPilha(pilhas, posicao))
        {
            pilhas[posicao] = empilha.gameObject;
            posicao++;
            if (posicao >= 6)
            {
                SceneManager.LoadScene(nomeDoLevelDeJogo);
            }

            if (empilha.gameObject.CompareTag("azul"))
            {
                novoPassaro = empilhar[0];
                pilhaFormada[posicao - 1] = novoPassaro;
                interfacePassaro[posicao].SetActive(true);
                interfacePassaro[posicao - 1].SetActive(false);
            }
            if (empilha.gameObject.CompareTag("amarelo"))
            {
                novoPassaro = empilhar[1];
                pilhaFormada[posicao - 1] = novoPassaro;
                interfacePassaro[posicao].SetActive(true);
                interfacePassaro[posicao - 1].SetActive(false);
            }
            if (empilha.gameObject.CompareTag("vermelho"))
            {
                novoPassaro = empilhar[2];
                pilhaFormada[posicao - 1] = novoPassaro;
                interfacePassaro[posicao].SetActive(true);
                interfacePassaro[posicao - 1].SetActive(false);
            }
            if (empilha.gameObject.CompareTag("verde"))
            {
                novoPassaro = empilhar[3];
                pilhaFormada[posicao - 1] = novoPassaro;
                interfacePassaro[posicao].SetActive(true);
                interfacePassaro[posicao-1].SetActive(false);

            }

            
        }
    }

    //Destrói o pássaro principal no jogo.
    void DestroiPassaroPrincipal()
    {
        Destroy(this.gameObject);
    }

    //Desempilha a pilha de pássaros.
    void DesempilhaPassaro(GameObject[] pilhas,ref int posicao)
    {
        posicao--;
        if (!vaziaPilha(pilhas) && posicao>=0)
        {
            pilhas[posicao] = null;
            interfacePassaro[posicao].SetActive(true);
            interfacePassaro[posicao + 1].SetActive(false);
        }
        if(posicao<0)
        {
            DestroiPassaroPrincipal();
            SceneManager.LoadScene(nomeDoLevelDeJogo2);
        }
    }

    //Compara as tags dos pássaros
    void ComparaPassaro(Collision2D outro)
    {
        GameObject[] aux = new GameObject[6];
        int posaux = 0;
        int contador = 0;
        int tam = PilhaPassaroPrincipal.Length - 1;

        for (int i = 5; i >= 0; i--)
        {
            if (i != posicaoPilha)
            {
                aux[posaux] = PilhaPassaroPrincipal[i];
                posaux++;
                PilhaPassaroPrincipal[i] = null;
                tam--;
                contador++;
            }
            else
            {
                if (posicaoPilha >= 0)
                {
                    valor = PilhaPassaroPrincipal[i].CompareTag(outro.gameObject.tag);
                }
            }
        }
        for (int i = 0; i < contador; i++)
        {
            tam++;
            PilhaPassaroPrincipal[tam] = aux[posaux - 1];
            posaux--;
        }
    }




    //É uma função que trata da colisão entre dois objetos, verificando se deve empilhar ou não.
    void OnCollisionEnter2D(Collision2D outro)
    {
        GameObject[] aux = new GameObject[6];
        if (outro.gameObject.CompareTag("desempilha"))
        {
            DesempilhaPassaro(aux, ref posicaoPilha);
        }
        else
        {
            ComparaPassaro(outro);
            if (valor == true)
            {
                EmpilhaPassaro(aux,ref posicaoPilha,ref outro);
            }
            else
            {
                DesempilhaPassaro(aux, ref posicaoPilha);
            }
            
        }
    }

    //Limita as bordas para que não seja possível o pássaro sair do cenário
    void LimiteBorda()
    {
        var distanceZ = (transform.position - Camera.main.transform.position).z;
        var leftBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, distanceZ)).x;
        var rightBorder = Camera.main.ViewportToWorldPoint(new Vector3(1, 0, distanceZ)).x;
        var topBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, distanceZ)).y;
        var bottomBorder = Camera.main.ViewportToWorldPoint(new Vector3(0, 1, distanceZ)).y;
        transform.position = new Vector3(
            Mathf.Clamp (transform.position.x, leftBorder, rightBorder),
            Mathf.Clamp (transform.position.y, topBorder, bottomBorder),
            transform.position.z);
    }
    //Carrega a tela menu
    void menu()
    {
        if(Input.GetKeyDown(KeyCode.Escape))
        {
            SceneManager.LoadScene(nomeDoLevelDeJogo3);
        }
    }

    //Pausa o jogo ao pressionar a barra de espaço
    void PausarJogo()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (Time.timeScale == 0)
            {
                Time.timeScale = 1;
            }
            else
            {
                if (Time.timeScale == 1)
                {
                    Time.timeScale = 0;
                }
            }
        }
    }


    // Inicia uma apenas uma vez.
    void Start()
    {
        posicaoPilha = 0;
        geraPilhaAleatoria();
    }

    // É executado a cada 1 frame.
    void Update()
    {
        inputTeclado();
        LimiteBorda();
        PausarJogo();
        menu();

    }
} 