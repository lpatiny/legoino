


mp3TF mp3tf = mp3TF ();

// SoftwareSerial mySerial(4, 8); // RX, TX

SoftwareSerial mySerial(7, 4);

NIL_WORKING_AREA(waThreadAction1, 0);
NIL_THREAD(ThreadAction1, arg) {

  mySerial.begin (9600);
  mp3tf.init (&mySerial);

  while (TRUE) {
    playAudio();



nilThdSleepMilliseconds(40);

  }
}


void playAudio() {
  mp3tf.setVolume (20);
  nilThdSleepMilliseconds(200);
  mp3tf.play ((int)random(getParameter(PARAM_FIRST_SOUND),getParameter(PARAM_LAST_SOUND+1)));	
  if (getParameter(PARAM_SOUND_LENGTH)>0) {
    nilThdSleepMilliseconds (getParameter(PARAM_SOUND_LENGTH)*1000);
    mp3tf.pause (); 
  }
}















