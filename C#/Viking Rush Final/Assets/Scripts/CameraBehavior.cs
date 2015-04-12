using UnityEngine;
using System.Collections;

public class CameraBehavior : MonoBehaviour {
	public float speed;
	public bool isRunning;
	private Transform rb;

	void Start() {
		rb = GetComponent<Transform> ();
	}

	// To start the game
	public void startGame(){
		isRunning = true;
	}

	void FixedUpdate () {
		if (isRunning) {
			Vector3 tmp;
			tmp = rb.position;
			tmp.x -= speed;
			rb.position = tmp;
		}
	}
}