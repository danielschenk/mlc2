/**
 * @file
 *
 * MIT License
 * 
 * @copyright (c) 2017 Daniel Schenk <danielschenk@users.noreply.github.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "ProcessingBlockFactory.h"
#include "NoteRgbSource.h"
#include "EqualRangeRgbSource.h"
#include "ProcessingChain.h"
#include "Patch.h"

ProcessingBlockFactory::ProcessingBlockFactory(IMidiInput& rMidiInput,
                                               const Processing::TNoteToLightMap& rNoteToLightMap,
                                               const IRgbFunctionFactory& rRgbFunctionFactory)
    : m_rMidiInput(rMidiInput)
    , m_rNoteToLightMap(rNoteToLightMap)
    , m_rRgbFunctionFactory(rRgbFunctionFactory)
{
}

ProcessingBlockFactory::~ProcessingBlockFactory()
{
}

IProcessingBlock* ProcessingBlockFactory::createProcessingBlock(json converted) const
{
    IProcessingBlock* processingBlock = nullptr;
    if(converted.count(IJsonConvertible::c_objectTypeKey) > 0)
    {
        std::string objectType = converted[IJsonConvertible::c_objectTypeKey];
        if(objectType == IProcessingBlock::c_typeNameEqualRangeRgbSource)
        {
            processingBlock = new EqualRangeRgbSource();
        }
        else if(objectType == IProcessingBlock::c_typeNameNoteRgbSource)
        {
            processingBlock = new NoteRgbSource(m_rMidiInput, m_rNoteToLightMap, m_rRgbFunctionFactory);
        }
        else if(objectType == IProcessingBlock::c_typeNameProcessingChain)
        {
            // A processing chain needs the factory to construct its children
            processingBlock = new ProcessingChain(*this);
        }
        else if(objectType == IProcessingBlock::c_typeNamePatch)
        {
            // A patch needs the factory to construct its children
            processingBlock = createPatch();
        }

        if(processingBlock != nullptr)
        {
            processingBlock->convertFromJson(converted);
        }
    }

    return processingBlock;
}

IPatch* ProcessingBlockFactory::createPatch() const
{
    // A patch needs the factory to construct its children
    return new Patch(*this);
}

IPatch* ProcessingBlockFactory::createPatch(json converted) const
{
    IPatch* pPatch = createPatch();

    if(pPatch != nullptr)
    {
        pPatch->convertFromJson(converted);
    }

    return pPatch;
}
