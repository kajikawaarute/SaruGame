#pragma once
#include "ISaruState.h"

class SaruStateFound : public ISaruState
{
public:
	/// <summary>
	/// Œ©‚Â‚©‚Á‚½ó‘Ô‚É‘JˆÚ‚µ‚½‚Æ‚«‚ÉŒÄ‚Î‚ê‚éŠÖ”
	/// </summary>
	void OnEnter();

	/// <summary>
	/// XVŠÖ”
	/// </summary>
	void Update();

	/// <summary>
	/// Œ©‚Â‚©‚Á‚½ó‘Ô‚ğ”²‚¯‚é‚ÉŒÄ‚Î‚ê‚éŠÖ”
	/// </summary>
	void OnLeave();
};

