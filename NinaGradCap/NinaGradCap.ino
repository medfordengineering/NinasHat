
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define INTPIN2   2
#define INTPIN3   3

#define BLK     0x0000
#define BLE     0x001F
#define RED     0xF800
#define GRN     0x07E0
#define CYN     0x07FF
#define MGA     0xF81F
#define YEW     0xFFE0
#define WHE     0xFFFF

volatile int state = 0;

static const uint16_t PROGMEM

RGB_bmp[64] = {
  RED, RED, RED, RED, RED, RED, RED, RED,
  RED, RED, RED, RED, WHE, RED, RED, RED,
  RED, RED, RED, WHE, WHE, WHE, RED, RED,
  BLK, RED, WHE, WHE, WHE, RED, RED, BLK,
  BLK, RED, WHE, RED, WHE, RED, RED, BLK,
  BLK, BLK, RED, RED, WHE, RED, BLK, BLK,
  BLK, BLK, BLK, RED, WHE, RED, BLK, BLK,
  BLK, BLK, BLK, BLK, RED, BLK, BLK, BLK,
};



Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(11, 12, PIN,
                            NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(250);
  matrix.setTextColor(colors[0]);


  // while (1);

  pinMode(INTPIN2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTPIN2), ablink, LOW);

  pinMode(INTPIN3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTPIN3), noblink, LOW);
}
int x  = matrix.width();
int pass = 0;

void loop() {

  switch (state) {
    case 0:
      matrix.fillScreen(0);
      matrix.setCursor(x, 0);
      matrix.print(F("HARVARD"));
      if (--x < -36) {
        x = matrix.width();
        if (++pass >= 3) pass = 0;
        matrix.setTextColor(colors[pass]);
      }
      matrix.show();
      delay(100);
      break;
    case 1:
      //for (int x = 0; x < 9; x++) {
      matrix.drawRGBBitmap(0, 0, (const uint16_t *) RGB_bmp, 8, 8);
      matrix.show();
      //   delay(300);
      //   matrix.clear();
      // }
      break;
  }


}

void noblink() {
  state = 0;
}

void ablink() {
  state = 1;
}
