
void setup()
{
}

void loop()
{
}

// functions grabbed from main-dev before removing all button functionality
// should be modified into button lib

// BUTTONS READ BLOCK
/*
bool alarmSilButState = FALSE;   // not V1
void buttonsReadSetup() {   // not V1
  for (int vesselInd = 0; vesselInd < NumVessels; vesselInd++) {
    pinMode(AlarmSilButPin[vesselInd], INPUT);
    pinMode(AutopilotButPin[vesselInd], INPUT);
  }
}
void buttonsReadLoop() {  // not V1
  for (int vesselInd = 0; vesselInd < NumVessels; vesselInd++) {
    // alarm button section
    if (TempHigh[vesselInd] == TRUE || TempLow[vesselInd] == TRUE) {
      bool alarmSilPrevButState = alarmSilButState;
      alarmSilButState = digitalRead(AlarmSilButPin[vesselInd]);
      if (alarmSilButState == TRUE && alarmSilPrevButState == FALSE) {
        AlarmTempSilenced[vesselInd] = TRUE;
      }
    }
    //autopilot button section
    AutopilotButPushedPrev[vesselInd] = AutopilotButPushed[vesselInd];
    AutopilotButPushed[vesselInd] = digitalRead(AutopilotButPin[vesselInd]);
    if (AutopilotButPushed[vesselInd] != AutopilotButPushedPrev[vesselInd]) { // these can be one if statement
      if (AutopilotOn[vesselInd] == TRUE) {
        if (AutopilotButPushed[vesselInd] == TRUE) {
          AutopilotOn[vesselInd] = FALSE;
        }
      }
      else {
        if (AutopilotButPushed[vesselInd] == TRUE) {
          AutopilotOn[vesselInd] = TRUE;
        }
      }
    }
  }
}
*/
