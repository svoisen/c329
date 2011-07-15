/**
 * Copyright 2011
 * Sean Voisen <http://voisen.org>
 *
 * Based on the original library for the now-obsolete C328R camera, also by
 * Sean Voisen in collaboration with Beatriz da Costa 
 * <http://beatrizdacosta.net>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "CameraC329.h"

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

  while (syncAttempts < MAX_SYNC_ATTEMPTS)
  {
    sendCommand();

    // Wait for ACK response
    success = waitForACK(RESPONSE_DELAY, CMD_SYNC);

    // Make sure it is an ACK
    if (success)
    {
      // Now wait for SYNC from camera
      success = waitForResponse(RESPONSE_DELAY);
      if (success && inputCommand[3] == CMD_SYNC)
      {
        // All is good, flush the buffer
        Serial.flush();

        // Send ACK
        setOutputCommand(CMD_ACK, CMD_SYNC, 0, 0, 0);
        sendCommand();

        return true;
      }
    }

    syncAttempts++;
  }

  return false;
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
  bool success = waitForResponse(timeout);

  if (success && inputCommand[3] == CMD_ACK && inputCommand[4] == cmd)
    return true;

  return false;
}

bool CameraC329::waitForResponse(uint32_t timeout)
{
  return waitForResponse(timeout, inputCommand, CMD_SIZE);
}

bool CameraC329::waitForResponse(uint32_t timeout, byte buffer[], uint16_t bufferLength)
{
  uint8_t byteCount = 0;
  unsigned long time = millis();

  while (millis() - time <= timeout)
  {
    while (Serial.available() > 0)
    {
      buffer[byteCount] = Serial.read();
      byteCount++;

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
