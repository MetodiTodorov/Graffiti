#pragma once
///////////////////////////////////////////////////////////////////////////////
class Message;

///////////////////////////////////////////////////////////////////////////////
struct MsgReceiver
{
	enum EPriority
	{
		VERY_LOW,
		LOW,
		MEDIUM,
		HIGH,
		VERY_HIGH
	};

	const EPriority Priority;

	MsgReceiver(EPriority p = LOW) : Priority(p) {}
	virtual ~MsgReceiver() {}

	virtual void OnMsgReceived(const Message&) = 0;
};

///////////////////////////////////////////////////////////////////////////////
inline bool ReceiversCompare(const MsgReceiver* a, const MsgReceiver* b)
{
	return a->Priority > b->Priority;
}

///////////////////////////////////////////////////////////////////////////////