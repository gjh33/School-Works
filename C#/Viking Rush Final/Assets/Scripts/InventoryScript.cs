using UnityEngine;
using System.Collections;

public class InventoryScript : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnCollisionEnter2D(Collision2D col){
		if (col.gameObject.name == "LegendItem" || col.gameObject.name == "RareItem" || col.gameObject.name == "CommonItem") {

		}
	}
}
