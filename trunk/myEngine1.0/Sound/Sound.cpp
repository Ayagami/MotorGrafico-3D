#include "Sound.h"
using namespace DoMaRe;
//---------------------------------------------------------------- 
Sound::Sound():
m_pkSoundEngine(NULL),
m_bIsStarted(false){

}
//---------------------------------------------------------------- 
Sound::~Sound(){

}
//---------------------------------------------------------------- 
bool Sound::startSoundEngine(){
	m_pkSoundEngine = irrklang::createIrrKlangDevice();

	if (!m_pkSoundEngine)
		return false;

	m_bIsStarted = true;
	return true;
}
//---------------------------------------------------------------- 
bool Sound::stopSoundEngine(){
	if (m_bIsStarted)
	{
		m_pkSoundEngine->drop();
		return true;
	}
	else
	{
		return false;
	}

}
//---------------------------------------------------------------- 
bool Sound::playSoundFile(std::string kFileName, bool bLoop){
	if (kFileName=="")
		return false;

	if (m_bIsStarted)
	{
		m_pkSoundEngine->play2D(kFileName.c_str(), bLoop);
		return true;
	}
	else
	{
		return false;
	}
}
ISound*	Sound::GetAndplaySoundFile(std::string kFileName, bool bLoop){
	if (kFileName=="")
		return NULL;

	if (m_bIsStarted){
		ISound* theSound = m_pkSoundEngine->play2D(kFileName.c_str(), bLoop);
		return theSound;
	}
	else{
		return NULL;
	}
}

//---------------------------------------------------------------- 
void Sound::stopAllSounds(){
	if (m_bIsStarted)
		m_pkSoundEngine->stopAllSounds();
}
//---------------------------------------------------------------- 
void Sound::setMasterVolume(float fVolume)
{
	if (m_bIsStarted)
		if (fVolume >= 0.0f && fVolume <=1.0f)
			m_pkSoundEngine->setSoundVolume(fVolume);
}
//---------------------------------------------------------------- 
float Sound::getMasterVolume(){
	if (m_bIsStarted)
		return m_pkSoundEngine->getSoundVolume();
	else
		return -1.0f;
}
//---------------------------------------------------------------- 
void Sound::pauseAllSounds(bool bPause){
	if (m_bIsStarted)
		m_pkSoundEngine->setAllSoundsPaused(bPause);	
}
//----------------------------------------------------------------