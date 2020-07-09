/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismMotionManager.hpp"

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            CubismMotionManager::CubismMotionManager() : _currentPriority(0), _reservePriority(0)
            {
            }

            CubismMotionManager::~CubismMotionManager()
            {
            }

            int CubismMotionManager::GetCurrentPriority() const
            {
                return _currentPriority;
            }

            int CubismMotionManager::GetReservePriority() const
            {
                return _reservePriority;
            }

            void CubismMotionManager::SetReservePriority(int val)
            {
                _reservePriority = val;
            }

            CubismMotionQueueEntryHandle CubismMotionManager::StartMotionPriority(ACubismMotion *motion, bool autoDelete, int priority)
            {
                if (priority == _reservePriority)
                {
                    _reservePriority = 0; // 予約を解除
                }

                _currentPriority = priority; // 再生中モーションの優先度を設定

                return CubismMotionQueueManager::StartMotion(motion, autoDelete, _userTimeSeconds);
            }

            bool CubismMotionManager::UpdateMotion(CubismModel *model, csmFloat32 deltaTimeSeconds)
            {
                _userTimeSeconds += deltaTimeSeconds;

                const bool updated = CubismMotionQueueManager::DoUpdateMotion(model, _userTimeSeconds);

                if (IsFinished())
                {
                    _currentPriority = 0; // 再生中モーションの優先度を解除
                }

                return updated;
            }

            bool CubismMotionManager::ReserveMotion(int priority)
            {
                if ((priority <= _reservePriority) || (priority <= _currentPriority))
                {
                    return false;
                }

                _reservePriority = priority;

                return true;
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
