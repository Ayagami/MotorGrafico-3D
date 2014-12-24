
//---------------------------------------------------------------------------
#ifndef PG1_TIMER_H
#define PG1_TIMER_H
//---------------------------------------------------------------------------
#include "..\myEngine_API.h"
#include <Windows.h>
//---------------------------------------------------------------------------
namespace DoMaRe
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
	float time() const;
	
	float deltaTime() const;
	void setdeltaTime(float deltaTime);

private:
	double m_dTimeBetweenFrames;
	double m_dMeasureFpsSample;
	unsigned int m_uiFPS;
	unsigned int m_uiFrameCounter;

	LARGE_INTEGER m_kPerfCount1;
	LARGE_INTEGER m_kPerfCount2;
	LARGE_INTEGER m_kFrequency;

	double m_dTime;

	float m_dDeltaTime;
};
//---------------------------------------------------------------------------
#include "pg1_timer.inl"
//---------------------------------------------------------------------------
} // end namespace
//---------------------------------------------------------------------------
#endif // PG1_TIMER_H
//---------------------------------------------------------------------------
