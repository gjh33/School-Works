using UnityEngine;
using System.Collections;

public class InsanityBarManager : MonoBehaviour {

	public GameObject owner; //who this healthbar is displaying
	public Sprite greyBar;
	public Sprite redBar;

	private CharProperties ownerProp;
	private GameObject underBar;

	// Use this for initialization
	void Start () {
		ownerProp = owner.GetComponent<CharProperties> ();
		underBar = GameObject.Find ("Underbar");
	}
	
	// Update is called once per frame
	void Update () {
		underBar.transform.localScale = new Vector3 (ownerProp.insanity / 100, 1, 1);
		if (ownerProp.insanity < 30) {
			underBar.GetComponent<SpriteRenderer> ().sprite = redBar;
		} 
		else {
			underBar.GetComponent<SpriteRenderer> ().sprite = greyBar;
		}
	}
}
