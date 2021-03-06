#include "Shoot.h"

Shoot::Shoot()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(shooter);
	Requires(utility);
}

// Called just before this Command runs the first time
void Shoot::Initialize()
{
	SetTimeout(4.5);
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute()
{
	char motorRPMString[64] = "";
	double motorRPM = shooter->GetRPM();
	// Adjust power if shooter motor is running at less than optimum speed
	// Shooter counter not working?
//	shooter->Shoot(SHOOT_POWER);
	if (OPTIMUM_SHOOTER_RPM > motorRPM)
	{
		shooter->Shoot(OPTIMUM_SHOOTER_RPM/motorRPM * SHOOT_POWER);
		utility->gearLightOff();
	}
	else
	{
		shooter->Shoot(SHOOT_POWER);
		utility->gearLightOn();
	}

	sprintf(motorRPMString, "%6.2f RPM", motorRPM);
	printf(motorRPMString);
	SmartDashboard::PutString("Shooter Speed: ", motorRPMString);
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void Shoot::End()
{
	shooter->Stop();
	utility->gearLightOff(); // Double Duty used to indicate motor up to speed
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted()
{
	shooter->Stop();
	utility->gearLightOff();
}
