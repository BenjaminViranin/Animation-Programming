#pragma once

#include "../include/stdafx.h"
#include "skeletonBone.h"
#include <AltMath/Vector/Vector4.h>
#include <AltMath/Vector/Vector3.h>
#include <vector>

struct AnimationData
{
	size_t						s_animeKeyCount;
	int							s_currentKeyFrame;

	/* Animation Speed have to be between 0 and 100 */
	float						s_alphaLerp;
	float						s_animationSpeed;
	float						s_initialTimeToUpdate;
	float						s_currentTimeToUpdate;
	float						s_elapsedTime;

	AnimationData::AnimationData() : s_animeKeyCount(0), s_currentKeyFrame(0), 
									 s_alphaLerp(0.0f), s_animationSpeed(50.0f), s_initialTimeToUpdate(1.0f),
									 s_currentTimeToUpdate(s_initialTimeToUpdate), s_elapsedTime(0.0f) {}
};

class Skeleton
{
private:
	std::string					m_name;
	int							m_bonesCount;
	std::vector<SkeletonBone>	m_bones;
	AnimationData				m_animationData;

	bool						m_isFirstUpdate;

	bool						m_drawPowerfullStar;
	float						m_timeSinceGameStart;
	float						LinesScale;
	float						CircleScale;

public:
	Skeleton();
	Skeleton(std::string p_name);
	~Skeleton();

	void						Init();
	void						InitBones();
	void						InitBonesTransform();
	void						InitBoneTransform(int p_index);

	void						UpdateBonesTransform(int p_keyFrame);
	void						UpdateBoneTransform(int p_index, int p_keyFrame);
	void						UpdateMesh();
	void						Update(float p_deltaTime);
	void						LerpSkeletonAnimation();

	void						Draw();
	void						DrawSkeletonLine(int p_index, AltMath::Vector4f p_spacing, bool p_drawRoot = true);
	void						DrawAnimeState();
	void						DrawCurrentFrameLine(AltMath::Vector4f p_position, float p_scale, AltMath::Vector3f p_color);
	void						DrawSphere(AltMath::Vector4f p_position, float p_scale, AltMath::Vector3f p_color);
	void						DrawNumber(AltMath::Vector3f p_position, float p_scale, AltMath::Vector3f p_color);

	SkeletonBone&				GetBoneByIndex(int p_index);
	void						DrawPowerfullStar();
	std::vector<SkeletonBone>&  GetBones();
	std::string					GetName();
};