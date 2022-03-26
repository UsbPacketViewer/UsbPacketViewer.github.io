/** 示例文件, DEMO file
 * data viewer是一个通过分析结构体定义来解析数据的在线工具
 * 此工具的原型为USB Packet Viewer的协议解析功能
 * lua原型代码地址：https://github.com/UsbPacketViewer/parser
 * data viewer使用TypeScript重写了结构体解析功能
 * 使用注解的方式来指定数据解析格式，为了保证结构体定义与C语言兼容
 * 注解内容写在C语言注释中，不会影响代码正常编译
 */ 

// 
// 默认情况下uint8_t和int8_t分别以无符号和有符号10进制格式解析
// 其它整数类型以16进制格式解析
// 数据类型说明
typedef struct base {
    // 基本数据类型
    struct base_type{
    // 基本整数类型为uint*_t int*_t，*号为8,16,24,32,40,48,56,64
    // uint8_t可以简写成u8 uint8, int8_t可以简写成s8 int8,其它类似
    uint8_t  bv_u8;   // 默认无符号10进制
    int8_t   bv_s8;   // 默认有符号10进制
    uint16_t bv_u16;  // 默认16进制
    uint16_t bv_s16;  // 默认16进制
    u32      bv_u32;  // 默认16进制
    u64      bv_u64;  // 默认16进制
    // 基本浮点类型为float, double
    float    bv_f32;  // 默认32位浮点
    double   bv_f64;  // 默认64位浮点
    // 数据默认为小端模式，可以通过注解调整模式
    //@big
    uint48_t ev_u48; // 调整为大端模式
    }base_type;

    // 数组类型
    struct arr_type{
        // 数组有定长和变长两种
        // 其中变长数组长度可以由结构体的其它字段指定
        // 指定长度的字段必须先于数组定义
        uint16_t arr_u16[4]; // 定长数组
        uint8_t  arr_length; // 数组长度字段
        uint8_t  arr_u8[arr_length]; // 使用其它字段指定数组长度
        // 为了保持与c语言兼容，可通过array注解来指定数组长度字段
        // @array[arr_length]
        uint8_t  arr_u8[]; // 使用其它字段指定数组长度,注解模式
    }arr_type;
    // 位域类型及表达式求值
    struct bf_type{
        // 位域
        uint16_t  bf_a:3;  // 3bit位域
        uint16_t  bf_b:5;  // 5bit位域
        // @dec
        uint16_t  bf_c:8;  // 8bit位域

        // 在注释中可使用表达式，类似Vue，将表达式放在{{}}中，即可求值
        // 表达式只支持右值
        float fa_f32; // 表达式求值 (bf_a+bf_b)*bf_c + fa_f32 = {{(bf_a+bf_b)*bf_c + fa_f32}}
    }bf_type;

    // 结构体类型
    struct st_type{
        //为了表示复杂数据类型，支持嵌套结构体
        // 嵌套结构体
        struct inner{
            uint8_t  in_a;
            uint8_t  in_b;
            struct {
                uint8_t  in2_a;
                uint8_t  in2_b;
            }in2;
        }in1;
        // 引用嵌套结构体内部的值做为数组长度
        uint8_t arr_u8[in1.in2.in2_a]; 
    

    // 匿名结构体
    struct {
        uint8_t anony_a; // 自动展开 anony_a = {{anony_a}}
        uint8_t anony_b; // 自动展开 anony_b = {{anony_b}}
    }; // 匿名结构体内容会自动展开
    
    struct{
        uint8_t st1_a;
        uint8_t st1_b;
    }st[2];
    uint8_t dummy1;  // 引用结构体数组中的值 st[1].st1_b = {{st[1].st1_b}}

    // 匿名结构体数组，标准C不支持
    struct{
        uint8_t st_anony_a; // 展开后会在名称后加后缀
        uint8_t st_anony_b; // 展开后会在名称后加后缀
    }[2];

    uint8_t dummy2;  // 引用匿名结构体数组中的值 st_anony_a$1 = {{st_anony_a$1}}

    // 嵌套匿名结构体数组，匿名结构体定义可以省略struct
    {
        uint8_t a;      // 一层展开
        {
            uint8_t aa; // 两层展开
            uint8_t bb; // 两层展开
        }[2];
        uint8_t b;      // 一层展开
    }[2];

    uint8_t dummy3;  // 引用匿名结构体数组中的值 aa$1$0 = {{aa$1$0}}, bb$0$1 = {{bb$0$1}}
    }st_type;

    // 以注解的形式声明枚举数据
    // 枚举注解
    struct enum_type{
        // 简单的枚举
        uint8_t  enum_v1; // @enum{type_a,type_b,type_c=5,type_d,type_e}
        /* @enum{
            type_a, // 枚举描述A
            type_b, // 枚举描述B
            type_c, // 枚举描述C
            type_d, // 枚举描述D
        }
        */
        uint8_t  enum_v2;  // 带描述的枚举
        // @enum test_enum
        uint8_t  enum_v3;  // 使用外部定义的枚举类型
    }enum_type;

    // 格式注解
    struct format_annotation{
        // @dec
        uint16_t  u16_dec;  // dec注解, 格式化为有符号10进制
        // @signed
        uint16_t  u16_signed;  // signed 注解, 格式化为有符号10进制
        // @unsigned
        uint16_t  u16_unsigned;  // unsigned 注解, 格式化为无符号10进制
        // @hex
        uint16_t  u16_hex;  // hex 注解, 格式化为16进制
        // @float
        uint32_t  u32_float; // float 注解, 格式化为32位浮点数
        // @double
        uint64_t  u64_double; // double 注解, 格式化为64位浮点数
        // @ascii
        uint8_t  u8_ascii[8];   // ascii 注解, 格式化为ASCII
        // @unicode
        uint16_t  u16_unicode[8];   // unicode 注解, 格式化为Unicode
        // @ipv4
        uint8_t  ipv4[4];   // ipv4 注解, 格式化为ipv4
        // @ipv6
        uint8_t  ipv6[16];   // ipv6 注解, 格式化为ipv6
        // @ipv64
        uint8_t  ipv64[16];   // ipv64 注解, 格式化为ipv6+ipv4格式
        // @guid
        uint8_t  guid[16];   // guid 注解, 格式化为guid
        // @timestamp
        uint32_t  ts32;   // timestamp 注解, 格式化为本地时间，以秒为单位
        // @timestamp
        uint64_t  ts64;   // timestamp 注解, 格式化为本地时间，以毫秒为单位
        // @ts
        uint32_t  ts32;   // ts 注解, 与timestamp相同
        // @utc
        uint32_t  utc32;   // utc 注解, 格式化为UTC时间，以秒为单位
        // @utc
        uint64_t  utc64;   // utc 注解, 格式化为UTC时间，以毫秒为单位

    }format_annotation;

    // 类型注释可以将一种类型转换成另外一种类型
    // 要求两种类型长度必须一致
    // 类型注解
    struct type_annotation{
        // @uint32 @dec
        uint8_t u8_a4[4]; // 将数组转化成32位整形，并以10进制显示
        // @uint32 @dec
        uint8_t u8_a5[5]; // 长度不一致，不能转化，数据以10进制数组显示
        // @u64 @double
        uint8_t u8_a8[8]; // 转化为64位整形，以64位浮点数显示
        // @f64
        uint8_t u8_a8[8]; // 转化为64位浮点数，与上一条等效
        // @u64 @ts
        uint16_t u16_a4[4]; // 转化为64位整形，以本地时间显示

    }type_annotation;

    // 柔性数组
    struct flex_arr_t{
        // 当数组长度为0时，会将剩余数据都当作数组内容
        // 如果数组长度通过字段计算后为零，不会作为柔性数组处理
        uint8_t zero_length;
        uint8_t arr_zero[zero_length]; // 数组长度表达式求值后为{{zero_length}}, 不会当作柔性数组
        // 柔性数组支持结构体数据
        // 柔性数组
        uint8_t flex_arr[];  // 数组长度 = 0, 柔性数组，剩余数据都作为数组内容。[]与[0]等效
    }flex_arr_t;
}base_t;

enum test_enum{
    test_a,  // 测试枚举a
    test_b,  // 测试枚举d
    test_c,  // 测试枚举c
    test_d,  // 测试枚举d
};