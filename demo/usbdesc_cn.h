// 中文版USB描述符示例

#define 设备描述符类型        0x01
#define 配置描述符类型        0x02
#define 字符描述符类型        0x03
#define 接口描述符类型        0x04
#define 端点描述符类型        0x05
#define 接口联合描述符类型     0x0B
#define HUB描述符类型         0x29
#define HID描述符类型         0x21
#define 报告描述符类型         0x22
#define 功能描述符类型         0x24
#define 高速伴随描述符类型     0x30

enum 端点类型{
    控制端点 = 0,
    同步端点 = 1,
    批量端点 = 2,
    中断端点 = 3,
}
#define 端点类型掩码  3

typedef struct 标准描述符 {
    uint8_t 描述符长度;
    uint8_t 描述符类型;
    uint8_t 数据[]; // @array[描述符长度-2]
}标准描述符;


// @match[描述符类型 == 设备描述符类型]
// @alias[标准描述符]
typedef struct 设备描述符 {
    uint8_t 描述符长度;
    uint8_t 描述符类型;
    uint16_t USB版本;
    uint8_t 设备类;
    uint8_t 设备子类;
    uint8_t 设备协议;
    uint8_t 最大包长;
    uint16_t 制造商ID;
    uint16_t 产品ID;
    uint16_t 设备版本;
    uint8_t 制造商名称索引;
    uint8_t 产品名称索引;
    uint8_t 序列号索引;
    uint8_t 配置数量;
}设备描述符;

// @match[描述符类型 == 配置描述符类型]
// @alias[标准描述符]
typedef struct 配置描述符 {
    uint8_t 描述符长度;
    uint8_t 描述符类型;
    uint16_t 总长度; //@dec
    uint8_t 接口数量;
    uint8_t 配置编号;
    uint8_t 配置描述索引;
    struct 属性{
    uint8_t 保留:5;
    uint8_t 远程唤醒:1;
    uint8_t 自供电:1;
    uint8_t 总线供电:1; // 为兼容1.0，始终为1
    }属性;
    uint8_t 最大电流;  // 最大电流 {{最大电流*2}} 毫安
  }配置描述符

// @match[描述符类型 == 接口描述符类型]
// @alias[标准描述符]
typedef struct 接口描述符 {
    uint8_t 描述符长度;
    uint8_t 描述符类型;
    uint8_t 接口编号;
    uint8_t 替代接口编号;
    uint8_t 端点数量;
    uint8_t 接口类;
    uint8_t 接口子类;
    uint8_t 接口协议;
    uint8_t 接口描述索引;
} 接口描述符;

// @match[描述符类型 == 端点描述符类型]
// @alias[标准描述符]
typedef struct 端点描述符 {
    uint8_t 描述符长度;
    uint8_t 描述符类型;
    uint8_t 端点地址:7;
    /*
     @enum{
       IN=1, // 从设备到主机
       OUT=0 // 从主机到设备
    }
    */
    uint8_t 端点方向:1;
    uint8_t 端点属性; // @enum 端点类型
    uint16_t 最大包长; // 最大包长 {{最大包长}}
    uint8_t  通讯周期;
}端点描述符;

// @match[描述符类型 == 接口联合描述符类型]
// @alias[标准描述符]
typedef struct 接口联合描述符 {
    uint8_t 描述符长度;
    uint8_t 描述符类型;
    uint8_t 首个接口编号;
    uint8_t 接口数量;
    uint8_t 功能类;
    uint8_t 功能子类;
    uint8_t 功能协议;
    uint8_t 功能描述索引;
} 接口联合描述符;

// @match[描述符类型 == 功能描述符类型]
// @alias[标准描述符]
typedef struct 功能描述符 {
    uint8_t 描述符长度;
    uint8_t 描述符类型;
    uint8_t 描述符子类型;
    // @array[描述符长度-3]
    uint8_t 数据[]; // 与接口相关的功能数据
} 功能描述符;
