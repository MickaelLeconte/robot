/*
 * com_bluetooth.cpp
 *
 *  Created on: 3 oct. 2018
 *      Author: mleconte
 */
#include "com_bluetooth.h"

TRAME trame;

BluetoothManager::BluetoothManager() : btSerial(8, 7) {
	newData=false;
	csum=0;
	length=0;
	key=-1;
}
void BluetoothManager::init(){
	btSerial.begin(115200);
}
void BluetoothManager::recvTrame() {
	static boolean recvInProgress = false;
	static byte ndx = 0;
	byte rc;

	if (btSerial.available() > 0) {
		rc = btSerial.read();
		if (recvInProgress) {
			ndx++;
			receivedChars[ndx]=rc;
			if (ndx == 1) {
				length=receivedChars[ndx];
			}
			else if(ndx == length+1){
				csum=receivedChars[ndx];
				newData = true;
				recvInProgress = false;
				ndx = 0;
			}
		} else if (rc == ID_ROBOT) {
			recvInProgress = true;
			receivedChars[ndx]=rc;
		}
	}
}
bool BluetoothManager::checksum(){
	newData = false;
	byte tempCsum=0;
	for(int i=0;i<length+1;i++){
		tempCsum=tempCsum+receivedChars[i];
	}
	tempCsum=(~tempCsum)+1;
	if ( tempCsum == csum){
		return 1;

	}else{
		return 0;
	}
}

