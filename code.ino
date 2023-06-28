#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Définition des fréquences des notes de musiques de la 4ème octave
#define OCTAVE_4_DO 523
#define OCTAVE_4_RE 587
#define OCTAVE_4_MI 659
#define OCTAVE_4_FA 698
#define OCTAVE_4_SOL 784
#define OCTAVE_4_LA 880
#define OCTAVE_4_SI 988

// Définition de la durée d'un temps en millisecondes 
#define DUREE_TEMPS 200

// name of the project : ArduConsole
LiquidCrystal_I2C lcd(0x27, 16, 2);
int selectButton = 2;
int vrx = A0;
int vry = A1;
int backButton = 3;
int menu = 1;
int action = 1;
int Recharge_detector_pin = 0;
int maxx = 600;
int minn = 401;

int version_software = 1000;


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.println("loading...");
  
  pinMode(backButton, INPUT_PULLUP);
  
  pinMode(selectButton, INPUT_PULLUP);
  lcd.clear();
  logo();
  updateMenu();
  Serial.begin(9600);
}

void logo(){
  byte logo1[8] = {
  0b11111,
  0b11111,
  0b11100,
  0b11000,
  0b10001,
  0b10011,
  0b10011,
  0b10000
  };

  byte logo2[8] = {
  0b10000,
  0b10011,
  0b10011,
  0b10011,
  0b10011,
  0b10011,
  0b11111,
  0b11111
  };
  byte logo3[8] = {
  0b11111,
  0b11111,
  0b00111,
  0b00011,
  0b10001,
  0b11001,
  0b11001,
  0b00001
  };
  byte logo4[8] = {
  0b00001,
  0b11001,
  0b11001,
  0b11001,
  0b11001,
  0b11001,
  0b11111,
  0b11111
  };
  byte c1[8] = {
  0b11111,
  0b11111,
  0b11100,
  0b11000,
  0b10001,
  0b10011,
  0b10011,
  0b10011
  };
  byte c2[8] = {
  0b11111,
  0b11111,
  0b00011,
  0b00011,
  0b11111,
  0b11111,
  0b11111,
  0b11111
  };
  byte c3[8] = {
  0b10011,
  0b10011,
  0b10011,
  0b10001,
  0b11000,
  0b11100,
  0b11111,
  0b11111
  };

  byte c4[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00011,
  0b00011,
  0b11111,
  0b11111
  };

  lcd.createChar(0, logo1);
  lcd.createChar(1, logo2);
  lcd.createChar(2, logo3);
  lcd.createChar(3, logo4);
  lcd.createChar(4, c1);
  lcd.createChar(5, c2);
  lcd.createChar(6, c3);
  lcd.createChar(7, c4);

  lcd.setCursor(6,0);
  lcd.write(byte(0));
  lcd.setCursor(7,0);
  lcd.write(byte(2));
  lcd.setCursor(6,1);
  lcd.write(byte(1));
  lcd.setCursor(7,1);
  lcd.write(byte(3));

  lcd.setCursor(8,0);
  lcd.write(byte(4));
  lcd.setCursor(9,0);
  lcd.write(byte(5));
  lcd.setCursor(8,1);
  lcd.write(byte(6));
  lcd.setCursor(9,1);
  lcd.write(byte(7));
  tone(8, OCTAVE_4_DO, DUREE_TEMPS);
   delay(DUREE_TEMPS);
  delay(2300);
  lcd.clear();
  
  

  
  lcd.setCursor(1,0);
  lcd.write(byte(0));
  lcd.setCursor(2,0);
  lcd.write(byte(2));
  lcd.setCursor(1,1);
  lcd.write(byte(1));
  lcd.setCursor(2,1);
  lcd.write(byte(3));

  lcd.setCursor(3,1);
  lcd.print("rdu");

  lcd.setCursor(7,0);
  lcd.write(byte(4));
  lcd.setCursor(8,0);
  lcd.write(byte(5));
  lcd.setCursor(7,1);
  lcd.write(byte(6));
  lcd.setCursor(8,1);
  lcd.write(byte(7));

  lcd.setCursor(9,1);
  lcd.print("onsole");
  
 tone(8, OCTAVE_4_DO, DUREE_TEMPS);
    delay(DUREE_TEMPS);
    tone(8, OCTAVE_4_RE, DUREE_TEMPS);
    delay(DUREE_TEMPS);
    tone(8, OCTAVE_4_MI, DUREE_TEMPS);
    delay(DUREE_TEMPS);
    tone(8, OCTAVE_4_FA, DUREE_TEMPS);
    delay(DUREE_TEMPS);
    tone(8, OCTAVE_4_SOL, DUREE_TEMPS);
    delay(350);
    tone(8, OCTAVE_4_FA, DUREE_TEMPS);
    delay(DUREE_TEMPS);
    tone(8, OCTAVE_4_MI, DUREE_TEMPS);
    delay(350);
    tone(8, OCTAVE_4_RE, DUREE_TEMPS);
    delay(DUREE_TEMPS);
    tone(8, OCTAVE_4_DO, DUREE_TEMPS);
    
  
}

void loop() {
  
  int xread = analogRead(vrx);
  int yread = analogRead(vry);  // FROM 530 TO 545 IS THE NORMAL VALUE

  Serial.println(xread);
  Serial.println(yread);
 if (!digitalRead(yread < minn) ){  
    action++;
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(yread < minn) );
  }
  if (!digitalRead(yread > maxx) ){
    action--;
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(yread > maxx));
  }
  if (!digitalRead(selectButton)){
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }
//  if(digitalRead(Recharge_detector_pin) == HIGH){
//    charge_anim();
//  }

}

void charge_anim(){
  lcd.clear();
  byte battery1[8] = {
  0b01111,
  0b10000,
  0b10111,
  0b10111,
  0b10111,
  0b10111,
  0b10000,
  0b01111
};
byte battery2[8] = {
  0b11111,
  0b00000,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b00000,
  0b11111
};
byte battery3[8] = {
  0b11100,
  0b00010,
  0b11010,
  0b11011,
  0b11011,
  0b11010,
  0b00010,
  0b11100
};

byte empty1[8] = {
  0b01111,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b01111
};
byte empty2[8] = {
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};
byte empty3[8] = {
  0b11100,
  0b00010,
  0b00010,
  0b00011,
  0b00011,
  0b00010,
  0b00010,
  0b11100
};

while(digitalRead(Recharge_detector_pin) == HIGH){
  
  lcd.createChar(0, battery1);
  lcd.createChar(1, battery2);
  lcd.createChar(2, battery3);
  lcd.createChar(3, empty1);
  lcd.createChar(4, empty2);
  lcd.createChar(5, empty3);

  lcd.setCursor(6, 0);
  lcd.write(byte(0));
  lcd.setCursor(7, 0);
  lcd.write(byte(4));
  lcd.setCursor(8, 0);
  lcd.write(byte(5));
  delay(500);
  lcd.setCursor(6, 0);
  lcd.write(byte(0));
  lcd.setCursor(7, 0);
  lcd.write(byte(1));
  lcd.setCursor(8, 0);
  lcd.write(byte(5));
  delay(500);
  lcd.setCursor(6, 0);
  lcd.write(byte(0));
  lcd.setCursor(7, 0);
  lcd.write(byte(1));
  lcd.setCursor(8, 0);
  lcd.write(byte(2));
  delay(500);
}
  lcd.clear();
  updateMenu();
}




void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Jumper L    >");
      lcd.setCursor(0, 1);
      lcd.print("     Games    ");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("< CATCH THEM!  >");
      lcd.setCursor(0, 1);
      lcd.print("     Games   ");
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("< SPACE BATTLE >");
      lcd.setCursor(0, 1);
      lcd.print("     Games   ");
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("<     DEMO     >");
      lcd.setCursor(0, 1);
      lcd.print("     Tool   ");
      break;
    case 5:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("<     Settings    ");
      lcd.setCursor(0, 1);
      lcd.print("       Tool   ");
      break;
    case 6:
      menu = 5;
      break;
  }
}

void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
    case 5:
      action5();
      break;
  }
}


void action1() {
 int exit = 0;
 int pos = 15;
 int posp = 1;
 int score = 0;
 int d = 500;
 int startup = 0;
 lcd.init();
 lcd.backlight();
 lcd.print("Jumper L");
 lcd.setCursor(5, 1);

 lcd.print("Start on 3");
 delay(1000);
 lcd.setCursor(5, 1);
 lcd.print("Start on 2");
 delay(1000);
 lcd.setCursor(5, 1);
 lcd.print("Start on 1");
 delay(1000);
 lcd.setCursor(5, 1);
 lcd.print("                 ");
 delay(10);
 lcd.setCursor(5, 1);
 lcd.print("GO!");
 delay(1000);


 while(exit == 0){
   if(!digitalRead(backButton)){
     exit = 1;
     delay(10);
     updateMenu();
   }
   int xread = analogRead(vrx);
   int yread = analogRead(vry);

   
   lcd.clear();
   lcd.setCursor(14, 0);
   lcd.print(score);
   lcd.setCursor(4, posp);
   lcd.print("L");
   lcd.setCursor(pos, 1);
   lcd.print("|");
   delay(d);
   lcd.print(" ");
   Serial.println(pos);
   pos = pos - 1;
   if(pos < -1){
     pos = 15;
   }

   if(yread >maxx or !digitalRead(selectButton) ){
     lcd.setCursor(4, posp);
     lcd.print(" ");
     posp = 0;
     lcd.setCursor(4, posp);
     lcd.print("L");
    
    
   }else{
     lcd.setCursor(4, posp);
     lcd.print(" ");
     posp = 1;
     lcd.setCursor(4, posp);
     lcd.print("L");
   }
  
   if(pos == 4 and posp == 1){
     lcd.clear();
     lcd.print("GAME OVER");
     lcd.setCursor(14, 0);
     lcd.print(score);
     lcd.setCursor(1, 1);
     lcd.print("Press A");
     while(digitalRead(selectButton) == 1 );
     lcd.clear();
     score = 0;
     pos = 15;
     d = random(500, 750);
     lcd.setCursor(4, posp);
     lcd.print("L");
   }
   if(pos == 4 && posp == 0){
     score = score + 1;
     d = d - random(50,70);
     Serial.println(d);
   }
   if(d < 0){
     d = random(20, 50);
   }
 }
 
}
void action2() {
 int plrpos = 0;
 int pos = 4; // la position de depare des ballon
 int d = 500;
 int ranpos = 0;
 int score = 0;
 int exit = 0;
 lcd.init();
 lcd.backlight();
 lcd.print("CATCH THEM!");
 lcd.setCursor(5, 1);

 lcd.print("Start on 3");
 delay(1000);
 lcd.setCursor(5, 1);
 lcd.print("Start on 2");
 delay(1000);
 lcd.setCursor(5, 1);
 lcd.print("Start on 1");
 delay(1000);
 lcd.setCursor(5, 1);
 lcd.print("                 ");
 delay(10);
 lcd.setCursor(5, 1);
 lcd.print("GO!");
 delay(1000);
 lcd.clear();
 lcd.setCursor(3, 0);
  lcd.print("|");
  lcd.setCursor(3, 1);
  lcd.print("|");
  lcd.setCursor(0, 0);
  lcd.print("Sco");
  lcd.setCursor(0, 1);
  lcd.print(score);

 while(exit == 0){
   if(!digitalRead(backButton) ){
     exit = 1;
     delay(10);
     updateMenu();
   }
   int xread = analogRead(vrx);
   int yread = analogRead(vry);

   
   Serial.println(ranpos);

 lcd.setCursor(0, 0);
  lcd.print("Sco");
  lcd.setCursor(0, 1);
  lcd.print(score);

 // Moving the PLR
  lcd.setCursor(15, plrpos);
  lcd.print("]");
 if(xread > maxx){
   lcd.setCursor(15,plrpos);
   lcd.print(" ");
   plrpos = 1;
 }else if(xread < minn){
   lcd.setCursor(15,plrpos);
   lcd.print(" ");
   plrpos = 0;
 }
 
 
 if(ranpos == 0){
   lcd.setCursor(pos, ranpos);
   lcd.print("o");
   delay(d);
   lcd.setCursor(pos, ranpos);
   lcd.print(" ");
   pos = pos + 1;
   if(pos > 15){
     ranpos = random(2);
     d = d - random(7, 15);
     pos = 4;
   }
 }else if(ranpos == 1){
   lcd.setCursor(pos, ranpos);
   lcd.print("o");
   delay(d);
   lcd.setCursor(pos, ranpos);
   lcd.print(" ");
   pos = pos + 1;
   if(pos > 15){
     d = d - random(7, 15);
     ranpos = random(2);
     pos = 4;
   }

 }
 if(d < 0){
   d = random(200, 300);
 }
  
 if(pos >= 15 and ranpos == plrpos){
   Serial.println(d);
   score = score + 1;
 }
 if(pos >= 15 and ranpos != plrpos){
   lcd.clear();
   lcd.print("GAME OVER!");
   lcd.setCursor(0, 14);
   lcd.print(score);
   while(digitalRead(selectButton) == 1);
   lcd.clear();
   score = 0;
   lcd.setCursor(3, 0);
  lcd.print("|");
  lcd.setCursor(3, 1);
  lcd.print("|");
  lcd.setCursor(0, 0);
 }
}

}

void action3(){
  

int exit = 0;

int plrpos = 0;
int numpos = random(2);
int score = 0;


byte fusee[8] = {
  0b11000,
  0b11100,
  0b11110,
  0b00111,
  0b00111,
  0b11110,
  0b11100,
  0b11000
};

byte cartouche[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b01110,
  0b00000,
  0b00000,
  0b00000
};

byte advers[8] = {
  0b00000,
  0b00100,
  0b01010,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01010
};

lcd.init();
 lcd.backlight();
 lcd.print("SPACE BATTLE");
 lcd.setCursor(5, 1);

 lcd.print("Start on 3");
 delay(1000);
 lcd.setCursor(5, 1);
 lcd.print("Start on 2");
 delay(1000);
 lcd.setCursor(5, 1);
 lcd.print("Start on 1");
 delay(1000);
 lcd.setCursor(5, 1);
 lcd.print("                 ");
 delay(10);
 lcd.setCursor(5, 1);
 lcd.print("GO!");
 delay(1000);
 lcd.clear();
 lcd.createChar(0, fusee);
 lcd.createChar(1, advers);
 lcd.createChar(2, cartouche);
 
 while(exit == 0){
   if(!digitalRead(backButton)){
     exit = 1;
     delay(10);
     updateMenu();
   }

   
   int yread = analogRead(vrx);
  int xread = analogRead(vry);
 
  lcd.setCursor(8, 0);
  lcd.print(score);

  lcd.setCursor(0, plrpos);
  lcd.write(byte(0));

  if(yread <= minn){
    lcd.setCursor(0, plrpos);
    lcd.print(" ");
    plrpos++ ;
    if(plrpos > 1){
      plrpos = 1;
    }
  }else if (yread >= maxx){
   lcd.setCursor(0, plrpos);
    lcd.print(" ");
    plrpos-- ;
    if(plrpos < 0){
      plrpos = 0;
    }
  }
  if(numpos == 0){
    lcd.setCursor(15, numpos);
    lcd.write(byte(1));
  }else if(numpos == 1){
    lcd.setCursor(15, numpos);
    lcd.write(byte(1));
  }
  if(!digitalRead(selectButton)){
   for (int t=0; t>15; t++)
   {
     lcd.setCursor(t, plrpos);
     lcd.write(byte(2));
     delay(500);
   }
    if(plrpos == numpos){
      lcd.setCursor(15, numpos);
      lcd.print(" ");
      score++ ;
      numpos = random(2);
      delay(100);
    }else{
      lcd.clear();
      lcd.print("GAME OVER");
      lcd.setCursor(2, 1);
      lcd.print("Press A");
      while(!digitalRead(selectButton));
      lcd.clear();
      score = 0;
      numpos = random(2);
    }
 }
 
}
}

void action4(){
  int exit = 0;
    while(exit == 0){
      lcd.clear();
      logo();

      if(!digitalRead(backButton)){
        lcd.clear();
        exit = 1;
        updateMenu();
      }
 }
}

void action5(){
  int exit = 0;

  int menu1 = 1;
  int action1 = 1;

  while(exit == 0){
    lcd.clear();
    if(!digitalRead(backButton)){
        lcd.clear();
        exit = 1;
        updateMenu();
      }

      switch (menu1) {
    case 0:
      menu1 = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Update   >");
      lcd.setCursor(0, 1);
      lcd.print("    Settings    ");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("<Information>");
      lcd.setCursor(0, 1);
      lcd.print("    Settings    ");
      break;
    case 3:
      menu1 = 2;
      break;
  }

  int xread = analogRead(vrx);
  int yread = analogRead(vry);  // FROM 530 TO 545 IS THE NORMAL VALUE

  Serial.println(xread);
  Serial.println(yread);
 if (!digitalRead(yread < minn) ){  
    action1++;
    menu1++;
    
    delay(100);
    while (!digitalRead(yread < minn) );
  }
  if (!digitalRead(yread > maxx) ){
    action1--;
    menu1--;
    
    delay(100);
    while(!digitalRead(yread > maxx));
  }
  if (!digitalRead(selectButton)){
    switch (menu1) {
    case 1:
      action11();
      break;
    case 2:
      action21();
      break;
  }
    delay(100);
    while (!digitalRead(selectButton));
  }
  }

}

void action11(){
  lcd.clear();
  lcd.print("comming soon");
  delay(2500);
}

void action21(){
  lcd.clear();
  lcd.print("comming soon");
  delay(2500);
}
