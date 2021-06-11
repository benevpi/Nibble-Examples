#include <CircuitOS.h>
#include <Nibble.h>

Display* display;
Sprite* sprite;

int position_x = 0;
int direction = 1;

bool face[] = {false, false, true, true, true, false, false,
        false, true, false, false, false, true, false,
        true, false, true, false, true, false, true,
        true, false, false, false, false, false, true,
        true, false, true, true, true, false, true,
        false, true, false, false, false, true, false,
        false, false, true, true, true, false, false};

void setup() {
  Nibble.begin();
  display = Nibble.getDisplay();

  Serial.begin(115200);

  sprite = display->getBaseSprite();
  sprite->clear(TFT_BLACK);
	display->commit();

}

void loop() {
  // put your main code here, to run repeatedly:

  sprite->clear(TFT_BLACK);
  sprite->drawMonochromeIcon(face, position_x, 50, 7, 7, 1, TFT_WHITE);
  display->commit();

  position_x += direction;

  if(position_x == (display->getWidth()-7) || position_x == 0) direction = direction * -1;

  delay(10);

}