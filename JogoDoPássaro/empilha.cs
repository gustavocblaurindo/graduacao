using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class empilha : MonoBehaviour
{
    public float vel = 2.5f;

    void inputTeclado()
    {
        if (Input.GetKey(KeyCode.UpArrow))
        {
            transform.Translate(new Vector3(0, vel * Time.deltaTime, 0));
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            transform.Translate(new Vector3(0, -vel * Time.deltaTime, 0));
        }
    }


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        inputTeclado();
    }
}
