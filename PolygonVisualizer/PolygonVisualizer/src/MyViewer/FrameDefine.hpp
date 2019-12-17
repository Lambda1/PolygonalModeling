#ifndef __FRAME_DEFINE_HPP__
#define __FRAME_DEFINE_HPP__

enum class FrameProcessFlag : unsigned char
{
	NONE       = 0x00, // �����I�����Ă��Ȃ�
	UPDATE_END = 0x01, // �X�V�����I��
	DRAW_END   = 0x02, // �`�揈���I��

	// 1�t���[�������̏I��
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