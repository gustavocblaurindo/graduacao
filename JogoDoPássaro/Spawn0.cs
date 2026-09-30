/* É o código utilizado para criar objetos aleatórios como pássaros de cores diferentes e aviões/gaiolas */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawn0 : MonoBehaviour
{
    public GameObject[] spawn;
    int quantidade;
    public float spawntime;
    public float spawndelay;

    void SpawnObjetos()
    {
        quantidade = Random.Range(0, spawn.Length);
        Instantiate(spawn[quantidade], transform.position, transform.rotation);
    }

    
    // Start is called before the first frame update
    void Start()
    {
        InvokeRepeating("SpawnObjetos", spawntime, spawndelay);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
