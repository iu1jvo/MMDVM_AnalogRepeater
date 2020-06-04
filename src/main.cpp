#include <Arduino.h>

/**
 * @brief Define Used Pins
 * 
 */
#define INP_SIGNAL  PIN2
#define OUT_PTT     PIN3
#define OUT_AUDIO   PIN4

/**
 * @brief Define Timings
 * 
 */
#define DEACTIVE_PTT_MS 1000
#define DEACTVE_AUDIO_MS 350

/**
 * @brief TimeExpired: compute if (interval) is elapsed form (start) to millis().
 * 
 * @param start starting time
 * @param interval interval of time to wating from.
 * @return true if time interval is elapsed
 * @return false if time interval is NOT elapsed
 */
bool TimeExpired(unsigned long start, unsigned long interval)
{
    if ((millis() - start) >= interval)
      return true;

    return false; 
}


void setup() {
  /**
   * @brief Setup Pin Mode
   * 
   */
  pinMode(INP_SIGNAL, INPUT_PULLUP);
  pinMode(OUT_AUDIO, OUTPUT);
  pinMode(OUT_PTT, OUTPUT);
  /**
   * @brief Start Output state
   * 
   */
  digitalWrite(OUT_AUDIO, false);
  digitalWrite(OUT_PTT, false);


}

void loop() {
  static unsigned long StartWait = 0;
  /**
   * @brief Read Signal: beware the signal is inverted!
   * if signal is present, activate output.
   * 
   */
  if (digitalRead(INP_SIGNAL) == 0) {
    StartWait = millis();
    digitalWrite(OUT_AUDIO, true);
    digitalWrite(OUT_PTT, true);
  }
  else {
  /**
   * @brief No siglal, deactivate outpur after the expected time.
   * 
   */
    if (TimeExpired(StartWait, DEACTIVE_PTT_MS)) 
      digitalWrite(OUT_PTT, false);
    
    if (TimeExpired(StartWait, DEACTVE_AUDIO_MS)) 
      digitalWrite(OUT_AUDIO, false);  
  }
}
