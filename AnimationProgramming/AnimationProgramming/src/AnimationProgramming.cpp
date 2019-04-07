// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "../include/stdafx.h"
#include "../include/SkeletonBone.h"
#include "../include/Skeleton.h"

class CSimulation : public ISimulation
{
	Skeleton m_skeleton;

	virtual void Init() override
	{
		m_skeleton = Skeleton("ThirdPerson");
		m_skeleton.Init();
	}

	virtual void Update(float frameTime) override
	{
		DrawAxis();
		m_skeleton.Update(frameTime);
		m_skeleton.Draw();
	}

	void DrawAxis()
	{
		// X axis
		DrawLine(50, 0, 0, 75, 0, 0, 1, 0, 0);
		// Y axis
		DrawLine(50, 0, 0, 50, -25, 0, 0, 1, 0);
		// Z axis
		DrawLine(50, 0, 0, 50, 0, 25, 0, 0, 1);
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

