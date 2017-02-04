
//---------------------------------------------------------------------------
#ifndef Timer_H
#define Timer_H
//---------------------------------------------------------------------------
#include "..\myEngine_API.h"
#include <Windows.h>
//---------------------------------------------------------------------------
namespace engine
{
//---------------------------------------------------------------------------
	class MYENGINE_API Timer
	{
		// constructor
		public:
			Timer ();

		// measure
		public:
			void firstMeasure ();
			void measure ();

			float timeBetweenFrames () const;
			unsigned int fps () const;

		private:
			double m_dTimeBetweenFrames;
			double m_dMeasureFpsSample;
			unsigned int m_uiFPS;
			unsigned int m_uiFrameCounter;

			LARGE_INTEGER m_kPerfCount1;
			LARGE_INTEGER m_kPerfCount2;
			LARGE_INTEGER m_kFrequency;
	};
//---------------------------------------------------------------------------
	#include "Timer.inl"
//---------------------------------------------------------------------------
} // end namespace
//---------------------------------------------------------------------------
#endif // Timer_H
//---------------------------------------------------------------------------
