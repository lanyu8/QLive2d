/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismMoc.hpp"

#include "CubismModel.hpp"

namespace Live2D
{
    namespace Cubism::Framework
    {

        CubismMoc *CubismMoc::Create(const QByteArray &buffer)
        {
            void *alignedBuffer = CSM_MALLOC_ALLIGNED(buffer.size(), Core::csmAlignofMoc);
            memcpy(alignedBuffer, buffer.data(), buffer.size());

            const auto moc = Core::csmReviveMocInPlace(alignedBuffer, buffer.size());
            if (moc)
                return CSM_NEW CubismMoc(moc);
            return nullptr;
        }

        void CubismMoc::Delete(CubismMoc *moc)
        {
            CSM_DELETE_SELF(CubismMoc, moc);
        }

        CubismMoc::CubismMoc(Core::csmMoc *moc) : _moc(moc), _modelCount(0)
        {
        }

        CubismMoc::~CubismMoc()
        {
            CSM_ASSERT(_modelCount == 0);
            CSM_FREE_ALLIGNED(_moc);
        }

        CubismModel *CubismMoc::CreateModel()
        {
            const auto modelSize = Core::csmGetSizeofModel(_moc);

            void *modelMemory = CSM_MALLOC_ALLIGNED(modelSize, Core::csmAlignofModel);
            Core::csmModel *model = Core::csmInitializeModelInPlace(_moc, modelMemory, modelSize);

            if (model)
            {
                auto cubismModel = CSM_NEW CubismModel(model);
                cubismModel->Initialize();
                ++_modelCount;
                return cubismModel;
            }

            return nullptr;
        }

        void CubismMoc::DeleteModel(CubismModel *model)
        {
            CSM_DELETE_SELF(CubismModel, model);
            --_modelCount;
        }
    } // namespace Cubism::Framework
} // namespace Live2D
