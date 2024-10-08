#include "ziputils.h"
#include <fstream>
#include <iostream>
#include <zip.h>
#include <zlib.h>
#include <QFileInfo>
#include <QDir>

bool ZipUtils::unzip(const QString &zipFilename, const QString &dir, QStringList &files,
                     bool checkConsistency)
{
    files.clear();
    if (!QFileInfo::exists(zipFilename))
    {
        fprintf(stderr, "Error zip file does not exist: '%s'\n", zipFilename.toStdString().c_str());
        return false;
    }
    else if (zipFilename.isEmpty())
    {
        fprintf(stderr, "Error zip filename is empty\n");
        return false;
    }
    else if (!QDir(dir).exists(dir))
    {
        fprintf(stderr, "Error output dir does not exist: '%s'\n", dir.toStdString().c_str());
        return false;
    }
    else if (!QFileInfo(dir).isDir())
    {
        fprintf(stderr, "Error output dir is not a directory: '%s'\n", dir.toStdString().c_str());
        return false;
    }
    else if (!QFileInfo(dir).isWritable())
    {
        fprintf(stderr, "Error output dir is not writable: '%s'\n", dir.toStdString().c_str());
        return false;
    }
    int rc = 0;
    const QByteArray fileNamePtr = zipFilename.toUtf8();
    struct zip *z = zip_open(fileNamePtr.constData(), checkConsistency ? ZIP_CHECKCONS : 0, &rc);
    if (rc == ZIP_ER_OK && z)
    {
        const int count = zip_get_num_entries(z, ZIP_FL_UNCHANGED);
        if (count != -1)
        {
            struct zip_stat stat;
            for (int i = 0; i < count; i++)
            {
                zip_stat_index(z, i, 0, &stat);
                const size_t len = stat.size;
                struct zip_file *file = zip_fopen_index(z, i, 0);
                const std::unique_ptr<char[]> buf(new char[len]);
                if (zip_fread(file, buf.get(), len) != -1)
                {
                    const QString fileName(stat.name);
                    const QFileInfo newFile(QDir(dir), fileName);
                    if (!newFile.absoluteDir().exists())
                    {
                        if (!QDir(dir).mkpath(newFile.absolutePath()))
                            fprintf(stderr, "Failed to create a subdirectory %s/%s\n",
                                    dir.toStdString().c_str(), fileName.toStdString().c_str());
                    }
                    QFile outFile(newFile.absoluteFilePath());
                    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    {
                        fprintf(stderr, "Could not write to /%s\n", dir.toStdString().c_str(),
                                newFile.absoluteFilePath().toStdString().c_str());
                    }
                    else
                    {
                        outFile.write(buf.get(), len);
                    }
                    zip_fclose(file);
                    files.append(newFile.absoluteFilePath());
                }
                else
                {
                    zip_fclose(file);
                    fprintf(stderr, "Error reading file: '%s'\n", zip_strerror(z));
                    return false;
                }
            }
        }
        else
        {
            zip_close(z);
            fprintf(stderr, "Error getting files: '%s'\n", zip_strerror(z));
            return false;
        }
        zip_close(z);
    }
    else
    {
        fprintf(stderr, "Error opening zip archive: '%s' (Error code: %d)\n",
                z ? zip_strerror(z) : zipFilename, rc);
        return false;
    }
    return true;
}

bool ZipUtils::zip(const QString &zipFilename, const QStringList &files)
{
    if (zipFilename.isEmpty())
    {
        fprintf(stderr, "Error zip filename is empty\n");
        return false;
    }
    int rc = 0;
    const QByteArray zipFileNamePtr = zipFilename.toUtf8();
    struct zip *z = zip_open(zipFileNamePtr.constData(), ZIP_CREATE, &rc);
    if (rc == ZIP_ER_OK && z)
    {
        for (const auto &file: files)
        {
            const QFileInfo fileInfo(file);
            if (!fileInfo.exists())
            {
                fprintf(stderr, "Error input file does not exist: '%s'\n", file.toStdString().c_str());
                zip_close(z);
                return false;
            }
            const QByteArray fileNamePtr = file.toUtf8();
            zip_source *src = zip_source_file(z, fileNamePtr.constData(), 0, 0);
            if (src)
            {
                const QByteArray fileInfoPtr = fileInfo.fileName().toUtf8();
#if LIBZIP_VERSION_MAJOR < 1
                rc = (int) zip_add(z, fileInfoPtr.constData(), src);
#else
                rc = (int) zip_file_add(z, fileInfoPtr.constData(), src, 0);
#endif
                if (rc == -1)
                {
                    fprintf(stderr, "Error adding file '%s': %s\n",
                            file.toStdString().c_str(), zip_strerror(z));
                    zip_close(z);
                    return false;
                }
            }
            else
            {
                fprintf(stderr, "Error creating data source '%s': %s\n", file.toStdString().c_str(),
                        zip_strerror(z));
                zip_close(z);
                return false;
            }
        }
        zip_close(z);
    }
    else
    {
        fprintf(stderr, "Error creating zip archive '%s': %s\n", zipFilename.toStdString().c_str(),
                zip_strerror(z));
        return false;
    }
    return true;
}

bool ZipUtils::decodeGzip(const QByteArray &bytesIn, QByteArray &bytesOut)
{
    return ZipUtils::decodeGzip(bytesIn.constData(), bytesIn.count(), bytesOut);
}

bool ZipUtils::decodeGzip(const char *bytesIn, std::size_t size, QByteArray &bytesOut)
{
    unsigned char *bytesInPtr = reinterpret_cast<unsigned char *>(const_cast<char *>(bytesIn));
    uint bytesInLeft = static_cast<uint>(size);
    const uint CHUNK = 16384;
    unsigned char out[CHUNK];
    const int DEC_MAGIC_NUM_FOR_GZIP = 16;
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    int ret = inflateInit2(&strm, MAX_WBITS + DEC_MAGIC_NUM_FOR_GZIP);
    if (ret != Z_OK) return false;
    while (ret != Z_STREAM_END)
    {
        const uint bytesToProcess = std::min(CHUNK, bytesInLeft);
        strm.next_in = bytesInPtr;
        strm.avail_in = bytesToProcess;
        bytesInPtr += bytesToProcess;
        bytesInLeft -= bytesToProcess;
        if (bytesToProcess == 0)
            break;
        do
        {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            Q_ASSERT(ret != Z_STREAM_ERROR);
            if (ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR)
            {
                inflateEnd(&strm);
                return false;
            }
            const unsigned have = CHUNK - strm.avail_out;
            bytesOut.append(QByteArray::fromRawData(reinterpret_cast<const char *>(out),
                                                    static_cast<int>(have)));
        } while (strm.avail_out == 0);
    }
    inflateEnd(&strm);
    return ret == Z_STREAM_END;
}

bool ZipUtils::encodeGzip(const QByteArray &bytesIn, QByteArray &bytesOut)
{
    unsigned char *bytesInPtr =
            reinterpret_cast<unsigned char *>(const_cast<char *>(bytesIn.constData()));
    const uint bytesInLeft = static_cast<uint>(bytesIn.count());
    const uint CHUNK = 16384;
    unsigned char out[CHUNK];
    const int DEC_MAGIC_NUM_FOR_GZIP = 16;
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    int ret = deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                           MAX_WBITS + DEC_MAGIC_NUM_FOR_GZIP, 8, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK) return false;
    strm.avail_in = bytesInLeft;
    strm.next_in = bytesInPtr;
    do
    {
        strm.avail_out = CHUNK;
        strm.next_out = out;
        ret = deflate(&strm, Z_FINISH);
        Q_ASSERT(ret != Z_STREAM_ERROR);
        const unsigned have = CHUNK - strm.avail_out;
        bytesOut.append(QByteArray::fromRawData(reinterpret_cast<const char *>(out),
                                                static_cast<int>(have)));
    } while (strm.avail_out == 0);
    Q_ASSERT(ret == Z_STREAM_END);
    deflateEnd(&strm);
    return true;
}

const QStringList ZipUtils::files(const QString &zip)
{
    if (zip.isEmpty() && !QFileInfo::exists(zip))
    {
        return QStringList();
    }
    QStringList files;
    int rc = 0;
    const QByteArray fileNamePtr = zip.toUtf8();
    struct zip *z = zip_open(fileNamePtr.constData(), 0, &rc);
    if (rc == ZIP_ER_OK && z)
    {
        const int count = zip_get_num_entries(z, ZIP_FL_UNCHANGED);
        if (count != -1)
        {
            struct zip_stat stat;
            for (int i = 0; i < count; i++)
            {
                zip_stat_index(z, i, 0, &stat);
                files << QString(stat.name);
            }
        }
        zip_close(z);
    }
    return files;
}