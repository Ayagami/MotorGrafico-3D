#pragma once
//---------------------------------------------------------------- 
// irrKlang specific instructions
#include "../../ext/irrKlang/include/irrKlang.h"
#pragma comment(lib, "../ext/irrKlang/lib/irrKlang.lib") // link with irrKlang.dll
using namespace irrklang;
typedef ISoundEngine* SoundEngine;
//---------------------------------------------------------------- 
#include "../myEngine_API.h"
#include <string>
//---------------------------------------------------------------- 
namespace DoMaRe{
class MYENGINE_API Sound{
public:
	Sound();
	~Sound();

	bool startSoundEngine();
	bool stopSoundEngine();

	bool playSoundFile(std::string kFileName, bool bLoop=false);
	ISound*	GetAndplaySoundFile(std::string kFileName, bool bLoop=false);
	void stopAllSounds();

	void pauseAllSounds(bool bPause);

	void setMasterVolume(float fVolume);
	float getMasterVolume();

protected:
	SoundEngine m_pkSoundEngine;
	bool m_bIsStarted;
};
}
//---------------------------------------------------------------- 
//---------------------------------------------------------------- 

