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

void network()
{
    IP_ADAPTER_ADDRESSES staticBuf[2];
    PIP_ADAPTER_ADDRESSES pAdapter = staticBuf;
    ULONG bufSize = sizeof(staticBuf);

    ULONG flags = GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_SKIP_DNS_SERVER | GAA_FLAG_SKIP_MULTICAST;
    ULONG retval = GetAdaptersAddresses(AF_UNSPEC, flags, NULL, pAdapter, &bufSize);
    if (retval == ERROR_BUFFER_OVERFLOW)
    {
        pAdapter = reinterpret_cast<IP_ADAPTER_ADDRESSES *>(malloc(bufSize));
        if (pAdapter)
            return;

        if (GetAdaptersAddresses(AF_UNSPEC, flags, NULL, pAdapter, &bufSize) != ERROR_SUCCESS)
        {
            free(pAdapter);
            return;
        }
    }
    else if (retval != ERROR_SUCCESS)
    {
        return;
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
            std::cout << "ip is up and running" << std::endl;
        }
        if ((ptr->Flags & IP_ADAPTER_NO_MULTICAST) == 0)
        {
            std::cout << "can multi cast" << std::endl;
        }
        if (ptr->IfType == IF_TYPE_PPP)
        {
            std::cout << "is point to point" << std::endl;
        }

        switch (ptr->IfType)
        {
        case IF_TYPE_ETHERNET_CSMACD:
            std::cout << "IEEE 802.3 Ethernet interfaces, though on many systems other types of IEEE 802 interfaces may also be detected as Ethernet (especially Wi-Fi)." << std::endl;
            break;
        case IF_TYPE_FDDI:
            std::cout << "ANSI X3T12 Fiber Distributed Data Interface, a local area network over optical fibers." << std::endl;
            break;
        case IF_TYPE_PPP:
            break;
        case IF_TYPE_SLIP:
            break;
        case IF_TYPE_SOFTWARE_LOOPBACK:
            break;
        case IF_TYPE_IEEE80211:
            break;
        case IF_TYPE_IEEE1394:
            break;
        };
    }

#else

#endif //
