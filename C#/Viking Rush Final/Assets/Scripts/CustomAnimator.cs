using UnityEngine;
using System.Collections;

public class CustomAnimator : MonoBehaviour {

	/* Hi, Welcome to my animator. Here's a quick guide to get started!
	 * frameDelay slows down the framerate of the animation to change the speed of the animation
	 * IdleSword is the sprite that is shown when not attacking with Sword equipped
	 * The following Idles variables are similar
	 * BodyIdle is for when you're not walking
	 * For each animation, line up the sprites in the order of the animation. When calling that animation, they will play in that order.
	 * You can use RAnimInd and AAnimInd to see if the animation has stopped. If it is not running, the value will be -1. Else it is the current frame of the animation
	 * 
	 * Run() starts the run animation. Calling this again will have no affect until the animation is finished
	 * StopRun() Cancels the current Run() animation and resets back to Idle
	 * Attack() starts the current attack animation based on your current weapon. Has same behavior as Run()
	 * StopAttack() Cancels the current Attack() animation and resets to the idle of your current weapon
	 * SetWeapon() takes an in 0 to 3 and sets the animator's animation set to that weapon.
	 * 		0 = Sword
	 * 		1 = Trident
	 * 		2 = Axe
	 * 		3 = Hammer
	 */

	//private
	private int weapon = 0;
	private Sprite currentIdle;
	private SpriteRenderer SR;
	private SpriteRenderer ChildSR;
	private int delayCount = 0;

	//Settings
	public int frameDelay = 0;

	//Idle Sprites
	public Sprite IdleSword;
	public Sprite IdleTrident;
	public Sprite IdleAxe;
	public Sprite IdleHammer;
	public Sprite BodyIdle;

	//Animation Sets
	public Sprite[] RunAnim; //the sprites in order for the run animation
	public Sprite[] SwordAttack; //the sprites in order for the sword attack
	public Sprite[] TridentAttack; //the sprites in order for the trident attack
	public Sprite[] AxeAttack; //the sprites in order for the axe attack
	public Sprite[] HammerAttack; //the sprites in order for the hammer attack

	//Run States
	[HideInInspector]
	public int RAnimInd = -1;

	//Attack States
	[HideInInspector]
	public int AAnimInd = -1;



	// Use this for initialization
	void Start () {
		currentIdle = IdleSword;
		SR = GetComponent<SpriteRenderer> ();
		ChildSR = transform.GetChild (0).gameObject.GetComponent<SpriteRenderer> ();
		Debug.Log (ChildSR.sprite);
	}
	
	// Update is called once per frame
	void Update () {
		if (delayCount == 0) {
			delayCount = frameDelay;
			Animate ();
		} else {
			delayCount--;
		}
	}

	public void Run() {
		if (RAnimInd == -1) {
			RAnimInd = 0;
		}
	}

	public void StopRun() {
		if (RAnimInd != -1) {
			RAnimInd = -1;
			SR.sprite = BodyIdle;
		}
	}

	public void Attack() {
		if (AAnimInd == -1) {
			AAnimInd = 0;
		}
	}

	public void StopAttack() {
		if (AAnimInd != -1) {
			AAnimInd = -1;
			ChildSR.sprite = currentIdle;
		}
	}

	public void SetWeapon(int type){
		weapon = type;
		switch (weapon) {
		case 0:
			currentIdle = IdleSword;
			break;
		case 1:
			currentIdle = IdleTrident;
			break;
		case 2:
			currentIdle = IdleAxe;
			break;
		case 3:
			currentIdle = IdleHammer;
			break;
		}
		ChildSR.sprite = currentIdle;
	}
	private void Animate() {
		//do Run
		if (RAnimInd != -1) {
			if (RAnimInd == RunAnim.Length) {
				RAnimInd = -1;
				SR.sprite = BodyIdle;
			}
			else {
				SR.sprite = RunAnim[RAnimInd];
				RAnimInd++;
			}
		}
		if (AAnimInd != -1) {
			switch (weapon) {
			case 0:
				if (AAnimInd == SwordAttack.Length) {
					AAnimInd = -1;
					ChildSR.sprite = currentIdle;
				}
				else {
					ChildSR.sprite = SwordAttack[AAnimInd];
					AAnimInd++;
				}
				break;
			case 1:
				if (AAnimInd == TridentAttack.Length) {
					AAnimInd = -1;
					ChildSR.sprite = currentIdle;
				}
				else {
					ChildSR.sprite = TridentAttack[AAnimInd];
					AAnimInd++;
				}
				break;
			case 2:
				if (AAnimInd == AxeAttack.Length) {
					AAnimInd = -1;
					ChildSR.sprite = currentIdle;
				}
				else {
					ChildSR.sprite = AxeAttack[AAnimInd];
					AAnimInd++;
				}
				break;
			case 3:
				if (AAnimInd == HammerAttack.Length) {
					AAnimInd = -1;
					ChildSR.sprite = currentIdle;
				}
				else {
					ChildSR.sprite = HammerAttack[AAnimInd];
					AAnimInd++;
				}
				break;
			}
		}
	}
}
