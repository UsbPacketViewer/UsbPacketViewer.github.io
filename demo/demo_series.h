// 此示例主要介绍match和alias注解，这两个注解是使用在结构体上的
// 典型的USB配置描述符是由一系列的标准描述符组成的
// 需要按照不同的描述符类型来对其内容进行解析

// Step 1: 先定义一个基本类型，需要包含所有类型都共有字段
// 基础类型
typedef struct base_type{
    uint8_t type;  // 未知类型 type={{type}}
    uint8_t len;
    uint8_t data[len];
}base_type;

// Step 2: 使用match注解指明需要匹配字段
// @match[type==2]
// Step 3: 使用alias注解将基础类型与当前类型关联
// @alias[base_type]
// 类型2
typedef struct base_2_type{
    uint8_t type;  // 类型2
    uint8_t len;
    uint8_t d2_v1;
    uint8_t d2_v2;
    uint8_t d2_v3;
}base_2_type;

#define TYPE_3  3
#define TYPE_4  4
// 表达式中可以使用宏定义
// @match[type==TYPE_3]
// 使用alias注解指明基础类型
// @alias[base_type]
// 类型3
typedef struct base_3_type{
    uint8_t type; // 类型3
    uint8_t len;
    uint8_t d3_v1;
    uint8_t d3_v2;
    uint8_t d3_v3;
}base_3_type;

// match注解可以使用多个条件指明需要匹配字段
// 表达式优先级可能与C语言不一致，尽量多使用括号
// @match[type==4 && len==2]
// 使用alias注解指明基础类型
// @alias[base_type]
// 类型4_len2
typedef struct base_4_len_2_type{
    uint8_t type; // 类型4 长度2
    uint8_t len;
    uint8_t d4_l2_v1;
    uint8_t d4_l2_v2;
}base_4_len_2_type;

// 也可以不通过alias注解关联基础类型
// 需要将结构体名称设置为与基础类型相同，这样做会导致不兼容标准C语言
// @match[type==4 && len==3]
// 类型4_len3
typedef struct base_4_len_3_type{
    uint8_t type; // 类型4 长度3
    uint8_t len;
    uint8_t d4_l3_v1;
    uint8_t d4_l3_v2;
    uint8_t d4_l3_v3;
}base_type;

// @match[type==4 && len>3]
// @alias[base_type]
// 类型4_len
typedef struct base_4_len_type{
    uint8_t type; // 类型4 长度大于3
    uint8_t len;
    uint8_t d4_data[len];
}base_4_len_type;

struct def_struct
{
    uint8_t def_a;
    uint8_t def_b;
    uint8_t def_c;
};

// @match[type==5]
// @alias[base_type]
// 类型5
typedef struct base_5_type{
    uint8_t type; // 类型5, 包含子结构体
    uint8_t len;
    struct def_struct data;
}base_5_type;

// 子结构体也可以先使用后定义，可以按照C++风格使用结构体名称
// @match[type==6]
// @alias[base_type]
// 类型6
typedef struct base_6_type{
    uint8_t type; // 类型6, 子结构体包含子结构体
    uint8_t len;
    struct out_type data; 
}base_6_type;

struct out_type{
    uint8_t out_a;
    in_type out_in_a;
    uint8_t out_b;
    in_type out_in_b;
};

struct in_type{
    uint8_t in_a;
    uint8_t in_b;
};