#pragma once

// std
#include <cstdint>
#include <map>

// project
#include "Type.hpp"
#include "Section.hpp"
#include "Memory.hpp"

namespace dai
{
namespace bootloader
{

namespace request {

    enum Command : uint32_t {
        USB_ROM_BOOT = 0,
        BOOT_APPLICATION,
        UPDATE_FLASH,
        GET_BOOTLOADER_VERSION,
        BOOT_MEMORY,
        UPDATE_FLASH_EX,
        UPDATE_FLASH_EX_2,
        NO_OP,
        GET_BOOTLOADER_TYPE,
        SET_BOOTLOADER_CONFIG,
        GET_BOOTLOADER_CONFIG,
        BOOTLOADER_MEMORY,
        UPDATE_BOOT_HEADER,
        READ_FLASH,
    };

    struct BaseRequest {
        BaseRequest(Command command) : cmd(command){}
        Command cmd;
    };

    // Specific request PODs
    struct UsbRomBoot : BaseRequest {
        // Common
        UsbRomBoot() : BaseRequest(USB_ROM_BOOT) {}

        static constexpr auto VERSION = "0.0.2";
        static constexpr const char* NAME = "UsbRomBoot";
    };
    struct BootApplication : BaseRequest {
        // Common
        BootApplication() : BaseRequest(BOOT_APPLICATION) {}

        // Data

        static constexpr const char* VERSION = "0.0.2";
        static constexpr const char* NAME = "BootApplication";
    };

    struct UpdateFlash : BaseRequest {
        // Common
        UpdateFlash() : BaseRequest(UPDATE_FLASH) {}

        // Data
        enum Storage : uint32_t { SBR, BOOTLOADER };
        Storage storage;
        uint32_t totalSize;
        uint32_t numPackets;

        static constexpr const char* VERSION = "0.0.2";
        static constexpr const char* NAME = "UpdateFlash";
    };


    struct GetBootloaderVersion : BaseRequest {
        // Common
        GetBootloaderVersion() : BaseRequest(GET_BOOTLOADER_VERSION) {}

        // Data

        static constexpr const char* VERSION = "0.0.2";
        static constexpr const char* NAME = "GetBootloaderVersion";
    };

    // 0.0.12 or higher
    struct BootMemory : BaseRequest {
        // Common
        BootMemory() : BaseRequest(BOOT_MEMORY) {}

        // Data
        uint32_t totalSize;
        uint32_t numPackets;

        static constexpr const char* VERSION = "0.0.12";
        static constexpr const char* NAME = "BootMemory";
    };

    // UpdateFlashEx - Additional options
    struct UpdateFlashEx : BaseRequest {
        // Common
        UpdateFlashEx() : BaseRequest(UPDATE_FLASH_EX) {}

        // Data
        Memory memory;
        Section section;
        uint32_t totalSize;
        uint32_t numPackets;

        static constexpr const char* VERSION = "0.0.12";
        static constexpr const char* NAME = "UpdateFlashEx";
    };

    // UpdateFlashEx2 - Additional options
    struct UpdateFlashEx2 : BaseRequest {
        // Common
        UpdateFlashEx2() : BaseRequest(UPDATE_FLASH_EX_2) {}

        // Data
        Memory memory;
        uint32_t offset;
        uint32_t totalSize;
        uint32_t numPackets;

        static constexpr const char* VERSION = "0.0.12";
        static constexpr const char* NAME = "UpdateFlashEx2";
    };


    struct GetBootloaderType : BaseRequest {
        // Common
        GetBootloaderType() : BaseRequest(GET_BOOTLOADER_TYPE) {}

        // Data

        static constexpr const char* VERSION = "0.0.12";
        static constexpr const char* NAME = "GetBootloaderType";
    };


    // 0.0.14 or higher
    struct SetBootloaderConfig : BaseRequest {
        // Common
        SetBootloaderConfig() : BaseRequest(SET_BOOTLOADER_CONFIG) {}

        // Data
        Memory memory = Memory::AUTO;
        int64_t offset = -1;
        uint32_t clearConfig = 0;
        uint32_t totalSize = 0;
        uint32_t numPackets = 0;

        static constexpr const char* VERSION = "0.0.14";
        static constexpr const char* NAME = "SetBootloaderConfig";
    };

    struct GetBootloaderConfig : BaseRequest {
        // Common
        GetBootloaderConfig() : BaseRequest(GET_BOOTLOADER_CONFIG) {}

        // Data
        Memory memory = Memory::AUTO;
        int64_t offset = -1;
        uint32_t maxSize = 0;

        static constexpr const char* VERSION = "0.0.14";
        static constexpr const char* NAME = "GetBootloaderConfig";
    };
    struct BootloaderMemory : BaseRequest {
        // Common
        BootloaderMemory() : BaseRequest(BOOTLOADER_MEMORY) {}

        // Data

        static constexpr const char* VERSION = "0.0.14";
        static constexpr const char* NAME = "BootloaderMemory";
    };

    struct UpdateBootHeader : BaseRequest {
        // Common
        UpdateBootHeader() : BaseRequest(UPDATE_BOOT_HEADER) {}

        // Data
        enum Type : int32_t { GPIO_MODE = 0, USB_RECOVERY, FLASH, FAST_FLASH };

        Type type;
        int64_t offset = -1;
        int64_t location = -1;
        int32_t dummyCycles = -1;
        int32_t frequency = -1;
        int32_t gpioMode = -1;


        static constexpr const char* VERSION = "0.0.16";
        static constexpr const char* NAME = "UpdateBootHeader";
    };

    struct ReadFlash : BaseRequest {
        // Common
        ReadFlash() : BaseRequest(READ_FLASH) {}

        // Data
        Memory memory = Memory::AUTO;
        uint32_t offset = 0;
        uint32_t totalSize = 0;

        static constexpr const char* VERSION = "0.0.16";
        static constexpr const char* NAME = "ReadFlash";
    };

}


namespace response {

    enum Command : uint32_t {
        FLASH_COMPLETE = 0,
        FLASH_STATUS_UPDATE,
        BOOTLOADER_VERSION,
        BOOTLOADER_TYPE,
        GET_BOOTLOADER_CONFIG,
        BOOTLOADER_MEMORY,
        BOOT_APPLICATION,
        READ_FLASH,
    };

    struct BaseResponse {
        BaseResponse(Command command) : cmd(command){}
        Command cmd;
    };

    // Specific request PODs
    struct FlashComplete : BaseResponse {
        // Common
        FlashComplete() : BaseResponse(FLASH_COMPLETE) {}

        // Data
        uint32_t success;
        char errorMsg[64];

        static constexpr const char* VERSION = "0.0.2";
        static constexpr const char* NAME = "FlashComplete";
    };
    struct FlashStatusUpdate : BaseResponse {
        // Common
        FlashStatusUpdate() : BaseResponse(FLASH_STATUS_UPDATE) {}

        // Data
        float progress;

        static constexpr const char* VERSION = "0.0.2";
        static constexpr const char* NAME = "FlashStatusUpdate";
    };
    struct BootloaderVersion : BaseResponse {
        // Common
        BootloaderVersion() : BaseResponse(BOOTLOADER_VERSION) {}

        // Data
        uint32_t major, minor, patch;

        static constexpr const char* VERSION = "0.0.2";
        static constexpr const char* NAME = "BootloaderVersion";
    };

    struct BootloaderType : BaseResponse {
        // Common
        BootloaderType() : BaseResponse(BOOTLOADER_TYPE) {}

        // Data
        Type type;

        static constexpr const char* VERSION = "0.0.12";
        static constexpr const char* NAME = "BootloaderType";
    };


    // 0.0.14
    struct GetBootloaderConfig : BaseResponse {
        // Common
        GetBootloaderConfig() : BaseResponse(GET_BOOTLOADER_CONFIG) {}

        // Data
        uint32_t success;
        char errorMsg[64];
        uint32_t totalSize;
        uint32_t numPackets;

        static constexpr const char* VERSION = "0.0.14";
        static constexpr const char* NAME = "GetBootloaderConfig";
    };

    struct BootloaderMemory : BaseResponse {
        // Common
        BootloaderMemory() : BaseResponse(BOOTLOADER_MEMORY) {}

        // Data
        Memory memory;

        static constexpr const char* VERSION = "0.0.14";
        static constexpr const char* NAME = "BootloaderMemory";
    };

    struct BootApplication : BaseResponse {
        // Common
        BootApplication() : BaseResponse(BOOT_APPLICATION) {}

        // Data
        uint32_t success;
        char errorMsg[64];

        static constexpr const char* VERSION = "0.0.14";
        static constexpr const char* NAME = "BootApplication";
    };

    struct ReadFlash : BaseResponse {
        // Common
        ReadFlash() : BaseResponse(READ_FLASH) {}

        // Data
        uint32_t success;
        char errorMsg[64];
        uint32_t totalSize;
        uint32_t numPackets;

        static constexpr const char* VERSION = "0.0.16";
        static constexpr const char* NAME = "ReadFlash";
    };


}

} // namespace bootloader
} // namespace dai
