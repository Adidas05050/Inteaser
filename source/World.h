#pragma once
class World
{
public:
	World();
	float GetTime() { return m_time; }
	void OnFrame();

private:
	float m_time, m_tick;
};

