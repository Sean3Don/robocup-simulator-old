#pragma once

#include <boost/array.hpp>

#include <Constants.hpp>
#include <Configuration.hpp>
#include <framework/SystemState.hpp>
#include <framework/ConfigFile.hpp>

namespace Motion {

	/**
	 * Controller that converts motion velocities to
	 * wheel velocities. For now, this is relatively simple,
	 * but could become more complex to handle traction
	 * control scenarios.
	 */
	class WheelController {

	private:
		/** information pertaining to a single robot axle */
		struct Axle
		{
			Axle()
			{
				motor = 0;
				lastWheelVel = 0;
			}

			//motor value
			float motor;

			//weeel velocities in the last frame
			int8_t lastWheelVel;

			Geometry2d::Point wheel;
		};

		typedef boost::array<Axle, 4> Axles;

	public:

		typedef boost::array<int8_t, 4> MotorCmd;

		WheelController(SystemState *state, Configuration *cfg);
		~WheelController() {}

		void run();

	private:
		SystemState *_state;

		Configuration *_config;

		/**
		 * function that actually generates motor commands
		 * Needs velocity as well as a dynamics model
		 */
		MotorCmd genMotor(const Geometry2d::Point& vel, float w, SystemState::Robot* robot);
	};

}
