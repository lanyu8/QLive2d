#ifndef CONFIG_H
#define CONFIG_H
#include <CubismFramework.hpp>
#include <iostream>

inline const QString ResourcesPath = "Resources/";
inline const QString ModelDir = "Haru";
inline const QString MotionGroupIdle = "Idle";
//
inline const int ModelDirSize = sizeof(ModelDir) / sizeof(QString &);
inline const int PriorityNone = 0;
inline const int PriorityIdle = 1;
inline const int PriorityNormal = 2;
inline const int PriorityForce = 3;
//
inline const Csm::CubismFramework::Option::LogLevel CubismLoggingLevel = Csm::CubismFramework::Option::LogLevel_Verbose;

#endif
