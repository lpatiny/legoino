


mp3TF mp3tf = mp3TF ();

// SoftwareSerial mySerial(4, 8); // RX, TX

SoftwareSerial mySerial(7, 4);

NIL_WORKING_AREA(waThreadAction1, 0);
NIL_THREAD(ThreadAction1, arg) {

  int action1Step=0;

  mySerial.begin (9600);
  mp3tf.init (&mySerial);

  while (TRUE) {

    if ((getParameter(PARAM_DETECTOR1)==1) || (action1Step>0)) {
      action1Step++;
    }

    if (action1Step==getParameter(PARAM_DELAY0)) {
      playAudio();
      #ifdef KEYBOARD_EVENT
      sendKey();
      #endif
    }

    if (getParameter(PARAM_DELAY8)==action1Step) {
      mp3tf.pause (); 
    }

    if (getParameter(PARAM_DELAY9)==action1Step) {
      action1Step=0;
    }

    setParameter(PARAM_ACTION1, action1Step);
    nilThdSleepMilliseconds(40);

  }
}


void playAudio() {
  mp3tf.setVolume (20);
  nilThdSleepMilliseconds(200);
  mp3tf.play ((int)random(getParameter(PARAM_FIRST_SOUND),getParameter(PARAM_LAST_SOUND+1)));	
}




















