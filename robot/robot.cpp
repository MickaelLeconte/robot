/*
 * robot.cpp
 *
 *  Created on: 19 déc. 2018
 *      Author: mleconte
 */

#include "robot.h"

RobotManager::RobotManager(){
	pwm_d=0;
	pwm_g=0;
}

void RobotManager::init(){

	pinMode(Pin_PWM_D_AV,OUTPUT);
	pinMode(Pin_PWM_D_AR,OUTPUT);
	pinMode(Pin_PWM_G_AV,OUTPUT);
	pinMode(Pin_PWM_G_AR,OUTPUT);

	pinMode(Pin_AU,OUTPUT);
	pinMode(Pin_lame,OUTPUT);
	pinMode(Pin_brosse,OUTPUT);
	pinMode(Pin_electro,OUTPUT);
	pinMode(Pin_compresseur,OUTPUT);

	digitalWrite(Pin_AU,0);
	digitalWrite(Pin_lame,0);
	digitalWrite(Pin_electro,0);
	digitalWrite(Pin_compresseur,0);

	analogWrite(Pin_brosse,0);

	analogWrite(Pin_PWM_D_AV,0);
	analogWrite(Pin_PWM_D_AR,0);
	analogWrite(Pin_PWM_D_AV,0);
	analogWrite(Pin_PWM_D_AR,0);

}

void RobotManager::stop(bool state){
	digitalWrite(Pin_AU,!state);
}


void RobotManager::brosse(int vitesse){
	analogWrite(Pin_brosse,vitesse);
}

void RobotManager::deplacement(){
	// commande moteur droit
	if (pwm_d >= 0){
		analogWrite(Pin_PWM_D_AV , pwm_d);
		analogWrite(Pin_PWM_D_AR , 0);
	}
	else{
		pwm_d = -pwm_d;
		analogWrite(Pin_PWM_D_AV , 0);
		analogWrite(Pin_PWM_D_AR , pwm_d);
	}
	// commande moteur gauche
	if (pwm_g >= 0){
		analogWrite(Pin_PWM_G_AV , pwm_g);
		analogWrite(Pin_PWM_G_AR , 0);
	}
	else{
		pwm_g = -pwm_g;
		analogWrite(Pin_PWM_G_AV , 0);
		analogWrite(Pin_PWM_G_AR , pwm_g);
	}
}



