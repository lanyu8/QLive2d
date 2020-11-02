/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once
#include "3rdparty/QJsonStruct/QJsonIO.hpp"
#include "CubismFramework.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <stdio.h>

//------------ LIVE2D NAMESPACE ------------
namespace Live2D
{
    namespace Cubism::Framework
    {
        namespace Utils
        {
            typedef QJsonObject CubismJson;
            typedef QJsonValue Value;
            class Error;
            class NullValue;

        } // namespace Utils

#define CSM_JSON_ERROR_TYPE_MISMATCH "Error:type mismatch"
#define CSM_JSON_ERROR_INDEX_OUT_OF_BOUNDS "Error:index out of bounds"
    } // namespace Cubism::Framework
} // namespace Live2D
