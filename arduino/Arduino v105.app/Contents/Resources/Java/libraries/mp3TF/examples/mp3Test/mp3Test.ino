/*	2014-01-07 by lisper <leyapin@gmail.com>
 *	control mp3 module by seirial
 *	use mp3TF.h	
 *	test on UNO
 */

#include <mp3TF.h>

mp3TF mp3tf = mp3TF ();

//
void setup () {
	mp3tf.init (&Serial);
	Serial.begin (9600);
	//Serial1.begin (9600);
}

//
void loop () {
	mp3tf.play ();
	delay (5000);
	mp3tf.next ();
	delay (5000);
	mp3tf.previous ();
	delay (5000);
 	mp3tf.play (4);	
	delay (5000);
	mp3tf.pause ();
	delay (5000);	
}

/****************************************************************
 *		mp3TF mp3tf = mp3TF ();
 *	UNO:
 *		Serial.begin (9600);
 *		mp3tf.init (&Serial);
 *	LEONARDO:
 *		Serial1.begin (9600);
 *		mp3tf.init (&Serial1);
 *	
 *	function:
 *		mp3tf.play ();		play once
 *		mp3tf.play (1);		play first
 *		mp3tf.play (3);		play third
 *		mp3tf.pause ();		pause
 *		mp3tf.stop ();		stop
 *		mp3tf.next ();		next
 *		mp3tf.previous ();	previous
 *****************************************************************/

