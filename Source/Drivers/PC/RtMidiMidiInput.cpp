/**
 * @file
 * @copyright (c) Daniel Schenk, 2017
 * This file is part of mlc2.
 * 
 * @brief <brief description of the file>
 */

#include <cstdio>
#include <cassert>
#include <rtmidi/RtMidi.h>

#include "RtMidiMidiInput.h"

RtMidiMidiInput::RtMidiMidiInput()
    : m_pRtMidiIn(new RtMidiIn())
    , m_noteOnOffSubscribers()
{
    assert(m_pRtMidiIn != nullptr);
    m_pRtMidiIn->setCallback(&RtMidiCommonCallback, (void*)this);
}

RtMidiMidiInput::~RtMidiMidiInput()
{
    delete m_pRtMidiIn;
}

unsigned int RtMidiMidiInput::getPortCount() const
{
    return m_pRtMidiIn->getPortCount();
}

void RtMidiMidiInput::openPort(int number)
{
    m_pRtMidiIn->openPort(number);
}

void RtMidiMidiInput::subscribeNoteOnOff(IMidiInput::TNoteOnOffFunction callback)
{
    m_noteOnOffSubscribers.push_back(callback);
}

void RtMidiMidiInput::RtMidiCommonCallback(double deltatime, std::vector<unsigned char> *message, void *userData)
{
    // userData tells us the instance to call the specific callback on
    RtMidiMidiInput* pMidiInput = static_cast<RtMidiMidiInput*>(userData);
    if(pMidiInput != nullptr)
    {
        pMidiInput->RtMidiCallback(deltatime, message);
    }
}

void RtMidiMidiInput::RtMidiCallback(double deltatime, std::vector<unsigned char> *pMessage)
{
    // Get status (high nibble) and channel (low nibble) from status byte
    uint8_t status = pMessage->at(0) & 0xF0;
    uint8_t channel = pMessage->at(0) & 0x0F;

    switch(status)
    {
        case NOTE_OFF:
            for(const auto& it : m_noteOnOffSubscribers)
            {
                // Channel, pitch, velocity, note off
                it(channel, pMessage->at(1), pMessage->at(2), false);
            }
            break;
        case NOTE_ON:
            for(const auto& it : m_noteOnOffSubscribers)
            {
                // Channel, pitch, velocity, note on
                it(channel, pMessage->at(1), pMessage->at(2), true);
            }
            break;
        default:
            break;
    }
}

