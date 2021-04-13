/*
  Scale Callibrator Sketch
  Henry J. Webster
*/

#include "HX711.h"

// known mass of object 
const float reference_kg = 8.0;
// float equality tolerance
const float tolerance = 0.03;
// amount calibration factor changes to adjust each iteration
const float calibration_step = 50.0;

const unsigned int DOUT = 7;
const unsigned int CLK = 6;

HX711 scale;

bool complete = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Scale Controller Calibrator");
  Serial.println("Remove all weight from scales");

  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare();
}

void loop() {

  if(!complete) {
    float calibration_factor = 0.0;
    scale.set_scale(calibration_factor);
    float measurement = scale.get_units();

    // wait for something to be put on scale
    while(abs(measurement) < 1.0) {
      // 
    }
    
    float difference = reference_kg - measurement;
    while(abs(difference) > tolerance) {
      if (difference > 0.0) {
        calibration_factor += calibration_step;
      } else {
        calibration_factor -= calibration_step;
      }
      Serial.println(measurement);
      if (measurement < 0.0) {
        calibration_factor = calibration_factor * -1;
      }
      scale.set_scale(calibration_factor);
      measurement = scale.get_units();
      difference = reference_kg - measurement;
    }
    Serial.print("Calibration factor: ");
    Serial.println(calibration_factor);
    complete = true;
  }
}
