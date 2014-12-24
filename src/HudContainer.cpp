#include <pihud/HudContainer.hpp>

namespace PiH
{
    HudContainer::HudContainer(Widget *parent)
        : Widget(parent)
    {

    }
    HudContainer::~HudContainer()
    {
        clear();
    }
    void HudContainer::clear()
    {
        for(auto &widget : m_widgets)
        {
            delete widget.second;
        }
        m_widgets.clear();
    }
    void HudContainer::onEvent(const Event &e)
    {
     	for(auto &widget : m_widgets)
        {
            widget.second->onEvent(e);
        }
    }
    void HudContainer::onUpdate(float frametime)
    {
        for(auto &widget : m_widgets)
        {
            widget.second->onUpdate(frametime);
        }
    }
    void HudContainer::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        for(auto &widget : m_widgets)
        {
            widget.second->onRender(renderer, offset);
        }
    }
    void HudContainer::updateRectFromBeneath()
    {

    }
    Widget *HudContainer::getWidget(const std::string &name)
    {
        if(m_widgets.count(name))
            return m_widgets[name];
        return nullptr;
    }
    void HudContainer::addWidget(Widget *widget, std::string name)
    {
        if(m_widgets.count(name))
        {
            if(m_widgets[name] != nullptr)
            {
                delete m_widgets[name];
            }
        }
        m_widgets[name] = widget;
    }
    void HudContainer::deleteWidget(const std::string &name)
    {
        if(m_widgets.count(name))
        {
            delete m_widgets[name];
            m_widgets.erase(name);
        }
    }
}
