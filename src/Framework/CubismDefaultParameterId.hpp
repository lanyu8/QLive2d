/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "CubismFramework.hpp"

/**
 * @brief パラメータIDのデフォルト値を保持する定数<br>
 *         デフォルト値の仕様は以下のマニュアルに基づく<br>
 *         https://docs.live2d.com/cubism-editor-manual/standard-parametor-list/
 */

//--------- LIVE2D NAMESPACE ------------
namespace Live2D
{
    namespace Cubism::Framework::DefaultParameterId
    {
        // パーツID
        const inline QString HitAreaPrefix = "HitArea";
        const inline QString HitAreaHead = "Head";
        const inline QString HitAreaBody = "Body";
        const inline QString PartsIdCore = "Parts01Core";
        const inline QString PartsArmPrefix = "Parts01Arm_";
        const inline QString PartsArmLPrefix = "Parts01ArmL_";
        const inline QString PartsArmRPrefix = "Parts01ArmR_";

        // パラ inline QString
        const inline QString ParamAngleX = "ParamAngleX";
        const inline QString ParamAngleY = "ParamAngleY";
        const inline QString ParamAngleZ = "ParamAngleZ";
        const inline QString ParamEyeLOpen = "ParamEyeLOpen";
        const inline QString ParamEyeLSmile = "ParamEyeLSmile";
        const inline QString ParamEyeROpen = "ParamEyeROpen";
        const inline QString ParamEyeRSmile = "ParamEyeRSmile";
        const inline QString ParamEyeBallX = "ParamEyeBallX";
        const inline QString ParamEyeBallY = "ParamEyeBallY";
        const inline QString ParamEyeBallForm = "ParamEyeBallForm";
        const inline QString ParamBrowLY = "ParamBrowLY";
        const inline QString ParamBrowRY = "ParamBrowRY";
        const inline QString ParamBrowLX = "ParamBrowLX";
        const inline QString ParamBrowRX = "ParamBrowRX";
        const inline QString ParamBrowLAngle = "ParamBrowLAngle";
        const inline QString ParamBrowRAngle = "ParamBrowRAngle";
        const inline QString ParamBrowLForm = "ParamBrowLForm";
        const inline QString ParamBrowRForm = "ParamBrowRForm";
        const inline QString ParamMouthForm = "ParamMouthForm";
        const inline QString ParamMouthOpenY = "ParamMouthOpenY";
        const inline QString ParamCheek = "ParamCheek";
        const inline QString ParamBodyAngleX = "ParamBodyAngleX";
        const inline QString ParamBodyAngleY = "ParamBodyAngleY";
        const inline QString ParamBodyAngleZ = "ParamBodyAngleZ";
        const inline QString ParamBreath = "ParamBreath";
        const inline QString ParamArmLA = "ParamArmLA";
        const inline QString ParamArmRA = "ParamArmRA";
        const inline QString ParamArmLB = "ParamArmLB";
        const inline QString ParamArmRB = "ParamArmRB";
        const inline QString ParamHandL = "ParamHandL";
        const inline QString ParamHandR = "ParamHandR";
        const inline QString ParamHairFront = "ParamHairFront";
        const inline QString ParamHairSide = "ParamHairSide";
        const inline QString ParamHairBack = "ParamHairBack";
        const inline QString ParamHairFluffy = "ParamHairFluffy";
        const inline QString ParamShoulderY = "ParamShoulderY";
        const inline QString ParamBustX = "ParamBustX";
        const inline QString ParamBustY = "ParamBustY";
        const inline QString ParamBaseX = "ParamBaseX";
        const inline QString ParamBaseY = "ParamBaseY";
        const inline QString ParamNONE = "NONE:";
    } // namespace Cubism::Framework::DefaultParameterId
} // namespace Live2D
