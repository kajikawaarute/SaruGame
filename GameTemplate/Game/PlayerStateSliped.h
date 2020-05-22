#pragma once
#include "IPlayerState.h"

class PlayerStateSliped : public IPlayerState
{
public:
	/// <summary>
	/// ŠŠ‚Á‚Ä‚¢‚éó‘Ô‚É‘JˆÚ‚µ‚½‚Æ‚«‚ÉŒÄ‚Î‚ê‚éŠÖ”
	/// </summary>
	void OnEnter();

	/// <summary>
	/// XVŠÖ”
	/// </summary>
	void Update();

	/// <summary>
	/// ŠŠ‚Á‚Ä‚¢‚éó‘Ô‚ğ”²‚¯‚é‚ÉŒÄ‚Î‚ê‚éŠÖ”
	/// </summary>
	void OnLeave();
};

