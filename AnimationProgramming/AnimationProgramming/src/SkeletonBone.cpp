
#include "../include/SkeletonBone.h"
#include <AltMath/Vector/Vector3.h>
#include <Engine.h>
#include <AltMath/Quaternion/Quaternion.h>

SkeletonBone::SkeletonBone(int p_index) : m_haveParent(true)
{
	m_index = p_index;
	SetParentIndex(m_index);
	m_name = GetSkeletonBoneName(p_index);
	if (m_parentIndex == -1)
		m_haveParent = false;

	InitCircleBuffer(1.5f);
}

SkeletonBone::SkeletonBone(std::string p_name) : m_haveParent(true)
{
	m_name = p_name;
	SetIndex(m_name);
	SetParentIndex(m_index);
	if (m_parentIndex == -1)
		m_haveParent = false;

	InitCircleBuffer(1.5f);
}

SkeletonBone::~SkeletonBone()
{
}

void SkeletonBone::Draw()
{
	AltMath::Vector4f l_position(m_globalTransform.GetTransformation().GetColumn(3));
	AltMath::Vector4f l_spacing(100.0f, 0, 0);
	l_position += l_spacing;

	DrawSphere(l_position, AltMath::Vector3f(1, 0, 0));
}

void SkeletonBone::InitCircleBuffer(float p_scale)
{
	for (int i = 0; i <= 360; i += 36)
	{
		m_circleBuffer.emplace_back(std::pair<float, float>(AltMath::Tools::Utils::Cos(AltMath::Tools::Utils::ToRadians(i)) * p_scale, AltMath::Tools::Utils::Sin(AltMath::Tools::Utils::ToRadians(i)) * p_scale));
	}
}

void SkeletonBone::SetInitialTransform(AltMath::Vector3f p_position, AltMath::Quaternion p_rotation)
{
	m_initialTransform.SetPosition(p_position);
	m_initialTransform.SetRotation(p_rotation);
	m_initialTransform.InitTransformation();
}

void SkeletonBone::SetInitialGlobalTransform(Transform& p_parentGlobalTransform)
{
	m_initialGlobalTransform.SetTransformation(p_parentGlobalTransform.GetTransformation() * m_localTransform.GetTransformation());
}

void SkeletonBone::SetOldLocalTransform(Transform& p_transform)
{
	m_lerpTransform.first = p_transform;
}

void SkeletonBone::SetNextLocalTransform(Transform& p_transform)
{
	m_lerpTransform.second = p_transform;
}

void SkeletonBone::SetNextLocalTransform(AltMath::Vector3f p_position, AltMath::Quaternion p_rotation)
{
	m_lerpTransform.second.SetPosition(p_position);
	m_lerpTransform.second.SetRotation(p_rotation);
	m_lerpTransform.second.InitTransformation();
}

void SkeletonBone::SetLocalTransform(AltMath::Vector3f p_position, AltMath::Quaternion p_rotation)
{
	m_localTransform.SetPosition(p_position);
	m_localTransform.SetRotation(p_rotation);
	m_localTransform.InitTransformation();
}

void SkeletonBone::SetGlobalTransform(Transform& p_parentGlobalTransform)
{
	m_globalTransform.SetTransformation(p_parentGlobalTransform.GetTransformation() * m_localTransform.GetTransformation());
}

void SkeletonBone::SetIndex(std::string p_name)
{
	m_index = GetSkeletonBoneIndex(p_name.c_str());
}

void SkeletonBone::SetParentIndex(int p_index)
{
	m_parentIndex = GetSkeletonBoneParentIndex(p_index);
}

void SkeletonBone::SetName(int p_index)
{
	m_name = GetSkeletonBoneName(p_index);
}

void SkeletonBone::DrawCross(AltMath::Vector4f p_position, float p_scale, AltMath::Vector3f p_color)
{
	DrawLine(p_position.x - (1 * p_scale), p_position.y, p_position.z,
		p_position.x + (1 * p_scale), p_position.y, p_position.z,
		p_color.x, p_color.y, p_color.z);
	DrawLine(p_position.x, p_position.y - (1 * p_scale), p_position.z,
		p_position.x, p_position.y + (1 * p_scale), p_position.z,
		p_color.x, p_color.y, p_color.z);
	DrawLine(p_position.x, p_position.y, p_position.z - (1 * p_scale),
		p_position.x, p_position.y, p_position.z + (1 * p_scale),
		p_color.x, p_color.y, p_color.z);
}

void SkeletonBone::DrawCross(AltMath::Vector4f p_position, float p_scale, std::string p_name, AltMath::Vector3f p_color)
{
	if (m_name == p_name)
	{
		DrawLine(p_position.x - (1 * p_scale), p_position.y, p_position.z,
			p_position.x + (1 * p_scale), p_position.y, p_position.z,
			p_color.x, p_color.y, p_color.z);
		DrawLine(p_position.x, p_position.y - (1 * p_scale), p_position.z,
			p_position.x, p_position.y + (1 * p_scale), p_position.z,
			p_color.x, p_color.y, p_color.z);
		DrawLine(p_position.x, p_position.y, p_position.z - (1 * p_scale),
			p_position.x, p_position.y, p_position.z + (1 * p_scale),
			p_color.x, p_color.y, p_color.z);
	}
}

void SkeletonBone::DrawSphere(AltMath::Vector4f p_position, AltMath::Vector3f p_color)
{
	for (int i = 0; i < m_circleBuffer.size() - 1; ++i)
	{
		DrawLine(p_position.x + m_circleBuffer[i].first, p_position.y, p_position.z + m_circleBuffer[i].second,
				 p_position.x + m_circleBuffer[i + 1].first, p_position.y, p_position.z + m_circleBuffer[i + 1].second,
				 p_color.x, p_color.y, p_color.z);
		DrawLine(p_position.x + m_circleBuffer[i].first, p_position.y + m_circleBuffer[i].second, p_position.z,
				 p_position.x + m_circleBuffer[i + 1].first, p_position.y + m_circleBuffer[i + 1].second, p_position.z,
				 p_color.x, p_color.y, p_color.z);
		DrawLine(p_position.x, p_position.y + m_circleBuffer[i].first, p_position.z + m_circleBuffer[i].second,
			  	 p_position.x, p_position.y + m_circleBuffer[i + 1].first, p_position.z + m_circleBuffer[i + 1].second,
				 p_color.x, p_color.y, p_color.z);
	}
}

void SkeletonBone::DrawSphere(AltMath::Vector4f p_position, std::string p_name, AltMath::Vector3f p_color)
{
	if (m_name == p_name)
	{
		for (int i = 0; i < m_circleBuffer.size() - 1; ++i)
		{
			DrawLine(p_position.x + m_circleBuffer[i].first, p_position.y, p_position.z + m_circleBuffer[i].second,
				p_position.x + m_circleBuffer[i + 1].first, p_position.y, p_position.z + m_circleBuffer[i + 1].second,
				p_color.x, p_color.y, p_color.z);
			DrawLine(p_position.x + m_circleBuffer[i].first, p_position.y + m_circleBuffer[i].second, p_position.z,
				p_position.x + m_circleBuffer[i + 1].first, p_position.y + m_circleBuffer[i + 1].second, p_position.z,
				p_color.x, p_color.y, p_color.z);
			DrawLine(p_position.x, p_position.y + m_circleBuffer[i].first, p_position.z + m_circleBuffer[i].second,
				p_position.x, p_position.y + m_circleBuffer[i + 1].first, p_position.z + m_circleBuffer[i + 1].second,
				p_color.x, p_color.y, p_color.z);
		}
	}
}

bool SkeletonBone::HaveParent()
{
	return m_haveParent;
}

int SkeletonBone::GetIndex()
{
	return m_index;
}

int SkeletonBone::GetParentIndex()
{
	return m_parentIndex;
}

Transform& SkeletonBone::GetInitialTransform()
{
	return m_initialTransform;
}

Transform& SkeletonBone::GetInitialGlobalTransform()
{
	return m_initialGlobalTransform;
}

Transform& SkeletonBone::GetOldLocalTransform()
{
	return m_lerpTransform.first;
}

Transform& SkeletonBone::GetNextLocalTransform()
{
	return m_lerpTransform.second;
}

Transform& SkeletonBone::GetLocalTransform()
{
	return m_localTransform;
}

Transform& SkeletonBone::GetGlobalTransform()
{
	return m_globalTransform;
}

std::string SkeletonBone::GetName()
{
	return m_name;
}
