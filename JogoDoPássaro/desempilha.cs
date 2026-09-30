/* É o código utilizado para os objetos gaiola e avião, que basicamente atribui movimento a eles e se colidir com o pássaro controlado pelo
usuário, o próprio objeto é destruído. */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class desempilha : MonoBehaviour
{
    public float vel = 2.5f;
    
    void movimenta()
    {
        transform.Translate(new Vector3(-vel * Time.deltaTime, 0, 0));
    }
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        movimenta();
    }

    void OnCollisionEnter2D(Collision2D outro)
    {
        if (outro.gameObject.CompareTag("empilha"))
        {
            Destroy(this.gameObject);
        }
    }
}
