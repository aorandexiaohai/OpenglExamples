#pragma once
#include <string>
class Render
{
private:
	std::string m_name{};
public:
	Render(const std::string& name) {
		m_name = name;
	}
	virtual void render() = 0;
	virtual ~Render() {};
	virtual void init() = 0;
	virtual void release() = 0;
	std::string getName()const {
		return m_name;
	}
};