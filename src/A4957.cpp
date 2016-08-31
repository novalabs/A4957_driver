/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <core/A4957_driver/A4957.hpp>
#include <core/os/Thread.hpp>

namespace core {
namespace A4957_driver {
A4957::A4957(
   core::hw::PWMMaster&  pwm,
   core::hw::PWMChannel& channel0,
   core::hw::PWMChannel& channel1,
   core::hw::Pad&        reset,
   core::hw::Pad&        fault
) : _pwm(pwm), _channel0(channel0), _channel1(channel1), _reset(reset), _fault(fault) {}

A4957_SignMagnitude::A4957_SignMagnitude(
   const char* name,
   A4957&      device
) : CoreConfigurable<core::A4957_driver::A4957_SignMagnitudeConfiguration>::CoreConfigurable(name),
   _device(device) {}

A4957::~A4957()
{}

A4957_SignMagnitude::~A4957_SignMagnitude()
{}

bool
A4957::probe()
{
   return true;
}

bool
A4957_SignMagnitude::init()
{
   _device._reset.clear();
   core::os::Thread::sleep(core::os::Time::ms(5));

   return true;
}

bool
A4957_SignMagnitude::configure()
{
   if (!isConfigured()) {
      return false;
   }

   _device._pwm.setFrequency(configuration().frequency);
   _device._pwm.setPeriod(configuration().period);

   return true;
}

bool
A4957_SignMagnitude::start()
{
   CORE_ASSERT(isConfigured());

   _device._channel0.enable();
   _device._channel1.enable();
   _device._reset.set();

   return true;
}

bool
A4957_SignMagnitude::stop()
{
   _device._reset.clear();
   _device._channel0.disable();
   _device._channel1.disable();

   return true;
}

bool
A4957_SignMagnitude::set(
   const DataType& data
)
{
   int16_t PWM_MAX = _device._pwm.getPeriod();

   int16_t pwm = (data * configuration().kappa) * PWM_MAX;

   if (pwm > PWM_MAX) {
      pwm = PWM_MAX;
   } else if (pwm <= -PWM_MAX) {
      pwm = -PWM_MAX;
   }

   if (pwm >= 0) {
      _device._channel0.set(pwm);
      _device._channel1.set(0);
   } else {
      _device._channel0.set(0);
      _device._channel1.set(-pwm);
   }

   return true;
}       // A4957_SignMagnitude::set

bool
A4957_SignMagnitude::waitUntilReady()
{
   return true;
}
}
}
