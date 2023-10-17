#pragma once
class WindowMgr
{
private:
    WindowMgr() {}
    ~WindowMgr() {}
public:
    static WindowMgr* GetInst()
    {
        static WindowMgr Inst;
        return &Inst;
    }
private:
    RenderWindow m_window;
public:
    RenderWindow& GetWindow() { return m_window; }

};