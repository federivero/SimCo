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

unsigned long Message::getOriginDeviceId(){
    return originDeviceId;
}

unsigned long Message::getDestinationDeviceId(){
    return destinationDeviceId;
}

void Message::setOriginDeviceId(unsigned long id){
    this->originDeviceId = id;
}

void Message::setDestinationDeviceId(unsigned long id){
    this->destinationDeviceId = id;
}



Message::~Message(){
    
}

/* InvalidateMessage */

InvalidateMessage::InvalidateMessage(unsigned int address, MessageType type):Message(type){ 
    invalidateAddress = address;
}

void InvalidateMessage::setInvalidateAddress(unsigned int address){
    invalidateAddress = address;
}

unsigned int InvalidateMessage::getInvalidateAddress(){
    return invalidateAddress;
}


