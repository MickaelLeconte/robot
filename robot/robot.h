/*
 * robot.h
 *
 *  Created on: 19 déc. 2018
 *      Author: mleconte
 */

#ifndef ROBOT_ROBOT_H_
#define ROBOT_ROBOT_H_

#include "../key.h"

/** Déclaration des pins **/
#define Pin_PWM_D_AV 5
#define Pin_PWM_D_AR 6
#define Pin_PWM_G_AV 10
#define Pin_PWM_G_AR 11
#define Pin_electro 2
#define Pin_lame 4
#define Pin_AU A2
#define Pin_brosse 9
#define Pin_compresseur A4

class RobotManager{
private:

public:
	int pwm_d,pwm_g;

	RobotManager();
	void init();
	void stop(bool state);
	void deplacement();
	void brosse(int vitesse);
};


#endif /* ROBOT_ROBOT_H_ */
