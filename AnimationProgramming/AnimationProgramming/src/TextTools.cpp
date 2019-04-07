
#include <Engine.h>
#include "../include/TextTools.h"

TextTools TextTools::m_instance = TextTools::TextTools();

void TextTools::Draw(std::string p_text, AltMath::Vector3f p_pos, AltMath::Vector3f p_color, float p_scale)
{
	for (int i = 0; i < p_text.size(); ++i)
	{
		switch (p_text[i])
		{
		case '0':
			m_instance.Draw_0(p_pos, i, p_text.size(), p_color, p_scale);
			break;
		case '1':
			m_instance.Draw_1(p_pos, i, p_text.size(), p_color, p_scale);
			break;
		case '2':
			m_instance.Draw_2(p_pos, i, p_text.size(), p_color, p_scale);
			break;
		case '3':
			m_instance.Draw_3(p_pos, i, p_text.size(), p_color, p_scale);
			break;
		case '4':
			m_instance.Draw_4(p_pos, i, p_text.size(), p_color, p_scale);
			break;
		case '5':
			m_instance.Draw_5(p_pos, i, p_text.size(), p_color, p_scale);
			break;
		case '6':
			m_instance.Draw_6(p_pos, i, p_text.size(), p_color, p_scale);
			break;
		case '7':
			m_instance.Draw_7(p_pos, i, p_text.size(), p_color, p_scale);
			break;
		case '8':
			m_instance.Draw_8(p_pos, i, p_text.size(), p_color, p_scale);
			break;
		case '9':
			m_instance.Draw_9(p_pos, i, p_text.size(), p_color, p_scale);
			break;
		}
	}
}

void TextTools::Draw(int p_text, AltMath::Vector3f p_pos, AltMath::Vector3f p_color, float p_scale)
{
	Draw(std::to_string(p_text), p_pos, p_color, p_scale);
}

void TextTools::Draw_0(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale)
{
	p_pos.x -= (p_scale * 0.5f + 1.0f) * p_textSize;
	p_pos.z -= p_scale;
	float l_posInText = (p_scale + 2.0f)* p_index;
	
	DrawTop(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDown(p_pos, p_index, l_posInText, p_color, p_scale);

}

void TextTools::Draw_1(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale)
{
	p_pos.x -= (p_scale * 0.5f + 1.0f) * p_textSize;
	p_pos.z -= p_scale;
	float l_posInText = (p_scale + 2.0f)* p_index;
	
	DrawTopRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownRight(p_pos, p_index, l_posInText, p_color, p_scale);
}

void TextTools::Draw_2(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale)
{
	p_pos.x -= (p_scale * 0.5f + 1.0f) * p_textSize;
	p_pos.z -= p_scale;
	float l_posInText = (p_scale + 2.0f)* p_index;

	DrawTop(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawMiddle(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDown(p_pos, p_index, l_posInText, p_color, p_scale);
}

void TextTools::Draw_3(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale)
{
	p_pos.x -= (p_scale * 0.5f + 1.0f) * p_textSize;
	p_pos.z -= p_scale;
	float l_posInText = (p_scale + 2.0f)* p_index;
	
	DrawTop(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawMiddle(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDown(p_pos, p_index, l_posInText, p_color, p_scale);
}

void TextTools::Draw_4(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale)
{
	p_pos.x -= (p_scale * 0.5f + 1.0f) * p_textSize;
	p_pos.z -= p_scale;
	float l_posInText = (p_scale + 2.0f)* p_index;
	
	DrawTopLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawMiddle(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownRight(p_pos, p_index, l_posInText, p_color, p_scale);
}

void TextTools::Draw_5(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale)
{
	p_pos.x -= (p_scale * 0.5f + 0.5f) * p_textSize;
	p_pos.z -= p_scale;
	float l_posInText = (p_scale + 1.0f)* p_index;
	
	DrawTop(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawMiddle(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDown(p_pos, p_index, l_posInText, p_color, p_scale);
}

void TextTools::Draw_6(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale)
{
	p_pos.x -= (p_scale * 0.5f + 1.0f) * p_textSize;
	p_pos.z -= p_scale;
	float l_posInText = (p_scale + 2.0f)* p_index;

	DrawTop(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawMiddle(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDown(p_pos, p_index, l_posInText, p_color, p_scale);
}

void TextTools::Draw_7(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale)
{
	p_pos.x -= (p_scale * 0.5f + 1.0f) * p_textSize;
	p_pos.z -= p_scale;
	float l_posInText = (p_scale + 2.0f)* p_index;

	DrawTop(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownRight(p_pos, p_index, l_posInText, p_color, p_scale);
}

void TextTools::Draw_8(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale)
{
	p_pos.x -= (p_scale * 0.5f + 1.0f) * p_textSize;
	p_pos.z -= p_scale;
	float l_posInText = (p_scale + 2.0f)* p_index;

	DrawTop(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawMiddle(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDown(p_pos, p_index, l_posInText, p_color, p_scale);
}

void TextTools::Draw_9(AltMath::Vector3f p_pos, int p_index, int p_textSize, AltMath::Vector3f p_color, float p_scale)
{
	p_pos.x -= (p_scale * 0.5f + 1.0f) * p_textSize;
	p_pos.z -= p_scale;
	float l_posInText = (p_scale + 2.0f)* p_index;

	DrawTop(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopLeft(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawTopRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawMiddle(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDownRight(p_pos, p_index, l_posInText, p_color, p_scale);
	DrawDown(p_pos, p_index, l_posInText, p_color, p_scale);
}

void TextTools::DrawTop(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale)
{
	DrawLine(/* first */ p_pos.x + l_posInText, p_pos.y, p_pos.z + 2 * p_scale,
			 /* second */p_pos.x + p_scale + l_posInText, p_pos.y, p_pos.z + 2 * p_scale,
			 /* color */ p_color.x + p_index, p_color.y, p_color.z);
}

void TextTools::DrawMiddle(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale)
{
	DrawLine(/* first */ p_pos.x + l_posInText, p_pos.y, p_pos.z + p_scale,
			 /* second */p_pos.x + p_scale + l_posInText, p_pos.y, p_pos.z + p_scale,
			 /* color */ p_color.x + p_index, p_color.y, p_color.z);
}

void TextTools::DrawDown(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale)
{
	DrawLine(/* first */ p_pos.x + l_posInText, p_pos.y, p_pos.z,
			 /* second */p_pos.x + p_scale + l_posInText, p_pos.y, p_pos.z,
			 /* color */ p_color.x + p_index, p_color.y, p_color.z);
}

void TextTools::DrawTopLeft(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale)
{
	DrawLine(/* first */ p_pos.x + l_posInText, p_pos.y, p_pos.z + p_scale,
			 /* second */p_pos.x + l_posInText, p_pos.y, p_pos.z + 2 * p_scale,
			 /* color */ p_color.x + p_index, p_color.y, p_color.z);
}

void TextTools::DrawTopRight(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale)
{
	DrawLine(/* first */ p_pos.x + p_scale + l_posInText, p_pos.y, p_pos.z + p_scale,
			 /* second */p_pos.x + p_scale + l_posInText, p_pos.y, p_pos.z + 2 * p_scale,
			 /* color */ p_color.x + p_index, p_color.y, p_color.z);
}

void TextTools::DrawDownLeft(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale)
{
	DrawLine(/* first */ p_pos.x + l_posInText, p_pos.y, p_pos.z + p_scale,
			 /* second */p_pos.x + l_posInText, p_pos.y, p_pos.z ,
			 /* color */ p_color.x + p_index, p_color.y, p_color.z);
}

void TextTools::DrawDownRight(AltMath::Vector3f p_pos, int p_index, float l_posInText, AltMath::Vector3f p_color, float p_scale)
{
	DrawLine(/* first */ p_pos.x + p_scale + l_posInText, p_pos.y, p_pos.z + p_scale,
			 /* second */p_pos.x + p_scale + l_posInText, p_pos.y, p_pos.z,
			 /* color */ p_color.x + p_index, p_color.y, p_color.z);
}
