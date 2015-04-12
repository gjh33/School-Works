using UnityEngine;
using System.Collections;

public class BlockManager : MonoBehaviour {

	public GameObject block1;
	public GameObject block2;
	public GameObject block3;
	public GameObject block4;
	public GameObject block5;


	public int numBlocks;
	public float xPos;
	public float yPos;
	public GameObject Ground;

	// Use this for initialization
	void Start () {

		for (int i=0; i<numBlocks; i++) {
			float tmp = 0;
			float rand = 0;
			bool isValid = false;

			while(!isValid){
				tmp = Random.value*10;
				rand = Mathf.Round(tmp);
				if(rand <= 5.0){
					isValid = true;
				}

			}
			if(rand == 1.0){
				GameObject temp = Instantiate(block1);
				temp.transform.parent = Ground.transform;
				temp.transform.position = new Vector3(xPos, yPos, 0f);
				temp.name = "Ground";
				xPos = xPos + 20f;
			} else if(rand == 2.0){
				GameObject temp = Instantiate(block2);
				temp.transform.parent = Ground.transform;
				temp.transform.position = new Vector3(xPos, yPos, 0f);
				temp.name = "Ground";
				xPos = xPos + 12f;
			} else if(rand== 3.0){
				GameObject temp = Instantiate(block3);
				temp.transform.parent = Ground.transform;
				temp.transform.position = new Vector3(xPos, yPos, 0f);
				temp.name = "Ground";
				xPos = xPos + 20f;
			} else if(rand== 4.0){
				GameObject temp = Instantiate(block4);
				temp.transform.parent = Ground.transform;
				temp.transform.position = new Vector3(xPos, yPos, 0f);
				temp.name = "Ground";
				xPos = xPos + 12f;
			} else {
				GameObject temp = Instantiate(block5);
				temp.transform.parent = Ground.transform;
				temp.transform.position = new Vector3(xPos, yPos, 0f);
				temp.name = "Ground";
				xPos = xPos + 10f;
			}
		}
	
	}
}
