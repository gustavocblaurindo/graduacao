using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/* O cenário do jogo está em um objeto 3D. O código abaixo é para que o objeto em 3D
realize um loop infinito em torno do eixo x, dando a sensação do cenário do jogo ser 
infinito. */

public class infinitocenario : MonoBehaviour
{
    public float vel = 0.1f;
    public Renderer quad;

    void giraObjeto3D()
    {
        Vector2 offset = new Vector2(vel * Time.deltaTime, 0);
        quad.material.mainTextureOffset += offset;
    }
    //O start só executa uma vez.
    void Start()
    {
        
    }
    
    //O Update executa infinitamente vezes.
    void Update()
    {
        giraObjeto3D();
    }
}
