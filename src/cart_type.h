#pragma once

enum CART_TYPE
{
    NO_MBC,
    MBC1,
    MBC2,
    MBC3,
    MBC5,
    MBC6,
    MBC7,
    MMM01,
    POCKET_CAMERA,
    BANDAI_TAMA5,
    HUC3,
	HUC1,
	UNUSED,
};

struct cart_type_info 
{
    CART_TYPE type;
    bool has_ram;
    bool has_battery;
    bool has_timer;
    bool has_rumble;
    bool has_accelerometer;
    const char* readable_name;
};

const cart_type_info cart_type_data[256] =
{
    {CART_TYPE::NO_MBC, false, false, false, false, false,  "No MBC, ROM Only"},                        //0x00
    {CART_TYPE::MBC1,   false, false, false, false, false,  "MBC1"},                                    //0x01
    {CART_TYPE::MBC1,   true, false, false, false, false,   "MBC1 + RAM"},                              //0x02
    {CART_TYPE::MBC1,   true, true, false, false, false,    "MBC1 + RAM + Battery"},                    //0x03
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x04
    {CART_TYPE::MBC2,   false, false, false, false, false,  "MBC2"},                                    //0x05
    {CART_TYPE::MBC2,   true, true, false, false, false,    "MBC2 + RAM + Battery"},                    //0x06
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x07
    {CART_TYPE::NO_MBC, true, false, false, false, false,   "ROM + RAM"},                               //0x08
    {CART_TYPE::NO_MBC, true, true, false, false, false,    "ROM + RAM + Battery"},                     //0x09
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x0A
    {CART_TYPE::MMM01,  false, false, false, false, false,  "MMM01"},                                   //0x0B
    {CART_TYPE::MMM01,  true, false, false, false, false,   "MMM01 + RAM"},                             //0x0C
    {CART_TYPE::MMM01,  true, true, false, false, false,    "MMM01 + RAM + Battery"},                   //0x0D
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x0E
    {CART_TYPE::MBC3,   false, true, true, false, false,    "MBC3 + Timer + Battery"},                  //0x0F
    {CART_TYPE::MBC3,   true, true, true, false, false,     "MBC3 + RAM + Timer + Battery"},            //0x10
    {CART_TYPE::MBC3,   false, false, false, false, false,  "MBC3"},                                    //0x11
    {CART_TYPE::MBC3,   true, false, false, false, false,   "MBC3 + RAM"},                              //0x12
    {CART_TYPE::MBC3,   true, true, false, false, false,    "MBC3 + RAM + Battery"},                    //0x13
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x14
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x15
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x16
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x17
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x18
    {CART_TYPE::MBC5,   false, false, false, false, false,  "MBC5"},                                    //0x19
    {CART_TYPE::MBC5,   true, false, false, false, false,   "MBC5 + RAM"},                              //0x1A
    {CART_TYPE::MBC5,   true, true, false, false, false,    "MBC5 + RAM, + Battery"},                   //0x1B
    {CART_TYPE::MBC5,   false, false, false, true, false,   "MBC5 + Rumble"},                           //0x1C
    {CART_TYPE::MBC5,   true, false, false, true, false,    "MBC5 + RAM + Rumble"},                     //0x1D
    {CART_TYPE::MBC5,   true, true, false, true, false,     "MBC5 + RAM + Battery + Rumble"},           //0x1E
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x1F
    {CART_TYPE::MBC6,   true, true, false, false, false,    "MBC6 + RAM + Battery"},                    //0x20
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x21
    {CART_TYPE::MBC7,   true, true, false, false, true,     "MBC7 + RAM + Battery + Accelerometer"},    //0x22
    {CART_TYPE::UNUSED, false, false, false, false, false,  "Unused"},                                  //0x23
    // TODO: Copy paste unused a bunch of times
    {CART_TYPE::POCKET_CAMERA,  false, false, false, false, false, "Pocket Camera"},                    //0xFC
    {CART_TYPE::BANDAI_TAMA5,   false, false, false, false, false,  "Bandai Tama5"},                    //0xFD
    {CART_TYPE::HUC3,   false, false, false, false, false,  "HuC3"},                                    //0xFE
    {CART_TYPE::HUC1,   true, true, false, false, false,  "HuC1 + RAM + Battery"},                      //0xFF
};