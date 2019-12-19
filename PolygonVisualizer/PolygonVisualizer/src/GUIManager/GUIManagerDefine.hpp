#ifndef __GUI_MANAGER_DEFINE_HPP__
#define __GUI_MANAGER_DEFINE_HPP__

namespace GUI_MANAGER_DEFINE
{
	using TYPE = int;
	enum class FLAGS : int
	{
		NONE = 0x00,

		OPEN_FILE = 0x01,
		SAVE_FILE = 0x02,
	};
};

constexpr GUI_MANAGER_DEFINE::FLAGS operator|(const GUI_MANAGER_DEFINE::FLAGS& lhs, const GUI_MANAGER_DEFINE::FLAGS& rhs)
{
	return static_cast<GUI_MANAGER_DEFINE::FLAGS>(static_cast<GUI_MANAGER_DEFINE::TYPE>(lhs) | static_cast<GUI_MANAGER_DEFINE::TYPE>(rhs));
}
constexpr void operator|=(GUI_MANAGER_DEFINE::FLAGS& lhs, const GUI_MANAGER_DEFINE::FLAGS& rhs) { lhs = lhs | rhs; }
constexpr GUI_MANAGER_DEFINE::FLAGS operator&(const GUI_MANAGER_DEFINE::FLAGS& lhs, const GUI_MANAGER_DEFINE::FLAGS& rhs)
{
	return static_cast<GUI_MANAGER_DEFINE::FLAGS>(static_cast<GUI_MANAGER_DEFINE::TYPE>(lhs) & static_cast<GUI_MANAGER_DEFINE::TYPE>(rhs));
}

#endif