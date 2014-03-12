// Check if the header has been defined already.
#ifndef _CAMERA_H_
// If not, define it.
#define _CAMERA_H_

#include <ovr\Include\OVR.h>
#include <GL\GL.h>
#include <GL\GLU.h>

using namespace OVR;
using namespace OVR::Util::Render;

struct camera_axis_t
{
	float x, y, z;
};

struct camera_orientation_t
{
	float yaw, pitch, roll;
};

struct camera_orentation_quart_t
{
	Vector3f axis;
	float angle;
};

enum RiftEye
{
	Left = 0,
	Right = 1
};

/**
  * A class for managing cameras.  It contains all of the information for viewing the 3D world and
  * also supports an Oculus Rift and Kinect when detected.
  */
class camera_t
{
public:
	/**
	  * The position of the camera in 3D space.
	  */
	camera_axis_t Position;
	/**
	  * The rotation of the camera in 3D space. (Eular)
	  */
	camera_axis_t Rotation;
	/**
	  * The rotation for the camear in 3D space. (Quaternion)
	  */
	camera_orentation_quart_t RotationQuart;

	/**
	  * The field of view on the Y-axis that can be seen by the camera.
	  */
	float FieldOfView;
	/**
	  * The aspect ration to display with the camera.
	  */
	float AspectRatio;
	/**
	  * How close the camera can be to an object before it is past it.
	  */
	float CloseDepth;
	/**
	  * How far the camera can be from an object before it vanishes due to
	  * the vanishing point.
	  */
	float FarDepth;

	/**
	  * Manages the USB devices connected to the computer (specifically used for the
	  * oculus rift.
	  */
	Ptr<DeviceManager> deviceManager;
	/**
	  * Manages an Head Mounted Display (HMD) device (IE: The oculus rift).  This is used
	  * mainly for getting hardware information, rather than user info (IE: No eye distance info).
	  */
	Ptr<HMDDevice> riftHMDDevice;
	/**
	  * The actual oculus rift sensor.  Can be used to get various things from the actual
	  * device now.
	  */
	Ptr<SensorDevice> riftSensor;
	/**
	  * The oculus rift's information in the form of a Head Mounted Display (HMD).  This is used
	  * to get information specially needed for HMD's, rather than hardware information.
	  */
	HMDInfo riftHMD;
	/**
	  * The fusion sensor object is used to get information from the HDM's built in sensors.
	  * (IE: Accelerometer information, orientation, etc.)
	  */
	SensorFusion* sensorFusion;
	/**
	  * A boolean indicating whether an oculus rift is connected or not.
	  */
	bool hasOculusRift;
	/**
	  * The orientation of the oculus rift. (yaw, pitch, roll)
	  */
	camera_orientation_t OculusRiftOrientation;
	/**
	  * The orientation of the oculus rift. (Quaternion)
	  */
	camera_orentation_quart_t OculusRiftOrientation_quart;
	/**
	  * The configuration for the stereo-scopic viewing.  Contains properties like how big
	  * the display for each eye is.
	  */
	StereoConfig StereoConfiguration;
	/**
	  * The stereo parameters for the left eye.
	  */
	StereoEyeParams LeftEye;
	/**
	  * The stereo parameters for the right eye.
	  */
	StereoEyeParams RightEye;
	/**
	  * The center viewing point.
	  */
	float ViewCenter;
	/**
	  * The offset for the projection view due to the eyes and screen size.
	  */
	float ProjectionCenterOffset;
	/**
	  * This is half of the interpupillary distance (IE: Distance between the eyes).
	  */
	float HalfIPD;

	bool useingQuarts;
	
	camera_t();
	camera_t(bool useRift, bool useKinect);
	~camera_t();
	void UpdateOculusRiftData();
	void UpdateRiftView(RiftEye eye);
	bool EnableOculusRift();
protected:
	camera_orientation_t PreviousOculusRiftOrientation;
	camera_orentation_quart_t PreviousOculusRiftOrientation_Quart;
private:
	void InitializeOculusRift();
	void SetupOculusRift();
};

// End the definition for the game state header.
#endif

