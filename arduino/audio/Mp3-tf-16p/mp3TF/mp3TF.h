/*        2014-01-07 by lisper <leyapin@gmail.com>
 *        control mp3 module by seirial
 */

#include <Arduino.h>

class mp3TF{         
       HardwareSerial* mySerial;
public :
	void init (HardwareSerial*);
	void sendCmd (uint8_t *); 
    void play(); 
	void play (uint16_t index);
	void play (int index);
    void pause(); 
    void stop(); 
    void next (); 
    void previous(); 
	void setVolume( byte vol );
};

