/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismIdManager.hpp"

#include "CubismFramework.hpp"
#include "CubismId.hpp"

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            CubismIdManager::CubismIdManager()
            {
            }

            CubismIdManager::~CubismIdManager()
            {
                for (auto i = 0; i < _ids.size(); ++i)
                {
                    CSM_DELETE_SELF(CubismId, _ids[i]);
                }
            }

            //            void CubismIdManager::RegisterIds(const QString &ids, int count)
            //            {
            //                for (int i = 0; i < count; ++i)
            //                {
            //                    RegisterId(ids[i]);
            //                }
            //            }

            //            void CubismIdManager::RegisterIds(const QVector<QString> &ids)
            //            {
            //                for (csmUint32 i = 0; i < ids.GetSize(); ++i)
            //                {
            //                    RegisterId(ids[i]);
            //                }
            //            }

            const CubismId *CubismIdManager::GetId(const QString &id)
            {
                return RegisterId(id);
            }

            bool CubismIdManager::IsExist(const QString &id) const
            {
                return (FindId(id) != NULL);
            }

            const CubismId *CubismIdManager::RegisterId(const QString &id)
            {
                CubismId *result = NULL;

                if ((result = FindId(id)) != NULL)
                {
                    return result;
                }

                result = CSM_NEW CubismId(id);
                _ids.append(result);
                return result;
            }

            CubismId *CubismIdManager::FindId(const QString &id) const
            {
                for (auto i = 0; i < _ids.size(); ++i)
                {
                    if (_ids[i]->GetString() == id)
                    {
                        return _ids[i];
                    }
                }

                return NULL;
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
