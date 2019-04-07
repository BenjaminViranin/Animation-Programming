#pragma once

#include "../include/stdafx.h"
#include "Transform.h"

class SkeletonBone
{
private:
	int										m_index;
	int										m_parentIndex;
	bool									m_haveParent;

	std::string								m_name;
	Transform								m_initialTransform;
	Transform								m_initialGlobalTransform;
	Transform								m_localTransform;
	Transform								m_globalTransform;
	std::pair<Transform, Transform>			m_lerpTransform;

	std::vector<std::pair<float, float>>	m_circleBuffer;

public:
	SkeletonBone(int p_index);
	SkeletonBone(std::string p_name);
	~SkeletonBone();

	void			Draw();
	void			InitCircleBuffer(float p_scale);

	void			SetInitialTransform(AltMath::Vector3f p_position, AltMath::Quaternion p_rotation);
	void			SetInitialGlobalTransform(Transform& p_parentGlobalTransform);

	void			SetOldLocalTransform(Transform& p_transform);
	void			SetNextLocalTransform(Transform& p_transform);
	void			SetNextLocalTransform(AltMath::Vector3f p_position, AltMath::Quaternion p_rotation);
	void			SetLocalTransform(AltMath::Vector3f p_position, AltMath::Quaternion p_rotation);

	void			SetGlobalTransform(Transform& p_parentGlobalTransform);
	
	void			SetIndex(std::string p_name);
	void			SetParentIndex(int p_index);
	void			SetName(int p_index);
	void			DrawCross(AltMath::Vector4f p_position, float p_scale, AltMath::Vector3f p_color = AltMath::Vector3f(1, 0, 0));
	void			DrawCross(AltMath::Vector4f p_position, float p_scale, std::string p_name, AltMath::Vector3f p_color);
	void			DrawSphere(AltMath::Vector4f p_position, AltMath::Vector3f p_color = AltMath::Vector3f(1, 0, 0));
	void			DrawSphere(AltMath::Vector4f p_position, std::string p_name, AltMath::Vector3f p_color);
		
	bool			HaveParent();
	int				GetIndex();
	int				GetParentIndex();
	Transform&		GetOldLocalTransform();
	Transform&		GetNextLocalTransform();
	Transform&		GetInitialTransform();
	Transform&		GetInitialGlobalTransform();
	Transform&		GetLocalTransform();
	Transform&		GetGlobalTransform();
	std::string		GetName();
};