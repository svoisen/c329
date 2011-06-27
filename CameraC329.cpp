#include "CameraC329R.h"

//-----------------------------------------------------------------------------
//
// Constants
//
//-----------------------------------------------------------------------------

static const byte CMD_PREFIX = 0xFF;
static const byte CMD_INITIAL = 0x01;
static const byte CMD_GETPICTURE = 0x04;
static const byte CMD_SNAPSHOT = 0x05;
static const byte CMD_RESET = 0x08;
static const byte CMD_POWEROFF = 0x09;
static const byte CMD_DATA = 0x0A;
static const byte CMD_SYNC = 0x0D;
static const byte CMD_ACK = 0x0E;
static const byte CMD_NAK = 0x0F;
static const byte CMD_QUALITY = 0x10;

/**
 * Constructor
 */
CameraC329::CameraC329()
{
}

/**
 * Synchronize with the camera. Synchronization will be attempted up to
 * MAX_SYNC_ATTEMPTS. You must synchronize with the camera before you can
 * call other methods.
 *
 * @return True if successful, false otherwise.
 */
bool CameraC329::sync()
{
  uint8_t syncAttempts = 0;
  bool success = false;

  setOutputCommand(CMD_SYNC, 0, 0, 0, 0);

  while (attempts < MAX_SYNC_ATTEMPTS)
  {
    sendCommand();

    success = waitForACK(RESPONSE_DELAY, CMD_SYNC);
  }
}

void CameraC329::sendCommand()
{
  uint8_t i;

  // Big endian
  for (i = 0; i < CMD_SIZE; i++)
  {
    Serial.print(outputCommand[i], BYTE);
  }
}

bool CameraC329::waitForACK(uint32_t timeout, uint8_t cmd)
{
}

bool CameraC329::waitForResponse(uint32_t timeout)
{
  return watiForResponse(timeout, inputCommand, CMD_SIZE);
}

bool CameraC329::waitForResponse(uint32_t timeout, byte buffer[], uint16_t bufferLength)
{
  uint8_t byteCount = 0;
  unsigned long time = millis();

  while (millis() - time <= timeout)
  {
    while (Serial.available() > 0)
    {
      buffer[byteCount++] = Serial.read();

      if (byteCount == bufferLength)
        return true;
    }
  }

  if (byteCount > 0)
    return true;

  return false;
}

void CameraC329::setOutputCommand(const byte command, byte param1, byte param2, byte param3, byte param4)
{
  outputCommand[0] = CMD_PREFIX;
  outputCommand[1] = CMD_PREFIX;
  outputCommand[2] = CMD_PREFIX;
  outputCommand[3] = command;
  outputCommand[4] = param1;
  outputCommand[5] = param2;
  outputCommand[6] = param3;
  outputCommand[7] = param4;
}
