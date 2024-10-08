#ifndef ZIPUTILS_H
#define ZIPUTILS_H

#include "trionmetahubutils_global.h"
#include <QByteArray>
#include <QString>
#include <QStringList>

namespace ZipUtils {

bool unzip(const QString &zip, const QString &dir, QStringList &files,
                                    bool checkConsistency = true);

bool zip(const QString &zip, const QStringList &files);

bool decodeGzip(const QByteArray &bytesIn, QByteArray &bytesOut);

bool decodeGzip(const char *bytesIn, std::size_t size,
                                         QByteArray &bytesOut);

bool encodeGzip(const QByteArray &bytesIn, QByteArray &bytesOut);

const QStringList files(const QString &zip);

};// namespace ZipUtils


#endif//ZIPUTILS_H