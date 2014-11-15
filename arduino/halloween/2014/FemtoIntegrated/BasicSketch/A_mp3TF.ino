#include <SoftwareSerial.h>

class mp3TF{         
  SoftwareSerial* mySerial;
public :
  void init (SoftwareSerial*);
  void sendCmd (uint8_t *); 
  void play(); 
  void play (uint16_t index);
  void playInFolder (uint16_t index);
  void play (int index);
  void pause(); 
  void stop(); 
  void next (); 
  void previous(); 
  void setVolume(uint8_t vol);
  void reset (); 
  void increaseVolume();
};

void mp3TF::init (SoftwareSerial* theSerial) {
  mySerial = theSerial;
}

//
void mp3TF::sendCmd (uint8_t *cmd) {
  uint16_t checksum = 0; // the first character $ does not count we should really start at 1
  for (int i=1; i<7; i++) {
    checksum += cmd[i];
  }
  checksum--; // no idea why we should remove one ... BUG ????
  checksum = ~checksum; // seems we should invert

  cmd[7] = ((uint8_t)(checksum>>8));
  cmd[8] = (uint8_t)checksum;

  //  setParameter(45,cmd[7]);
  //  setParameter(46,cmd[8]);

  for (int i=0; i<10; i++) { //send cmd
    (*mySerial).write (cmd[i]);
  }
}

//
void mp3TF::play() {
  static uint8_t play_cmd [10] = { 
    0X7E, 0xFF, 0x06, 0X0D, 00, 00, 00, 0xFE, 0xee, 0XEF        };
  sendCmd (play_cmd);
}

void mp3TF::increaseVolume() {
  static uint8_t play_cmd [10] = { 
    0X7E, 0xFF, 0x06, 0X05, 00, 00, 00, 0xFE, 0xee, 0XEF        };
  sendCmd (play_cmd);
}

void mp3TF::setVolume(uint8_t volume) {
  static uint8_t play_cmd [10] = { 
    0X7E, 0xFF, 0x06, 0X06, 00, 00, 0x30, 0xFE, 0xEE, 0XEF        };
  play_cmd[6] = (uint8_t)(volume);
  sendCmd (play_cmd);
}

//
void mp3TF::play(uint16_t index) {
  static uint8_t play_cmd [10] = { 
    0x7E, 0xFF, 0x06, 0x03, 00, 00, 00, 0xFE, 0xEE, 0xEF        };
  play_cmd[5] = (uint8_t)(index >> 8);
  play_cmd[6] = (uint8_t)(index);
  sendCmd (play_cmd);
}

void mp3TF::playInFolder(uint16_t index) {
  static uint8_t play_cmd [10] = { 
    0x7E, 0xFF, 0x06, 0x0F, 00, 00, 00, 0xFE, 0xEE, 0xEF        };
  play_cmd[5] = (uint8_t)(index/100);
  play_cmd[6] = (uint8_t)(index%100);

  sendCmd (play_cmd);
}

//
void mp3TF::play(int index) {
  play ((uint16_t)index);
}


//
void mp3TF::pause() {
  static uint8_t pause_cmd [] = { 
    0X7E, 0xFF, 0x06, 0X0E, 00, 00, 00, 0xFE, 0xED, 0XEF        };
  sendCmd (pause_cmd);
}

void mp3TF::reset() {
  static uint8_t pause_cmd [] = { 
    0X7E, 0xFF, 0x06, 0x0C, 00, 00, 00, 0xFE, 0xED, 0XEF        };
  sendCmd (pause_cmd);
}

//
void mp3TF::stop() {
  static uint8_t stop_cmd [] = { 
    0X7E, 0xFF, 0x16, 0X0E, 00, 00, 00, 0xFE, 0xED, 0XEF        };
  sendCmd (stop_cmd);
}

//
void mp3TF::next () {
  static uint8_t next_cmd [] = { 
    0X7E, 0xFF, 0x06, 0X01, 00, 00, 00, 0xFE, 0xFA, 0XEF        };
  sendCmd(next_cmd);
}

//
void mp3TF::previous() {
  static uint8_t previous_cmd [] = { 
    0X7E, 0xFF, 0x06, 0X02, 00, 00, 00, 0xFE, 0xF9, 0XEF        };
  sendCmd (previous_cmd);
}


mp3TF mp3tf = mp3TF ();

void stopAudio() {
  mp3tf.pause ();
  setParameter(PARAM_CURRENT_SONG, -1);
}

void playAudio() {
  if (getParameter(PARAM_VOLUME)<0) {
    mp3tf.setVolume (20);
  } 
  else {
    mp3tf.setVolume (getParameter(PARAM_VOLUME));
  }
  nilThdSleepMilliseconds(20);
  int song=(int)random(getParameter(PARAM_FIRST_SONG),getParameter(PARAM_LAST_SONG)+1);
  setParameter(PARAM_CURRENT_SONG, song);
  mp3tf.playInFolder (song);	
}






