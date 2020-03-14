/*
** Copyright (c) 2020 LunarG, Inc.
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef GFXRECON_DECODE_VULKAN_RESOURCE_ALLOCATOR_H
#define GFXRECON_DECODE_VULKAN_RESOURCE_ALLOCATOR_H

#include "decode/handle_pointer_decoder.h"
#include "decode/struct_pointer_decoder.h"
#include "util/defines.h"

#include "vulkan/vulkan.h"

#include <string>
#include <vector>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

struct DeviceMemoryInfo;
struct BufferInfo;
struct ImageInfo;

class VulkanResourceAllocator
{
  public:
    struct Functions
    {
        PFN_vkGetPhysicalDeviceProperties        get_physical_device_properties{ nullptr };
        PFN_vkGetPhysicalDeviceMemoryProperties  get_physical_device_memory_properties{ nullptr };
        PFN_vkGetPhysicalDeviceMemoryProperties2 get_physical_device_memory_properties2{ nullptr };
        PFN_vkAllocateMemory                     allocate_memory{ nullptr };
        PFN_vkFreeMemory                         free_memory{ nullptr };
        PFN_vkGetDeviceMemoryCommitment          get_device_memory_commitment{ nullptr };
        PFN_vkMapMemory                          map_memory{ nullptr };
        PFN_vkUnmapMemory                        unmap_memory{ nullptr };
        PFN_vkFlushMappedMemoryRanges            flush_memory_ranges{ nullptr };
        PFN_vkInvalidateMappedMemoryRanges       invalidate_memory_ranges{ nullptr };
        PFN_vkCreateBuffer                       create_buffer{ nullptr };
        PFN_vkDestroyBuffer                      destroy_buffer{ nullptr };
        PFN_vkGetBufferMemoryRequirements        get_buffer_memory_requirements{ nullptr };
        PFN_vkGetBufferMemoryRequirements2       get_buffer_memory_requirements2{ nullptr };
        PFN_vkBindBufferMemory                   bind_buffer_memory{ nullptr };
        PFN_vkBindBufferMemory2                  bind_buffer_memory2{ nullptr };
        PFN_vkCmdCopyBuffer                      cmd_copy_buffer{ nullptr };
        PFN_vkCreateImage                        create_image{ nullptr };
        PFN_vkDestroyImage                       destroy_image{ nullptr };
        PFN_vkGetImageMemoryRequirements         get_image_memory_requirements{ nullptr };
        PFN_vkGetImageMemoryRequirements2        get_image_memory_requirements2{ nullptr };
        PFN_vkBindImageMemory                    bind_image_memory{ nullptr };
        PFN_vkBindImageMemory2                   bind_image_memory2{ nullptr };
    };

  public:
    virtual ~VulkanResourceAllocator() {}

    virtual VkResult Initialize(uint32_t                                api_version,
                                VkInstance                              instance,
                                VkPhysicalDevice                        physical_device,
                                VkDevice                                device,
                                const std::vector<std::string>&         enabled_device_extensions,
                                const VkPhysicalDeviceMemoryProperties& capture_memory_properties,
                                const VkPhysicalDeviceMemoryProperties& replay_memory_properties,
                                const Functions&                        functions) = 0;

    virtual void Destroy() = 0;

    virtual VkResult CreateBuffer(const StructPointerDecoder<Decoded_VkBufferCreateInfo>& pCreateInfo,
                                  const VkAllocationCallbacks*                            pAllocator,
                                  HandlePointerDecoder<VkBuffer>*                         pBuffer) = 0;

    virtual void DestroyBuffer(BufferInfo* buffer_info, const VkAllocationCallbacks* pAllocator) = 0;

    virtual VkResult CreateImage(const StructPointerDecoder<Decoded_VkImageCreateInfo>& pCreateInfo,
                                 const VkAllocationCallbacks*                           pAllocator,
                                 HandlePointerDecoder<VkImage>*                         pImage) = 0;

    virtual void DestroyImage(ImageInfo* image_info, const VkAllocationCallbacks* pAllocator) = 0;

    virtual VkResult AllocateMemory(const StructPointerDecoder<Decoded_VkMemoryAllocateInfo>& pAllocateInfo,
                                    const VkAllocationCallbacks*                              pAllocator,
                                    HandlePointerDecoder<VkDeviceMemory>*                     pMemory) = 0;

    virtual void FreeMemory(DeviceMemoryInfo* memory_info, const VkAllocationCallbacks* pAllocator) = 0;

    virtual void GetDeviceMemoryCommitment(const DeviceMemoryInfo* memory_info,
                                           VkDeviceSize*           pCommittedMemoryInBytes) = 0;

    virtual VkResult
    BindBufferMemory(BufferInfo* buffer_info, DeviceMemoryInfo* memory_info, VkDeviceSize memoryOffset) = 0;

    virtual VkResult BindBufferMemory2(uint32_t                      bindInfoCount,
                                       const VkBindBufferMemoryInfo* pBindInfos,
                                       DeviceMemoryInfo* const*      memory_infos,
                                       BufferInfo* const*            buffer_infos) = 0;

    virtual VkResult
    BindImageMemory(ImageInfo* image_info, DeviceMemoryInfo* memory_info, VkDeviceSize memoryOffset) = 0;

    virtual VkResult BindImageMemory2(uint32_t                     bindInfoCount,
                                      const VkBindImageMemoryInfo* pBindInfos,
                                      DeviceMemoryInfo* const*     memory_infos,
                                      ImageInfo* const*            image_infos) = 0;

    virtual VkResult MapMemory(DeviceMemoryInfo* memory_info,
                               VkDeviceSize      offset,
                               VkDeviceSize      size,
                               VkMemoryMapFlags  flags,
                               void**            ppData) = 0;

    virtual void UnmapMemory(DeviceMemoryInfo* memory_info) = 0;

    virtual VkResult FlushMappedMemoryRanges(uint32_t                   memoryRangeCount,
                                             const VkMappedMemoryRange* pMemoryRanges,
                                             DeviceMemoryInfo* const*   memory_infos) = 0;

    virtual VkResult InvalidateMappedMemoryRanges(uint32_t                   memoryRangeCount,
                                                  const VkMappedMemoryRange* pMemoryRanges,
                                                  DeviceMemoryInfo* const*   memory_infos) = 0;

    virtual void WriteMappedMemoryRange(const DeviceMemoryInfo* memory_info,
                                        uint64_t                offset,
                                        uint64_t                size,
                                        const uint8_t*          data) = 0;
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_VULKAN_RESOURCE_ALLOCATOR_H
