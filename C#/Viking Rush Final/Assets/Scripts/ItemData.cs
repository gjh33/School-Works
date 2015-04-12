using UnityEngine;
using System.Collections;

public class ItemData : MonoBehaviour {

	//public
	public float AttackSpeed = 0;
	public float Damage = 0;
	public float Range = 0;
	public float KnockBack = 0;
	public int type = 0; //0 = Sword | 1 = Trident | 2 = Axe | 3 = Warhammer

	//private
	private float asMod = 0;
	private float damMod = 0;
	private float rangeMod = 0;
	private float kbMod = 0;

	// Use this for initialization
	void Start () {
		//roll weapon class
		type = Random.Range (0, 4);

		//Set modifiers for stat roles by weapon class
		switch (type) {
		case 1:
			asMod = 10;//nerf attack speed
			damMod = 10;//buff dmg
			rangeMod = 10;//buf range
			break;
		case 2:
			asMod = -10;//attack speed buff
			damMod = -10;//damage nerf
			rangeMod = -5;//range nerf
			break;
		case 3:
			damMod = 10;//buff dmg
			rangeMod = -5;//nerf range
			kbMod = 10;//buff knockback
			break;
		}

		//roll stats
		if (gameObject.name == "LegendItem") {
			AttackSpeed = Random.Range (10 + asMod, 21 + asMod);
			Damage = Random.Range (101 + (damMod * 5), 1001 + (damMod * 50));
			Range = Random.Range (81 + (4 * rangeMod), 121 + (4 * rangeMod));
			KnockBack = Random.Range (41 + kbMod, 61 + kbMod);
		} 
		else if (gameObject.name == "RareItem") {
			AttackSpeed = Random.Range (21 + asMod, 41 + asMod);
			Damage = Random.Range (51 + (damMod*2), 101 + (damMod*2));
			Range = Random.Range (41 + (2 * rangeMod), 81 + (2 * rangeMod));
			KnockBack = Random.Range (21 + kbMod, 41 + kbMod);
		} 
		else if (gameObject.name == "CommonItem") {
			AttackSpeed = Random.Range(41+asMod, 61+asMod);
			Damage = Random.Range (35+damMod, 51+damMod);
			Range = Random.Range (21+rangeMod, 41+rangeMod);
			KnockBack = Random.Range (10+kbMod, 21+kbMod);
		}
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
