using UnityEngine;
using System.Collections;

public class MovementScript : MonoBehaviour {
	/*
	 * LightGame_MovementScript.cs
	 * Author: Luke Jones
	 * Use: Player Controlled movement
	 * Details: Smooth movement that follows the mouse. Customizable
	 */

	//public variables
	public bool slowTurn; //slow down on turns?
	public float speed; //max speed your character reach
	public float acceleration; //acceleration to meet that max speed
	public float angularAcceleration; //how fast the object accelerates
	public float maxRotationSpeed; //max speed the object can rotate at
	//private variables
	private Vector2 charToMouse; //used to store vector between char and mouse
	private float Mag_charToMouse; //used to store the magnitude of charToMouse
	private float angleCharToMouse; //the angle between the char and the mouse.
	private Quaternion Qhelper; //Rotation of the character as if it were currently facing the mouse (used to find the angle between current char, and the mouse)
	private Vector3 mousePosition; //used to store mouse position
	private Vector2 mousePosition2D; //The projection of mousePosition unto the 2D plane
	private Vector3 charPosition; //used to store position of char
	private Vector2 charPosition2D; //The projection of charPosition unto the 2D plane
	private Camera mainCamera; //the main camera
	private Animator anim; //the animator so i can access variables
	private float torqueM; //the torque applied based on angularAcceleration
	private Rigidbody2D rb; //the rigid body for the attached character
	private float initialADrag; //used to record the initial angular drag of the rigidbody
	private float initialDrag; //used to record the initial linear drag of the rigidbody
	private bool hasRClipped; //used to see if we've already clipped to place
	private bool hasClipped; //same but for motion not rotation


	// Use this for initialization
	void Start () {
		//get the main camera by type
		mainCamera = GameObject.FindObjectOfType<Camera> ();
		//get the animator
		anim = GetComponent<Animator> ();
		//get the rigidbody
		rb = GetComponent<Rigidbody2D> ();
		//set the torque
		torqueM = angularAcceleration / 1000;
		//set angular drag
		initialADrag = rb.angularDrag;
		initialDrag = rb.drag;
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButton (0)) {
			//Set up variables
			mousePosition = mainCamera.ScreenToWorldPoint(Input.mousePosition);
			mousePosition2D = new Vector2(mousePosition.x, mousePosition.y);
			charPosition = transform.position;
			charPosition2D = new Vector2(charPosition.x, charPosition.y);
			charToMouse = mousePosition2D-charPosition2D;
			Mag_charToMouse = charToMouse.magnitude;
			//see NOTES index 1 at the bottom for explanation of the following line
			angleCharToMouse = (((Mathf.Rad2Deg * Mathf.Atan2(charToMouse.y, charToMouse.x))+180+90)%360) - gameObject.transform.rotation.eulerAngles.z;
			//by doing this next part, we remove negative values and always get x<180 mouse is left, x>180 mouse is right.
			if (angleCharToMouse < 0) {
				angleCharToMouse += 360;
			}

			//Rotation
			//acceleration is less buggy at higher values. This is due to the user moving the mouse a huge rotation between frames
			rb.angularDrag = 0;
			if(angularAcceleration != -1) {
				if (angleCharToMouse < 180 && angleCharToMouse > 5 && charToMouse.magnitude > 0.5){
					rb.AddTorque (torqueM, ForceMode2D.Impulse);
					hasRClipped = false;
				}
				else if (angleCharToMouse > 180 && angleCharToMouse < 355 && charToMouse.magnitude > 0.5){
					rb.AddTorque (-torqueM, ForceMode2D.Impulse);
					hasRClipped = false;
				}
			}
			else{
				gameObject.transform.eulerAngles = new Vector3 (0,0, ((Mathf.Rad2Deg * Mathf.Atan2(charToMouse.y, charToMouse.x))+180+90)%360);
			}
			//check the new speed and if it's too fast, set it to the max speed
			if (maxRotationSpeed != -1) {
				if (rb.angularVelocity > maxRotationSpeed) {
					rb.angularVelocity = maxRotationSpeed;
				}
				else if (rb.angularVelocity < -maxRotationSpeed){
					rb.angularVelocity = -maxRotationSpeed;
				}
			}
			//check to see if character is going to pass the mouse then set it's rotation to the mouse
			if ((angleCharToMouse + (rb.angularVelocity * Time.fixedDeltaTime)) < 0 || (angleCharToMouse + (rb.angularVelocity * Time.fixedDeltaTime)) > 360) {
				if (!hasRClipped) {
					rb.angularVelocity = 0;
					gameObject.transform.eulerAngles = new Vector3 (0,0, ((Mathf.Rad2Deg * Mathf.Atan2(charToMouse.y, charToMouse.x))+180+90)%360);
					hasRClipped = true;
				}
			}

			//Movement
			rb.drag = 0;
			//without acceleration
			//recommend not using this with angular acceleration. Probably best to set angular acceleration to -1
			if (acceleration == -1) {
				if (charToMouse.magnitude > 0.5){
					//get normalized vector representing the current direction of the object
					//find the angle of the object's facing in standard position from -PI to PI
					float curAngle = gameObject.transform.rotation.eulerAngles.z; // 0 to 360 facing north
					curAngle = (curAngle + 270)%360 - 180; // this is setting it to standard position then -180 sets the domain to -PI to PI
					//convert to radians
					curAngle = curAngle * Mathf.Deg2Rad;
					//build and normalize
					Vector2 curDirection = new Vector2(Mathf.Cos(curAngle), Mathf.Sin(curAngle));//gets the vector with the correct angle
					curDirection.Normalize();//normalizes the vector
					//multiply vector by speed. 0 speed = 0 magnitude of vector, 1 speed = 1 magnitude. x = x magnitude
					curDirection = curDirection * speed;
					//apply the motion
					rb.velocity = curDirection;
					hasClipped = false;
				}
				//check to see if character is going to pass the mouse, if so set his position accordingly
				Vector2 nextPosition = rb.position + (rb.velocity * Time.fixedDeltaTime);
				//nextPosition = mousePosition2D - nextPosition;
				if (charToMouse.magnitude - (nextPosition - rb.position).magnitude < 0) {
					if (!hasClipped) {
						rb.velocity = Vector2.zero;
						rb.position = mousePosition2D;
						hasClipped = true;
					}
				}
			}
			else{
				rb.drag = initialDrag;
				//get normalized vector representing the current direction of the object
				//find the angle of the object's facing in standard position from -PI to PI
				float curAngle = gameObject.transform.rotation.eulerAngles.z; // 0 to 360 facing north
				curAngle = (curAngle + 270)%360 - 180; // this is setting it to standard position then -180 sets the domain to -PI to PI
				//convert to radians
				curAngle = curAngle * Mathf.Deg2Rad;
				//build and normalize
				Vector2 curDirection = new Vector2(Mathf.Cos(curAngle), Mathf.Sin(curAngle));//gets the vector with the correct angle
				curDirection.Normalize();//normalizes the vector
				//use angleCharToMouse to calculate what % of acceleration the object should accelerate. Please see note 2
				float tmp_ACM = angleCharToMouse; //so we can modify the value without affecting original value
				if (tmp_ACM > 180) {
					tmp_ACM = 360 - tmp_ACM;//this makes the angle 0 to 180 on either side, rather than 360 to the right and 1 to the left, it will now be 1 to both sides
				}
				float multipier = tmp_ACM/180;//this is our multiplier that will be between 0 and 1
				multipier = 1-multipier; //makes it correct
				//simple acceleration when outside the deaccell range
				if (charToMouse.magnitude > 0.5) {
					if (slowTurn) {
						rb.AddForce((curDirection * acceleration * (rb.drag + 1)) * multipier / 100, ForceMode2D.Impulse);
					}
					else {
						rb.AddForce((curDirection * acceleration * (rb.drag + 1)) / 100, ForceMode2D.Impulse);
					}
				}
				//complex acceleration when inside deaccRange

				//checking max speed
				if (rb.velocity.magnitude > speed && speed != -1) {
					rb.velocity = rb.velocity.normalized * speed;
				}
			}
		}
		//when release stop movement
		if (Input.GetMouseButtonUp (0)) {
			rb.angularDrag = initialADrag;
			rb.drag = initialDrag;
		}
		//set animation
		anim.SetFloat ("speed", rb.velocity.magnitude);
	}
}

//NOTES
/*
 * 1 ================================================================
 * angleCharToMouse = (((Mathf.Rad2Deg * Mathf.Atan2(charToMouse.y, charToMouse.x))+180+90)%360) - gameObject.transform.rotation.eulerAngles.z;
 * start with (Mathf.Rad2Deg * Mathf.Atan2(charToMouse.y, charToMouse.x), this is the absolute angle. However our game object starts facing up, so we need to correct for this
 * by adding +90 to the end. The + 180 is because it current only gives values -180 to 180 and we want the domain 0 to 360.
 * modding it my 360 makes sure we are extra gucci
 * We did all this so the subtraction of the rotation of the player makes sense. The rotation of euler angle z when mouse is JUST to the right is 360, and JUST to the left is 1
 * with 0 being directly above. That's why we needed to make those adjustments to our raw angle in standard degrees.
 * 2 ================================================================
 * movement in odd directions
 * When the character is facing away from the mouse, you don't want him to accelerate away from the mouse, so we assign a % value based on the facing of the object
 * if the object is facing the cursor completely it will accelerate at 100% of acceleration speed in it's current direction. If it's facing away it will
 * accelerate at 0% of it's acceleration speed. 90 degrees will be 50% of it's acceleration speed.
 */

