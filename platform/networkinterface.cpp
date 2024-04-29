/*
获取网络相关平台化信息，例如Mac地址，IP地址
*/

#include <string>
#include <cassert>
#include <iostream>

#ifdef _WIN32

#include <Windows.h>
#include <winsock2.h>
#include <ws2ipdef.h>
#include <wincrypt.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>

static char toHexUpper(unsigned int value) { return "0123456789ABCDEF"[value & 0xF]; }

static std::string makeHwAddress(int len, unsigned char *data)
{
  const int outLen = std::max(len * 2 + (len - 1) * 1, 0);
  std::string result;
  for (int i = 0; i < len; ++i)
  {
    if (i)
      result.push_back(':');
    result.push_back(toHexUpper(data[i] / 16));
    result.push_back(toHexUpper(data[i] % 16));
  }
  return result;
}

static std::string queryMacAddress()
{
    std::string macAddress;

  IP_ADAPTER_ADDRESSES staticBuf[2];
  PIP_ADAPTER_ADDRESSES pAdapter = staticBuf;
  ULONG bufSize = sizeof(staticBuf);

  ULONG flags = GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_SKIP_DNS_SERVER | GAA_FLAG_SKIP_MULTICAST;
  ULONG retval = GetAdaptersAddresses(AF_UNSPEC, flags, NULL, pAdapter, &bufSize);
  if (retval == ERROR_BUFFER_OVERFLOW)
  {
    pAdapter = reinterpret_cast<IP_ADAPTER_ADDRESSES *>(malloc(bufSize));
    if (!pAdapter)
      return "0";

    if (GetAdaptersAddresses(AF_UNSPEC, flags, NULL, pAdapter, &bufSize) != ERROR_SUCCESS)
    {
      free(pAdapter);
      return "0";
    }
  }
  else if (retval != ERROR_SUCCESS)
  {
    return "0";
  }

  for (PIP_ADAPTER_ADDRESSES ptr = pAdapter; ptr; ptr = ptr->Next)
  {
    assert(ptr->Length >= offsetof(IP_ADAPTER_ADDRESSES, Luid));
    assert(ptr->Length >= offsetof(IP_ADAPTER_ADDRESSES, Ipv6IfIndex));

    // ip
    if (ptr->Ipv6IfIndex != 0)
      std::cout << "Ipv6IfIndex index " << ptr->Ipv6IfIndex << std::endl;
    else if (ptr->IfIndex != 0)
      std::cout << "IfIndex index " << ptr->IfIndex << std::endl;

    int mtu = std::min<int64_t>(ptr->Mtu, INT_MAX);
    std::cout << "mtu is " << mtu << std::endl;

    if (ptr->OperStatus == IfOperStatusUp)
    {
      if (ptr->PhysicalAddressLength)
        macAddress = makeHwAddress(ptr->PhysicalAddressLength, ptr->PhysicalAddress);

      break;
    }
  }
  return macAddress.empty() ? "0" : macAddress;
}

  
#else

#endif //
