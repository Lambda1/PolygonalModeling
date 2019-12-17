#ifndef __KEY_BOARD_STATE_HPP__
#define __KEY_BOARD_STATE_HPP__

namespace KeyState
{
	enum class STATE : unsigned int
	{
		PUSH,    /* 押された */
		HOLD,    /* 押されている */
		RELEASE, /* 離された */
		NONE,    /* 押されていない */

		SIZE
	};
};

#endif
