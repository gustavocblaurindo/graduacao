:- dynamic jogador_atual/1.
:- dynamic barril/2.
:- dynamic proximo_id/1.
:- dynamic explorado/3.
:- dynamic visitado/1.
:- dynamic martelo/1.
:- dynamic subiu/0.
:- dynamic tem_martelo/0.

% ===== Cenario =====
tamanho(12, 12).

inicio((1, 11)).
donkey((12, 1)).

plataforma(1). plataforma(2). plataforma(4).
plataforma(6). plataforma(8). plataforma(10). plataforma(12).

escada((2,5)). escada((3,5)). escada((4,5)).
escada((4,6)). escada((5,6)). escada((6,6)).
escada((6,2)). escada((7,2)). escada((8,2)).
escada((8,11)). escada((9,11)). escada((10,11)).
escada((10,9)). escada((11,9)). escada((12,9)).
escada((10,5)). escada((11,5)). escada((12,5)).
escada((1,8)). escada((2,8)).

% ===== Martelo =====
posicao_martelo((12,7)).

% ===== Inicializa��o =====
inicial(estado(Pos)) :- inicio(Pos).

%Inicializa
inicializar_jogo :-
    inicial(E),
    retractall(jogador_atual(_)),
    retractall(barril(_,_)),
    retractall(proximo_id(_)),
    retractall(martelo(_)),
    retractall(tem_martelo),
    assert(jogador_atual(E)),
    assert(proximo_id(1)),
    posicao_martelo(PosMartelo),
    assert(martelo(PosMartelo)),
    gerar_barril_inicial,
    nl, write('=== Novo jogo iniciado! ==='), nl,
    imprimir_estado(E).

%Gera o barril inicial
gerar_barril_inicial :-
    donkey((L, C)), Cdir is C + 1,
    proximo_id(ID),
    assert(barril(ID, (L, Cdir))),
    NovoID is ID + 1,
    retractall(proximo_id(_)),
    assert(proximo_id(NovoID)).

%Gera o novo barril
gerar_novo_barril :-
    donkey((L, C)), Cdir is C + 1,
    proximo_id(ID),
    assert(barril(ID, (L, Cdir))),
    NovoID is ID + 1,
    retractall(proximo_id(_)),
    assert(proximo_id(NovoID)).

% ===== Exibi��o =====
imprimir_estado(estado((A, C))) :-
    tamanho(Linhas, Colunas),
    nl,
    numlist(1, Linhas, Ls),
    reverse(Ls, LinhasInv),
    imprimir_todas_linhas(LinhasInv, Colunas, (A, C)),
    nl.

imprimir_todas_linhas([], _, _).
imprimir_todas_linhas([L|R], Cmax, Pos) :-
    imprimir_linha(L, Cmax, Pos),
    imprimir_todas_linhas(R, Cmax, Pos).

imprimir_linha(L, Cmax, Pos) :-
    numlist(1, Cmax, Cols),
    imprimir_todas_colunas(Cols, L, Pos),
    nl.

imprimir_todas_colunas([], _, _).
imprimir_todas_colunas([K|R], L, (A, C)) :-
    (   (A == L, C == K) -> (tem_martelo -> write(' J*') ; write(' J '))
    ;   donkey((L, K)) -> write(' D ')
    ;   barril(_, (L, K)) -> write(' O ')
    ;   escada((L, K)) -> write(' E ')
    ;   martelo((L, K)) -> write(' M ')
    ;   (plataforma(L), L = 1 -> write(' - '))
    ;   (plataforma(L), L = 2, K =\= 1 -> write(' - '))
    ;   (plataforma(L), L = 4, K =\= 12 -> write(' - '))
    ;   (plataforma(L), L = 6, K =\= 1 -> write(' - '))
    ;   (plataforma(L), L = 8, K =\= 12 -> write(' - '))
    ;   (plataforma(L), L = 10, K =\= 1 -> write(' - '))
    ;   (plataforma(L), L = 12, K =\= 12 -> write(' - '))
    ;   write('   ')
    ),
    imprimir_todas_colunas(R, L, (A, C)).

% ===== Movimento =====
% O agente se move � direita se e somente se o caminho estiver dentro do limite e sobre a plataforma.
mover_direita((L, C), (L, C2)) :-
    tamanho(_, MaxC),
    C < MaxC,
    C2 is C + 1,
    plataforma(L).

%O agente se move � esquerda se e somente se o caminho estiver dentro do limite e sobre a plataforma.
mover_esquerda((L, C), (L, C2)) :-
    C > 1,
    C2 is C - 1,
    plataforma(L).

%O agente sobe se e somente se tiver escada.
subir((L, C), (L2, C)) :-
    L2 is L + 1,
    escada((L, C)),
    escada((L2, C)).

aplicar_gravidade(Pos, Pos).


%O agente pode pular se estiver sobre a plataforma exceto a primeira, por estar pr�xima da segunda.
pode_pular((L,_)) :- plataforma(L), L \= 1.

%O agente pula se a condi��o do pode_pular for cumprida.
pular(Pos, Pos) :- pode_pular(Pos).

%O agente pula dois passos � direita se esse caminho estiver dentro do limite.
pular_direita((L, C), (L, C2)) :-
    pode_pular((L, C)),
    tamanho(_, MaxC),
    C < MaxC,
    C2 is C + 2.

%O agente pula dois passos � esquerda se esse caminho estiver dentro do limite.
pular_esquerda((L, C), (L, C2)) :-
    pode_pular((L, C)),
    C > 1,
    C2 is C - 2.

%Predicados utilizados para executar os movimentos. Vale destacar que a ideia inicial era aplicar a gravidade no
%jogo, mas foi deixada de lado ao fim do projeto.
executar_movimento(direita, estado(Pos), estado(PosFinal)) :-
    mover_direita(Pos, P2),
    aplicar_gravidade(P2, PosFinal).
executar_movimento(esquerda, estado(Pos), estado(PosFinal)) :-
    mover_esquerda(Pos, P2),
    aplicar_gravidade(P2, PosFinal).
executar_movimento(subir, estado(Pos), estado(PosFinal)) :-
    subir(Pos, P2),
    aplicar_gravidade(P2, PosFinal).
executar_movimento(pular, estado(Pos), estado(PosFinal)) :-
    pular(Pos, P2),
    aplicar_gravidade(P2, PosFinal).
executar_movimento(pular_direita, estado(Pos), estado(PosFinal)) :-
    pular_direita(Pos, P2),
    aplicar_gravidade(P2, PosFinal).
executar_movimento(pular_esquerda, estado(Pos), estado(PosFinal)) :-
    pular_esquerda(Pos, P2),
    aplicar_gravidade(P2, PosFinal).
executar_movimento(esperar, estado(Pos), estado(Pos)).

% ===== Barris =====
%Praticamente faz todos os barris formados na lista se moverem.
tick_barris :-
    findall(ID, barril(ID,_), Lista),
    mover_lista_barris(Lista).

mover_lista_barris([]).
mover_lista_barris([ID|R]) :-
    ( mover_barril(ID) -> true ; true ),
    mover_lista_barris(R).

%Donkey kong gera barris.
dk_para_gerar :-
    jogador_atual(estado((AL, AC))),
    donkey((DL, DC)),              
    AL == DL,                      
    Dist is abs(AC - DC),          
    Dist =< 4.                    

%Move cada barril.
mover_barril(ID) :-
    barril(ID, PosAtual),
    proxima_posicao_barril(PosAtual, PosTemp),
    ( PosTemp = quebrado -> retractall(barril(ID,_))
    ; retractall(barril(ID,_)),
      assert(barril(ID, PosTemp)),
      ( PosAtual = (10,1), PosTemp = (8,1) ->
          ( \+ dk_para_gerar ->  
              gerar_novo_barril  
          ; true )
      ; true )
    ).

%Define como cada barril se move e quando se quebra.
proxima_posicao_barril((12,12), (10,12)) :- !.
proxima_posicao_barril((10,1), (8,1)) :- !.
proxima_posicao_barril((8,12), (6,12)) :- !.
proxima_posicao_barril((6,1), (4,1)) :- !.
proxima_posicao_barril((4,12), (2,12)) :- !.
proxima_posicao_barril((2,1), quebrado) :- !.
proxima_posicao_barril((2,12), quebrado) :- !.
proxima_posicao_barril((L, C), (L, C2)) :-
    direcao_barril(L, Direcao),
    mover_lado((L, C), Direcao, (L, C2)), !.
proxima_posicao_barril((L, _), quebrado) :- L < 1, !.


%Define arbitrariamente as poss�veis dire��es de cada barris em cada n�vel de plataforma.
direcao_barril(13, direita). direcao_barril(12, direita).
direcao_barril(10, esquerda). direcao_barril(8, direita).
direcao_barril(6, esquerda). direcao_barril(4, direita).
direcao_barril(2, esquerda).

%Define o movimento do barril.
mover_lado((L, C), direita, (L, C2)) :-
    tamanho(_, MaxC), ( C < MaxC -> C2 is C + 1 ; C2 = C ).
mover_lado((L, C), esquerda, (L, C2)) :-
    ( C > 1 -> C2 is C - 1 ; C2 = C ).

% ===== Colis�es =====
%Checa as poss�veis colis�es para vit�ria ou derrota do agente.
checar_colisoes(estado((L, C))) :-
    ( (barril(_, (L, C)) -> nl, write('Voc� foi atingido por um barril!'), nl, fail)
    ; donkey((L, C)) ->
        ( tem_martelo -> nl, write('PARAB�NS! VOC� VENCEU! Donkey Kong foi derrotado com o martelo!'), nl, halt
        ; nl, write('VOC� N�O TEM O MARTELO! Donkey Kong te derrotou!'), nl, fail
        )
    ; true
    ).

% ===== Martelo =====
%Coleta o martelo
coletar_martelo(estado((L,C))) :-
    ( martelo((L,C)) -> retract(martelo((L,C))), assert(tem_martelo)
    ; martelo((L,C+1)) -> retract(martelo((L,C+1))), assert(tem_martelo)
    ; martelo((L,C-1)) -> retract(martelo((L,C-1))), assert(tem_martelo)
    ; true ).

coletar_martelo(_).

% ===== Jogar =====
%Usado para jogar manualmente.
jogar(Movimento) :-
    jogador_atual(EstadoAtual),
    ( executar_movimento(Movimento, EstadoAtual, NovoEstado) ->
        tick_barris,
        retractall(jogador_atual(_)),
        assert(jogador_atual(NovoEstado)),
        coletar_martelo(NovoEstado),
        checar_colisoes(NovoEstado),
        imprimir_estado(NovoEstado)
    ; nl
    ).


%Inicializa a lista de explora��o do tipo (P,E,D), em que P � o n�vel da plataforma, E � se o agente
%se movimentou para a esquerda e D para a direita.
inicializar_exploracao :-
    retractall(explorado(_,_,_)),
    findall(N, plataforma(N), Ns),
    inicializar_exploracao_niveis(Ns).

inicializar_exploracao_niveis([]).
inicializar_exploracao_niveis([N|R]) :-
    assert(explorado(N, 0, 0)),
    inicializar_exploracao_niveis(R).

%Reseta a explora��o
reset_exploracao :-
    retractall(explorado(_,_,_)),
    inicializar_exploracao.

%Verifica o valor do limite � direita de acordo com o n�vel da plataforma.
limite_direita((L, C)) :-
    plataforma(L),
    tamanho(_, MaxC),
    Aux is MaxC - 1,
    ( (L = 12 ; L = 8 ; L = 4) -> C = Aux ; C = MaxC ).

%Verifica o valor do limite � esquerda de acordo com o n�vel da plataforma.
limite_esquerda((L, C)) :-
    plataforma(L),
    ( (L = 10 ; L = 6 ; L = 2) -> C = 2 ; C = 1 ).


%Atualiza a lista de explora��o de acordo os valores dos limites caso o agente tenha atingido, por exemplo,
%o final da plataforma atual.
atualizar_explorado((L,C)) :-
    ( explorado(L, Eold, Dold) ->
        ( limite_direita((L,C)) ->
            ( Eold = 0, Dold = 0 ->
                retractall(explorado(L,_,_)), assert(explorado(L, 0, 1))
            ; Eold = 1, Dold = 1 ->
                retractall(explorado(L,_,_)), assert(explorado(L, 1, 1))
            ; true )
        ; limite_esquerda((L,C)) ->
            ( Eold = 0, Dold = 1 ->
                retractall(explorado(L,_,_)), assert(explorado(L, 1, 1))
            ; Eold = 1, Dold = 0 ->
                retractall(explorado(L,_,_)), assert(explorado(L, 1, 1))
            ; true )
        ; true )
    ; true ).

%Verifica se tem barril perto da escada.
barril_perto_escada((LJ, CJ)) :-
    escada((LJ, CJ)),
    (L_acima is LJ + 1 ; L_acima is LJ + 2 ; L_acima is LJ + 3),
    plataforma(L_acima),
    barril(_, (L_acima, CB)),
    direcao_barril(L_acima, Direcao),
    ( (Direcao == direita, abs(CB - CJ) < 5)
    ; (Direcao == esquerda, abs(CB - CJ) < 5) ), !. 

%Verifica se tem barril acima do agente.
barril_acima((L,C)) :-
    (L2 is L + 1 ; L2 is L + 2 ; L2 is L + 3),
    barril(_, (L2, C2)),
    abs(C2 - C) =< 3.

%Define os poss�veis movimentos seguros de acordo com 'barril_acima', 'barril_perto_escada' e 'barril_perigoso'.
movimento_seguro(Pos, subir, Mov) :-
    ( barril_acima(Pos)        -> Mov = esperar
    ; subir(Pos, _)            -> Mov = subir
    ; Mov = esperar ).

movimento_seguro(Pos, direita, Mov) :-
    Pos = (L,C),
    Prox = (L, C+1),
    ( barril_perigoso(Pos, esquerda) -> Mov = pular_direita
    ; barril_acima(Prox)             -> Mov = pular
    ; Mov = direita ).

movimento_seguro(Pos, esquerda, Mov) :-
    Pos = (L,C),
    Prox = (L, C-1),
    ( barril_perigoso(Pos, direita) -> Mov = pular_esquerda
    ; barril_acima(Prox)            -> Mov = esperar
    ; Mov = esquerda ).

movimento_seguro(_, pular, pular).
movimento_seguro(_, pular_direita, pular_direita).
movimento_seguro(_, pular_esquerda, pular_esquerda).
movimento_seguro(_, esperar, esperar).

%Verifica se tem um barril pr�ximo do agente.
barril_perigoso(Pos, Direcao) :-
    barril(_, (LB, CB)),
    proxima_posicao_barril((LB, CB), (LB2, CB2)),
    Pos = (LJ, CJ),
    LJ =:= LB2,
    ( Direcao = direita ->
        DestinoAgente is CJ - 1,
        (CB2 =:= DestinoAgente ; CB2 =:= CJ)
    ; Direcao = esquerda ->
        DestinoAgente is CJ + 1,
        (CB2 =:= DestinoAgente ; CB2 =:= CJ)
    ).

%Verifica se o agente est� no meio da escada, ou seja, na posi��o entre os dois n�veis de plataforma.
no_meio_da_escada((L,C)) :-
    L_ant is L - 1,
    L_dep is L + 1,
    escada((L_ant, C)),
    escada((L_dep, C)).

%A ideia inicial era fazer a lista de explora��o do tipo (E,D), em que exigia o reset a cada novo n�vel de
%plataforma. No entanto, foi descartada posteriormente para uma lista para cada n�vel e optamos por deixar
%esse predicado, pois verifica se o agente subiu de plataforma.
checar_reset_exploracao(PosAntiga, PosNova) :-
    ( subiu,
      PosAntiga = (L_Antiga, _),
      PosNova = (L_Nova, _),
      plataforma(L_Nova),
      L_Nova \= L_Antiga
    -> retractall(subiu)
    ; true
    ).

%Define as movimenta��es sugeridas do agente.
proximo_movimento(Pos, Mov) :-
    Pos = (L, C),
    ( martelo((L, CM)), \+ barril_perigoso(Pos, direita), C < CM -> Mov = direita
    ; martelo((L, CM)), \+ barril_perigoso(Pos, esquerda), C > CM -> Mov = esquerda
    ; martelo((L, CM)), C = CM -> Mov = esperar
    ; tem_martelo, subir(Pos, _) -> Mov = subir
    ; no_meio_da_escada(Pos), \+ barril_perto_escada(Pos) -> Mov = subir
    ; no_meio_da_escada(Pos), barril_perto_escada(Pos) -> Mov = esperar
    ;  Pos = (L, _),
      explorado(L, E, D),
      ( D = 0, E = 0, \+ no_meio_da_escada(Pos) -> Mov = direita
      ; D = 1, E = 0, \+ no_meio_da_escada(Pos) -> Mov = esquerda
      ; D = 1, E = 1, \+ subir(Pos, _), \+ no_meio_da_escada(Pos) -> Mov = direita
      ; D = 1, E = 1, subir(Pos, _) -> Mov = subir
      ; Mov = esperar
      )
    ).

%Realiza a movimenta��o autom�tica do agente, em busca da vit�ria do jogo.
busca(PosAtual) :-
    proximo_movimento(PosAtual, MovSugerido),
    movimento_seguro(PosAtual, MovSugerido, MovFinal),
    ( MovFinal = subir -> assert(subiu) ; retractall(subiu) ),
    jogar(MovFinal),
    jogador_atual(estado(PosNova)),
    checar_reset_exploracao(PosAtual, PosNova),
    atualizar_explorado(PosNova),
    sleep(0.2),
    busca(PosNova).

%Coloca a posi��o inicial do agente como explorada.
buscar_inicio_e_atualizar( (L,C) ) :-
    atualizar_explorado((L,C)).

% Execu��o autom�tica do agente inteligente
agente_inteligente :-
    retractall(visitado(_)),
    retractall(subiu),
    inicializar_jogo,
    inicializar_exploracao,
    jogador_atual(estado(PosInicial)),
    buscar_inicio_e_atualizar(PosInicial),
    busca(PosInicial).

% Comando para limpar tudo
reset_completo :-
    retractall(jogador_atual(_)),
    retractall(barril(_,_)),
    retractall(proximo_id(_)),
    retractall(explorado(_,_,_)),
    retractall(visitado(_)),
    retractall(martelo(_)),
    retractall(subiu),
    retractall(tem_martelo),
    write('Mem�ria completamente limpa!'), nl.
