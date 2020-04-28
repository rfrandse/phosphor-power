/**
 * Copyright © 2020 IBM Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "action_environment.hpp"
#include "i2c_action.hpp"
#include "i2c_interface.hpp"
#include "pmbus_read_sensor_action.hpp"
#include "pmbus_utils.hpp"

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>

#include <gtest/gtest.h>

using namespace phosphor::power::regulators;

TEST(PMBusReadSensorActionTests, Constructor)
{
    // Test where works: exponent value is specified
    try
    {
        pmbus_utils::SensorValueType type{pmbus_utils::SensorValueType::iout};
        uint8_t command = 0x8C;
        pmbus_utils::SensorDataFormat format{
            pmbus_utils::SensorDataFormat::linear_16};
        std::optional<int8_t> exponent{-8};
        PMBusReadSensorAction action{type, command, format, exponent};
        EXPECT_EQ(action.getType(), pmbus_utils::SensorValueType::iout);
        EXPECT_EQ(action.getCommand(), 0x8C);
        EXPECT_EQ(action.getFormat(), pmbus_utils::SensorDataFormat::linear_16);
        EXPECT_EQ(action.getExponent().has_value(), true);
        EXPECT_EQ(action.getExponent().value(), -8);
    }
    catch (...)
    {
        ADD_FAILURE() << "Should not have caught exception.";
    }

    // Test where works: exponent value is not specified
    try
    {
        pmbus_utils::SensorValueType type{pmbus_utils::SensorValueType::iout};
        uint8_t command = 0x8C;
        pmbus_utils::SensorDataFormat format{
            pmbus_utils::SensorDataFormat::linear_11};
        std::optional<int8_t> exponent{};
        PMBusReadSensorAction action{type, command, format, exponent};
        EXPECT_EQ(action.getType(), pmbus_utils::SensorValueType::iout);
        EXPECT_EQ(action.getCommand(), 0x8C);
        EXPECT_EQ(action.getFormat(), pmbus_utils::SensorDataFormat::linear_11);
        EXPECT_EQ(action.getExponent().has_value(), false);
    }
    catch (...)
    {
        ADD_FAILURE() << "Should not have caught exception.";
    }
}

TEST(PMBusReadSensorActionTests, Execute)
{
    // TODO: Not implemented yet
}

TEST(PMBusReadSensorActionTests, GetCommand)
{
    pmbus_utils::SensorValueType type{pmbus_utils::SensorValueType::iout};
    uint8_t command = 0x8C;
    pmbus_utils::SensorDataFormat format{
        pmbus_utils::SensorDataFormat::linear_16};
    std::optional<int8_t> exponent{-8};
    PMBusReadSensorAction action{type, command, format, exponent};
    EXPECT_EQ(action.getCommand(), 0x8C);
}

TEST(PMBusReadSensorActionTests, GetExponent)
{
    pmbus_utils::SensorValueType type{pmbus_utils::SensorValueType::iout};
    uint8_t command = 0x8C;
    pmbus_utils::SensorDataFormat format{
        pmbus_utils::SensorDataFormat::linear_16};

    // Exponent value is specified
    {
        std::optional<int8_t> exponent{-9};
        PMBusReadSensorAction action{type, command, format, exponent};
        EXPECT_EQ(action.getExponent().has_value(), true);
        EXPECT_EQ(action.getExponent().value(), -9);
    }

    // Exponent value is not specified
    {
        std::optional<int8_t> exponent{};
        PMBusReadSensorAction action{type, command, format, exponent};
        EXPECT_EQ(action.getExponent().has_value(), false);
    }
}

TEST(PMBusReadSensorActionTests, GetFormat)
{
    pmbus_utils::SensorValueType type{pmbus_utils::SensorValueType::iout};
    uint8_t command = 0x8C;
    pmbus_utils::SensorDataFormat format{
        pmbus_utils::SensorDataFormat::linear_16};
    std::optional<int8_t> exponent{-8};
    PMBusReadSensorAction action{type, command, format, exponent};
    EXPECT_EQ(action.getFormat(), pmbus_utils::SensorDataFormat::linear_16);
}

TEST(PMBusReadSensorActionTests, GetType)
{
    pmbus_utils::SensorValueType type{pmbus_utils::SensorValueType::pout};
    uint8_t command = 0x8C;
    pmbus_utils::SensorDataFormat format{
        pmbus_utils::SensorDataFormat::linear_16};
    std::optional<int8_t> exponent{-8};
    PMBusReadSensorAction action{type, command, format, exponent};
    EXPECT_EQ(action.getType(), pmbus_utils::SensorValueType::pout);
}

TEST(PMBusReadSensorActionTests, ToString)
{
    // Test where exponent value is specified
    {
        pmbus_utils::SensorValueType type{
            pmbus_utils::SensorValueType::temperature_peak};
        uint8_t command = 0x8C;
        pmbus_utils::SensorDataFormat format{
            pmbus_utils::SensorDataFormat::linear_16};
        std::optional<int8_t> exponent{-8};
        PMBusReadSensorAction action{type, command, format, exponent};
        EXPECT_EQ(action.toString(), "pmbus_read_sensor: { type: "
                                     "temperature_peak, command: 0x8C, format: "
                                     "linear_16, exponent: -8 }");
    }

    // Test where exponent value is not specified
    {
        pmbus_utils::SensorValueType type{pmbus_utils::SensorValueType::vout};
        uint8_t command = 0x8C;
        pmbus_utils::SensorDataFormat format{
            pmbus_utils::SensorDataFormat::linear_11};
        std::optional<int8_t> exponent{};
        PMBusReadSensorAction action{type, command, format, exponent};
        EXPECT_EQ(action.toString(), "pmbus_read_sensor: { type: vout, "
                                     "command: 0x8C, format: linear_11 }");
    }
}