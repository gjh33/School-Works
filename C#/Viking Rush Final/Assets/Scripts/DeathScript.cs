using UnityEngine;
using System.Collections;

public class DeathScript : MonoBehaviour {

	//public
	public bool runScript = false;
	public GameObject comItem;
	public GameObject rareItem;
	public GameObject legendItem;
	public GameObject Ground;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void FixedUpdate () {
		if (runScript) {
			death ();
			runScript = false;
		}
	}

	//DeathScript
	void death() {
		int roll = Random.Range (1, 101);
		GameObject temp;
		Vector2 tmp;
		Rigidbody2D rb;
		//Legend
		if (roll == 1) {//1/1000 chance
			temp = Instantiate (legendItem);
			temp.transform.parent = Ground.transform;
			temp.name = "LegendItem";
			rb = temp.GetComponent<Rigidbody2D>();
			tmp = rb.position;
			tmp.x = GetComponent<Rigidbody2D>().position.x;
			tmp.y = GetComponent<Rigidbody2D>().position.y + 0.5f;
			rb.position = tmp;
		}
		//Rare
		else if (roll > 1 && roll <= 5) {//2,3,4,5 for a 1/250 chance
			temp = Instantiate (rareItem);
			temp.transform.parent = Ground.transform;
			temp.name = "RareItem";
			rb = temp.GetComponent<Rigidbody2D>();
			tmp = rb.position;
			tmp.x = GetComponent<Rigidbody2D>().position.x;
			tmp.y = GetComponent<Rigidbody2D>().position.y + 0.5f;
			rb.position = tmp;
		}
		//Common
		else if (roll > 5 && roll <= 25) {//6,7,8,...,25 for 20/1000 = 1/50 chance
			temp = Instantiate (comItem);
			temp.transform.parent = Ground.transform;
			temp.name = "CommonItem";
			rb = temp.GetComponent<Rigidbody2D>();
			tmp = rb.position;
			tmp.x = GetComponent<Rigidbody2D>().position.x;
			tmp.y = GetComponent<Rigidbody2D>().position.y + 0.5f;
			rb.position = tmp;
		}
		GameObject.Destroy (this.gameObject);
	}
}
