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
 */

#include <Common/Logging.h>

#include "Patch.h"
#include "Interfaces/IProcessingBlockFactory.h"

#define LOGGING_COMPONENT "Patch"

Patch::Patch(const IProcessingBlockFactory& rProcessingBlockFactory)
    : ProcessingChain(rProcessingBlockFactory)
    , m_hasBankAndProgram(false)
    , m_bank(0)
    , m_program(0)
    , m_name("Untitled Patch")
{
}

Patch::Patch(const Patch& rOther)
    : ProcessingChain(rOther.m_rProcessingBlockFactory)
{
    // Use JSON because the base doesn't implement a copy constructor.
    convertFromJson(rOther.convertToJson());
}

Patch::~Patch()
{
}

json Patch::convertToJson() const
{
    // Start with contents of base
    json converted = ProcessingChain::convertToJson();
    // Overwrite object type
    converted[IProcessingBlock::c_objectTypeKey] = std::string(IProcessingBlock::c_typeNamePatch);

    // Add items specific for Patch
    converted[c_hasBankAndProgramJsonKey] = m_hasBankAndProgram;
    converted[c_bankJsonKey] = m_bank;
    converted[c_programJsonKey] = m_program;
    converted[c_nameJsonKey] = m_name;

    return converted;
}

void Patch::convertFromJson(json converted)
{
    // Get items specific for Patch
    if(converted.count(c_hasBankAndProgramJsonKey) > 0)
    {
        m_hasBankAndProgram = converted[c_hasBankAndProgramJsonKey];
    }
    else
    {
        LOG_ERROR("convertFromJson: missing key 'hasBankAndProgram'");
    }

    if(converted.count(c_programJsonKey) > 0)
    {
        m_program = converted[c_programJsonKey];
    }
    else
    {
        LOG_ERROR("convertFromJson: missing key 'program'");
    }

    if(converted.count(c_bankJsonKey) > 0)
    {
        m_bank = converted[c_bankJsonKey];
    }
    else
    {
        LOG_ERROR("convertFromJson: missing key 'bank'");
    }

    if(converted.count(c_nameJsonKey) > 0)
    {
        m_name = converted[c_nameJsonKey];
    }
    else
    {
        LOG_ERROR("convertFromJson: missing key 'name'");
    }

    // Remove keys the base doesn't know about, to prevent warnings
    converted.erase(c_hasBankAndProgramJsonKey);
    converted.erase(c_programJsonKey);
    converted.erase(c_bankJsonKey);
    converted.erase(c_nameJsonKey);

    // Get contents of base
    ProcessingChain::convertFromJson(converted);
}

uint8_t Patch::getBank() const
{
    return m_bank;
}

void Patch::setBank(uint8_t bank)
{
    m_bank = bank;
}

bool Patch::hasBankAndProgram() const
{
    return m_hasBankAndProgram;
}

void Patch::setHasBankAndProgram(bool hasBankAndProgram)
{
    m_hasBankAndProgram = hasBankAndProgram;
}

uint8_t Patch::getProgram() const
{
    return m_program;
}

void Patch::setProgram(uint8_t program)
{
    m_program = program;
}

std::string Patch::getName() const
{
    return m_name;
}

void Patch::setName(const std::string name)
{
    m_name = name;
}
