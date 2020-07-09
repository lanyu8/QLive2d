/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismMotionQueueManager.hpp"

#include "CubismFramework.hpp"
#include "CubismMotionQueueEntry.hpp"

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            const CubismMotionQueueEntryHandle InvalidMotionQueueEntryHandleValue = reinterpret_cast<CubismMotionQueueEntryHandle *>(-1);

            CubismMotionQueueManager::CubismMotionQueueManager() : _userTimeSeconds(0.0f), _eventCallback(NULL), _eventCustomData(NULL)
            {
            }

            CubismMotionQueueManager::~CubismMotionQueueManager()
            {
                for (auto i = 0; i < _motions.size(); ++i)
                {
                    if (_motions[i])
                    {
                        CSM_DELETE(_motions[i]);
                    }
                }
            }

            CubismMotionQueueEntryHandle CubismMotionQueueManager::StartMotion(ACubismMotion *motion, bool autoDelete,
                                                                               csmFloat32 userTimeSeconds)
            {
                if (motion == NULL)
                {
                    return InvalidMotionQueueEntryHandleValue;
                }

                CubismMotionQueueEntry *motionQueueEntry = NULL;

                // 既にモーションがあれば終了フラグを立てる
                for (auto i = 0; i < _motions.size(); ++i)
                {
                    motionQueueEntry = _motions.at(i);
                    if (motionQueueEntry == NULL)
                    {
                        continue;
                    }

                    motionQueueEntry->StartFadeout(motionQueueEntry->_motion->GetFadeOutTime(),
                                                   userTimeSeconds); //フェードアウトを開始し終了する
                }

                motionQueueEntry = CSM_NEW CubismMotionQueueEntry(); // 終了時に破棄する
                motionQueueEntry->_autoDelete = autoDelete;
                motionQueueEntry->_motion = motion;

                _motions.append(motionQueueEntry);

                return motionQueueEntry->_motionQueueEntryHandle;
            }

            bool CubismMotionQueueManager::DoUpdateMotion(CubismModel *model, csmFloat32 userTimeSeconds)
            {
                bool updated = false;

                // ------- 処理を行う --------
                // 既にモーションがあれば終了フラグを立てる

                for (QVector<CubismMotionQueueEntry *>::iterator ite = _motions.begin(); ite != _motions.end();)
                {
                    CubismMotionQueueEntry *motionQueueEntry = *ite;

                    if (motionQueueEntry == NULL)
                    {
                        ite = _motions.erase(ite); // 削除
                        continue;
                    }

                    ACubismMotion *motion = motionQueueEntry->_motion;

                    if (motion == NULL)
                    {
                        CSM_DELETE(motionQueueEntry);
                        ite = _motions.erase(ite); // 削除

                        continue;
                    }

                    // ------ 値を反映する ------
                    motion->UpdateParameters(model, motionQueueEntry, userTimeSeconds);
                    updated = true;

                    // ------ ユーザトリガーイベントを検査する ----
                    const QVector<const QString *> &firedList =
                        motion->GetFiredEvent(motionQueueEntry->GetLastCheckEventTime() - motionQueueEntry->GetStartTime(),
                                              userTimeSeconds - motionQueueEntry->GetStartTime());

                    for (auto i = 0; i < firedList.size(); ++i)
                    {
                        _eventCallback(this, *(firedList[i]), _eventCustomData);
                    }

                    motionQueueEntry->SetLastCheckEventTime(userTimeSeconds);

                    // ----- 終了済みの処理があれば削除する ------
                    if (motionQueueEntry->IsFinished())
                    {
                        CSM_DELETE(motionQueueEntry);
                        ite = _motions.erase(ite); // 削除
                    }
                    else
                    {
                        ++ite;
                    }
                }

                return updated;
            }

            CubismMotionQueueEntry *CubismMotionQueueManager::GetCubismMotionQueueEntry(CubismMotionQueueEntryHandle motionQueueEntryNumber)
            {
                //------- 処理を行う --------
                //既にモーションがあれば終了フラグを立てる

                for (QVector<CubismMotionQueueEntry *>::iterator ite = _motions.begin(); ite != _motions.end(); ++ite)
                {
                    CubismMotionQueueEntry *motionQueueEntry = *ite;

                    if (motionQueueEntry == NULL)
                    {
                        continue;
                    }

                    if (motionQueueEntry->_motionQueueEntryHandle == motionQueueEntryNumber)
                    {
                        return motionQueueEntry;
                    }
                }

                return NULL;
            }

            bool CubismMotionQueueManager::IsFinished()
            {
                // ------- 処理を行う --------
                // 既にモーションがあれば終了フラグを立てる

                for (QVector<CubismMotionQueueEntry *>::iterator ite = _motions.begin(); ite != _motions.end();)
                {
                    CubismMotionQueueEntry *motionQueueEntry = *ite;

                    if (motionQueueEntry == NULL)
                    {
                        ite = _motions.erase(ite); // 削除
                        continue;
                    }

                    ACubismMotion *motion = motionQueueEntry->_motion;

                    if (motion == NULL)
                    {
                        CSM_DELETE(motionQueueEntry);
                        ite = _motions.erase(ite); // 削除
                        continue;
                    }

                    // ----- 終了済みの処理があれば削除する ------
                    if (!motionQueueEntry->IsFinished())
                    {
                        return false;
                    }
                    else
                    {
                        ++ite;
                    }
                }

                return true;
            }

            bool CubismMotionQueueManager::IsFinished(CubismMotionQueueEntryHandle motionQueueEntryNumber)
            {
                // 既にモーションがあれば終了フラグを立てる

                for (QVector<CubismMotionQueueEntry *>::iterator ite = _motions.begin(); ite != _motions.end(); ite++)
                {
                    CubismMotionQueueEntry *motionQueueEntry = *ite;

                    if (motionQueueEntry == NULL)
                    {
                        continue;
                    }

                    if (motionQueueEntry->_motionQueueEntryHandle == motionQueueEntryNumber && !motionQueueEntry->IsFinished())
                    {
                        return false;
                    }
                }

                return true;
            }

            void CubismMotionQueueManager::StopAllMotions()
            {
                // ------- 処理を行う --------
                // 既にモーションがあれば終了フラグを立てる

                for (QVector<CubismMotionQueueEntry *>::iterator ite = _motions.begin(); ite != _motions.end();)
                {
                    CubismMotionQueueEntry *motionQueueEntry = *ite;

                    if (motionQueueEntry == NULL)
                    {
                        ite = _motions.erase(ite);

                        continue;
                    }

                    // ----- 終了済みの処理があれば削除する ------
                    CSM_DELETE(motionQueueEntry);
                    ite = _motions.erase(ite); //削除
                }
            }

            void CubismMotionQueueManager::SetEventCallback(CubismMotionEventFunction callback, void *customData)
            {
                _eventCallback = callback;
                _eventCustomData = customData;
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
