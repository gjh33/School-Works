using UnityEngine;
using System.Collections;

public class CharProperties : MonoBehaviour {

	public float insanity;
	public int lightLevel;
	public bool isInLight;

	// Use this for initialization
	void Start () {
		insanity = 100;
		lightLevel = 1;
		isInLight = true;
	}
}
