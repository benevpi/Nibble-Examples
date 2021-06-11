#include <CircuitOS.h>
#include <Nibble.h>

Display* display;
Sprite* sprite;


void setup() {
  Nibble.begin();
  display = Nibble.getDisplay();

  Serial.begin(115200);

  sprite = display->getBaseSprite();
  sprite->clear(TFT_BLACK);
	display->commit();

  Piezo.begin(BUZZ_PIN);

  sprite->setTextColor(TFT_WHITE);
  sprite->setTextFont(1);
  sprite->setTextSize(1);
  sprite->printCenter("hello world");
  display->commit();

  Piezo.tone(440, 500);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("hello from nibble\n");

  delay(1000);

}
