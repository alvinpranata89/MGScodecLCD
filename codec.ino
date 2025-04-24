#include <UTFTGLUE.h>
#include "campbell.h"
#include "snake.h"
#include "incoming.h"

#define activeclr 85, 204, 155
#define inactiveclr 30, 71, 54
#define codecbg 0, 25, 0
//      (LCD_ID ,RS,WR,CS, RST,RD);
UTFTGLUE lcd(0, 13, 12, 33, 32, 15);  
int scan_y = 0;
int delayMs=1;
int a=0;
int *ap=&a;

struct VoiceMeter {
  
  void draw(int barActive, int *ap) {
    // --- the 9 Bars ---
    for (int i = 0; i < 9; i++) {
      int top = 80 - i * 7;
      int bottom = top + 5;
      
      if (i<=5) 
        {lcd.setColor(activeclr);}
      else if (barActive >= i)
            {lcd.setColor(activeclr);}
           else 
            {lcd.setColor(inactiveclr);}
      lcd.fillRect(108, top, 110, bottom);
      if(a==0) {delay(50);}
      // lcd.fillRect(112, top, 208, bottom);
      if (i==6)
      {lcd.fillRect(112, top, 128+(i*2)+1, bottom);}
      else if (i==7)
      {lcd.fillRect(112, top, 118+(i*10), bottom);}
      else if (i==8)
      {
        lcd.fillRect(112, top, 217, bottom);
        //m  
        lcd.drawLine(202,31,206,31);//      -------
        lcd.drawLine(202,32,202,34);     // |
        lcd.drawLine(204,32,204,34);     //    |
        lcd.drawLine(206,32,206,34);    //        |
        //a
        lcd.drawLine(208,31,212,31);        // top -----
        lcd.drawLine(208,32,208,34);        //     |
        lcd.drawLine(208,32,212,32);        // mid -----
        lcd.drawLine(212,32,212,34);    //             |
        //x  
        lcd.drawLine(214,31,217,34);/*  \   */ 
        lcd.drawLine(217,31,214,34);/* /    */
       //
      }
      else
      {lcd.fillRect(112, top, 128+(i*2), bottom);}
    }

  }
};
VoiceMeter meter;
VoiceMeter *meterp = &meter;

void drawImageFromCenter(int x, int y, int w, int h, const uint16_t* img) {
  int center = h / 2;

  for (int offset = 0; offset <= center; offset++) {
    int upperRow = center - offset;
    int lowerRow = center + offset;

    if (upperRow >= 0) {
      for (int i = 0; i < w; i++) {
        uint16_t color = img[upperRow * w + i];
        lcd.setColor((color >> 11) << 3, ((color >> 5) & 0x3F) << 2, (color & 0x1F) << 3);
        lcd.drawPixel(x + i, y + upperRow);
      }
    }

    if (lowerRow < h && lowerRow != upperRow) {
      for (int i = 0; i < w; i++) {
        uint16_t color = img[lowerRow * w + i];
        lcd.setColor((color >> 11) << 3, ((color >> 5) & 0x3F) << 2, (color & 0x1F) << 3);
        lcd.drawPixel(x + i, y + lowerRow);
      }
    }

    delay(2);  // Adjust speed of expansion effect
  }
}

void drawCodecFrame(int *ap) {

  lcd.setColor(codecbg); 
  lcd.fillRect(0, 0, 320, 240);
  delay(1);
  //P
  lcd.setColor(inactiveclr);
  lcd.fillRect(111,14,114,18);
  lcd.fillRect(118,14,120,16);
  lcd.drawLine(115, 14, 118, 14);
  lcd.drawLine(115, 16, 118, 16);
//
//T
  lcd.setColor(inactiveclr);
  lcd.drawLine(123,14,132,14);
  lcd.fillRect(126,15,128,18);
//
//T
  lcd.setColor(inactiveclr);
  lcd.drawLine(134,14,143,14);
  lcd.fillRect(138,15,140,18);
  // VoiceMeter *meterp = &meter;
  meterp->draw(0, &a);

//down arrow                     x0   y0   x1  y1   x2  y2
  lcd.Adafruit_GFX::fillTriangle(107, 100, 102, 95, 112, 95, lcd.color565(inactiveclr));
// 
//m  
  lcd.setColor(inactiveclr);
  lcd.drawLine(114,95,120,95);// -----
  lcd.drawLine(114,96,114,99);// |
  lcd.drawLine(117,96,117,99);//   |
  lcd.drawLine(120,96,120,99);//     |
//e
   lcd.drawLine(122,95,122,99); //      |
   lcd.drawLine(123,95,128,95); //top -
   lcd.drawLine(123,97,128,97); //middle -
   lcd.drawLine(123,99,128,99); //bottom -
//m  
  lcd.drawLine(131,95,137,95);// -------
  lcd.drawLine(131,96,131,99);// |
  lcd.drawLine(134,96,134,99);//    |
  lcd.drawLine(137,96,137,99);//       |
// .
  lcd.drawLine(139,98,139,99);//         .     
// <]
  lcd.Adafruit_GFX::fillTriangle(164, 98, 170, 95, 170, 101, lcd.color565(inactiveclr));
//
// T
  lcd.drawLine(174,95,181,95);//---
  lcd.drawLine(178,95,178,99);// |
//
// U
  lcd.drawLine(183,95,183,99);// |
  lcd.drawLine(184,99,190,99);//  __
  lcd.drawLine(190,95,190,99);//    |
//
// N
  lcd.drawLine(192,95,192,99);// | 
  lcd.drawLine(193,95,199,95);// top ---
  lcd.drawLine(199,95,199,99);//        |
//
// E
   lcd.drawLine(201,95,201,99); //      |
   lcd.drawLine(202,95,207,95); //top -
   lcd.drawLine(202,97,207,97); //middle -
   lcd.drawLine(202,99,207,99); //bottom -
//   
// [>
  lcd.Adafruit_GFX::fillTriangle(218, 98, 212, 95, 212, 101, lcd.color565(inactiveclr));
//
/////////////////////////////////////////////start drawing codec frame//////////////////////////////////////////////////
  lcd.setColor(activeclr);//color for codec frame line
  lcd.fillRect(5,10,7,18);//top left frame decoration
  lcd.fillRect(5,95,7,103);//bottom left frame decoration
  lcd.fillRect(312,10,314,18);//top right frame decoration
  lcd.fillRect(312,95,314,103);//bottom right frame decoration
  
  lcd.drawRect(13,8,307,105);//outer box
  lcd.drawRect(13,8,95,105);//left box
  lcd.drawRect(225,8,307,105);//right box
  lcd.drawLine(96, 92, 224, 92);// freq / mem tune separator
//
//dialog box
  lcd.setColor(activeclr);
  lcd.drawRect(13,128,307,230);

  // --- Frequency digits ---
    lcd.setColor(activeclr);
    // 1
    lcd.drawLine(152, 61, 153, 61);
    lcd.drawLine(153, 62, 153, 67);
    // 4
    lcd.drawLine(157, 61, 157, 64);
    lcd.drawLine(158, 64, 165, 64);
    lcd.drawLine(166, 61, 166, 67);
    // 0
    lcd.drawRect(170, 60, 180, 67);
    lcd.drawLine(173, 65, 177, 61);
    // .
    lcd.drawLine(184, 66, 184, 67);
    // 8
    lcd.drawRect(190, 60, 198, 63);
    lcd.drawRect(189, 63, 198, 67);
    // 5
    lcd.drawLine(212, 60, 202, 60);
    lcd.drawLine(202, 61, 202, 62);
    lcd.drawLine(202, 63, 212, 63);
    lcd.drawLine(212, 64, 212, 66);
    lcd.drawLine(212, 67, 202, 67);

    // little square
    lcd.drawRect(131, 82, 134, 85);

  drawImageFromCenter(235, 10, 60, 95, snake);
  drawImageFromCenter(25, 10, 60, 95, campbell);
}

void showMessage(const char* msg) {
  lcd.setBackColor(codecbg);
  lcd.setColor(255, 255, 255);  // white text
  delay(1000); 
}

void typeMessageSnake(const char* msg, int x, int y, int delayMs, int *ap) {

  String buffer = "";            // stores progressively built string
  for (int i = 0; msg[i] != '\0'; i++) {
    buffer += msg[i];            // add next character
    lcd.setBackColor(codecbg);     
    lcd.setColor(255, 255, 255);  
    lcd.print(buffer, x, y);     // redraw entire buffer
    if (i % 3 == 0) {
     lcd.drawRGBBitmap(235, 10, snake_talk, 60, 95);
     int upper_bound = 8;
     int lower_bound = 5;
     meterp->draw(rand() % (upper_bound - lower_bound + 1) + lower_bound, &a);
     delay(1);
     lcd.drawRGBBitmap(235, 10, snake, 60, 95);
    }
    delay(delayMs);
  }
  meterp->draw(2, &a);
}

void typeMessageCampbell(const char* msg, int x, int y, int delayMs, int *ap) { 
  String buffer = "";            // stores progressively built string
  for (int i = 0; msg[i] != '\0'; i++) {
    buffer += msg[i];            // add next character
    lcd.setBackColor(codecbg);     
    lcd.setColor(255, 255, 255);  
    lcd.print(buffer, x, y);     // redraw entire buffer            
    if (i % 3 == 0) {
     lcd.drawRGBBitmap(25, 10, campbell_talk, 60, 95);
     int upper_bound = 8;
     int lower_bound = 5;
     meterp->draw(rand() % (upper_bound - lower_bound + 1) + lower_bound, &a);
     delay(1);
     lcd.drawRGBBitmap(25, 10, campbell, 60, 95);
    }
    delay(delayMs);
  }
  meterp->draw(2,&a);
}

void setup() {

  lcd.InitLCD();
  lcd.clrScr();
  lcd.setBackColor(codecbg);
  lcd.setRotation(3); // this is optional, comment it if not needed

  lcd.setColor(0, 30, 0);
  lcd.setFont(SmallFont);  // GLUE maps to GFX fonts

  // Draw UI elements
  lcd.setColor(0, 0, 0); 
  lcd.fillRect(0, 0, 320, 240);
  lcd.drawRGBBitmap(110, 70, incoming, 120, 50);
  delay(2);
  lcd.fillRect(0, 0, 320, 240);
  delay(1);
  lcd.drawRGBBitmap(110, 70, incoming, 120, 50);
  delay(100);
  lcd.fillRect(0, 0, 320, 240);
  delay(1);
  lcd.drawRGBBitmap(110, 70, incoming, 120, 50);
  delay(400);
  lcd.fillRect(0, 0, 320, 240);
  delay(1);
  drawCodecFrame(&a);
  a=1;
  delay(100);
   
  typeMessageSnake("This is Snake. ", CENTER, 150, delayMs, &a);
  delay(700);
  lcd.print("                               ", CENTER, 150);
  typeMessageSnake("Colonel, can you hear me?", CENTER, 150, delayMs, &a);
  delay(700);
  lcd.print("                               ", CENTER, 150);
  typeMessageCampbell("Loud and Clear.", CENTER, 150, delayMs, &a);
  delay(700);
  lcd.print("                               ", CENTER, 150);
  typeMessageCampbell("What's the situation, Snake?", CENTER, 150, delayMs, &a);
  delay(700);
  lcd.print("                               ", CENTER, 150);
  typeMessageSnake("Looks like the elevator in the back\n   is the only way up.", CENTER, 150, delayMs, &a);
  delay(700);
  lcd.print("                                   ", CENTER, 150);
  lcd.print("                                   ", CENTER, 160);
  lcd.print("                                   ", CENTER, 165);
  typeMessageCampbell("Just as I expected.", CENTER, 150, delayMs, &a);
  delay(700);
  lcd.print("                                   ", CENTER, 150);
  typeMessageCampbell("You'll have to take the elevator to\n  the surface.", CENTER, 150, delayMs, &a);
  delay(700);
}

void loop() {

}
