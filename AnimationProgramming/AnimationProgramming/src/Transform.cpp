#include "../include/Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::SetPosition(AltMath::Vector3f p_position)
{
	m_position = p_position;
}

void Transform::SetRotation(AltMath::Quaternion p_rotation)
{
	m_rotation = p_rotation;
}

void Transform::InitTransformation()
{
	if (!m_rotation.IsNormalized())
		m_rotation.Normalize();

	m_transformation = AltMath::Matrix4f::Translation(m_position) * m_rotation.ToMatrix4();
}

void Transform::SetTransformation(AltMath::Matrix4f p_transformation)
{
	m_transformation = p_transformation;
}

AltMath::Vector3f Transform::GetPosition()
{
	return m_position;
}

AltMath::Quaternion Transform::GetRotation()
{
	return m_rotation;
}

AltMath::Matrix4f Transform::GetTransformation()
{
	return m_transformation;
}
