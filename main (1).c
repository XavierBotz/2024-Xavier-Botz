#include <kipr/wombat.h>

//declare variables
int lmotor = 1;
int rmotor = 0;
int fsensor = 0;
int rsensor = 1;
int tsensor = 0;
int bottomSensor = 2;
int pusher = 2;

int button = 0;


int rightBump = 0; //sensor in prt 0
int leftBump = 1;
int right = 1;
int left = 0;
int count = 0;

int lift = 2; 
int pinch = 0;
int waveCount = 0;
int wrist = 1;

int straightPause = 2000;
int turnPause = 1400;
int lspeed = 22.5;
int rspeed = 44.5;
int veerPower = 70;
int veerSlow = 20;
int conversion = 0;

int startPos = 1400;
int newPos = 1400;
int wristPos = 1500;

int speed = 40;
int speed2 = 20;
int turnSpeed = 70;
int revTurn = 10;

//declare functions
void forward(int speed);
void backward();
void turnRight(int pause);
void turnLeft(int pause);
void turnRightBump();
void turnLeftBump( int pause);
void wait(int wait);
void veerRight();
void veerLeft();
void veerRLoop();
void veerLLoop();
void avoidR();
void avoidL();
void turnLeftSplit();
void wave();
void slowMove();
void mpc();
void reverseEngine();
void negSlowMove();
void mpcBack();
void lineDetect();
void lineFollow();
void lineFollowV2();
void turnRightLoop();
void turnLeftLoop();
void turnLeft2(int pause);
void turn();
void rmpc(int distance);
void veerRightV2();
void veerRightV3();
void turnRightSpeed(int pause, int speed);
void ring();
void ring2();
void lmpc(int distance);
void wallFollowV2();
void wallFollowV3();
void ring3();
void pushTo(int distance);
void pushFrom(int distance);
void push();
void pushBack();
void release(int dis);
void shake(int startPosition);



int main()
{
    //reset 
    shut_down_in(120);
    enable_servos();
    slowMove(lift, 1700, 1800, 1);
    negSlowMove(pinch, 1000, 500, 1);
    negSlowMove(wrist, 1400, 1200, 1);
    printf("analong=%d\n",analog(2));
    
    negSlowMove(lift, 1800, 1600, 1);
    
    //follow wall to pipe
    mpc(320);
    //rmpc(15);
    lineDetect();
    wait(500);
    
    //fix position
    mpcBack(-235);
    rmpc(25);
    negSlowMove(lift, 1600, 1190, 1);
    
    // pick up austronaught
    
    negSlowMove(wrist, 1200, 430, 1);
    slowMove(pinch, 500, 1000, 1);
    wait(200);
    slowMove(wrist, 430, 1200, 1);
    
    // wait for tubes to drip
    wait(5000);
    lmpc(20);
 
    //go to astronaught hole
    mpc(800);
    negSlowMove(lift, 1200, 900, 1);
    //rmpc(20);
    wallFollowV3();
    wait(500);
    
    //drop astronaught in
	mpcBack(-65);
    wait(300);
    slowMove(wrist, 1200, 1570, 1);
    negSlowMove(pinch, 1000, 500, 1);
    
    
    negSlowMove(wrist, 1570, 1200, 1);
    wait(500);
    slowMove(pinch, 500, 1000, 1);
    
    //hit the austornaught to make sure button is pressed
    slowMove(wrist, 1200, 1570, 2);
    wait(200);
    negSlowMove(wrist, 1570, 1200, 1);
    
    //go to tubes
    wallFollowV3();
    wait(200);
    negSlowMove(lift, 900, 945, 1);
    wait(200);
    mpcBack(-19);
    wait(200);
    rmpc(16);
    
    //drop noodle into tube
    wait(200);
    release(1000);
    shake(945);
    shake(945);
    wait(400);
    
    
    
    
    // fix position to drop noodle into second tube
    mpcBack(-89);
    wait(200);
    slowMove(lift, 945, 1160, 1);
    rmpc(5);
    wait(500);
    release(1000);
    wait(200);
    shake(1160);
    shake(1160);
    wait(500);
    
    
    //move up and drop cap on tube
    negSlowMove(lift, 1160, 880, 1);
    lmpc(10);
    wait(200);
    wallFollowV3();
    wait(200);
    rmpc(15);
    
    slowMove(lift, 880, 950, 1);
    
    disable_servos();
    return 0;
}


void lineDetect(){
    while (analog(tsensor) < 2650) {
        forward(50);
    }
}

void wallFollowV2(){
    while (analog(rsensor) > 3760) {
        forward(50);
    }
}

void shake(int startPosition){
	negSlowMove(lift, startPosition, startPosition - 200, 2);
    slowMove(lift, startPosition - 200, startPosition, 2);
}

void wallFollowV3(){
    while (!digital(button)) {
        forward(50);
    }
}

void lineFollow(){
 	while (analog(1) < 1600) {
        if (analog(tsensor) > 3000){
            count++;
    		veerRight();
        } else {
            veerLeft();
        }
     }
    ao();
}

void rmpc(int distance){
    conversion = (1800*distance)/219.44;
	cmpc(1);
    while (gmpc(1) < conversion) {
    	turnRightLoop();
    }
	ao();
}

void lmpc(int distance){
    conversion = (1800*distance)/219.44;
	cmpc(0);
    while (gmpc(0) < conversion) {
    	turnLeftLoop();
    }
	ao();
}

void mpc(int distance){
    conversion = (1800*distance)/219.44;
	cmpc(0);
    while (gmpc(0) < conversion) {
    	forward(100);
    }
	ao();
}
        
void release(int dis){
    
    pushTo(dis);
    msleep(500);
    pushFrom(-dis);

}  
void pushTo(int distance){
	cmpc(pusher);
    while (gmpc(pusher) < distance) {
    	push(speed);
    }
	ao();
}

void pushFrom(int distance){
	cmpc(pusher);
    while (gmpc(pusher) > distance) {
    	pushBack(speed);
    }
	ao();
}
        
void push(){
    
	motor(2, 100);
}

void pushBack(){
    
	motor(2, -100);
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
    motor(rmotor,speed);
    motor(lmotor,speed);
    //msleep(straightPause);
    //ao();
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
    motor(rmotor,veerPower);
    motor(lmotor,veerSlow);
    //msleep(straightPause);
    //ao();
}

void veerLeft() {
	// go straight
    motor(rmotor,veerSlow);
    motor(lmotor,veerPower);
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
    motor(rmotor,-turnSpeed*.25);
    motor(lmotor,turnSpeed*.25);
}

void turnLeftLoop(){
    // turn left
    motor(rmotor,turnSpeed*.25);
    motor(lmotor,-turnSpeed*.25);
}


void turnLeft(int pause){
    // turn left
    motor(rmotor,speed2);
    motor(lmotor,-speed2);
    msleep(pause);
    ao();
}