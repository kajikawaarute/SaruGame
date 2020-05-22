#pragma once
#include "ISaruState.h"

class SaruStateGet : public ISaruState
{
public:
	/// <summary>
	/// •ßŠló‘Ô‚É‘JˆÚ‚µ‚½‚Æ‚«‚ÉŒÄ‚Î‚ê‚éŠÖ”
	/// </summary>
	void OnEnter();

	/// <summary>
	/// XVŠÖ”
	/// </summary>
	void Update();

	/// <summary>
	/// •ßŠló‘Ô‚ğ”²‚¯‚é‚ÉŒÄ‚Î‚ê‚éŠÖ”
	/// </summary>
	void OnLeave();

};

