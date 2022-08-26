#pragma once
#include <string>
#include <cmath>
class RenderContext
{
  public:
    bool press_list[256] = {};
    float elapsed_time{};
    int m_last_x = -1;
    int m_last_y = -1;
    int m_current_x = -1;
    int m_current_y = -1;
    void reset()
    {
        *this = {};
        m_last_x = -1;
        m_last_y = -1;
        m_current_x = -1;
        m_current_y = -1;
    }

    bool isMoveLeft() const
    {
        return m_last_x >= 0 && m_current_x < m_last_x;
    }
    bool isMoveRight() const
    {
        return m_last_x >= 0 && m_current_x > m_last_x;
    }
    bool isMoveDown() const
    {
        return m_last_y >= 0 && m_current_y < m_last_y;
    }
    bool isMoveUp() const
    {
        return m_last_y >= 0 && m_current_y > m_last_y;
    }

    int xDiff() const
    {
        return std::abs(m_current_x - m_last_x);
    }

    int yDiff() const
    {
        return std::abs(m_current_y - m_last_y);
    }
};
class Render
{
  private:
    std::string m_name{};

  public:
    RenderContext m_context{};

  public:
    Render(const std::string &name_utf8)
    {
        m_name = name_utf8;
    }
    virtual void render() = 0;
    virtual ~Render(){};
    virtual void init() = 0;
    virtual void release() = 0;
    std::string getName() const
    {
        return m_name;
    }
};