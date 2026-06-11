#include "gfx/hdr_pages.hpp"
#include "gfx/debug.hpp"
HDR_PageManager::HDR_PageManager() : m_Pages({}), m_CurrentPageIdx(0), m_CurrentPage() {

}

HDR_PageManager::~HDR_PageManager() {
    // TODO?
}

HDR_PageManager& HDR_PageManager::Instance() {
    static HDR_PageManager s_Instance;
    return s_Instance;
}

void HDR_PageManager::StartPage(const std::string& title) {
    auto& instance = Instance();
    instance.m_CurrentPage = Page {
        .title = std::string(title),
        .key_values = {}
    };
}

void HDR_PageManager::SetKeyValue(const std::string& key, const std::string& value) {
    auto& instance = Instance();
    SL_ASSERTM(instance.m_CurrentPage.has_value(), "no current page");
    instance.m_CurrentPage.value().key_values.push_back(
        std::make_pair(std::string(key), std::string(value))
    );
}

void HDR_PageManager::EndPage() {
    auto& instance = Instance();
    SL_ASSERTM(instance.m_CurrentPage.has_value(), "no current page");
    instance.m_Pages.push_back(std::move(instance.m_CurrentPage.value()));
    instance.m_CurrentPage = std::optional<Page>();
}

void HDR_PageManager::ClearPages() {
    auto& instance = Instance();
    instance.m_Pages.clear();
    instance.m_CurrentPage = std::optional<Page>();
}

void HDR_PageManager::DrawPages() {
    auto& instance = Instance();
    if (instance.m_Pages.empty()) {
        instance.m_PageWidth = 0.0f;
        return;
    }

    const auto& page = instance.m_Pages[instance.m_CurrentPageIdx % instance.m_Pages.size()];

    int y = 10;

    f32 page_max = 0.0f;
    for (const auto& page : instance.m_Pages) {
        size_t max_len = 0;
        for (const auto& kv : page.key_values) {
            max_len = std::max(max_len, kv.first.size());
        }
        FontManager::DrawText(10, y, 14.0f, page.title.c_str());
        for (const auto& kv : page.key_values) {
            y += 15;
            std::string buffer = kv.first;
            while (buffer.size() <= max_len)
                buffer += ' ';
            std::string line = buffer + kv.second;
            page_max = std::max(page_max, FontManager::DrawText(10, y, 14.0f, line.c_str()));
        }
        y += 30;
    }

    instance.m_PageWidth = page_max;
    instance.m_PageHeight = (float)y + 15.0f;
}

void HDR_PageManager::Render(nvn::CommandBuffer* cmdbuf) {
    auto& instance = Instance();
    if (instance.m_PageWidth == 0.0f)
        return;

    Scissor(0, 0, std::max(100, (int)instance.m_PageWidth + 10), (int)instance.m_PageHeight + 10).Bind(cmdbuf);
    ClearColor(0.0f, 0.0f, 0.0f, 0.66f).Draw(cmdbuf);
    Scissor(0, 0, 1920, 1080).Bind(cmdbuf);
}

void HDR_PageManager::IncrementPage() {
    auto& instance = Instance();
    instance.m_CurrentPageIdx++;
}

void HDR_PageManager::DecrementPage() {
    auto& instance = Instance();
    if (instance.m_CurrentPageIdx > 0)
        instance.m_CurrentPageIdx--;
}

extern "C" void hdr_pages_start_page(const char* string) {
    HDR_PageManager::StartPage(string);
}

extern "C" void hdr_pages_set_key_value(const char* key, const char* value) {
    HDR_PageManager::SetKeyValue(key, value);
}

extern "C" void hdr_pages_end_page() {
    HDR_PageManager::EndPage();
}

extern "C" void hdr_pages_clear_pages() {
    HDR_PageManager::ClearPages();
}

extern "C" void hdr_pages_increment_page() {
    HDR_PageManager::IncrementPage();
}

extern "C" void hdr_pages_decrement_page() {
    HDR_PageManager::DecrementPage();
}