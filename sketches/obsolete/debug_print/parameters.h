// square wave parameters' 2d array for frequency, duty ratio and amplitude
float params[3][10] = {
  { 0.25, 0.5, 0.66, 1.0, 2.0, 2.66, 3.0, 5.0, 10.0, 20.0 },  // FREQ values in Hz
  { 0.0, 0.05, 0.1, 0.2, 0.35, 0.5, 0.6, 0.75, 0.9, 1.0},  // DUTY cycle values
  { 435.0, 460.0, 485.0, 510.0, 535.0, 560.0, 585.0, 610.0, 635.0, 660.0}  // AMP  values in DAC level (non-saturated region) this was for 8-bit DAC
};