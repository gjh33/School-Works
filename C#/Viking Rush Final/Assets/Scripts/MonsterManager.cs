using UnityEngine;
using System.Collections;

public class MonsterManager : MonoBehaviour {
	public GameObject monster1;
	public GameObject Ground;
	//private
	private EnemyManager em;
	//Transform enemyTransform;
	public int numMonsters;
	//public float speed;
	public float xPos;
	public float yPos;
	
	void Start () {
		for (int i=0; i<numMonsters; i++) {
			GameObject temp = Instantiate (monster1);
			em = temp.GetComponent<EnemyManager>();
			em.Health = 50 + (xPos/2);
			em.MaxHealth = 50 + (xPos/2);
			em.Damage = 10 + Mathf.Round (xPos/10);
			temp.transform.parent = Ground.transform;
			temp.transform.position = new Vector3 (xPos, yPos, 0f);
			temp.name = "Enemy";
			temp.GetComponent<DeathScript>().Ground = Ground;
			xPos = xPos + Random.Range (4, 16); 
		}

	}
	
	void Update(){
		//transform.LookAt(target);
		//move towards the player
		//enemyTransform.position += transform.up * speed * Time.deltaTime;

		//MoveVector = rb.velocity;
		//MoveVector.x -= speed;
	}
}
