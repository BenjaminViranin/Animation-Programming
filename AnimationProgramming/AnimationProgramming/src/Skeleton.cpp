
#include "../include/skeleton.h"
#include "../include/TextTools.h"
#include <Engine.h>

Skeleton::Skeleton() : LinesScale(0), CircleScale(0), m_isFirstUpdate(true), 
					   m_drawPowerfullStar(false), m_timeSinceGameStart(0.0f)
{
}

Skeleton::Skeleton(std::string p_name) : m_name(p_name), LinesScale(0), 
										 CircleScale(0), m_isFirstUpdate(true),
										 m_drawPowerfullStar(false), m_timeSinceGameStart(0.0f)
{
}

Skeleton::~Skeleton()
{
}

void Skeleton::Init()
{
	m_animationData.s_animeKeyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
	InitBones();
}

void Skeleton::InitBones()
{ 
	m_bonesCount = GetSkeletonBoneCount();

	/* Substract Inverse Kinematic */
	m_bonesCount -= 7;

	for (int i = 0; i < m_bonesCount; ++i)
	{
		m_bones.emplace_back(SkeletonBone(i));
	}

	InitBonesTransform();
}

void Skeleton::InitBonesTransform()
{
	for (int i = 0; i < m_bones.size(); ++i)
	{
		InitBoneTransform(i);
	}
}

void Skeleton::InitBoneTransform(int p_index)
{
	AltMath::Vector3f l_position;
	AltMath::Vector4f l_tempRotation;

	GetSkeletonBoneLocalBindTransform(m_bones[p_index].GetIndex(),
			l_position.x, l_position.y, l_position.z,
			l_tempRotation.w, l_tempRotation.x, l_tempRotation.y, l_tempRotation.z);

	AltMath::Quaternion l_rotation(l_tempRotation.x, l_tempRotation.y, l_tempRotation.z, l_tempRotation.w);

	m_bones[p_index].SetInitialTransform(l_position, l_rotation);

	m_bones[p_index].SetLocalTransform(l_position, l_rotation);
	m_bones[p_index].SetOldLocalTransform(m_bones[p_index].GetInitialTransform());
	m_bones[p_index].SetNextLocalTransform(m_bones[p_index].GetInitialTransform()); 

	if (m_bones[p_index].HaveParent())
	{
		m_bones[p_index].SetGlobalTransform(GetBoneByIndex(m_bones[p_index].GetParentIndex()).GetGlobalTransform());
		m_bones[p_index].SetInitialGlobalTransform(GetBoneByIndex(m_bones[p_index].GetParentIndex()).GetGlobalTransform());
	}
	else
	{
		m_bones[p_index].SetGlobalTransform(m_bones[p_index].GetLocalTransform());
		m_bones[p_index].SetInitialGlobalTransform(m_bones[p_index].GetLocalTransform());
	}
}

void Skeleton::UpdateBonesTransform(int p_keyFrame)
{
	for (int i = 0; i < m_bones.size(); ++i)
	{
		UpdateBoneTransform(i, p_keyFrame);
	}
}

void Skeleton::UpdateBoneTransform(int p_index, int p_keyFrame)
{
	m_bones[p_index].SetOldLocalTransform(m_bones[p_index].GetNextLocalTransform());

	AltMath::Vector3f l_position;
	AltMath::Vector4f l_tempRotation; 

	GetAnimLocalBoneTransform("ThirdPersonWalk.anim", m_bones[p_index].GetIndex(), p_keyFrame,
			l_position.x, l_position.y, l_position.z,
			l_tempRotation.w, l_tempRotation.x, l_tempRotation.y, l_tempRotation.z);

	AltMath::Quaternion l_rotation(l_tempRotation.x, l_tempRotation.y, l_tempRotation.z, l_tempRotation.w);

	m_bones[p_index].SetNextLocalTransform(l_position, l_rotation);
	m_bones[p_index].GetNextLocalTransform().SetTransformation(m_bones[p_index].GetInitialTransform().GetTransformation() * m_bones[p_index].GetNextLocalTransform().GetTransformation());

	if (m_bones[p_index].HaveParent())
		m_bones[p_index].SetGlobalTransform(GetBoneByIndex(m_bones[p_index].GetParentIndex()).GetGlobalTransform());
	else
		m_bones[p_index].SetGlobalTransform(m_bones[p_index].GetLocalTransform());
}

void Skeleton::UpdateMesh()
{
	if (!m_isFirstUpdate)
	{
		std::vector<float> boneMatrices;
		for (auto bone : m_bones)
		{
			for (int i = 0; i < 16; ++i)
			{
				AltMath::Matrix4f l_inverseGlobalInitialMat = bone.GetInitialGlobalTransform().GetTransformation().Inverse();
				AltMath::Matrix4f l_mat4 = bone.GetGlobalTransform().GetTransformation() * l_inverseGlobalInitialMat;
				boneMatrices.push_back(l_mat4.ToArray()[i]);
			}
		}

		SetSkinningPose(boneMatrices.data(), m_bones.size());
	}
}

void Skeleton::Update(float p_deltaTime)
{
	m_animationData.s_elapsedTime += p_deltaTime;
	m_timeSinceGameStart += p_deltaTime;

	m_animationData.s_currentTimeToUpdate = (m_animationData.s_animationSpeed > 0 ? m_animationData.s_initialTimeToUpdate * (1.0f - (m_animationData.s_animationSpeed * 0.01f)) : 0.0f);
	
	if (m_animationData.s_currentKeyFrame == 30 || m_animationData.s_currentKeyFrame == 0)
		m_animationData.s_currentTimeToUpdate *= 1.5f;

	if (m_animationData.s_elapsedTime > m_animationData.s_currentTimeToUpdate)
	{
		UpdateBonesTransform(m_animationData.s_currentKeyFrame);

		m_animationData.s_currentKeyFrame = m_animationData.s_currentKeyFrame >= m_animationData.s_animeKeyCount - 1 ? 0 : m_animationData.s_currentKeyFrame + 1;

		m_animationData.s_elapsedTime = 0.0f;
	}

	LerpSkeletonAnimation();

	UpdateMesh();

	if (m_animationData.s_currentKeyFrame >= 4)
		m_isFirstUpdate = false;
	if (m_timeSinceGameStart >= 20.0f)
		m_drawPowerfullStar = true;
}

void Skeleton::LerpSkeletonAnimation()
{
	AltMath::Vector3f l_position;
	AltMath::Quaternion l_rotation;

	m_animationData.s_alphaLerp = 1.0f - ((m_animationData.s_currentTimeToUpdate - m_animationData.s_elapsedTime) / m_animationData.s_currentTimeToUpdate);

	if (m_animationData.s_alphaLerp > 1.0f)
		m_animationData.s_alphaLerp = 1.0f;

	for (int i = 0; i < m_bones.size(); ++i)
	{
		l_position = AltMath::Vector3f::Lerp(m_bones[i].GetOldLocalTransform().GetPosition(), m_bones[i].GetNextLocalTransform().GetPosition(), m_animationData.s_alphaLerp);
		l_rotation = AltMath::Quaternion::Slerp(m_bones[i].GetOldLocalTransform().GetRotation(), m_bones[i].GetNextLocalTransform().GetRotation(), m_animationData.s_alphaLerp);

		m_bones[i].SetLocalTransform(l_position, l_rotation);
		m_bones[i].GetLocalTransform().SetTransformation(m_bones[i].GetInitialTransform().GetTransformation() * m_bones[i].GetLocalTransform().GetTransformation());

		if (m_bones[i].HaveParent())
			m_bones[i].SetGlobalTransform(GetBoneByIndex(m_bones[i].GetParentIndex()).GetGlobalTransform());
		else
			m_bones[i].SetGlobalTransform(m_bones[i].GetLocalTransform());
	}
}

void Skeleton::Draw()
{
	if (!m_isFirstUpdate)
	{
		for (int i = 0; i < m_bones.size(); ++i)
		{
			m_bones[i].Draw();

			if (m_bones[i].HaveParent())
			{
				DrawSkeletonLine(i, AltMath::Vector4f(100.0f, 0, 0), false);
			}
		}
	}

	if (!m_isFirstUpdate)
		DrawAnimeState();

	if (m_isFirstUpdate)
		TextTools::Draw( 3 - m_animationData.s_currentKeyFrame, AltMath::Vector3f(50.0f, 0, 130.0f), AltMath::Vector3f(1, 0, 0), 10.0f);

	if (m_drawPowerfullStar)
	{
		//DrawPowerfullStar();
	}

}

void Skeleton::DrawSkeletonLine(int p_index, AltMath::Vector4f p_spacing, bool p_drawRoot)
{
	AltMath::Vector4f l_startPosition( m_bones[p_index].GetGlobalTransform().GetTransformation().GetColumn(3) );
	AltMath::Vector4f l_endPosition( GetBoneByIndex(m_bones[p_index].GetParentIndex()).GetGlobalTransform().GetTransformation().GetColumn(3) );

	l_startPosition += p_spacing;
	l_endPosition += p_spacing;
	if (p_drawRoot)
	{
		DrawLine(l_startPosition.x, l_startPosition.y, l_startPosition.z,
			     l_endPosition.x, l_endPosition.y, l_endPosition.z,
				 0, 0, 0);
	}
	else
	{
		if (p_index != 1)
		{
			DrawLine(l_startPosition.x, l_startPosition.y, l_startPosition.z,
					 l_endPosition.x, l_endPosition.y, l_endPosition.z,
					 0, 0, 0);
		}
	}
}

void Skeleton::DrawAnimeState()
{
	DrawSphere(AltMath::Vector4f(50.0f, 0, 250), 45.0f, AltMath::Vector3f(0, 0, 0));
	DrawNumber(AltMath::Vector3f(50.0f, 0, 250), 19.0f, AltMath::Vector3f(0, 0, 0));
	DrawCurrentFrameLine(AltMath::Vector4f(50.0f, 0, 250), 40.0f, AltMath::Vector3f(1, 0, 0));
}

void Skeleton::DrawCurrentFrameLine(AltMath::Vector4f p_position, float p_scale, AltMath::Vector3f p_color)
{
	float l_angle = (360.0f / m_animationData.s_animeKeyCount) * (static_cast<float>(m_animationData.s_currentKeyFrame) - static_cast<float>(m_animationData.s_animeKeyCount) / 4 - 1.0f);
	l_angle += m_animationData.s_alphaLerp * (360.0f / m_animationData.s_animeKeyCount);

	DrawLine(/* first */   p_position.x + AltMath::Tools::Utils::Cos(AltMath::Tools::Utils::ToRadians(-l_angle - 11.6129f)) * p_scale,
						   p_position.y,
						   p_position.z + AltMath::Tools::Utils::Sin(AltMath::Tools::Utils::ToRadians(-l_angle - 11.6129f)) * p_scale,

			 /* second */  p_position.x + AltMath::Tools::Utils::Cos(AltMath::Tools::Utils::ToRadians(-l_angle - 11.6129f)) * (p_scale + 15.0f),
						   p_position.y,
						   p_position.z + AltMath::Tools::Utils::Sin(AltMath::Tools::Utils::ToRadians(-l_angle - 11.6129f)) * (p_scale + 15.0f),

			 /* color */   p_color.x, p_color.y, p_color.z);
}

void Skeleton::DrawSphere(AltMath::Vector4f p_position, float p_scale, AltMath::Vector3f p_color)
{
	for (float i = 0; i <= 360.0f; i += 360.0f / m_animationData.s_animeKeyCount)
	{
		if (static_cast<int>(i) != 92)
		{
			DrawLine(/* first */   p_position.x + AltMath::Tools::Utils::Cos(AltMath::Tools::Utils::ToRadians(i - 2.8f)) * p_scale,
								   p_position.y,
							       p_position.z + AltMath::Tools::Utils::Sin(AltMath::Tools::Utils::ToRadians(i - 2.8f)) * p_scale,

					 /* second */  p_position.x + AltMath::Tools::Utils::Cos(AltMath::Tools::Utils::ToRadians(i - 2.8f)) * (p_scale + 10.0f),
								   p_position.y,
								   p_position.z + AltMath::Tools::Utils::Sin(AltMath::Tools::Utils::ToRadians(i - 2.8f)) * (p_scale + 10.0f),

					 /* color */   p_color.x, p_color.y, p_color.z);
		}
		else
		{
			DrawLine(/* first */   p_position.x + AltMath::Tools::Utils::Cos(AltMath::Tools::Utils::ToRadians(i - 2.8f)) * (p_scale + 2.5f),
								   p_position.y,
					               p_position.z + AltMath::Tools::Utils::Sin(AltMath::Tools::Utils::ToRadians(i - 2.8f)) * (p_scale + 2.5f),

					/* second */   p_position.x + AltMath::Tools::Utils::Cos(AltMath::Tools::Utils::ToRadians(i - 2.8f)) * (p_scale + 8.5f),
								   p_position.y,
								   p_position.z + AltMath::Tools::Utils::Sin(AltMath::Tools::Utils::ToRadians(i - 2.8f)) * (p_scale + 8.5f),

					/* color */	   0, 0.8f, 0);
		}
	}
}

void Skeleton::DrawNumber(AltMath::Vector3f p_position, float p_scale, AltMath::Vector3f p_color)
{
	if (m_animationData.s_currentKeyFrame < 10)
		TextTools::Draw("0" + std::to_string(m_animationData.s_currentKeyFrame), p_position, p_color, p_scale);
	else
		TextTools::Draw(m_animationData.s_currentKeyFrame, p_position, p_color, p_scale);
}

SkeletonBone& Skeleton::GetBoneByIndex(int p_index)
{
	for (int i = 0; i < m_bones.size(); ++i)
	{
		if (m_bones[i].GetIndex() == p_index)
			return m_bones[i];
	}
}

void Skeleton::DrawPowerfullStar()
{
	DrawLine(-3.73 * 100, 0, 4.7 * 100,
		3.73 * LinesScale, 0, 4.7 * LinesScale,
		1, 0, 0);

	DrawLine(-3.73 * 100, 0, 4.7 * 100,
		3.05 * LinesScale, 0, 0.26 * LinesScale,
		1, 0, 0);

	DrawLine(-3.09 * 100, 0, 0.3 * 100,
		3.73 * LinesScale, 0, 4.7 * LinesScale,
		1, 0, 0);

	DrawLine(-3.09 * 100, 0, 0.3 * 100,
		0, 0, 7.1 * LinesScale,
		1, 0, 0);

	DrawLine(3.05 * 100, 0, 0.26 * 100,
		0, 0, 7.1 * LinesScale,
		1, 0, 0);

	for (int i = 0; i < CircleScale; ++i)
	{
		DrawLine(AltMath::Tools::Utils::Cos((360 / 300 * i) * 180) * 915, 0, 300 + AltMath::Tools::Utils::Sin((360 / 300 * i) * 180) * 915,
			AltMath::Tools::Utils::Cos((360 / 300 * (i + 1)) * 180) * 915, 0, 300 + AltMath::Tools::Utils::Sin((360 / 300 * (i + 1)) * 180) * 915,
			1, 0, 0);
	}

	CircleScale += 0.05;
	if (CircleScale > 100)
		CircleScale = 100;

	LinesScale += 0.06;
	if (LinesScale > 100)
		LinesScale = 100;
}

std::vector<SkeletonBone>& Skeleton::GetBones()
{
	return m_bones;
}

std::string Skeleton::GetName()
{
	return m_name;
}

