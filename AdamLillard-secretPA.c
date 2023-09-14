#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: Enter IP Address i.e 10.0.0.5 then the subnet mask i.e 24 with a space in between\n");
        return 1;
    }
    
    char *ipNum = argv[1];
    int subnetBits = atoi(argv[2]);
    int availableAddr;
    
    if (subnetBits == 32) {
        availableAddr = 1;
    } else {
        availableAddr = (1 << (32 - subnetBits)) - 2;
    }

    if (subnetBits < 0 || subnetBits > 32) {
        printf("Invalid subnet mask bits (must be between 0 and 32)\n");
        return 1;
    }

    struct in_addr ip_addr, mask_addr, network_addr, first_addr, last_addr, broadcast_addr;

    if (inet_pton(AF_INET, ipNum, &ip_addr) == 0) {
        printf("Invalid IP address\n");
        return 1;
    }

    mask_addr.s_addr = htonl(~((1U << (32 - subnetBits)) - 1));

    network_addr.s_addr = ip_addr.s_addr & mask_addr.s_addr;

    first_addr.s_addr = htonl(ntohl(network_addr.s_addr) + 1);

    last_addr.s_addr = htonl(ntohl(network_addr.s_addr) + availableAddr);

    broadcast_addr.s_addr = htonl(ntohl(last_addr.s_addr) + 1);

    char subnet_mask_hex[9]; 
    snprintf(subnet_mask_hex, sizeof(subnet_mask_hex), "%08X", ntohl(mask_addr.s_addr));
    
    if (subnetBits == 32) {
        printf("Number of Available Addresses: %d\n", availableAddr);
        printf("Mask: %s = /%d\n", inet_ntoa(mask_addr), subnetBits);
        printf("Mask as Hex: %s\n", subnet_mask_hex);
        printf("First Usable IP Address: %s\n", ipNum);
    } else {

    printf("Usable Addresses: %d\n", availableAddr);
    printf("Mask: %s = /%d\n", inet_ntoa(mask_addr), subnetBits);
    printf("Mask as Hex: %s\n", subnet_mask_hex);
    printf("Network: %s\n", inet_ntoa(network_addr));
    printf("First Usable: %s\n", inet_ntoa(first_addr));
    printf("Last Usable: %s\n", inet_ntoa(last_addr));
    printf("Broadcast Address: %s\n", inet_ntoa(broadcast_addr));

    return 0;
    }

}


