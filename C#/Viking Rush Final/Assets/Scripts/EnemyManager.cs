using UnityEngine;
using System.Collections;

public class EnemyManager : MonoBehaviour {

	//public
	public float Damage;//damage alien deals
	public float Health;//alien's current health
	public float MaxHealth;//alien's max health
	public float Type;//this is for if we have different types of aliens, or you can make their stats scale as we go along. Up to you.
	[HideInInspector]
	public float DamageGiven;

	//private
	private DeathScript ds;

	// Use this for initialization
	void Start () {
		DamageGiven = 0;
		ds = GetComponent<DeathScript> ();
	}
	
	// Update is called once per frame
	void Update () {
		if (DamageGiven > 0) {
			Health -= DamageGiven;
			DamageGiven = 0;
		}
		if (Health <= 0) {
			ds.runScript = true;
		}
	}
}
