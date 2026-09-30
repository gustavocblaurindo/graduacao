/* É o código utilizado para a cena perdeu o jogo */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Perdeu : MonoBehaviour
{
    [SerializeField] private string nomeDoLevelDeJogo;
    [SerializeField] private string nomeDoLevelDeJogo2;

    public void menu()
    {
        SceneManager.LoadScene(nomeDoLevelDeJogo);
    }

    public void reiniciar()
    {
        SceneManager.LoadScene(nomeDoLevelDeJogo2);
    }
}
