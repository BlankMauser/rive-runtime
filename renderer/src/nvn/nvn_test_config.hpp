#pragma once

#include <cstdint>

struct RiveDescriptorPoolTestCase
{
    uint32_t flags = 0;
    int sampler_count = 0;
    int texture_count = 0;
    int sampler_extra_pages = 0;
    int texture_extra_pages = 0;
    int sampler_pool_pages = 0;
    int texture_pool_pages = 0;
    char name[48] = {};
};

extern "C" bool rive_nvn_get_descriptor_pool_test_case(
    RiveDescriptorPoolTestCase* out_case);
extern "C" uint32_t rive_nvn_get_descriptor_pool_test_version();
extern "C" void rive_nvn_set_descriptor_pool_test_case(
    const RiveDescriptorPoolTestCase* test_case,
    int index,
    int total);
