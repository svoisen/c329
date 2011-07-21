#include "CameraC329.h"

#define CAMERA_BAUD 14400

CameraC329 camera;
uint32_t pictureSize;

void setup()
{
  Serial.begin(CAMERA_BAUD);
  
  delay(2000);

  if (camera.sync())
  {
    if (camera.initialize(CameraC329::BAUD14400, CameraC329::CT_JPEG, CameraC329::PR_160x120, CameraC329::JR_320x240))
    {
      if (camera.getPicture(CameraC329::PT_JPEG_PREVIEW, pictureSize))
      {
        Serial.print("Size: ");
        Serial.println(pictureSize);
      }
      else
      {
        Serial.println("Get Picture Failed");
      }
    }
    else
    {
      Serial.println("Initialize Failed");
    }
  }
  else
  {
    Serial.println("Sync Failed");
  }
}

void loop()
{
}
