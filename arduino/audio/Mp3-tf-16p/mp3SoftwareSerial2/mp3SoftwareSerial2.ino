#include <SoftwareSerial.h>


class mp3TF{         
       SoftwareSerial* mySerial;
public :
	void init (SoftwareSerial*);
	void sendCmd (uint8_t *); 
    void play(); 
	void play (uint16_t index);
	void play (int index);
    void pause(); 
    void stop(); 
    void next (); 
    void previous(); 
	void setVolume(uint8_t vol);
	 void reset (); 
	void increaseVolume();
};


mp3TF mp3tf = mp3TF ();

SoftwareSerial mySerial(7, 4); // RX, TX

void setup()  
{

  mySerial.begin (9600);
  mp3tf.init (&mySerial);
}

void loop() // run over and over
{
  mp3tf.setVolume (30);
  delay(200);
  mp3tf.play (1);	
  delay (10000);
  mp3tf.pause ();
  delay (500);	
  mp3tf.setVolume (20);
  delay(200);
  mp3tf.play (1);
  delay (10000);
  mp3tf.pause ();
  delay (500);	
}



