/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <ModuleConfiguration.hpp>

#include <core/hw/PWM.hpp>
#include <core/hw/GPIO.hpp>
#include <core/utils/BasicActuator.hpp>

#include <core/A4957_driver/A4957_SignMagnitudeConfiguration.hpp>

namespace core {
namespace A4957_driver {
class A4957
{
public:
   A4957(
      core::hw::PWMMaster&  pwm,
      core::hw::PWMChannel& channel0,
      core::hw::PWMChannel& channel1,
      core::hw::Pad&        reset,
      core::hw::Pad&        fault
   );

   virtual
   ~A4957();

public:
   bool
   probe();


public:
   core::hw::PWMMaster&  _pwm;
   core::hw::PWMChannel& _channel0;
   core::hw::PWMChannel& _channel1;
   core::hw::Pad&        _reset;
   core::hw::Pad&        _fault;
};


class A4957_SignMagnitude:
   public core::utils::BasicActuator<float>,
   public core::mw::CoreConfigurable<core::A4957_driver::A4957_SignMagnitudeConfiguration>
{
public:
   A4957_SignMagnitude(
      const char* name,
      A4957&      device
   );

   virtual
   ~A4957_SignMagnitude();

public:
   bool
   init();

   bool
   configure();

   bool
   start();

   bool
   stop();

   bool
   waitUntilReady();

   bool
   set(
      const DataType& data
   );


protected:
   core::os::Time _set_timestamp;

private:
   A4957& _device;
};
}
}
