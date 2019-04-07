#pragma once

#include "../include/stdafx.h"

class Transform
{
private:
	AltMath::Vector3f	m_position;
	AltMath::Quaternion m_rotation;
	AltMath::Matrix4f   m_transformation;

public:
	Transform();
	~Transform();

	void				SetPosition(AltMath::Vector3f p_position);
	void				SetRotation(AltMath::Quaternion p_rotation);
	void				InitTransformation();
	void				SetTransformation(AltMath::Matrix4f   p_transformation);

	AltMath::Vector3f	GetPosition();
	AltMath::Quaternion GetRotation();
	AltMath::Matrix4f   GetTransformation();
};