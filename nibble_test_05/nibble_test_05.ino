#include <CircuitOS.h>
#include <Nibble.h>

#define MAX_ROCKS 10
#define INIT_ROCKS 1
#define ROCK_INCREASE_SPEED 100

Display* display;
Sprite* sprite;

const int icon_diameter = 16;

int position_x = 60;
int position_y = 60;

int loop_counter = 0;

int rocks_x[MAX_ROCKS];
int rocks_y[MAX_ROCKS];
int num_rocks = INIT_ROCKS;

bool up_held = false;
bool down_held = false;
bool left_held = false;
bool right_held = false;

bool beep = false;
bool boop = false;

const unsigned short face[0x100] ={
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFEAA, 0xFECA, 0xFEEA, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0010 (16)
0x0000, 0x0000, 0x0000, 0x0000, 0xFDC8, 0xFE89, 0xFE89, 0xFE69, 0xFE69, 0xFE69, 0xFE8A, 0xFE89, 0xFD45, 0x0000, 0x0000, 0x0000,   // 0x0020 (32)
0x0000, 0x0000, 0x0000, 0xFE29, 0xFEA9, 0xFF0A, 0xFEAA, 0xFE89, 0xFE69, 0xFE89, 0xFECA, 0xFF0A, 0xFE89, 0xFE29, 0x0000, 0x0000,   // 0x0030 (48)
0x0000, 0x0000, 0xFE89, 0xFE89, 0xFECA, 0xFE49, 0xFE69, 0xFE69, 0xFE69, 0xFE69, 0xFE69, 0xFE69, 0xFEEA, 0xFE69, 0xFE49, 0x0000,   // 0x0040 (64)
0x0000, 0x0000, 0xFE49, 0xFEEA, 0xFE49, 0xFE69, 0xFE69, 0xFE69, 0xFE69, 0xFE69, 0xFE69, 0xFE69, 0xFE49, 0xFF0A, 0xFE49, 0x0000,   // 0x0050 (80)
0x0000, 0xFE49, 0xFEAA, 0xFE69, 0xFE69, 0xFE29, 0xFE69, 0xFE69, 0xFE69, 0xFE69, 0xFE69, 0xFE29, 0xFE69, 0xFE69, 0xFE89, 0xFE49,   // 0x0060 (96)
0x0000, 0xFE49, 0xFEEA, 0xFE8A, 0xEDC8, 0x6A40, 0xAC24, 0xFEAA, 0xFE69, 0xFEAA, 0xA3E4, 0x7261, 0xF608, 0xFE89, 0xFEEA, 0xFE49,   // 0x0070 (112)
0x0000, 0xFE69, 0xFECA, 0xFEAA, 0xCCE6, 0x4120, 0x82E1, 0xFE8A, 0xFE69, 0xFE89, 0x7AA1, 0x4940, 0xD547, 0xFEAA, 0xFEEA, 0xFE49,   // 0x0080 (128)
0x0000, 0xFE49, 0xFECA, 0xFE69, 0xF608, 0x82E2, 0xC4A5, 0xFEAA, 0xFE69, 0xFE8A, 0xB465, 0x8B02, 0xF629, 0xFE69, 0xFEEA, 0xFE49,   // 0x0090 (144)
0x0000, 0xFE49, 0xFEEA, 0xFE49, 0xFE69, 0xFECA, 0xFEEA, 0xFEAA, 0xFEAA, 0xFEAA, 0xFEEA, 0xFECA, 0xFE69, 0xFE49, 0xFEEA, 0xFE69,   // 0x00A0 (160)
0x0000, 0xFE69, 0xFECA, 0xFE69, 0xFE69, 0xC4A5, 0xAC24, 0xB424, 0xB424, 0xB424, 0xAC04, 0xC4C6, 0xFE69, 0xFE69, 0xFEAA, 0xFE49,   // 0x00B0 (176)
0x0000, 0xFFE0, 0xFE49, 0xFEEA, 0xFE69, 0xC4A5, 0xAC24, 0xB444, 0xB444, 0xB444, 0xAC24, 0xC4C6, 0xFE69, 0xFEEA, 0xFE49, 0x0000,   // 0x00C0 (192)
0x0000, 0x0000, 0xFE49, 0xFE89, 0xFECA, 0xFEAA, 0xFEAA, 0xFEAA, 0xFEAA, 0xFEAA, 0xFEAA, 0xFE8A, 0xFECA, 0xFE89, 0xFE49, 0x0000,   // 0x00D0 (208)
0x0000, 0x0000, 0x0000, 0xFE29, 0xFEAA, 0xFF0A, 0xFEAA, 0xFE69, 0xFE69, 0xFE69, 0xFEAA, 0xFF0A, 0xFE89, 0xFE49, 0x0000, 0x0000,   // 0x00E0 (224)
0x0000, 0x0000, 0x0000, 0x0000, 0xFDE9, 0xFE89, 0xFE89, 0xFE69, 0xFEAA, 0xFE69, 0xFE89, 0xFE89, 0xFDA9, 0x0000, 0x0000, 0x0000,   // 0x00F0 (240)
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFDA9, 0xFECA, 0xFEA9, 0xFEA9, 0xFDE7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0100 (256)
};

void up_press_callback() { up_held=true; }
void up_rel_callback() { up_held=false; }
void down_press_callback() { down_held=true; }
void down_rel_callback() { down_held=false; }
void left_press_callback() { left_held=true; }
void left_rel_callback() { left_held=false; }
void right_press_callback() { right_held=true; }
void right_rel_callback() { right_held=false; }

void a_held_callback() { Piezo.tone(440, 500); }

void b_held_callback() { Piezo.tone(880, 500); }

void setup() {
  Nibble.begin();
  display = Nibble.getDisplay();
  Piezo.begin(BUZZ_PIN);

  //button presses
  Input::getInstance()->setBtnPressCallback(BTN_LEFT, left_press_callback);
  Input::getInstance()->setBtnReleaseCallback(BTN_LEFT, left_rel_callback);
  Input::getInstance()->setBtnPressCallback(BTN_RIGHT, right_press_callback);
  Input::getInstance()->setBtnReleaseCallback(BTN_RIGHT, right_rel_callback);
  Input::getInstance()->setBtnPressCallback(BTN_DOWN, down_press_callback);
  Input::getInstance()->setBtnReleaseCallback(BTN_DOWN, down_rel_callback);
  Input::getInstance()->setBtnPressCallback(BTN_UP, up_press_callback);
  Input::getInstance()->setBtnReleaseCallback(BTN_UP, up_rel_callback);

  //beep boop
  Input::getInstance()->setButtonHeldCallback(BTN_A, 50, a_held_callback);
  Input::getInstance()->setButtonHeldCallback(BTN_B, 50, b_held_callback);

  Serial.begin(115200);

  sprite = display->getBaseSprite();
  sprite->clear(TFT_BLACK);
	display->commit();

  for(int i=0; i<num_rocks; i++) {
    rocks_x[i] = random(0,display->getWidth());
    rocks_y[i] = 0;
  }
}

void loop() {

  loop_counter++;
  if(loop_counter > 100) {
    loop_counter = 0;
    if (num_rocks < MAX_ROCKS) {
      rocks_x[num_rocks] = random(0,display->getWidth());
      rocks_y[num_rocks] = 0;
      num_rocks++;
    }
  }
  
  Input::getInstance()->loop(0);

  if (up_held) position_y--;
  if (down_held) position_y++;
  if (left_held) position_x--;
  if (right_held) position_x++;

//note -- signed int here is important!!
  if (position_x > (signed int)display->getWidth() - icon_diameter) { 
    position_x = display->getWidth()- icon_diameter; 
  }
  if (position_x == -1) { position_x = 0; }
  if (position_y > (signed int) display->getHeight() - icon_diameter) { 
    position_y = display->getHeight() - icon_diameter; 
  }
  if (position_y == -1) { position_y = 0; }

  sprite->clear(TFT_BLACK);
  sprite->drawIcon(face, position_x, position_y, 16, 16, 1);
  

  for(int i=0; i<num_rocks; i++) {
    rocks_y[i]++;
    if (rocks_y[i] > display->getHeight()) {
      rocks_x[i] = random(0,display->getWidth());
      rocks_y[i] = 0;
    }
    sprite->drawIcon(face, rocks_x[i], rocks_y[i], 16, 16, 1);
  }
  display->commit();

  //collision detection
  for(int i=0; i<num_rocks; i++) {
    int delta_x = position_x - rocks_x[i];
    int delta_y = position_y - rocks_y[i];
    if (delta_x*delta_x + delta_y*delta_y < 64 )  { // 64 == r^2
      sprite->clear(TFT_BLACK);
      sprite->setTextColor(TFT_WHITE);
      sprite->setTextFont(1);
      sprite->setTextSize(1);
      sprite->printCenter("Game Over");
      display->commit();
      while(1); // note -- falls foul of the ESP8266 watchdog I think. resets the game and works quite well
    }

  }
  delay(10);

}