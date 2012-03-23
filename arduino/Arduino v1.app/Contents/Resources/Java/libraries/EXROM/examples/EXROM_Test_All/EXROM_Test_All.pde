#include <EXROM.h>


void setup()
{
  Serial.begin(9600);

  byte array[] = {
    43,23,67,176,23,79,81  };
  byte array2[sizeof(array)];
  EXROM.write(0, array, sizeof(array));
  EXROM.read(0, array2, sizeof(array2));
  Serial.println("Byte Array Test");
  Serial.println("original array");
  for(int i=0;i<sizeof(array);i++)
  {
    Serial.println(array[i], DEC);
  }
  Serial.println("new array");
  for(int i=0;i<sizeof(array);i++)
  {
    Serial.println(array2[i], DEC);
  }

  byte test = 55;
  byte test2;
  EXROM.write(99, test);
  EXROM.read(99, &test2);
  Serial.println("Byte test");
  Serial.println(test, DEC);
  Serial.println(test2, DEC);

  char array3[] = "Arduino";
  char array4[sizeof(array3)];
  EXROM.write(7, array3, sizeof(array3));
  EXROM.read(7, array4, sizeof(array4));
  Serial.println("Char Array Test");
  Serial.println("original array");
  for(int i=0;i<sizeof(array3);i++)
  {
    Serial.println(array3[i]);
  }
  Serial.println("new array");
  for(int i=0;i<sizeof(array4);i++)
  {
    Serial.println(array4[i]);
  }

  char test3 = 'a';
  char test4;
  EXROM.write(100, test3);
  EXROM.read(100, &test4);
  Serial.println("Char test");
  Serial.println(test3);
  Serial.println(test4);

  boolean array5[] = {
    true, false, true, true, false  };
  char array6[sizeof(array5)];
  EXROM.write(7, array5, sizeof(array5));
  EXROM.read(7, array6, sizeof(array6));
  Serial.println("Boolean Array Test");
  Serial.println("original array");
  for(int i=0;i<sizeof(array5);i++)
  {
    Serial.println(array5[i], DEC);
  }
  Serial.println("new array");
  for(int i=0;i<sizeof(array6);i++)
  {
    Serial.println(array6[i], DEC);
  }

  boolean test5 = true;
  boolean test6;
  EXROM.write(101, test5);
  EXROM.read(101, &test6);
  Serial.println("Boolean test");
  Serial.println(test5, DEC);
  Serial.println(test6, DEC);

  int inta[] = {
    43,23,67,176,23,79,81  };
  int inta2[sizeof(inta)/2];
  EXROM.write(76, inta, sizeof(inta));
  EXROM.read(76, inta2, sizeof(inta2));
  Serial.println("Int Array Test");
  Serial.println("original array");
  for(int i=0;i<sizeof(inta)/2;i++)
  {
    Serial.println(inta[i]);
  }
  Serial.println("new array");
  for(int i=0;i<sizeof(inta2)/2;i++)
  {
    Serial.println(inta2[i]);
  }

  int int1 = 3459;
  int int2;
  EXROM.write(101, int1);
  EXROM.read(101, &int2);
  Serial.println("Int test");
  Serial.println(int1);
  Serial.println(int2);

  float fTest[4] = {
    3.14,6.87,7.98332,12.764  };
  EXROM.write(54, fTest, sizeof(fTest));
  float fRec[4];
  EXROM.read(54, fRec, sizeof(fRec));
  Serial.println("Float Array Test");
  Serial.println("original array");
  for(int i=0;i<sizeof(fTest)/4;i++)
  {
    Serial.println(fTest[i]);
  }
  Serial.println("new array");
  for(int i=0;i<sizeof(fRec)/4;i++)
  {
    Serial.println(fRec[i]);
  }

  float fTest1 = 
    3.14;
  EXROM.write(54, fTest1);
  float fRec1;
  EXROM.read(54, &fRec1);
  Serial.println("Float test");
  Serial.println(fTest1);
  Serial.println(fRec1);

  long lTest2[3] = {
    123454,123456,876534        };
  EXROM.write(276, lTest2, sizeof(lTest2));
  long lRec2[3];
  EXROM.read(276, lRec2, sizeof(lRec2));
  Serial.println("Long Array Test");
  Serial.println("original array");
  for(int i=0;i<sizeof(lTest2)/4;i++)
  {
    Serial.println(lTest2[i]);
  }
  Serial.println("new array");
  for(int i=0;i<sizeof(lRec2)/4;i++)
  {
    Serial.println(lRec2[i]);
  }

  long lTest = 1324135;
  EXROM.write(87, lTest);
  long lRec;
  EXROM.read(87, &lRec);
  Serial.println("Long test");
  Serial.println(lTest);
  Serial.println(lRec);

  unsigned long lTest3[3] = {
    123454,123456,-876534  };
  EXROM.write(276, lTest3, sizeof(lTest2));
  unsigned long lRec3[3];
  EXROM.read(276, lRec3, sizeof(lRec2));
  Serial.println("Unsigned Long Array Test");
  Serial.println("original array");
  for(int i=0;i<sizeof(lTest3)/4;i++)
  {
    Serial.println(lTest3[i]);
  }
  Serial.println("new array");
  for(int i=0;i<sizeof(lRec3)/4;i++)
  {
    Serial.println(lRec3[i]);
  }

  unsigned long lTest4 = 1324135;
  EXROM.write(87, lTest4);
  unsigned long lRec4;
  EXROM.read(87, &lRec4);
  Serial.println("Unsigned Long test");
  Serial.println(lTest4);
  Serial.println(lRec4);

  unsigned int inta1[] = {
    43,23,67,-176,23,79,-81  };
  unsigned int inta21[sizeof(inta1)/2];
  EXROM.write(76, inta1, sizeof(inta1));
  EXROM.read(76, inta21, sizeof(inta21));
  Serial.println("Unsigned Int Array Test");
  Serial.println("original array");
  for(int i=0;i<sizeof(inta1)/2;i++)
  {
    Serial.println(inta1[i]);
  }
  Serial.println("new array");
  for(int i=0;i<sizeof(inta21)/2;i++)
  {
    Serial.println(inta21[i]);
  }

  unsigned int int11 = 3459;
  unsigned int int21;
  EXROM.write(101, int11);
  EXROM.read(101, &int21);
  Serial.println("Unsigned Int test");
  Serial.println(int11);
  Serial.println(int21);

}

void loop()
{

}





