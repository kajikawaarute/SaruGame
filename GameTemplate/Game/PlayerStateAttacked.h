#pragma once
#include "IPlayerState.h"

class PlayerStateAttacked : public IPlayerState
{
public:
	/// <summary>
	/// UŒ‚‚³‚ê‚½ó‘Ô‚É‘JˆÚ‚µ‚½‚Æ‚«‚ÉŒÄ‚Î‚ê‚éŠÖ”
	/// </summary>
	void OnEnter();

	/// <summary>
	/// XVŠÖ”
	/// </summary>
	void Update();

	/// <summary>
	/// UŒ‚‚³‚ê‚½ó‘Ô‚ğ”²‚¯‚é‚ÉŒÄ‚Î‚ê‚éŠÖ”
	/// </summary>
	void OnLeave();
};

