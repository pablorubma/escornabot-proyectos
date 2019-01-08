//Código inicial para la botnera

int adc_key_val[5] = {576, 735, 811, 854, 906 };    //Valores de la botonera en orden ascendente
int NUM_KEYS = 5;                                   //Número de botones
int adc_key_in;
int key = -1;
int oldkey = -1;


// Código inicial para los dos servos


#include <Servo.h>                //Añadimos la librería servo.h
int poser = 90;                   //Indicamos la posición inicial de los servos centrada a 90 grados

//Creamos dos referencias, una para cada servo
Servo servoDown;
Servo servoUp;

// Código inicial LED
int ledPin = 10;                  //Elegir el pin del LED
int inputPin;                     //Indicamos en el botón el input
int val = digitalRead(inputPin);  

bool estadoluz = 0;               //De este modo cuando pulsemos la tecla que maneja el LED se enciende y apaga

void setup()


{
  //Parte que pertenece a la Botonera
  pinMode(13, OUTPUT);            //we'll use the debug LED to output a heartbeat
  Serial.begin(9600);              

  //Parte de los servos
  servoDown.attach(7);            //Indicamos que el servo de abajo va en el pin 7
  servoUp.attach(8);              //Indicamos que el servo de arriba va en el pin 8
  delay(2000);

  //Parte del LED
  pinMode(ledPin, OUTPUT);        //Indica el LED como output
  pinMode(inputPin, INPUT);       //Declara el pulsar boton como input

}
void loop()
{
  //Parte que pertenece a la Botonera
  adc_key_in = analogRead(0);     //Lee el valor del botón presionado
  digitalWrite(13, LOW);
  key = get_key(adc_key_in);      //Identifica el valor a la tecla presionada


  if (key != oldkey)              //Acciones a ejecutar cuando se identifica la botonera
  {
    delay(50);                    //Delay para no saturarse
    adc_key_in = analogRead(0);   
    key = get_key(adc_key_in);    
    if (key != oldkey)
    {
      oldkey = key;
      if (key >= 0) {
        digitalWrite(13, HIGH);
        switch (key)
        {
          case 0: poser += 15; //than position of servo motor increases by 1 ( anti clockwise)
            servoDown.write(poser);// the servo will move according to position
            delay(10);
            break;
          case 1: poser += 15; //than position of servo motor increases by 1 ( anti clockwise)
            servoUp.write(poser);// the servo will move according to position
            delay(10);
            break;
          case 2: poser -= 15; //than position of servo motor increases by 1 ( anti clockwise)
            servoDown.write(poser);// the servo will move according to position
            delay(10);
            break;
          case 3: val == HIGH;
            estadoluz = !estadoluz;
            digitalWrite(ledPin, estadoluz); // turn LED ON
            break;
          case 4: poser -= 15; //than position of servo motor increases by 1 ( anti clockwise)
            servoUp.write(poser);// the servo will move according to position
            delay(10);
            break;
        }
      }
    }
  }
  delay(100);
}
// Convert ADC value to key number
int get_key(unsigned int input)
{
  int k;
  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {
      return k;
    }
  }
  if (k >= NUM_KEYS)k = -1;  // No valid key pressed
  return k;
}
