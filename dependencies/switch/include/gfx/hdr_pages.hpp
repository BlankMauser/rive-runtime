#pragma once

#include "font.hpp"

#include <optional>

class HDR_PageManager {
private:
    struct Page {
        std::string title;
        std::vector<std::pair<std::string, std::string>> key_values;
    };

    std::vector<Page> m_Pages;
    size_t m_CurrentPageIdx;
    std::optional<Page> m_CurrentPage;
    f32 m_PageWidth;
    f32 m_PageHeight;

    HDR_PageManager();
public:
    ~HDR_PageManager();

    static HDR_PageManager& Instance();

    static void StartPage(const std::string& title);
    static void SetKeyValue(const std::string& key, const std::string& value);
    static void EndPage();

    static void ClearPages();

    static void DrawPages();
    static void Render(nvn::CommandBuffer* cmdbuf);

    static void IncrementPage();
    static void DecrementPage();
};

extern "C" void hdr_pages_start_page(const char* string);
extern "C" void hdr_pages_set_key_value(const char* key, const char* value);
extern "C" void hdr_pages_end_page();

extern "C" void hdr_pages_clear_pages();
extern "C" void hdr_pages_increment_page();
extern "C" void hdr_pages_decrement_page();