


mp3TF mp3tf = mp3TF ();

// SoftwareSerial mySerial(4, 8); // RX, TX

SoftwareSerial mySerial(7, 4);

NIL_WORKING_AREA(waThreadAction1, 0);
NIL_THREAD(ThreadAction1, arg) {

  mySerial.begin (9600);
  mp3tf.init (&mySerial);

  while (TRUE) {
    testAudio3();
  }
}

void testAudio1() {
  mp3tf.setVolume (20);
  nilThdSleepMilliseconds(200);
  mp3tf.play (1);	
  nilThdSleepMilliseconds (5000);
  mp3tf.pause ();
  nilThdSleepMilliseconds (500);	
  mp3tf.setVolume (10);
  nilThdSleepMilliseconds(200);
  mp3tf.play (1);
  nilThdSleepMilliseconds (5000);
  mp3tf.pause ();
  nilThdSleepMilliseconds (500);

}

void testAudio2() {
  mp3tf.setVolume (20);
  nilThdSleepMilliseconds(200);
  mp3tf.play (5);	
  nilThdSleepMilliseconds (10000);
  mp3tf.pause ();
  nilThdSleepMilliseconds (500);		
}

void testAudio3() {
  mp3tf.setVolume (20);
  nilThdSleepMilliseconds(200);
  mp3tf.play (getParameter(PARAM_SOUND));	
  nilThdSleepMilliseconds (5000);
  mp3tf.pause ();
  nilThdSleepMilliseconds (500);		
}















