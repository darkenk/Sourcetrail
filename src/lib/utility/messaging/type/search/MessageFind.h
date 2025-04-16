#ifndef MESSAGE_FIND_H
#define MESSAGE_FIND_H

#include "Message.h"
#include "TabIds.h"

class MessageFind: public Message<MessageFind>
{
public:
	MessageFind(bool fulltext = false): findFulltext(fulltext)
	{
		setSchedulerId(TabIds::currentTab());
	}

	static const std::string getStaticType()
	{
		return "MessageFind";
	}

	bool findFulltext;
};

#endif	  // MESSAGE_FIND_H
