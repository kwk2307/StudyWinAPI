#pragma once

struct Event {
	EventType eType;
	DWORD_PTR WParam;
	DWORD_PTR LParam;
};

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<Event> m_vEvent;
public:
	void AddEvent(Event _event) {m_vEvent.push_back(_event);}
	void update();
};

