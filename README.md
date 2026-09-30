# Projetos da Graduação

Trabalhos e implementações desenvolvidos ao longo da graduação em Engenharia de Computação na UFSCar.

* [**Jogo da Cobrinha com IA**](#jogo-da-cobrinha-com-ia): agente desenvolvido para jogar o jogo da cobrinha de forma autônoma, utilizando A*, algoritmos genéticos e aprendizado supervisionado. Projeto realizado em grupo no 6º semestre. Foi utilizada a linguagem Python.
* [**Jogo do Pássaro**](#jogo-do-pássaro): jogo desenvolvido na Unity, utilizando a estrutura de dados pilha. Projeto realizado no 2º semestre. Foi utilizada a linguagem C#.
* [**Donkey Kong em Prolog**](#donkey-kong-em-prolog): versão textual do Donkey Kong com um agente automático capaz de jogar sozinho. Projeto realizado em grupo. Foi utilizada a linguagem Prolog.
* [**Implementações de Estruturas de Dados**](#implementações-de-estruturas-de-dados): implementação de algoritmos de ordenação, árvores, tabelas hash e Dijkstra, desenvolvidos até o 4º semestre. Foram utilizadas as linguagens C++ e Python.

---

## Jogo da Cobrinha com IA

Projeto do 6º semestre, realizado em grupo. Código na pasta [`JogoDaCobrinha`](JogoDaCobrinha).

O jogo em si é simples, representado em uma matriz com saída em texto. O foco do trabalho é resolvê-lo com diferentes técnicas de Inteligência Artificial e comparar os resultados.

**O que foi feito**

1. **Busca heurística:** o agente usa A* (com distância de Manhattan) e BFS para chegar até a comida, verificando se cada movimento é seguro antes de fazê-lo.
2. **Algoritmo genético:** cada indivíduo é uma sequência de movimentos. A população evolui com seleção, cruzamento, mutação e elitismo para reduzir a quantidade de movimentos necessários para vencer.
3. **Aprendizado supervisionado:** uma rede neural (PyTorch) é treinada com os jogos do agente heurístico para prever o próximo movimento em um tabuleiro 3x3.

**Resultados**

- A heurística atinge a pontuação máxima em praticamente todas as execuções nos tabuleiros pequenos (3x3, 5x5 e 7x7). Nos tabuleiros maiores, o desempenho varia mais entre execuções.
- No tabuleiro 17x17, o algoritmo genético reduziu a melhor solução de 4572 para 3798 movimentos, uma melhora de 16,93%.

**Como rodar:** o projeto é um notebook Jupyter (`JogoDaCobrinha.ipynb`), que pode ser aberto localmente ou no Google Colab. As bibliotecas usadas são `numpy`, `matplotlib` e `torch`. Basta executar as células na ordem para o funcionamento.

---

## Jogo do Pássaro

Projeto do 2º semestre, feito na Unity para aplicar a estrutura de dados pilha. Scripts na pasta [`JogoDoPássaro`](JogoDoPássaro).

<img width="1497" height="757" alt="image" src="https://github.com/user-attachments/assets/6dff644a-e288-4078-b90f-da09082983af" />

**[Clique aqui para jogar](https://play.unity.com/en/games/d2bf6a87-6626-4888-a2cd-12b6cd1e86cd/take-the-birds)**

**Lógica do jogo**

No topo da tela aparece uma sequência aleatória de 6 pássaros coloridos (azul, amarelo, vermelho e verde). Essa sequência é a pilha que o jogador precisa montar, na ordem certa.

- O jogador controla um pássaro com as setas para cima e para baixo, enquanto pássaros coloridos, gaiolas e aviões passam pelo cenário.
- **Empilhar:** encostar no pássaro da cor esperada coloca esse pássaro na pilha.
- **Desempilhar:** encostar em um pássaro da cor errada, em uma gaiola ou em um avião tira o último pássaro da pilha.
- **Vitória:** completar a pilha com os 6 pássaros.
- **Derrota:** desempilhar quando a pilha já está vazia.

A pilha é implementada em um vetor, com funções para verificar se está vazia ou cheia, empilhar e desempilhar. Uma nova sequência aleatória é gerada a cada partida.

**Outros controles:** `Espaço` pausa o jogo, `Esc` volta ao menu e `Enter` sai do tutorial e começa o jogo.

---

## Donkey Kong em Prolog

Versão em texto do Donkey Kong feita em SWI-Prolog, com um agente automático que joga sozinho. Este foi um trabalho realizado em grupo. Código na pasta [`DonkeyKong_Prolog`](DonkeyKong_Prolog).

<img width="405" height="317" alt="image" src="https://github.com/user-attachments/assets/f0dd46aa-ea78-4da4-97c8-f0ffd7063190" />

O jogo é impresso no terminal, e o agente vai se movimentando a cada passo. O arquivo [`video.mp4`](video.mp4) mostra o agente jogando do início ao fim.

**Lógica do jogo**

O mapa tem 12 linhas por 12 colunas, com plataformas, escadas e um martelo. O Donkey Kong fica no topo e joga barris que descem pelas plataformas.

- **Objetivo:** pegar o martelo e chegar até o Donkey Kong.
- **Vitória:** encontrar o Donkey Kong com o martelo.
- **Derrota:** ser atingido por um barril, ou encontrar o Donkey Kong sem o martelo.

Legenda da tela: `J` jogador (`J*` com o martelo), `D` Donkey Kong, `O` barril, `E` escada, `M` martelo e `-` plataforma.

**Agente automático**

O agente escolhe o próximo movimento por regras: vai até o martelo, explora cada plataforma de um lado ao outro e sobe pela escada quando ela está livre. Antes de se mover, ele verifica se há barris por perto e, quando necessário, espera ou pula para desviar.

**Como rodar**

É necessário ter o [SWI-Prolog](https://www.swi-prolog.org/) instalado. No terminal, dentro da pasta:

```
swipl Trabalho1_DonkeyKong_SWIProlog.pl
```

Para o agente jogar sozinho:

```
?- agente_inteligente.
```

Para jogar manualmente:

```
?- inicializar_jogo.
?- jogar(direita).
```

Os movimentos disponíveis são `direita`, `esquerda`, `subir`, `pular`, `pular_direita`, `pular_esquerda` e `esperar`.

---

## Implementações de Estruturas de Dados

Algoritmos e estruturas de dados implementados do zero, até o 4º semestre. Código na pasta [`ImplementaçõesEstruturaDeDados`](ImplementaçõesEstruturaDeDados). Os códigos em C++ usam ponteiros e alocação manual, sem bibliotecas prontas para as estruturas.

| Tópico | Arquivos | O que tem |
|--------|----------|-----------|
| Ordenação | `quicksort.cpp`, `shellshort.cpp`, `countingsort.cpp`, `radixsort.cpp`, `bucketsort.cpp` | Cinco algoritmos de ordenação. O radix sort usa o counting sort, e o bucket sort usa o quicksort dentro de cada balde. |
| Árvore binária | `arvore_binaria.cpp` | Árvore de busca usada em um jogo de adivinhar o time do Brasileirão série A. |
| Árvore AVL | `arvore_avl.cpp` | Árvore balanceada com rotações, inserção e remoção. |
| Tabela hash | `hash.cpp`, `hash_2.cpp` | Parte A com encadeamento por listas. Parte B com endereçamento aberto e três tipos de sondagem: linear, quadrática e hash duplo. |
| Grafos | `Djikstra_python.ipynb` | Algoritmo de Dijkstra em Python, com o grafo desenhado usando `networkx` e `matplotlib`. |

**Como rodar:** os arquivos `.cpp` são independentes, cada um com a sua função `main`:

```
g++ quicksort.cpp -o quicksort
./quicksort
```

O Dijkstra é um notebook Jupyter e precisa de `networkx` e `matplotlib`.
