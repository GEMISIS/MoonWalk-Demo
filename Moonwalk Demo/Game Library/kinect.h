#ifndef _KINECT_H_
#define _KINECT_H_

#include <Windows.h>
#include <NuiApi.h>

class Kinect
{
public:
	INuiSensor* sensor[4];
	bool active[4];
	int totalSensors;

	Kinect();
	void getColorFrameData(int sensorIndex, unsigned char* data);
	const NUI_SKELETON_DATA getMainPerson(int sensorIndex);
protected:
	HANDLE nextSkeletonEvent;
	HANDLE nextColorImageEvent;
	NUI_SKELETON_DATA mainSkeleton;
private:
};

#endif