#pragma once
#include <string>
class RenderContext
{
public:
	bool press_list[256] = {};
	void reset()
	{
		memset(press_list, 0, sizeof(press_list));
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