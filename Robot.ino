#include "bleutooth/com_bluetooth.h"
#include "robot/robot.h"

BluetoothManager btManager;
RobotManager robotManager;

bool first_time=false;
long long int start_time;
void setup()
{
	Serial.begin(9600);
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
					robotManager.pwm_d=0;
					robotManager.pwm_g=0;
					robotManager.deplacement();
				}break;

				case DEPLACEMENT:{
					robotManager.pwm_d=(int)(((btManager.receivedChars[3] & 0x7F) <<8) + btManager.receivedChars[4]);
					bool signe = ((int)(btManager.receivedChars[3] & 0x80)) > 0;
					if(signe){robotManager.pwm_d=-robotManager.pwm_d;}

					robotManager.pwm_g=(int)(((btManager.receivedChars[5] & 0x7F) <<8) + btManager.receivedChars[6]);
					signe = ((int)(btManager.receivedChars[5] & 0x80)) > 0;
					if(signe){robotManager.pwm_g=-robotManager.pwm_g;}

					robotManager.deplacement();
				}break;

				case BROSSES:{
					int vitesse = (int)( (btManager.receivedChars[3]<<8) + btManager.receivedChars[4]);
					robotManager.brosse(vitesse);
				}break;

				case EAU:{
					digitalWrite(Pin_electro,btManager.receivedChars[3]);
				}break;

				case LAME:{

					digitalWrite(Pin_lame,btManager.receivedChars[3]);

					if(btManager.receivedChars[3] & first_time){
						first_time=false;
						start_time=millis();
						digitalWrite(Pin_compresseur,1);
					}

					else if (!btManager.receivedChars[3]){
						first_time=true;
					}

				}break;

				default:{
				}break;

			};
		}
	}
	if ( millis()>(start_time+30000) ){
		digitalWrite(Pin_compresseur,0);
	}
}
