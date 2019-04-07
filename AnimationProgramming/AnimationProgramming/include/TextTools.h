#pragma once

#include <string>
#include <AltMath.h>

class TextTools
{
private:
	static TextTools m_instance;

public:
	TextTools() {};
	~TextTools() = default;

	static void Draw(std::string p_text, AltMath::Vector3f p_pos, AltMath::Vector3f p_color, float p_scale);
	static void Draw(int p_text, AltMath::Vector3f p_pos, AltMath::Vector3f p_color, float p_scale);

	void Draw_0(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale);
	void Draw_1(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale);
	void Draw_2(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale);
	void Draw_3(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale);
	void Draw_4(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale);
	void Draw_5(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale);
	void Draw_6(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale);
	void Draw_7(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale);
	void Draw_8(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale);
	void Draw_9(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale);

	/* Digital Number Bar */
	void DrawTop(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale);
	void DrawMiddle(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale);
	void DrawDown(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale);
	void DrawTopLeft(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale);
	void DrawTopRight(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale);
	void DrawDownLeft(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale);
	void DrawDownRight(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale);
};
