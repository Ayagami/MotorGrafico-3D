
//---------------------------------------------------------------------------
inline float Timer::timeBetweenFrames () const
{	
	return static_cast<float>(m_dTimeBetweenFrames) * m_dDeltaTime;
}
//---------------------------------------------------------------------------
inline unsigned int Timer::fps () const
{
	return m_uiFPS;
}
//---------------------------------------------------------------------------
inline float Timer::time() const{
	return static_cast<float>(m_dTime);
}
//---------------------------------------------------------------------------
inline float Timer::deltaTime() const{
	return m_dDeltaTime;
}