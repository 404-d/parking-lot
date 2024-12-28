#include <DFRobot_Servo.h> // 舵机

#include <DFRobot_URM10.h> // 超声波

#include <DFRobot_TM1650.h> // 数码管

#include <DFRobot_SSD1306_I2C.h> // oled

#include <DFRobot_edgeTrigging.h> // 中断



void up_3();

void down_2();

void up_2();


DFRobot_SSD1306_I2C oled12864;

DFRobot_TM1650 tm1650;

Servo servo_A5; // 进

Servo servo_8； // 出

DFRobot_URM10 urm10;

DFRobot_edgeTrigging edge;

int notavailable_space=0;// 已使用车位

int place1;

int place2;

// int place3=5;

// int place4=5;

// int place5=5;

// int place6=5;

// urm10.getDistanceCM(trig,echo);


void setup(){

	servo_8.attach(8);

	servo_A5.attach(A5);

	edge.registerEvent(3,EDGE_RISING,up_3);

	edge.registerEvent(2,EDGE_RISING,up_2);

	edge.registerEvent(2,EDGE_FALLING,down_2);

	oled12864.begin(0x3c);

	oled12864.setCursorLine(1);

	oled12864.printLine("nearest space:");

	tm1650.init();

}

void loop(){

	place1=urm10.getDistanceCM(4,5);

	place2=urm10.getDistanceCM(6,7);

	//--------------优化

	if(place1<=4){
		notavailable_space++;

  	}

  	if(place1>4){

		notavailable_space++;

 	}

	if(place2<=4){

		notavailable_space--;

  	}

	if(place2>4){

    		notavailable_space++;

	}

	//--------------优化

  	// 显示剩余车位

	tm1650.displayString(6-notavailable_space);

	// 计算收费，显示

}

void down_2(){

	servo_A5.angle(abs(180));

	// 找到最近车位

	String nearest_;

	int nearest[2]={};

	if(place1<=4){
		nearest[1]=1;

	}

	if(place2<=4){

 		nearest[2]=1;

  	}

	if(place1>4){

		nearest[1]=0;
	}

	if(place2>4){

		nearest[2]=0;

 	}

	// int nearest[6]={0,0,1,1,1,1};

	// for(int i=0;i<6;i++){

	//     // 遍历数组，写入车位状态

	// }

	if(/*车位全满*/place2==1 && place1==1){

    		oled12864.setCursorLine(2);

		oled12864.printLine("FULL");

	}

	else{

		if(place1==0 && place2==1){

		nearest_="place1";

		}

		if(place1==1 && place2==0){

			nearest_="place2";

		}

		else{

      			nearest_="place1";

		}

	}

	// 显示最近车位

	oled12864.setCursorLine(2);

	oled12864.printLine(nearest_);

}

void up_2(){

	servo_A5.angle(abs(90));

}

void up_3(){

	if(urm10.getDistanceCM(A3,A2)<=4){

    		servo_8.angle(abs(0));

	}
  
	else{

		delay(500);

   		servo_8.angle(abs(90));

	}

}