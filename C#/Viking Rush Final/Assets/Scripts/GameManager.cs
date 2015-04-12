using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class GameManager : MonoBehaviour {

	public Button start;
	public GameObject player;
	public GameObject ground;
	public GameObject title;
	public GameObject gameOver;
	private CameraBehavior cmBhvr;

	public void startGame() {
		start.interactable = false;
		start.GetComponent<CanvasGroup> ().alpha = 0;
		title.GetComponent<CanvasGroup> ().alpha = 0;
	}
	
	void endGame() {
		gameOver.GetComponent<CanvasGroup> ().alpha = 1;
	}

	void Start() {
		cmBhvr = ground.GetComponent<CameraBehavior> ();
	}
	

	void Update() {
		if (player.transform.position.y <= -10) {
			cmBhvr.isRunning = false;
			endGame ();
		}
	}
}
