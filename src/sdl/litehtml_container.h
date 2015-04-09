#pragma once

#include "../litehtml/litehtml.h"

class litehtml_container :	public litehtml::document_container {
private:
    char const *monoTtfFile, *sansTtfFile, *serifTtfFile;

public:
    litehtml_container(const std::string monoTtfFile, const std::string sansTtfFile, const std::string serifTtfFile);
    ~litehtml_container();

    litehtml::uint_ptr create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm);
    void delete_font(litehtml::uint_ptr hFont);
    int text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont);
    void draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos);
    int pt_to_px(int pt);
    int get_default_font_size();
    const litehtml::tchar_t* get_default_font_name();
    void draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker);
    void load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready);
    void get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz);
    void draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg);
    void draw_borders(litehtml::uint_ptr hdc, const litehtml::css_borders& borders, const litehtml::position& draw_pos, bool root);
    void set_caption(const litehtml::tchar_t* caption);
    void set_base_url(const litehtml::tchar_t* base_url);
    void link(litehtml::document* doc, litehtml::element::ptr el);
    void on_anchor_click(const litehtml::tchar_t* url, litehtml::element::ptr el);
    void set_cursor(const litehtml::tchar_t* cursor);
    void transform_text(litehtml::tstring& text, litehtml::text_transform tt);
    void import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl);
    void set_clip(const litehtml::position& pos, bool valid_x, bool valid_y);
    void del_clip();
    void get_client_rect(litehtml::position& client);
    litehtml::element* create_element(const litehtml::tchar_t* tag_name, const litehtml::string_map& attributes);
    void get_media_features(litehtml::media_features& media);
};
