//
// Copyright (c) 2014 CNRS
// Authors: Steve Tonneau (steve.tonneau@laas.fr)
//
// This file is part of hpp-rbprm.
// hpp-rbprm is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-rbprm is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-core  If not, see
// <http://www.gnu.org/licenses/>.

#ifndef HPP_RBPRM_DEVICE_HH
# define HPP_RBPRM_DEVICE_HH

# include <hpp/rbprm/config.hh>
# include <hpp/model/device.hh>

namespace hpp {

  namespace model {
    HPP_PREDEF_CLASS(RbPrmDevice);

    /// Dual representation of a robot for Reachability Based planning:
    /// Collision free part of the robot vs Range Of Motion of the limbs.
    ///
    class RbPrmDevice;
    typedef boost::shared_ptr <RbPrmDevice> RbPrmDevicePtr_t;

    class HPP_RBPRM_DLLAPI RbPrmDevice : public Device
    {
    public:
        static RbPrmDevicePtr_t create (const std::string& name, DevicePtr_t& robotRom);

    public:
        virtual ~RbPrmDevice();

    public:
        virtual bool currentConfiguration (ConfigurationIn_t configuration);
        //virtual bool setCurrentConfiguration(ConfigurationIn_t configuration);

    public:
      /// Range Of Motion of the robot
      const DevicePtr_t robotRom_;

    protected:
      RbPrmDevice (const std::string& name, const DevicePtr_t& robotRom);

      ///
      /// \brief Initialization.
      ///
      void init (const RbPrmDeviceWkPtr_t& weakPtr);

    private:
      RbPrmDeviceWkPtr_t weakPtr_;
    }; // class ConfigValidation
  } // namespace rbprm
} // namespace hpp

#endif // HPP_RBPRM_DEVICE_HH