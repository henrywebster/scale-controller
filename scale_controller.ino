/*
  Scale Controller Arduino Sketch
  Henry J. Webster
*/

#include "Keyboard.h"
#include "HX711.h"

const float L_CALIBRATION_FACTOR = -14000.0;
const float R_CALIBRATION_FACTOR = -14000.0;

const unsigned int L_DOUT = 3;
const unsigned int L_CLK = 2;

const unsigned int R_DOUT = 7;
const unsigned int R_CLK = 6;

HX711 l_scale;
HX711 r_scale;

float prev_bias = 0.0;
float bias = 0.0;

void setup() {
  
  l_scale.begin(L_DOUT, L_CLK);
  l_scale.set_scale(L_CALIBRATION_FACTOR); 
  l_scale.tare(); 

  r_scale.begin(R_DOUT, R_CLK);
  r_scale.set_scale(R_CALIBRATION_FACTOR); 
  r_scale.tare(); 
  
  Keyboard.begin();
}

void loop() {

  prev_bias = bias;
  bias = l_scale.get_units() - r_scale.get_units();

  if (prev_bias > 0 && bias < 0) {
    Keyboard.release(KEY_LEFT_ARROW);
    Keyboard.press(KEY_RIGHT_ARROW);
  }
  if (prev_bias < 0 && bias > 0) {
    Keyboard.release(KEY_RIGHT_ARROW);
    Keyboard.press(KEY_LEFT_ARROW);
  }
}
