/* 
 * File:   Message.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 03:52 PM
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

enum MessageType{
    MEMORY_REQUEST_MEMORY_READ,
    MEMORY_REQUEST_MEMORY_WRITE
};

class Message{
    private:
        MessageType messageType;
    public:
        Message(MessageType type):messageType(type){}; 
        MessageType getMessageType() { return messageType; };
};

#endif	/* MESSAGE_H */

