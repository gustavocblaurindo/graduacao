using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class passaroinverso : MonoBehaviour
{
    public float vel = 2.5f;

    void movimenta()
    {
        transform.Translate(new Vector3(-vel * Time.deltaTime, 0, 0));
    }

    void OnCollisionEnter2D(Collision2D outro)
    {
        if (outro.gameObject.CompareTag("empilha"))
        {
            Destroy(this.gameObject);
        }
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
}
