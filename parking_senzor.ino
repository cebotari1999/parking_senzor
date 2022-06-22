#include <LiquidCrystal.h>

LiquidCrystal LCD(3, 4, 5, 6, 10, 11); 
const int contrast = 100;

const int trig = 12;    // Trigger pin
const int echo = 13;    // Echo pin
const int buzzer = 2; // Buzzer pin

long cm, inches;
int duration;
int distance;

void setup() {
  Serial.begin(9600);
  
  // Se definesc inputurile/outputurile
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);

 // Se seteaza contrastul LCD-ului.
  analogWrite(9, contrast);
  
  // Se initializeaza LCD-ul
  LCD.begin(16, 2);



}

void loop() {
  /**
   * Senzorul ultrasonic este activat de un semnal HIGH care dureaza,
   * 10 sau mai multe microsecunde. Pentru ca acesta sa fie curat si
   * datele obtinute cat mai corecte, se transmite un semnal LOW timp
   * de 5 milisecunde.
   * 
   */
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  /**
   * Se citeste durata de timp, in care undele sau propagat 
   * de la senzor, spre obiect si inapoi.
   */
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  /**
   *  Se calculeaza distanta de la senzor la obiect 
   *  in cm si inci
   */
  cm = (duration / 2) / 29.1;
  inches = (duration / 2) / 74;

 /**
  * In functie de cat de aproape este obiectul,se transmit
  * fregvente din ce in ce mai mare, astfel buzzerul
  * va produce un sunet din ce in ce mai ascutit. Daca
  * obiectul este mai departe de 30 cm, buzzerul nu 
  * va mai emite sunete.
  */
  if (cm <= 5) {
    tone(buzzer, 400);
  }
  else if (cm > 5 && cm <= 15) {
    tone(buzzer, 370);
  }
  else if (cm > 15 && cm < 30) {
    tone(buzzer, 340);
  } else {
    noTone(buzzer);
  }

  
  /**
   * Se sterge textul vechi de pe ecran si se afiseaza 
   * distanta in cm si inci.
   */
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("dist. cm :");
  LCD.setCursor(11, 0);
  LCD.print(cm);
  
  LCD.setCursor(0, 1);
  LCD.print("dist. inch:");
  LCD.setCursor(11, 1);
  LCD.print(inches);
  
  delay(200);
};
