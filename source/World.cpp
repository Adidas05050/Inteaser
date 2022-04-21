#include "World.h"

World::World()
{
	m_tick = 0.1;
	m_time = 6.f;
}

void World::OnFrame()
{
	if (m_time > 20)
		m_tick = -m_tick;
	else if (m_time < 2)
		m_tick = -m_tick;
	m_time += m_tick;
}
