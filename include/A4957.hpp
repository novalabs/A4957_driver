/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <Configuration.hpp>

#include <Core/HW/PWM.hpp>
#include <Core/HW/GPIO.hpp>
#include <Core/MW/CoreActuator.hpp>

namespace actuators {
   class A4957
   {
public:
      A4957(
         Core::HW::PWMChannel& channel0,
         Core::HW::PWMChannel& channel1,
         Core::HW::Pad&        reset,
         Core::HW::Pad&        fault
      );

      virtual
      ~A4957();

public:
      bool
      probe();


public:
      Core::HW::PWMChannel& _channel0;
      Core::HW::PWMChannel& _channel1;
      Core::HW::Pad&        _reset;
      Core::HW::Pad&        _fault;
   };


   class A4957_SignMagnitude:
      public Core::MW::CoreActuator<float>
   {
public:
      A4957_SignMagnitude(
         A4957& device
      );

      virtual
      ~A4957_SignMagnitude();

public:
      bool
      init();

      bool
      start();

      bool
      stop();

      bool
      waitUntilReady();

      bool
      set(
         DataType& data
      );


protected:
      Core::MW::Time _set_timestamp;

private:
      A4957& _device;
   };
}
