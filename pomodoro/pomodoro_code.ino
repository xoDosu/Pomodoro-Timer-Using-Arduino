
//inclusion of the essential libraries 
#include <LiquidCrystal_I2C.h>

//definitions of the pins
#define RED_LED_PIN 4
#define YELLOW_LED_PIN 3
#define GREEN_LED_PIN 2
#define RESET_BUTTON_PIN 12
#define START_BUTTON_PIN 11
#define PAUSE_BUTTON_PIN 10
#define INC_BUTTON_PIN 9
#define DEC_BUTTON_PIN 8
#define BUZZ_PIN 7


LiquidCrystal_I2C lcd(0x27, 16, 2);


  const int increase_by = 1;//increase the time by how many hours
  const int decrease_by = 1;//decrease the time by how many hours
  const int study_time = 25;//time im minutes for studying 
  const int break_time = 5;//time in minutes for breaks

 
  int total_study_time = 0;//total time for the study sessions
  int user_time = 0; //the time the user wants to study for 
  int total_break_time = 0; //total break time by the user.
  int total_time = ((total_break_time + total_study_time) == 30) ? total_time += 0.5 : total_time += 0;  //calculates the total time by by adding up study time and break time 

  //variables to keep track of the time 
  int seconds = 0;
  int minutes = 0;
  int hours = 0;

  int counts = 0; //counts for 25 minutes for the break time 

  int start_button_state = 0;
  int reset_button_state = 0;
  int pause_button_state = 0;
  int inc_button_state = 0;
  int dec_button_state = 0;



void setup() {
  // sets the pins for the LEDS to output.
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);

  //sets the pins for the buttons to input 
  pinMode(RESET_BUTTON_PIN, INPUT);
  pinMode(START_BUTTON_PIN, INPUT);
  pinMode(INC_BUTTON_PIN, INPUT);
  pinMode(DEC_BUTTON_PIN, INPUT);
  pinMode(PAUSE_BUTTON_PIN, INPUT);

  //turns all LEDS ON.
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);


  //buzzer sounds to signify system boot
  tone(BUZZ_PIN, 1000);
  delay(3000);
  noTone(BUZZ_PIN);


  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);


  //lcd message on system boot
  lcd.init();//initialises the lcd
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("Pomodoro Timer");
  delay(4000);
  lcd.setCursor(1, 1);
  lcd.print("Enter Time");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(user_time + "Press Start");
}


void breaktime(){//break time method to display to the LCD the appropriate alloted time for the break (5).
//LED traffic light effect
  minutes = 0;
  seconds = 0;

  tone(BUZZ_PIN, 1000);
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(2000);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  delay(2000);
  digitalWrite(RED_LED_PIN, HIGH);
  noTone(BUZZ_PIN);



//writes break time to the LCD screen
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("BREAK TIME!");
//counts 5 mins for the breaktime
  while(minutes < break_time){
    seconds = 0;
    while(seconds < 60){
      lcd.setCursor(0, 1);
       if(minutes < 10){
        lcd.print(0);
      }
      lcd.print(minutes);
      lcd.print(":");
      
      if(seconds < 10){
        lcd.print(0);
      }
      lcd.print(seconds);
      delay(1000);
      seconds++;
    }
    minutes++;
  }
//checks if break time is over
  if(minutes == 5){
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
    total_break_time += 5;
    studytime();
  }
}

void studytime(){//study time method to display to the LCD the appropriate time for study.
  minutes = 0;
  seconds = 0;


  tone(BUZZ_PIN, 1000);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(2000);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  delay(2000);
  digitalWrite(GREEN_LED_PIN, HIGH);
  noTone(BUZZ_PIN);



  lcd.clear();
  while(minutes < study_time){
    seconds = 0;
    while(seconds < 60){
      lcd.setCursor(0, 1);
      if(minutes < 10){
        lcd.print(0);
      }
      lcd.print(minutes);
      lcd.print(":");
      
      if(seconds < 10){
        lcd.print(0);
      }
      lcd.print(seconds);
      delay(1000);
      seconds++;
    }
    minutes++;
  }

  if(minutes == 25){
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
    total_study_time += 25;
    breaktime();
  }

  if(total_time == user_time){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GOOD JOB");
    delay(4000);
    reset();
  }
}

void reset(){
  setup();
}

void loop() {
   
  //variables to store the states of the different buttons.
  start_button_state = digitalRead(START_BUTTON_PIN);
  pause_button_state = digitalRead(PAUSE_BUTTON_PIN);
  reset_button_state = digitalRead(RESET_BUTTON_PIN);
  inc_button_state = digitalRead(INC_BUTTON_PIN);
  dec_button_state = digitalRead(DEC_BUTTON_PIN);

  if(start_button_state == HIGH){
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
    studytime();
  }

  if(reset_button_state == HIGH){
    reset();
  }

  if(inc_button_state == HIGH){
      user_time++;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(user_time);

  }

  if(dec_button_state == HIGH){
      user_time--;
       lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(user_time);
  }

}
