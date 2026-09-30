/* É o código utilizado para destruir objetos que não foram pegos pelo pássaro, seja para empilhar ou desempilhar, e saíram do cenário */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroiObjetos : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    void OnCollisionEnter2D(Collision2D outro)
    {
        if (outro.gameObject.CompareTag("empilha"))
        {
            Destroy(outro.gameObject);
        }
        if (outro.gameObject.CompareTag("desempilha"))
        {
            Destroy(outro.gameObject);
        }
        if (outro.gameObject.CompareTag("verde"))
        {
            Destroy(outro.gameObject);
        }
        if (outro.gameObject.CompareTag("amarelo"))
        {
            Destroy(outro.gameObject);
        }
        if (outro.gameObject.CompareTag("vermelho"))
        {
            Destroy(outro.gameObject);
        }
        if (outro.gameObject.CompareTag("azul"))
        {
            Destroy(outro.gameObject);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
