/**
 * @file
 *
 * MIT License
 *
 * @copyright (c) 2019 Daniel Schenk <danielschenk@users.noreply.github.com>
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
 */

#include "../SystemSettingsModel.h"

#include <gtest/gtest.h>

class SystemSettingsModelTest : public testing::Test
{
public:
    SystemSettingsModelTest() = default;

    /** The unit under test */
    SystemSettingsModel m_model;
};

TEST_F(SystemSettingsModelTest, defaults)
{
    EXPECT_EQ("PianoLeds", m_model.getWifiStationSsid());
    EXPECT_EQ("LedsFlashSomeNotes", m_model.getWifiStationPassword());
}

TEST_F(SystemSettingsModelTest, wifiStationSsid)
{
    bool observerCalled = false;
    m_model.subscribe([&](){observerCalled = true;});

    std::string val("foo");
    m_model.setWifiStationSsid(val);
    EXPECT_EQ(val, m_model.getWifiStationSsid());

    EXPECT_TRUE(observerCalled);
}

TEST_F(SystemSettingsModelTest, wifiStationPassword)
{
    bool observerCalled = false;
    m_model.subscribe([&](){observerCalled = true;});

    std::string val("foo");
    m_model.setWifiStationPassword(val);
    EXPECT_EQ(val, m_model.getWifiStationPassword());

    EXPECT_TRUE(observerCalled);
}
