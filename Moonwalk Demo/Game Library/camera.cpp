#include "camera.h"

camera_t::camera_t()
{
	this->useingQuarts = false;

	this->hasOculusRift = false;

	this->OculusRiftOrientation.yaw = 0.0f;
	this->OculusRiftOrientation.pitch = 0.0f;
	this->OculusRiftOrientation.roll = 0.0f;

	this->PreviousOculusRiftOrientation.yaw = 0.0f;
	this->PreviousOculusRiftOrientation.pitch = 0.0f;
	this->PreviousOculusRiftOrientation.roll = 0.0f;

	this->OculusRiftOrientation_quart.angle = 0.0f;
	this->OculusRiftOrientation_quart.axis.x = 0.0f;
	this->OculusRiftOrientation_quart.axis.y = 0.0f;
	this->OculusRiftOrientation_quart.axis.z = 0.0f;

	this->PreviousOculusRiftOrientation_Quart.angle = 0.0f;
	this->PreviousOculusRiftOrientation_Quart.axis.x = 0.0f;
	this->PreviousOculusRiftOrientation_Quart.axis.y = 0.0f;
	this->PreviousOculusRiftOrientation_Quart.axis.z = 0.0f;

	this->RotationQuart.angle = 0.0f;
	this->RotationQuart.axis.x = 0.0f;
	this->RotationQuart.axis.y = 0.0f;
	this->RotationQuart.axis.z = 0.0f;

	// Use the oculus rift by default.
	this->EnableOculusRift();
}

camera_t::camera_t(bool useRift, bool useKinect)
{
	// Check that the oculus rift should be used.
	if(useRift)
	{
		// If so, initialize the oculus rift.
		this->InitializeOculusRift();
	}
}

void camera_t::InitializeOculusRift()
{
	// Check if we are debugging or not.
#ifdef _DEBUG
	// If so, log all interactions with the oculus rift.
	System::Init(Log::ConfigureDefaultLog(LogMask_All));
#else
	// Otherwise, log no interactions with the oculus rift.
	System::Init(Log::ConfigureDefaultLog(LogMask_None));
#endif

	// Then create a device manager.
	deviceManager = *DeviceManager::Create();
	// Then get the oculus rift's HMD device.
	riftHMDDevice = *deviceManager->EnumerateDevices<HMDDevice>().CreateDevice();

	deviceManager->Release();

	// Set the boolean indicating that there is an oculus rift to false.
	this->hasOculusRift = false;

	// Check if the oculus rift device was successfully gotten.
	if(riftHMDDevice)
	{
		// If so, set the oculus rift's HMD object.
		if(riftHMDDevice->GetDeviceInfo(&riftHMD))
		{
			// Then get the oculus rift sensor.
			riftSensor = *riftHMDDevice->GetSensor();

			riftHMDDevice->Release();
		
			// Check that the sensor was successfully gotten.
			if (riftSensor)
			{
				// Then attach the sensor to a sensor fusion object.
				sensorFusion = new SensorFusion(riftSensor);
				// Finally, set the boolean indicating that the oculus rift was gotten to true.
				hasOculusRift = true;
			}
		}
	}
	else
	{
		this->riftHMD.HResolution = 1280;
		this->riftHMD.VResolution = 800;
		this->riftHMD.HScreenSize = 0.14976f;
		this->riftHMD.VScreenSize = 0.0936f;
		this->riftHMD.VScreenCenter = this->riftHMD.VScreenSize / 2;
		this->riftHMD.EyeToScreenDistance = 0.041f;
		this->riftHMD.LensSeparationDistance = 0.0635f;
		this->riftHMD.InterpupillaryDistance = 0.064f;
		this->hasOculusRift = true;
	}
}

void camera_t::SetupOculusRift()
{
	/**
	  * Set the aspect ration.  Note that this has to be statically converted, as the normal
	  * data type is an unsigned integer for the screen resolution values.
	  */
	this->AspectRatio = static_cast<float>(this->riftHMD.HResolution * 0.5f)
		/ static_cast<float>(this->riftHMD.VResolution);
	/**
	  * The aspect ratio is determined based on the distance between the eyes and
	  * the size of the screen.  This is then converted to degrees for OpenGL.
	  */
	this->FieldOfView = RadToDegree(2.0f * 
		atan((this->riftHMD.VScreenSize / 2.0f) / this->riftHMD.EyeToScreenDistance));

	// Set how close an object can be before it clips.
	this->CloseDepth = 0.001f;
	// Set how far an object can be before it vanishes.
	this->FarDepth = 100000.0f;

	this->ViewCenter = this->riftHMD.HScreenSize * 0.25f;
	this->ProjectionCenterOffset = 4.0f * (this->ViewCenter - (this->riftHMD.LensSeparationDistance * 0.5f))
		/ this->riftHMD.HScreenSize;
	this->HalfIPD = this->riftHMD.InterpupillaryDistance * 0.5f;

	this->StereoConfiguration.SetFullViewport(Viewport(0, 0, 1280, 800));
	this->StereoConfiguration.SetStereoMode(Stereo_LeftRight_Multipass);
	this->StereoConfiguration.SetHMDInfo(this->riftHMD);
	this->StereoConfiguration.SetDistortionFitPointVP(-1.0f, 0.0f);

	this->LeftEye = this->StereoConfiguration.GetEyeRenderParams(StereoEye_Left);
	this->RightEye = this->StereoConfiguration.GetEyeRenderParams(StereoEye_Right);
}

void camera_t::UpdateOculusRiftData()
{
	this->sensorFusion->GetOrientation().GetEulerAngles<Axis_Y, Axis_X, Axis_Z>
		(&this->OculusRiftOrientation.yaw,
		&this->OculusRiftOrientation.pitch,
		&this->OculusRiftOrientation.roll);

	this->OculusRiftOrientation.yaw = RadToDegree(this->OculusRiftOrientation.yaw);
	this->OculusRiftOrientation.pitch = RadToDegree(this->OculusRiftOrientation.pitch);
	this->OculusRiftOrientation.roll = RadToDegree(this->OculusRiftOrientation.roll);

	this->Rotation.x -= (this->OculusRiftOrientation.pitch -
		this->PreviousOculusRiftOrientation.pitch);
	this->Rotation.y -= (this->OculusRiftOrientation.yaw -
		this->PreviousOculusRiftOrientation.yaw);
	this->Rotation.z -= (this->OculusRiftOrientation.roll -
		this->PreviousOculusRiftOrientation.roll);

	this->PreviousOculusRiftOrientation.yaw = this->OculusRiftOrientation.yaw;
	this->PreviousOculusRiftOrientation.pitch = this->OculusRiftOrientation.pitch;
	this->PreviousOculusRiftOrientation.roll = this->OculusRiftOrientation.roll;

	{
		this->sensorFusion->GetOrientation().GetAxisAngle(&this->OculusRiftOrientation_quart.axis,
			&this->OculusRiftOrientation_quart.angle);

		this->OculusRiftOrientation_quart.angle = -RadToDegree(this->OculusRiftOrientation_quart.angle);
		this->RotationQuart.angle += this->OculusRiftOrientation_quart.angle - this->PreviousOculusRiftOrientation_Quart.angle;
		this->RotationQuart.axis = this->OculusRiftOrientation_quart.axis;

		this->PreviousOculusRiftOrientation_Quart.angle = this->OculusRiftOrientation_quart.angle;
		this->PreviousOculusRiftOrientation_Quart.axis.x = this->OculusRiftOrientation_quart.axis.x;
		this->PreviousOculusRiftOrientation_Quart.axis.y = this->OculusRiftOrientation_quart.axis.y;
		this->PreviousOculusRiftOrientation_Quart.axis.z = this->OculusRiftOrientation_quart.axis.z;
	}
}

void camera_t::UpdateRiftView(RiftEye eye)
{
	if(eye == Left)
	{
		glViewport(this->LeftEye.VP.x, this->LeftEye.VP.y, this->LeftEye.VP.w, this->LeftEye.VP.h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glTranslatef(this->ProjectionCenterOffset, 0.0f, 0.0f);
		gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);
		//gluPerspective(this->FieldOfView, this->AspectRatio, this->CloseDepth, this->FarDepth);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(this->HalfIPD * this->ViewCenter, 0.0f, 0.0f);
	}
	else if(eye == Right)
	{
		glViewport(this->RightEye.VP.x, this->RightEye.VP.y, this->RightEye.VP.w, this->RightEye.VP.h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glTranslatef(-this->ProjectionCenterOffset, 0.0f, 0.0f);
		gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);
		//gluPerspective(this->FieldOfView, this->AspectRatio, this->CloseDepth, this->FarDepth);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(-this->HalfIPD * this->ViewCenter, 0.0f, 0.0f);
	}
}

bool camera_t::EnableOculusRift()
{
	// Initialize the oculus rift.
	this->InitializeOculusRift();
	// Setup the oculus rift's data.
	this->SetupOculusRift();
	// Return whether there is an oculus rift, indicating success.
	return this->hasOculusRift;
}

camera_t::~camera_t()
{
	System::Destroy();
}
