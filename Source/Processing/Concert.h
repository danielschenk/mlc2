/**
 * @file
 * @copyright (c) Daniel Schenk, 2017
 * This file is part of MLC2.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @brief Class which represents a concert.
 */

#ifndef PROCESSING_CONCERT_H_
#define PROCESSING_CONCERT_H_

#include <list>
#include <cstdint>

#include "Interfaces/IJsonConvertible.h"
#include "Interfaces/ProcessingTypes.h"
#include "Patch.h"

class IMidiInput;
class IProcessingBlockFactory;

/**
 * Class which represents a concert.
 *
 * A concert is a collection of patches, together with some settings which are typically constant
 * throughout a gig, like MIDI channels to listen to and the note-to-light mapping.
 */
class Concert
    : public IJsonConvertible
{
public:
    /**
     * Constructor.
     *
     * @param[in]   rMidiInput              Reference to the MIDI input.
     * @param[in]   rProcessingBlockFactory Reference to the processing block factory.
     */
    Concert(IMidiInput& rMidiInput, IProcessingBlockFactory& rProcessingBlockFactory);

    /**
     * Destructor.
     */
    virtual ~Concert();

    // Prevent implicit constructor, copy constructor and assignment operator.
    Concert() = delete;
    Concert(const Concert&) = delete;
    Concert& operator =(const Concert&) = delete;

    // IJsonConvertible implementation
    virtual json convertToJson() const;
    virtual void convertFromJson(json json);

    bool isListeningToProgramChange() const;
    void setListeningToProgramChange(bool listeningToProgramChange);
    Processing::TNoteToLightMap getNoteToLightMap() const;
    void setNoteToLightMap(Processing::TNoteToLightMap noteToLightMap);
    uint8_t getProgramChangeChannel() const;
    void setProgramChangeChannel(uint8_t programChangeChannel);

private:
    /** The note-to-light mapping. */
    Processing::TNoteToLightMap m_noteToLightMap;

    /** The collection of patches. */
    std::list<Patch> m_patches;

    /** Whether program changes should be able to change the patch. */
    bool m_listeningToProgramChange;

    /** The channel to listen to for program changes. */
    uint8_t m_programChangeChannel;

    /** Reference to the MIDI input. */
    IMidiInput& m_rMidiInput;

    /** Reference to the processing block factory. */
    IProcessingBlockFactory& m_rProcessingBlockFactory;

    // TODO add scheduler
};

#endif /* PROCESSING_CONCERT_H_ */