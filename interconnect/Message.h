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
    MEMORY_REQUEST_MEMORY_WRITE,
    MEMORY_RESPONSE,
    CACHE_COHERENCE_INVALIDATE
};

class Message{
    private:
        MessageType messageType;
        // for tracing
        unsigned long messageId;
    public: 
        Message(MessageType type);
        MessageType getMessageType();
        unsigned long getMessageId();
};


class InvalidateMessage : public Message{
    private:
        unsigned int invalidateAddress;
    public:
        InvalidateMessage(MessageType type);
        unsigned int getInvalidateAddress();
        void setInvalidateAddress(unsigned int address);
};

#endif	/* MESSAGE_H */


