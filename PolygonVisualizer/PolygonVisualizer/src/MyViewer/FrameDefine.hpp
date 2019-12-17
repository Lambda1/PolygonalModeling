#ifndef __FRAME_DEFINE_HPP__
#define __FRAME_DEFINE_HPP__

enum class FrameProcessFlag : unsigned char
{
	NONE       = 0x00, // 何も終了していない
	UPDATE_END = 0x01, // 更新処理終了
	DRAW_END   = 0x02, // 描画処理終了

	// 1フレーム処理の終了
	ALL_END = UPDATE_END | DRAW_END,
};

constexpr FrameProcessFlag operator|(const FrameProcessFlag &lhs, const FrameProcessFlag &rhs)
{
	return static_cast<FrameProcessFlag>(lhs | rhs);
}
constexpr FrameProcessFlag operator&(const FrameProcessFlag& lhs, const FrameProcessFlag& rhs)
{
	return static_cast<FrameProcessFlag>(lhs & rhs);
}

#endif