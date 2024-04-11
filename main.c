#include <kipr/wombat.h>

//declare variables
int lmotor = 0;
int rmotor = 3;
int fsensor = 0;
int tsensor = 0;


int lift = 0; 
int pinch = 2;
int sort = 1;

int count = 0;

int straightPause = 2000;
int turnPause = 1400;
int lspeed = 80;
int rspeed = 84;
int veerPower = 100;
int veerSlow = 20;
int conversion = 0;

int speed = 40;
int speed2 = 20;
int turnSpeed = 30;
int revTurn = 10;

//declare functions
void forward(int speed);
void backward();
void turnRight(int pause);
void turnLeft(int pause);
void wait(int wait);
void veerRight();
void veerLeft();
void veerRLoop();
void veerLLoop();
void slowMove();
void mpc();
void negSlowMove();
void mpcBack();
void lineDetect();
void turnRightLoop();
void turnLeftLoop();
void turn();
void rmpc(int distance);
void turnRightSpeed(int pause, int speed);
void lmpc(int distance);
void wallFollowV2();
void wallFollowV3();
void pushTo(int distance);
void pushFrom(int distance);
void push();
void pushBack();
void release(int dis);
void shake(int startPosition);
void lineFollow();



int main()
{
    //reset servos
    enable_servos();
    slowMove(lift, 400, 900, 1);
    negSlowMove(sort, 400, 300, 1);
    negSlowMove(pinch, 800, 700, 1);
    wait(1000);
    
    //go forward until detect line
    lineDetect();
    wait(1000);
    
    
    //line up robot with poms
    rmpc(150);
    wait(1000);
	mpc(160);
    wait(1000);
    negSlowMove(lift, 370, 1400, 3);
    rmpc(5);
    wait(1000);
    //mpc(5);
    wait(1000);
    
    //use swatters to sort poms
    slowMove(sort, 400, 800, 1);
    slowMove(sort, 800, 1900, 5);
    
    wait(2000);
    
    //adjust robot to line up with second pile of poms
    mpcBack(-105);
    wait(1000);
    lmpc(20);
    wait(1000);
    lineDetect();
    wait(1000);
    lmpc(30);
    wait(1000);
    
    //sort second pile of poms
    negSlowMove(sort, 1900, 400, 10);
    //lineFollow();
    
    //while(tsensor<3000){
    	//turnLeftLoop();
    //}   
    
    
    disable_servos();
    return 0;
}


void lineDetect(){
    while (analog(tsensor) < 3800) {
        forward(50);
    }
}

void shake(int startPosition){
	negSlowMove(lift, startPosition, startPosition - 200, 2);
    slowMove(lift, startPosition - 200, startPosition, 2);
}

void lineFollow(){
 	while (analog(5) < 2900) {
        if (analog(tsensor) > 3200){
    		veerLeft();
        } else {
            veerRight();
        }
     }
    ao();
}

// these mpcs move the robot right of left a certain distance
void rmpc(int distance){
    conversion = (1800*distance)/219.44;
	cmpc(lmotor);
    while (gmpc(lmotor) < conversion) {
    	turnRightLoop();
    }
	ao();
}

void lmpc(int distance){
    conversion = (1800*distance)/219.44;
	cmpc(rmotor);
    while (gmpc(rmotor) < conversion) {
    	turnLeftLoop();
    }
	ao();
}

//mpc functions move the robot back and forth a certain distance

void mpc(int distance){
    conversion = (1800*distance)/219.44;
	cmpc(0);
    while (gmpc(0) < conversion) {
    	forward(100);
    }
	ao();
}
       
void mpcBack(int distance){
    conversion = (1800*distance)/219.44;
	cmpc(0);
    while (gmpc(0) > conversion) {
    	backward();
    }
	ao();
}


void wait(int time) {
	ao();
    msleep(time);

}


//slow move functions move servo to a certain positions with a specific speed
void slowMove(int port, int startPosition, int  endPosition, int time){
    while (startPosition <= endPosition) {
        //enable_servos();
    	set_servo_position(port, startPosition);
		msleep(1);
		startPosition += time;
    	//disable_servos();
	}
    
}

void negSlowMove(int port, int startPosition, int  endPosition, int time){
    while (startPosition >= endPosition) {
        //enable_servos();
    	set_servo_position(port, startPosition);
		msleep(1);
		startPosition -= time;
    	//disable_servos();
	}
    
}

void forward(int speed) {
	// go straight
    motor(rmotor,rspeed);
    motor(lmotor,lspeed);
}

void backward() {
	// go back
    motor(rmotor,-speed);
    motor(lmotor,-speed);
 
    //ao();
}

void backwardL() {
	// go back
    motor(rmotor,-speed*2);
    motor(lmotor,-speed*2);
 
    //ao();
}

void veerRight() {
	// go straight
    motor(lmotor,veerPower);
    motor(rmotor,veerSlow);
    //msleep(straightPause);
    //ao();
}

void veerLeft() {
	// go straight
    motor(lmotor,veerSlow);
    motor(rmotor,veerPower);
    //msleep(straightPause);
    //ao();
}



void turnRight(int pause){
    // turn right
    motor(rmotor,-turnSpeed);
    motor(lmotor,turnSpeed);
    msleep(pause);
    ao();
}

void turnRightSpeed(int pause, int speed){
    // turn right
    motor(rmotor,-speed);
    motor(lmotor,speed);
    msleep(pause);
    ao();
}

void turnRightLoop(){
    // turn right
    motor(rmotor,-turnSpeed);
    motor(lmotor,turnSpeed);
}

void turnLeftLoop(){
    // turn left
    motor(rmotor,turnSpeed);
    motor(lmotor,-turnSpeed);
}


void turnLeft(int pause){
    // turn left
    motor(rmotor,speed2);
    motor(lmotor,-speed2);
    msleep(pause);
    ao();
}