#include <UTouch.h>
#include <UTouchCD.h>
#include <UTFT.h>

UTFT    myGLCD(SSD1289,38,39,40,41);
UTouch  myTouch( 6, 5, 4, 3, 2);

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

String names[] = {
  "nes",
  "snes",
  "gba",
  "gamecube",
  "genesis",
  "saturn",
  "dreamcast",
  "wii",
  "psx",
  "ps2",
  "ps3",
  "",
  "xbox",
  "xbox360",
  "",
  "mister"
};

void setup() {
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  
  draw(-1, -1);
}

int sel_x = -1;
int sel_y = -1;

void loop() {
  
  int width = myGLCD.getDisplayXSize();
  int height = myGLCD.getDisplayYSize();
  int w = width / 4;
  int h = height / 4;
  
  if (myTouch.dataAvailable()) {
    myTouch.read();
    int xx = myTouch.getX();
    int yy = myTouch.getY();
    int x = (xx / w);
    int y = (yy / h);
    if( x >= 0 && y >= 0) {
      if (sel_x == x && sel_y ==y){
        sel_x = -1;
        sel_y = -1;
        draw(-1, -1);
      } else {     
        sel_x = x;
        sel_y = y;   
        draw(x, y);
      }
    }
  }
}

void draw(int selected_x, int selected_y){
  //myGLCD.clrScr();
  myGLCD.setBackColor(0,0,0);
  
  int width = myGLCD.getDisplayXSize();
  int height = myGLCD.getDisplayYSize();
  int w = width / 4;
  int h = height / 4;

  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      int port = x + (y * 4) + 1;
      if (x == selected_x && y == selected_y) {
        myGLCD.setColor(255, 0, 0);
      } else {
        myGLCD.setColor(16, 167, 103);
      }
      myGLCD.drawRect(x*w, y*h, (x+1)*w-1, (y+1)*h-1);
      
      myGLCD.setFont(BigFont);   
      myGLCD.print(String(port), x*w+2, y*h+2);
      
      myGLCD.setFont(SmallFont);
      int fontheight = myGLCD.getFontYsize();
      myGLCD.print(names[port-1], x*w+3, y*h+(h-fontheight-3));      
    }
  }
}
