/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <A4957_driver/A4957.hpp>
#include <Core/MW/Thread.hpp>

namespace actuators {
   A4957::A4957(
  		Core::HW::PWMMaster&  pwm,
      Core::HW::PWMChannel& channel0,
      Core::HW::PWMChannel& channel1,
      Core::HW::Pad&        reset,
      Core::HW::Pad&        fault
   ) : _pwm(pwm), _channel0(channel0), _channel1(channel1), _reset(reset), _fault(fault) {}

   A4957_SignMagnitude::A4957_SignMagnitude(
      A4957& device
   ) : _device(device) {}

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
  	 _device._pwm.setFrequency(configuration.frequency);
   	 _device._pwm.setPeriod(configuration.period);

      _device._reset.clear();
      Core::MW::Thread::sleep(Core::MW::Time::ms(5));

      return true;
   }

   bool
   A4957_SignMagnitude::start()
   {
      _device._channel0.enable();
      _device._channel1.enable();
      _device._reset.set();
      Core::MW::Thread::sleep(Core::MW::Time::ms(5));

      return true;
   }

   bool
   A4957_SignMagnitude::stop()
   {
      _device._reset.clear();
      _device._channel0.disable();
      _device._channel1.disable();
      Core::MW::Thread::sleep(Core::MW::Time::ms(5));

      return true;
   }

   bool
   A4957_SignMagnitude::set(
      DataType& data
   )
   {
      int16_t PWM_MAX = _device._pwm.getPeriod();

      int16_t pwm = (data * configuration.kappa) * PWM_MAX;

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
   } // A4957_SignMagnitude::set

   bool
   A4957_SignMagnitude::waitUntilReady()
   {
      return true;
   }
}
