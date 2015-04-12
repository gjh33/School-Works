using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class StartButtonBehavior : MonoBehaviour {

	public void fadeOut(){
		gameObject.GetComponent<Button> ().interactable = false;
		StartCoroutine (fadeAnimation());
	}
		          

	IEnumerator fadeAnimation(){
		for (int i=0; i<10; i++) {
			gameObject.GetComponent<CanvasGroup>().alpha = gameObject.GetComponent<CanvasGroup>().alpha - 0.1f;
			yield return new WaitForEndOfFrame();
		}
	}
}
