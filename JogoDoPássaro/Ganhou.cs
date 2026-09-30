/* É o código utilizado para a cena ganhou o jogo. */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Ganhou : MonoBehaviour
{
    [SerializeField] private string nomeDoLevelDeJogo;
    [SerializeField] private GameObject painelMenuInicial;

    public void menu()
    {
        SceneManager.LoadScene(nomeDoLevelDeJogo);
    }
}
