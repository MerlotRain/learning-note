#include <iostream>

#include <iconv.h>
#include <string.h
#include <string>
#include <algorithm>

#include <errno.h>

/**
 * iconv是一个功能非常强大的编码转换库。
 * 在c/c++中，我们建议将所有的编码转换都使用iconv进行，并且通过对iconv封装实现编码转换
 *
 * 使用iconv，首先是需要知道当前的编码和目标编码格式的
 *
 * 这就需要我们主动在官网或者linux命令行中查询iconv支持的编码
 *
 * 然后再转换，在这里我们提供一些iconv转换的方法
 */

char *recode(const char *pszSrc, const char *pszSrcEncoding, const char *pszDstEncoding)
{
    iconv_t conv = iconv_open(pszDstEncoding, pszSrcEncoding);
    if (conv == (iconv_t)-1)
        return NULL;

    char *pszSrcBuf = const_cast<char *>(pszSrc);
    size_t nSrcLen = strlen(pszSrc);
    size_t nDstCurLen = std::max(nSrcLen, (size_t)32768);
    size_t nDstLen = nDstCurLen;
    char *pszDestination = static_cast<char *>(malloc(nDstLen + 1));
    memset(pszDestination, 0, nDstLen + 1);
    char *pszDstBuf = pszDestination;

    while (nSrcLen > 0)
    {
        size_t converted = iconv(conv, &pszSrcBuf, &nSrcLen, &pszDstBuf, &nDstLen);
        if (converted == (size_t)-1)
        {
            if (errno == EILSEQ)
            {
                if (nSrcLen == 0)
                    break;
                nSrcLen--;
                pszSrcBuf++;
                continue;
            }
            else if (errno == E2BIG)
            {
                size_t nTmp = nDstCurLen;
                nDstCurLen *= 2;
                pszDestination = static_cast<char *>(realloc(pszDestination, nDstCurLen + 1));
                pszDstBuf = pszDestination + nTmp - nDstLen;
                nDstLen += nTmp;
                continue;
            }
            else
                break;
        }
    }

    pszDestination[nDstCurLen - nDstLen] = '\0';
    iconv_close(conv);
    return pszDestination;
}

wchar_t *recode_to_wchar(const char *pszSrc, const char *pszSrcEncoding, const char *pszDstEncoding)
{
    if (strcmp(pszDstEncoding, "WCHAR_T") != 0)
        return nullptr;
    return static_cast<wchar_t *>(static_cast<void *>(recode(pszSrc, pszSrcEncoding, pszDstEncoding)));
}

char *recode_from_wchar(wchar_t *pszSrc, const char *pszSrcEncoding, const char *pszDstEncoding)
{
    // source length
    size_t nSrcLen = 0;
    while (pszSrc[nSrcLen] != 0)
        nSrcLen++;

    int nTargetCharWidth = 0;
    if (_stricmp(pszSrcEncoding, "UTF-8") == 0)
        nTargetCharWidth = 1;
    else if (_stricmp(pszSrcEncoding, "UTF-16LE") == 0 || _stricmp(pszSrcEncoding, "UTF-16") == 0)
        nTargetCharWidth = 2;
    else if (_stricmp(pszSrcEncoding, "UTF-32LE") || _stricmp(pszSrcEncoding, "UTF-32") == 0)
        nTargetCharWidth = 4;
    else
        return NULL;

    size_t nTargetLen = nSrcLen * nTargetCharWidth;
    unsigned char *pszIconvSrcBuf = static_cast<unsigned char *>(malloc((nSrcLen + 1) * nTargetCharWidth));
    memset(pszIconvSrcBuf, 0, (nSrcLen + 1) * nTargetCharWidth);

    for (unsigned int iSrc = 0; iSrc <= nSrcLen; ++iSrc)
    {
        if (nTargetCharWidth == 1)
            pszIconvSrcBuf[iSrc] = static_cast<unsigned char>(pszSrc[iSrc]);
        else if (nTargetCharWidth == 2)
            (reinterpret_cast<short *>(pszIconvSrcBuf))[iSrc] = static_cast<short>(pszSrc[iSrc]);
        else if (nTargetCharWidth == 4)
            (reinterpret_cast<int *>(pszIconvSrcBuf))[iSrc] = static_cast<int>(pszSrc[iSrc]);
    }

    iconv_t conv = iconv_open(pszDstEncoding, pszSrcEncoding);
    if (conv == (iconv_t)-1)
        return NULL;

    char *pszSrcBuf = const_cast<char *>(reinterpret_cast<char *>(pszIconvSrcBuf));
    nSrcLen *= nTargetCharWidth;
    size_t nDstCurLen = std::max(nSrcLen + 1, (size_t)32768);
    size_t nDstLen = nDstCurLen;
    char *pszDestination = static_cast<char *>(malloc(nDstCurLen));
    memset(pszDestination, 0, nDstCurLen);
    char *pszDstBuf = pszDestination;

    while (nSrcLen > 0)
    {
        const size_t converted = iconv(conv, &pszSrcBuf, &nSrcLen, &pszDstBuf, &nDstLen);
        if (converted == (size_t)-1)
        {
            if (errno == EILSEQ)
            {
                nSrcLen -= nTargetCharWidth;
                pszSrcBuf += nTargetCharWidth;
                continue;
            }
            else if (errno == E2BIG)
            {
                size_t nTmp = nDstCurLen;
                nDstCurLen *= 2;
                pszDestination = static_cast<char *>(realloc(pszDestination, nDstCurLen));
                pszDstBuf = pszDestination + nTmp - nDstLen;
                nDstLen += nDstCurLen - nTmp;
                continue;
            }
            else
                break;
        }
    }

    if (nDstLen == 0)
    {
        ++nDstCurLen;
        pszDestination =
            static_cast<char *>(realloc(pszDestination, nDstCurLen));
        ++nDstLen;
    }
    pszDestination[nDstCurLen - nDstLen] = '\0';

    iconv_close(conv);

    free(pszIconvSrcBuf);

    return pszDestination;
}

int main()
{
    std::cout << "Hello world!" << std::endl;
    // your code goes here
    return 0;
}