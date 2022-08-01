#pragma once
#include <string>
class Render
{
private:
	std::string m_name{};
public:
	Render(const std::string& name_utf8) {
		m_name = name_utf8;
	}
	virtual void render() = 0;
	virtual ~Render() {};
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void settingRender() {}
	std::string getName()const {
		return m_name;
	}
};