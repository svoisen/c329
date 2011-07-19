#include "CameraC329.h"

#define CAMERA_BAUD 14400

CameraC329 camera;

void setup()
{
  Serial.begin(CAMERA_BAUD);
  
  delay(2000);

  if (camera.sync())
  {
    Serial.println("Synced");
  }
  else
  {
    Serial.println("Failed");
  }
}

void loop()
{
}
