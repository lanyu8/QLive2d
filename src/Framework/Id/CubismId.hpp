/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once
#include <QString>

namespace Live2D::Cubism::Framework
{
    class CubismIdManager;
    struct CubismId
    {
        friend class CubismIdManager;
        const QString GetString() const;

      private:
        CubismId();
        CubismId(const QString &);
        ~CubismId();

        CubismId(const CubismId &c);
        CubismId &operator=(const CubismId &c);

        bool operator==(const CubismId &c) const;
        bool operator!=(const CubismId &c) const;

        QString _id; ///< ID名
    };

    typedef const CubismId *CubismIdHandle;

} // namespace Live2D::Cubism::Framework
