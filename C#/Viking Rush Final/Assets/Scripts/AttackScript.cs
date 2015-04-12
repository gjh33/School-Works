using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class AttackScript : MonoBehaviour {
	//private
	private BoxCollider2D cl;
	private BoxCollider2D[] cls;
	private EnemyManager enemyMan;
	private ItemData ID;
	private bool isAttacking = false;
	private List<GameObject> hasDealtDamage = new List<GameObject>();
	private List<GameObject> isHitting = new List<GameObject> ();
	private float oldRange = 0;
	private int ASCount;
	private CustomAnimator animator;
	//public
	public GameObject EquipedObject;

	// Use this for initialization
	void Start () {
		//get animator
		animator = GetComponent<CustomAnimator> ();
		//get both colliders, and check which one is the trigger which we want
		cls = GetComponents<BoxCollider2D> ();
		if (cls [0].isTrigger == true) {
			cl = cls[0];
		} 
		else {
			cl = cls[1];
		}
		//set ItemData
		ID = EquipedObject.GetComponent<ItemData> ();
		//set Collider Bounds
		Vector2 tmp = cl.size;
		tmp.x += (ID.Range / 100);//this is math done after playing around. Seems to work well.
		cl.size = tmp;
		tmp = cl.offset;
		tmp.x -= ((ID.Range / 100) / 2);//seperated the /2 to clarify what's going on. I'm adjusting the new position
		cl.offset = tmp;
		oldRange = ID.Range;
	}

	//Collision
	void OnTriggerEnter2D(Collider2D col) {
		if (col.gameObject.name == "Enemy") {
			isHitting.Add (col.gameObject);
		}
	}
	void OnTriggerExit2D(Collider2D col) {
		if (col.gameObject.name == "Enemy") {
			isHitting.Remove(col.gameObject);
		}
	}

	// Update is called once per frame
	void Update () {
		if (isAttacking){
			int i;
			for (i=0; i < isHitting.Count; i++){
				if (!hasDealtDamage.Contains (isHitting[i])){
					if(isHitting[i] == null) {
						isHitting.RemoveAt(i);
						i--;
						continue;
					}
					enemyMan = isHitting[i].GetComponent<EnemyManager>();
					enemyMan.DamageGiven = ID.Damage;
					isHitting[i].GetComponent<Rigidbody2D>().AddForce (new Vector2((ID.KnockBack/2)+5, (ID.KnockBack/4)), ForceMode2D.Impulse);
					hasDealtDamage.Add (isHitting[i]);
				}
			}
		}
		//Attack Speed
		if (ASCount > 0) {
			ASCount--;
		}
		//ATTACK
		if (Input.GetKey (KeyCode.Z) && ASCount == 0) {
			animator.Attack ();
			ASCount = (int)ID.AttackSpeed;
			isAttacking = true;
		}
		if (animator.AAnimInd == -1) {
			isAttacking = false;
		}
		if (!isAttacking && hasDealtDamage.Count > 0) {
			hasDealtDamage.Clear ();
		}
	}
	

	void UpdateWeapon () {
		ID = EquipedObject.GetComponent<ItemData> ();
		animator.SetWeapon (ID.type);
		float dif = ID.Range - oldRange;
		Vector2 tmp = cl.size;
		tmp.x += (dif / 100);
		cl.size = tmp;
		tmp = cl.offset;
		tmp.x -= ((dif / 100) / 2);
		cl.offset = tmp;
		oldRange = ID.Range;
	}

	//DELETE TEMPORARY
	void OnCollisionStay2D(Collision2D col) {
		if (Input.GetKey (KeyCode.X)) {
			if (col.gameObject.name == "LegendItem" || col.gameObject.name == "RareItem" || col.gameObject.name == "CommonItem") {
				EquipedObject = col.gameObject;
				UpdateWeapon ();
				Destroy (col.gameObject);
			}
		}
	}
}
