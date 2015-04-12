using UnityEngine;
using System.Collections;

public class Movement : MonoBehaviour {

	//private values
	private Rigidbody2D rb;
	private Collider2D cl;
	private float maxX;
	private float minX;
	private bool isJumping;
	private Camera cam;
	private CustomAnimator animator;

	//public values
	public float JumpForce;
	public float MoveSpeed;
	public float AirSpeed;

	//calculated values
	private Vector2 JumpVector;
	private Vector2 MoveVector;


	// Use this for initialization
	void Start () {
		JumpVector.x = 0;
		JumpVector.y = JumpForce;
		isJumping = false;
		rb = GetComponent<Rigidbody2D> ();
		cl = GetComponent<Collider2D> ();
		cam = GameObject.FindObjectOfType<Camera> ();
		animator = GetComponent<CustomAnimator> ();
	}
	
	// Update is called once per frame

	void Update () {
		animator.Run ();
	}
	void FixedUpdate () {
		//Move Vector Init
		MoveVector = rb.velocity;
		//set base velocity
		if (!isJumping) {
			MoveVector.x = 0;
		}
		//Movement Commands
		if (Input.GetKey (KeyCode.RightArrow)) {
			if (!isJumping) {
				MoveVector.x += MoveSpeed;
			}
			else {
				MoveVector.x += AirSpeed;
				//hardcap
				if(MoveVector.x > MoveSpeed){
					MoveVector.x = MoveSpeed;
				}
			}
		}
		if (Input.GetKey (KeyCode.LeftArrow)) {
			if(!isJumping){
				MoveVector.x -= MoveSpeed;
			}
			else {
				MoveVector.x -= AirSpeed;
				//hardcap
				if(MoveVector.x < -MoveSpeed) {
					MoveVector.x = -MoveSpeed;
				}
			}
		}
		if (Input.GetKey (KeyCode.Space) && !isJumping) {
			MoveVector.y = JumpForce;
			isJumping = true;
		}
		//Position Correction
		minX = cam.ScreenToWorldPoint (Vector3.zero).x;
		Vector3 tmp = new Vector3();
		tmp.x = cam.pixelWidth;
		maxX = cam.ScreenToWorldPoint (tmp).x;
		if ((cl.bounds.min.x + (MoveVector.x/100)) < minX) {//BECAUSE FOR SOME FUCKING REASON UNITY SEES MY MOVEVECTOR AS MULTIPLIED BY 100!!!!!! FOR NO REASON
			tmp = rb.position;
			tmp.x = minX + cl.bounds.extents.x;
			rb.position = tmp;
			MoveVector.x = 0;
		}
		else if ((cl.bounds.max.x + (MoveVector.x/100)) > maxX) {//SEE ABOVE RANT
			tmp = rb.position;
			tmp.x = maxX - cl.bounds.extents.x;
			rb.position = tmp;
			MoveVector.x = 0;
		}
		//Final Velocity Set
		rb.velocity = MoveVector;
	}

	//Collision Test for jump reset
	void OnCollisionEnter2D (Collision2D col) {
		if (col.gameObject.name == "Ground") {
			isJumping = false;
		}
	}	
}
