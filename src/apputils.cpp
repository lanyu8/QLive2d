#include "apputils.hpp"

#include <QFile>

bool AppUtils::readFileContent(const QString &filePath, FileContent &result)
{
    bool ok = false;
    QFile file(filePath);
    ok = file.open(QFile::ReadOnly);
    result = file.readAll();
    if (!ok)
        result.clear();
    return ok;
}
