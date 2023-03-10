#pragma once


namespace Orange
{
	enum class EventType
	{
		KeyPress, KeyRelease, KeyRepeat, Char,
		MouseButtonPress, MouseButtonRelease, Wheel, MouseMove,
		WindowClose, WindowMinimize, WindowMaximize, WindowResize
	};

	class Event
	{
	public:
		Event(){}
		virtual ~Event(){}

		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const = 0;

		template<typename E>
		const E& Cast() const;
	};

#define	EVENT_SETUP(type) \
	virtual EventType GetType() const override { return EventType::type; } \
	virtual const char* GetName() const override { return #type; } 
	
	template<typename E>
	inline const E& Event::Cast() const
	{
		return *dynamic_cast<const E*>(this);
	}
}
