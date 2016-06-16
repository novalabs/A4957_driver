/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <A4957_driver/A4957.hpp>

namespace actuators {
   A4957::A4957(
      Core::HW::PWMChannel& channel0,
      Core::HW::PWMChannel& channel1,
      Core::HW::Pad&        reset,
      Core::HW::Pad&        fault
   ) : _channel0(channel0), _channel1(channel1), _reset(reset), _fault(fault) {}

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
      return true;
   }

   bool
   A4957_SignMagnitude::start()
   {
      _device._reset.clear();
      _device._channel0.enable();
      _device._channel1.enable();

      return true;
   }

   bool
   A4957_SignMagnitude::stop()
   {
      _device._channel0.disable();
      _device._channel1.disable();
      _device._reset.set();

      return true;
   }

   bool
   A4957_SignMagnitude::set(
      DataType& data
   )
   {
      int16_t pwm = data * 4095; // TODO: check if max is 4095 or 4096

      if (pwm >= 0) {
         _device._channel0.set(pwm);
         _device._channel1.set(0);
      } else {
         _device._channel0.set(0);
         _device._channel1.set(-pwm);
      }

      return true;
   }

   bool
   A4957_SignMagnitude::waitUntilReady()
   {
      return true;
   }
}
