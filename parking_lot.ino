#include <DFRobot_Servo.h> // ���

#include <DFRobot_URM10.h> // ������

#include <DFRobot_TM1650.h> // �����

#include <DFRobot_SSD1306_I2C.h> // oled

#include <DFRobot_edgeTrigging.h> // �ж�



void up_3();

void down_2();

void up_2();


DFRobot_SSD1306_I2C oled12864;

DFRobot_TM1650 tm1650;

Servo servo_A5; // ��

Servo servo_8�� // ��

DFRobot_URM10 urm10;

DFRobot_edgeTrigging edge;

int notavailable_space=0;// ��ʹ�ó�λ

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

	//--------------�Ż�

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

	//--------------�Ż�

  	// ��ʾʣ�೵λ

	tm1650.displayString(6-notavailable_space);

	// �����շѣ���ʾ

}

void down_2(){

	servo_A5.angle(abs(180));

	// �ҵ������λ

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

	//     // �������飬д�복λ״̬

	// }

	if(/*��λȫ��*/place2==1 && place1==1){

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

	// ��ʾ�����λ

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