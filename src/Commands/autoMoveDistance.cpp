#include "autoMoveDistance.h"

autoMoveDistance::autoMoveDistance(float dir, float s, float dist)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(drivetrain);
	direction = dir;
	speed = s;
	distance = dist;
}

// Called just before this Command runs the first time
void autoMoveDistance::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void autoMoveDistance::Execute()
{
	drivetrain->Go(speed*direction, speed*direction, speed*direction, speed*direction);
}

// Make this return true when this Command no longer needs to run execute()
bool autoMoveDistance::IsFinished()
{
	double flDist, rlDist, frDist, rrDist;

	// Use the following return value for timed movement
	// return IsTimedOut();

	// Use encoder feedback to determine when to stop.
	flDist = abs(drivetrain->front_left_motor->GetPosition() * WHEEL_DISTANCE_FACTOR);
	rlDist = abs(drivetrain->rear_left_motor->GetPosition() * WHEEL_DISTANCE_FACTOR);
	// Presently only left side encoders working
	// frDist = abs(drivetrain->front_right_motor->GetPosition() * WHEEL_DISTANCE_FACTOR);
	// rrDist = abs(drivetrain->rear_right_motor->GetPosition() * WHEEL_DISTANCE_FACTOR);
	if (flDist >= this->distance && rlDist >= this->distance)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

// Called once after isFinished returns true
void autoMoveDistance::End()
{
	drivetrain->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void autoMoveDistance::Interrupted() {

}