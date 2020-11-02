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
        const QString GetString() const
        {
            return _id;
        }

      private:
        CubismId(){};
        CubismId(const QString &str) : _id(str){};
        CubismId(const CubismId &c) : _id(c._id){};

        ~CubismId(){};

        CubismId &operator=(const CubismId &c)
        {
            if (this != &c)
                _id = c._id;
            return *this;
        }

        bool operator==(const CubismId &c) const
        {
            return (_id == c._id);
        }

        bool operator!=(const CubismId &c) const
        {
            return !(_id == c._id);
        }

        QString _id;
    };

    typedef const CubismId *CubismIdHandle;

} // namespace Live2D::Cubism::Framework
