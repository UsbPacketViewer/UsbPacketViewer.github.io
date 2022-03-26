// put your own struct define here
#define USB_DEVICE_DESCRIPTOR_TYPE        0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE 0x02
#define USB_STRING_DESCRIPTOR_TYPE        0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE     0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE      0x05
#define USB_IAD_DESCRIPTOR_TYPE           0x0B
#define USB_HUB_DESCRIPTOR_TYPE           0x29
#define USB_HID_DESCRIPTOR_TYPE           0x21
#define USB_REPORT_DESCRIPTOR_TYPE        0x22
#define USB_DESC_TYPE_REPORT              0x22
#define USB_FUCNTION_DESCRIPTOR_TYPE      0x24
#define USB_SS_ENDPOINT_COMPANION_TYPE    0x30

enum EP_TYPE{
    USBD_EP_TYPE_CTRL = 0,
    USBD_EP_TYPE_ISOC = 1,
    USBD_EP_TYPE_BULK = 2,
    USBD_EP_TYPE_INTR = 3,
}
#define USBD_EP_TYPE_MASK  3

typedef struct _usb_device_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t content[]; // @array[bLength-2]
}usb_std_descriptor_t


// @match[bDescriptorType == USB_DEVICE_DESCRIPTOR_TYPE]
// @alias[usb_std_descriptor_t]
// Device descriptor
typedef struct _usb_device_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
}usb_device_descriptor_t;

// @match[bDescriptorType == USB_CONFIGURATION_DESCRIPTOR_TYPE]
// @alias[usb_std_descriptor_t]
// Config Desc
typedef struct _usb_config_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    struct{
      uint8_t reserved:5;
      uint8_t remote_wakeup:1;
      uint8_t self_power:1;
      uint8_t bus_power:1; // keep 1 to support 1.0
    }bmAttributes;
    uint8_t bMaxPower;  // {{bMaxPower*2}} mA
  }usb_config_descriptor_t

// @match[bDescriptorType == USB_INTERFACE_DESCRIPTOR_TYPE]
// @alias[usb_std_descriptor_t]
// Interface Desc
typedef struct _usb_interface_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} usb_interface_descriptor_t;

// @match[bDescriptorType == USB_ENDPOINT_DESCRIPTOR_TYPE]
// @alias[usb_std_descriptor_t]
// Endpoint Desc
typedef struct _usb_endpoint_descriptor {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bEndpointAddress:7;
  uint8_t bEndpointDirection:1; // @enum{IN=1,OUT=0}
  uint8_t bmAttributes; // @enum EP_TYPE
  uint16_t wMaxPacketSize; // max packet size {{wMaxPacketSize}}
  uint8_t bInterval;
}usb_endpoint_descriptor_t;

// @match[bDescriptorType == USB_IAD_DESCRIPTOR_TYPE]
// @alias[usb_std_descriptor_t]
// IAD Desc
typedef struct _usb_interface_association_descriptor {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bFirstInterface;
  uint8_t bInterfaceCount;
  uint8_t bFunctionClass;
  uint8_t bFunctionSubClass;
  uint8_t bFunctionProtocol;
  uint8_t iFunction;
} usb_interface_association_descriptor_t;

// @match[bDescriptorType == USB_FUCNTION_DESCRIPTOR_TYPE]
// @alias[usb_std_descriptor_t]
// Function Desc
typedef struct _usb_function_descriptor {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubtype;
  // @array[bLength-3]
  uint8_t data[]; // Interface related function data
} usb_function_descriptor_t;