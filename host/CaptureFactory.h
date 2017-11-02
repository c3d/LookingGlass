/*
KVMGFX Client - A KVM Client for VGA Passthrough
Copyright (C) 2017 Geoffrey McRae <geoff@hostfission.com>

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
*/

#pragma once

#define W32_LEAN_AND_MEAN
#include <Windows.h>

#include "common\debug.h"
#include "ICapture.h"
#include "Capture\NvFBC.h"
#include "Capture\DXGI.h"

class CaptureFactory
{
public:
  static ICapture * GetCaptureDevice()
  {
    ICapture *dev;

    dev = new Capture::NvFBC();
    if (dev->Initialize())
    {
      DEBUG_INFO("Using NvFBC");
      return dev;
    }
    dev->DeInitialize();
    delete dev;
    
    dev = new Capture::DXGI();
    if (dev->Initialize())
    {
      DEBUG_INFO("Using DXGI");
      return dev;
    }
    dev->DeInitialize();
    delete dev;

    DEBUG_ERROR("Failed to initialize a compatible capture device");
    return NULL;
  }
};