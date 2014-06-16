/*        2014-01-07 by lisper <leyapin@gmail.com>
 *        control mp3 module by seirial
 */

#include <Arduino.h>
#include "mp3TF.h"



//
void mp3TF::init (HardwareSerial* theSerial) {
	mySerial = theSerial;
}

//
void mp3TF::sendCmd (uint8_t *cmd) {
	uint8_t checksum = 0;
	for (int i=2; i<8; i++) {
		checksum += cmd[i];
	}
	cmd[8] = (uint8_t)~checksum;
	for (int i=0; i<10; i++) { //send cmd
		(*mySerial).write (cmd[i]);
	}
}

//
void mp3TF::play() {
	static uint8_t play_cmd [10] = { 0X7E, 0xFF, 0x06, 0X0D, 00, 00, 00, 0xFE, 0xee, 0XEF};
	sendCmd (play_cmd);
}

//
void mp3TF::play(uint16_t index) {
	static uint8_t play_cmd [10] = { 0X7E, 0xFF, 0x06, 0X03, 00, 00, 00, 0xFE, 0xee, 0XEF};
	play_cmd[5] = (uint8_t)(index >> 8);
	play_cmd[6] = (uint8_t)(index);
	sendCmd (play_cmd);
}

//
void mp3TF::play(int index) {
	play ((uint16_t)index);
}


//
void mp3TF::pause() {
	static uint8_t pause_cmd [] = { 0X7E, 0xFF, 0x06, 0X0E, 00, 00, 00, 0xFE, 0xED, 0XEF};
	sendCmd (pause_cmd);
}

//
void mp3TF::stop() {
	static uint8_t stop_cmd [] = { 0X7E, 0xFF, 0x16, 0X0E, 00, 00, 00, 0xFE, 0xED, 0XEF};
	sendCmd (stop_cmd);
}

//
void mp3TF::next () {
	static uint8_t next_cmd [] = { 0X7E, 0xFF, 0x06, 0X01, 00, 00, 00, 0xFE, 0xFA, 0XEF};
	sendCmd(next_cmd);
}

//
void mp3TF::previous() {
	static uint8_t previous_cmd [] = { 0X7E, 0xFF, 0x06, 0X02, 00, 00, 00, 0xFE, 0xF9, 0XEF};
	sendCmd (previous_cmd);
}


