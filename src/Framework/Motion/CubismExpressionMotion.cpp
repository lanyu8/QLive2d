/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismExpressionMotion.hpp"

#include "Id/CubismIdManager.hpp"

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            namespace
            {
                // exp3.jsonのキーとデフォルト値
                const QString &ExpressionKeyFadeIn = "FadeInTime";
                const QString &ExpressionKeyFadeOut = "FadeOutTime";
                const QString &ExpressionKeyParameters = "Parameters";
                const QString &ExpressionKeyId = "Id";
                const QString &ExpressionKeyValue = "Value";
                const QString &ExpressionKeyBlend = "Blend";
                const QString &BlendValueAdd = "Add";
                const QString &BlendValueMultiply = "Multiply";
                const QString &BlendValueOverwrite = "Overwrite";
                const csmFloat32 DefaultFadeTime = 1.0f;
            } // namespace

            CubismExpressionMotion::CubismExpressionMotion()
            {
            }

            CubismExpressionMotion::~CubismExpressionMotion()
            {
            }

            CubismExpressionMotion *CubismExpressionMotion::Create(const QByteArray &buffer)
            {
                CubismExpressionMotion *expression = CSM_NEW CubismExpressionMotion();

                const auto &root = QJsonDocument::fromJson(buffer).object();

                expression->SetFadeInTime(root[ExpressionKeyFadeIn].toDouble(DefaultFadeTime));   // フェードイン
                expression->SetFadeOutTime(root[ExpressionKeyFadeOut].toDouble(DefaultFadeTime)); // フェードアウト

                // 各パラメータについて
                const int parameterCount = root[ExpressionKeyParameters].toArray().size();

                for (int i = 0; i < parameterCount; ++i)
                {
                    const auto param = root[ExpressionKeyParameters][i].toObject();
                    const CubismIdHandle parameterId = CubismFramework::GetIdManager()->GetId(param[ExpressionKeyId].toString()); // パラメータID
                    const csmFloat32 value = static_cast<csmFloat32>(param[ExpressionKeyValue].toVariant().toFloat());            // 値

                    // 計算方法の設定
                    ExpressionBlendType blendType;

                    if (param[ExpressionKeyBlend].isNull() || param[ExpressionKeyBlend].toString() == BlendValueAdd)
                    {
                        blendType = ExpressionBlendType_Add;
                    }
                    else if (param[ExpressionKeyBlend].toString() == BlendValueMultiply)
                    {
                        blendType = ExpressionBlendType_Multiply;
                    }
                    else if (param[ExpressionKeyBlend].toString() == BlendValueOverwrite)
                    {
                        blendType = ExpressionBlendType_Overwrite;
                    }
                    else
                    {
                        // その他 仕様にない値を設定したときは加算モードにすることで復旧
                        blendType = ExpressionBlendType_Add;
                    }

                    // 設定オブジェクトを作成してリストに追加する
                    ExpressionParameter item;

                    item.ParameterId = parameterId;
                    item.BlendType = blendType;
                    item.Value = value;

                    expression->_parameters.append(item);
                }

                // Utils::CubismJson::Delete(json); // JSONデータは不要になったら削除する

                return expression;
            }

            void CubismExpressionMotion::DoUpdateParameters(CubismModel *model, csmFloat32, csmFloat32 weight, CubismMotionQueueEntry *)
            {
                for (auto i = 0; i < _parameters.size(); ++i)
                {
                    ExpressionParameter &parameter = _parameters[i];

                    switch (parameter.BlendType)
                    {
                        case ExpressionBlendType_Add:
                        {
                            model->AddParameterValue(parameter.ParameterId, parameter.Value, weight); // 相対変化 加算
                            break;
                        }
                        case ExpressionBlendType_Multiply:
                        {
                            model->MultiplyParameterValue(parameter.ParameterId, parameter.Value, weight); // 相対変化 乗算
                            break;
                        }
                        case ExpressionBlendType_Overwrite:
                        {
                            model->SetParameterValue(parameter.ParameterId, parameter.Value, weight); // 絶対変化 上書き
                            break;
                        }
                        default:
                            // 仕様にない値を設定したときは既に加算モードになっている
                            break;
                    }
                }
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
