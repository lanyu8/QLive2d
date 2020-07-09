/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismModelMatrix.hpp"

#include <QString>

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            CubismModelMatrix::CubismModelMatrix() : _width(0.0f), _height(0.0f)
            {
            }

            CubismModelMatrix::CubismModelMatrix(csmFloat32 w, csmFloat32 h)
            {
                _width = w;
                _height = h;

                SetHeight(1.0f);
            }

            CubismModelMatrix::~CubismModelMatrix()
            {
            }

            void CubismModelMatrix::SetCenterPosition(csmFloat32 x, csmFloat32 y)
            {
                CenterX(x);
                CenterY(y);
            }

            void CubismModelMatrix::Bottom(csmFloat32 y)
            {
                const csmFloat32 h = _height * GetScaleY();
                TranslateY(y - h);
            }

            void CubismModelMatrix::CenterY(csmFloat32 y)
            {
                const csmFloat32 h = _height * GetScaleY();
                TranslateY(y - (h / 2.0f));
            }

            void CubismModelMatrix::Right(csmFloat32 x)
            {
                const csmFloat32 w = _width * GetScaleX();
                TranslateX(x - w);
            }

            void CubismModelMatrix::CenterX(csmFloat32 x)
            {
                const csmFloat32 w = _width * GetScaleX();
                TranslateX(x - (w / 2.0f));
            }

            void CubismModelMatrix::SetWidth(csmFloat32 w)
            {
                const csmFloat32 scaleX = w / _width;
                const csmFloat32 scaleY = scaleX;
                Scale(scaleX, scaleY);
            }

            void CubismModelMatrix::SetHeight(csmFloat32 h)
            {
                const csmFloat32 scaleX = h / _height;
                const csmFloat32 scaleY = scaleX;
                Scale(scaleX, scaleY);
            }

            void CubismModelMatrix::SetupFromLayout(QMap<QString, csmFloat32> &layout)
            {
                const QString &KeyWidth = "width";
                const QString &KeyHeight = "height";
                const QString &KeyX = "x";
                const QString &KeyY = "y";
                const QString &KeyCenterX = "center_x";
                const QString &KeyCenterY = "center_y";
                const QString &KeyTop = "top";
                const QString &KeyBottom = "bottom";
                const QString &KeyLeft = "left";
                const QString &KeyRight = "right";

                for (auto ite = layout.begin(); ite != layout.end(); ++ite)
                {
                    const QString key = ite.key();
                    const csmFloat32 value = ite.value();

                    if (key == KeyWidth)
                    {
                        SetWidth(value);
                    }
                    else if (key == KeyHeight)
                    {
                        SetHeight(value);
                    }
                }

                for (auto ite = layout.begin(); ite != layout.end(); ++ite)
                {
                    const QString key = ite.key();
                    const csmFloat32 value = ite.value();

                    if (key == KeyX)
                    {
                        SetX(value);
                    }
                    else if (key == KeyY)
                    {
                        SetY(value);
                    }
                    else if (key == KeyCenterX)
                    {
                        CenterX(value);
                    }
                    else if (key == KeyCenterY)
                    {
                        CenterY(value);
                    }
                    else if (key == KeyTop)
                    {
                        Top(value);
                    }
                    else if (key == KeyBottom)
                    {
                        Bottom(value);
                    }
                    else if (key == KeyLeft)
                    {
                        Left(value);
                    }
                    else if (key == KeyRight)
                    {
                        Right(value);
                    }
                }
            }

            void CubismModelMatrix::SetPosition(csmFloat32 x, csmFloat32 y)
            {
                Translate(x, y);
            }

            void CubismModelMatrix::Top(csmFloat32 y)
            {
                SetY(y);
            }

            void CubismModelMatrix::Left(csmFloat32 x)
            {
                SetX(x);
            }

            void CubismModelMatrix::SetX(csmFloat32 x)
            {
                TranslateX(x);
            }

            void CubismModelMatrix::SetY(csmFloat32 y)
            {
                TranslateY(y);
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
