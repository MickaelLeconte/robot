#include "bleutooth/com_bluetooth.h"
#include "robot/robot.h"

BluetoothManager btManager;
RobotManager robotManager;

void setup()
{
	btManager.init();
	robotManager.init();
}

void loop()
{
	btManager.recvTrame();
	if(btManager.newData){
		if(btManager.checksum()){
			switch(btManager.receivedChars[2]){

				case AU:{
					robotManager.stop(btManager.receivedChars[3]);
				}break;

				case DEPLACEMENT:{
					robotManager.pwm_d=(int)(((btManager.receivedChars[3] & 0x7F) <<8) + btManager.receivedChars[4]);
					bool signe = ((int)(btManager.receivedChars[3] & 0x80)) > 0;
					if(signe){robotManager.pwm_d=-robotManager.pwm_d;}

					robotManager.pwm_g=(int)(((btManager.receivedChars[5] & 0x7F) <<8) + btManager.receivedChars[6]);
					signe = ((int)(btManager.receivedChars[5] & 0x80)) > 0;
					if(signe){robotManager.pwm_g=-robotManager.pwm_g;}
				}break;

				case BROSSES:{
					robotManager.brosse(btManager.receivedChars[3]);
				}break;

				case EAU:{
					digitalWrite(Pin_electro,btManager.receivedChars[3]);
					digitalWrite(LED_BUILTIN,btManager.receivedChars[3]);
				}break;

				default:{
				}break;

			};
		}

	}
}
