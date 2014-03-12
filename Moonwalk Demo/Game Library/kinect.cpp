#include "kinect.h"

Kinect::Kinect()
{
	if (NuiGetSensorCount(&totalSensors) < 0 || totalSensors < 1)
	{
		for(int i = 0;i < 4;i += 1)
		{
			this->active[i] = false;
		}
	}
	else
	{
		for(int i = 0;i < totalSensors && i < 4;i += 1)
		{
			if(NuiCreateSensorByIndex(i, &this->sensor[i]) < 0)
			{
				this->active[i] = false;
			}
			else
			{
			    // Initialize sensor
				this->nextSkeletonEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
				this->nextColorImageEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
				this->sensor[i]->NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH | NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_SKELETON);
				this->sensor[i]->NuiSkeletonTrackingEnable(this->nextSkeletonEvent, 0);
				this->sensor[i]->NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480,
					0, 2, NULL, &this->nextColorImageEvent);
		
				this->active[i] = true;
			}
		}
	}
}

void Kinect::getColorFrameData(int sensorIndex, unsigned char* data)
{
	if(this->active)
	{
		NUI_IMAGE_FRAME colorImageFrame;
		NUI_LOCKED_RECT lockedRectangle;

		if(this->sensor[sensorIndex]->NuiImageStreamGetNextFrame(this->nextColorImageEvent, 0, &colorImageFrame) == S_OK)
		{
			INuiFrameTexture* colorImageTexture = colorImageFrame.pFrameTexture;
			colorImageTexture->LockRect(0, &lockedRectangle, NULL, 0);

			if(lockedRectangle.Pitch != 0)
			{
				const BYTE* currentData = (const BYTE*)lockedRectangle.pBits;
				const BYTE* dataEnd = currentData + (640 * 480 * 4);

				int j = 0;
				for(int i = 0;currentData <= dataEnd;i += 1, currentData += 1)
				{
					data[i] = currentData[0];
					if(j == 0)
					{
						data[i] = 255;
					}

					if(j >= 4)
					{
						j = 0;
					}
					else
					{
						j += 1;
					}
				}
			}

			colorImageTexture->UnlockRect(0);
			this->sensor[sensorIndex]->NuiImageStreamReleaseFrame(this->nextColorImageEvent, &colorImageFrame);
		}
	}
}

const NUI_SKELETON_DATA Kinect::getMainPerson(int sensorIndex)
{
	if(this->active[sensorIndex])
	{
		NUI_SKELETON_FRAME frame;
		sensor[sensorIndex]->NuiSkeletonGetNextFrame(0, &frame);

		const NUI_TRANSFORM_SMOOTH_PARAMETERS VerySmoothParams = {0.7f, 0.3f, 1.0f, 1.0f, 1.0f};
		sensor[sensorIndex]->NuiTransformSmooth(&frame, &VerySmoothParams);

		for (int i = 0; i < NUI_SKELETON_COUNT; i++)
		{
			this->mainSkeleton = frame.SkeletonData[i];

			if(this->mainSkeleton.eTrackingState == NUI_SKELETON_TRACKING_STATE::NUI_SKELETON_TRACKED)
			{
				return this->mainSkeleton;
			}
		}
	}
}