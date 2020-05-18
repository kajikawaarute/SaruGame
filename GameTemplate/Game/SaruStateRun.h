#pragma once
#include "ISaruState.h"

class SaruStateRun : public ISaruState
{
public:
	/// <summary>
	/// ‘–‚èó‘Ô‚É‘JˆÚ‚µ‚½‚Æ‚«‚ÉŒÄ‚Î‚ê‚éŠÖ”
	/// </summary>
	void OnEnter();

	/// <summary>
	/// XVŠÖ”
	/// </summary>
	void Update();

	/// <summary>
	/// ‘–‚èó‘Ô‚ğ”²‚¯‚é‚ÉŒÄ‚Î‚ê‚éŠÖ”
	/// </summary>
	void OnLeave();
};

