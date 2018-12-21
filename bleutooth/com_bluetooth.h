/*
 * com_bluetooth.h
 *
 *  Created on: 3 oct. 2018
 *      Author: mleconte
 */

#ifndef BLEUTOOTH_COM_BLUETOOTH_H_
#define BLEUTOOTH_COM_BLUETOOTH_H_

#include <SoftwareSerial.h>
#include "../key.h"

#define MAX_TRAME_SIZE 16

class BluetoothManager{
private:


	void ack(bool ACK);
	void send_data();
	byte checksum_calculator();

	int length;
	byte csum;

public:
	BluetoothManager();
	SoftwareSerial btSerial;
	byte receivedChars[MAX_TRAME_SIZE]; // an array to store the received data
	byte key;
	bool newData;
	void init();
	void recvTrame();
	bool checksum();

	void reponse_set_calibration();
	void reponse_get_calibration(int a,int b);
	void reponse_tare_set();
	void reponse_weight(int poids);
	void reponse_distri_done(int dose);
	void reponse_distri_stop(int dose);
	void reponse_purge();
};
typedef struct {
	int size;
	byte buffer[MAX_TRAME_SIZE];
} TRAME;


#endif /* BLEUTOOTH_COM_BLUETOOTH_H_ */
