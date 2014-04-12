#include "Message.h"
#include "../simulator/TraceManager.h"

Message::Message(MessageType type){
    messageType = type;
    this->messageId = TraceManager::getInstance()->getNextDynamicId();
}

MessageType Message::getMessageType() { 
    return messageType; 
}
        
unsigned long Message::getMessageId() { 
    return messageId;   
}

/* InvalidateMessage */

InvalidateMessage::InvalidateMessage(MessageType type):Message(type)
{ }

void InvalidateMessage::setInvalidateAddress(unsigned int address){
    invalidateAddress = address;
}

unsigned int InvalidateMessage::getInvalidateAddress(){
    return invalidateAddress;
}


