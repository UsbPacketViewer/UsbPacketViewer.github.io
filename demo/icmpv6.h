// Sample ICMP v6
// @big
struct network{
    struct{
        uint8_t dst_mac[6];
        uint8_t src_mac[6];
        uint16_t type;
    }eth;
    struct{
        //@dec
        uint16_t reserved:4;
        //@dec
        uint16_t ECN:2;  // Explicit Congestion Notification
        //@dec
        uint16_t DSCP:6; // Differentiated services codepoint
        // @dec
        uint16_t version:4; // IP V{{version}}
        uint16_t padding;
        uint16_t payload_length; // @dec
        uint8_t  next_header;
        uint8_t  hop_limit;
        uint8_t  src[16]; // @ipv6
        uint8_t  dst[16]; // @ipv6
        struct {
            uint8_t next_header;
            uint8_t length; // {{(length+1)*8}} bytes
            struct{
                uint8_t lower_order_bits:5; //@dec
                uint8_t may_change:1; //@dec
                uint8_t action:2; //@dec
                uint8_t length;
                // @array[length]
                uint8_t route_alert[];
            }route_alert;
            struct{
                uint8_t lower_order_bits:5;
                uint8_t may_change:1;
                uint8_t action:2;
                uint8_t length;
                // @array[length]
                uint8_t PadN[];
            }PadN;
        }option;
    }ipv6;
    struct{
        uint8_t type;
        uint8_t code;
        uint16_t checksum;
        uint16_t reserved;
        uint16_t record_count; //@dec
        //@array[record_count]
        struct{
            uint8_t record_type;
            uint8_t aux_data_len;
            uint16_t number_of_source; //@dec
            uint8_t  addr[16]; //@ipv6
        }records[];
    }icmpv6;
}network;
