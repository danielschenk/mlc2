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

#include "NetworkTask.h"
#include "SystemSettingsModel.h"

#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

NetworkTask::NetworkTask(const SystemSettingsModel &systemSettingsModel,
                         uint32_t stackSize,
                         UBaseType_t priority)
    : BaseTask()
    , m_systemSettingsModel(systemSettingsModel)
{
    m_systemSettingsModelSubscription = m_systemSettingsModel.subscribe(
            [this](){
                xTaskNotifyGive(getTaskHandle());
    });

    start("network", stackSize, priority);
}

NetworkTask::~NetworkTask()
{
    m_systemSettingsModel.unsubscribe(m_systemSettingsModelSubscription);
}

void NetworkTask::run()
{
    // TODO scan & try connect to known network before enabling AP

    std::string apSsid(m_systemSettingsModel.getWifiAPSsid());
    if(!apSsid.empty())
    {
        WiFi.softAPConfig({192, 168, 1, 1}, {192, 168, 1, 1}, {255, 255, 255, 0});
        WiFi.softAP(apSsid.c_str(), m_systemSettingsModel.getWifiAPPassword().c_str());
    }

    // Wait for event
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
}
