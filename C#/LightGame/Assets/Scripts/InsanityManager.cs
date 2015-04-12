using UnityEngine;
using System.Collections;

public class InsanityManager : MonoBehaviour {

	public float dropRate;

	private CharProperties prop;
	private GameObject TheLight;

	// Use this for initialization
	void Start () {
		prop = GetComponent<CharProperties> ();
		TheLight = GameObject.Find ("The Light");
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 charPos = gameObject.transform.position;
		Vector3 lightPos = TheLight.transform.position;
		Vector2 lightToChar = new Vector2 (charPos.x - lightPos.x, charPos.y - lightPos.y);
		if (lightToChar.magnitude > getRadius (prop.lightLevel)) {
			prop.insanity -= dropRate;
			if (prop.insanity < 0) prop.insanity = 0;
		}
	}

	float getRadius(int level) {
		float toRet = 11.5f;
		switch (level) {
		case 1:
			toRet = 5.5f;
			break;
		case 2:
			toRet = 20f;
			break;
		}
		return toRet;
	}
}
