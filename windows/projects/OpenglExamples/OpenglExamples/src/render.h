#pragma once
#include <string>
class RenderContext
{
public:
	bool press_list[256] = {};
	float elapsed_time{};
	bool m_move_left = {};
	bool m_move_right = {};
	bool m_move_up = {};
	bool m_move_down = {};
	void reset()
	{
		memset(press_list, 0, sizeof(press_list));
		elapsed_time = {};
		m_move_left = {};
		m_move_right = {};
		m_move_up = {};
		m_move_down = {};
	}
};
class Render
{
private:
	std::string m_name{};
public:
	RenderContext m_context{};
public:
	Render(const std::string& name_utf8) {
		m_name = name_utf8;
	}
	virtual void render() = 0;
	virtual ~Render() {};
	virtual void init() = 0;
	virtual void release() = 0;
	std::string getName()const {
		return m_name;
	}
};