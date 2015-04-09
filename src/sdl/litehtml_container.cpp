#include <SDL_ttf.h>
#include <iostream>
#include "litehtml_container.h"


litehtml_container::litehtml_container(const std::string monoTtfFile, const std::string sansTtfFile,
                                       const std::string serifTtfFile)
        : monoTtfFile(monoTtfFile.c_str()), sansTtfFile(sansTtfFile.c_str()), serifTtfFile(serifTtfFile.c_str()) {
}

litehtml_container::~litehtml_container() {

}

litehtml::uint_ptr litehtml_container::create_font(const litehtml::tchar_t *faceName, int size, int weight,
                                                   litehtml::font_style italic, unsigned int decoration,
                                                   litehtml::font_metrics *fm) {

    std::cout << "[create_font] faceName: " << faceName
        << ", size: " << size
        << ", weight: " << weight
        << ", italic: " << italic
        << ", decoration: " << decoration << std::endl;

    litehtml::string_vector fonts;
    litehtml::split_string(faceName, fonts, _t(","));

    //std::string fnt_name = fonts.empty() ? "sans-serif" : fonts[0];
    const char* fnt_name = this->monoTtfFile;

    TTF_Font* font = TTF_OpenFont(fnt_name, size);

    //If there was an error in loading the font
    if(font == nullptr)
    {
        std::cout << "[create_font] can't load ttf: " << fnt_name << std::endl;
        return nullptr;
    }

    int ttfStyle = TTF_STYLE_NORMAL;
    if(italic == litehtml::fontStyleItalic) {
        ttfStyle = ttfStyle | TTF_STYLE_ITALIC;
    }

    if((decoration & litehtml::font_decoration_linethrough) != 0) {
        ttfStyle = ttfStyle | TTF_STYLE_STRIKETHROUGH;
    }

    if((decoration & litehtml::font_decoration_underline) != 0) {
        ttfStyle = ttfStyle | TTF_STYLE_UNDERLINE;
    }

    if(weight >= 700) {
        ttfStyle = ttfStyle | TTF_STYLE_BOLD;
    }

    TTF_SetFontStyle(font, ttfStyle);

    int iWidth = 0, iHeight = 0;
    TTF_SizeText(font, _t("x"), &iWidth, &iHeight);

    if(fm)
    {
        fm->ascent		= TTF_FontAscent(font);
        fm->descent		= TTF_FontDescent(font);
        fm->height		= TTF_FontHeight(font);
        fm->x_height	= iWidth;
        fm->draw_spaces = italic == litehtml::fontStyleItalic || decoration;
    }

    return (litehtml::uint_ptr) font;
}

void litehtml_container::delete_font(litehtml::uint_ptr hFont) {
    TTF_Font* font = (TTF_Font*)hFont;
    if(font)
    {
        TTF_CloseFont( font );
    }
}

int litehtml_container::text_width(const litehtml::tchar_t *text, litehtml::uint_ptr hFont) {
    TTF_Font* font = (TTF_Font*)hFont;
    if(!font)
    {
        return 0;
    }

    int iWidth = 0, iHeight = 0;
    TTF_SizeText(font, _t(text), &iWidth, &iHeight);
    return iWidth;
}

void litehtml_container::draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t *text, litehtml::uint_ptr hFont,
                                   litehtml::web_color color, const litehtml::position &pos) {

}

int litehtml_container::pt_to_px(int pt) {
    return (int) round(pt * 125.0 / 72.0);
}

int litehtml_container::get_default_font_size() {
    return this->pt_to_px(10);
}

const litehtml::tchar_t *litehtml_container::get_default_font_name() {
    return _t("sans-serif");
}

void litehtml_container::draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker &marker) {

}

void litehtml_container::load_image(const litehtml::tchar_t *src, const litehtml::tchar_t *baseurl,
                                    bool redraw_on_ready) {

}

void litehtml_container::get_image_size(const litehtml::tchar_t *src, const litehtml::tchar_t *baseurl,
                                        litehtml::size &sz) {

}

void litehtml_container::draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint &bg) {

}

void litehtml_container::draw_borders(litehtml::uint_ptr hdc, const litehtml::css_borders &borders,
                                      const litehtml::position &draw_pos, bool root) {

}

void litehtml_container::set_caption(const litehtml::tchar_t *caption) {

}

void litehtml_container::set_base_url(const litehtml::tchar_t *base_url) {

}

void litehtml_container::link(litehtml::document *doc, litehtml::element::ptr el) {

}

void litehtml_container::on_anchor_click(const litehtml::tchar_t *url, litehtml::element::ptr el) {

}

void litehtml_container::set_cursor(const litehtml::tchar_t *cursor) {

}

void litehtml_container::transform_text(litehtml::tstring &text, litehtml::text_transform tt) {

}

void litehtml_container::import_css(litehtml::tstring &text, const litehtml::tstring &url, litehtml::tstring &baseurl) {

}

void litehtml_container::set_clip(const litehtml::position &pos, bool valid_x, bool valid_y) {

}

void litehtml_container::del_clip() {

}

void litehtml_container::get_client_rect(litehtml::position &client) {

}

litehtml::element *litehtml_container::create_element(const litehtml::tchar_t *tag_name,
                                                      const litehtml::string_map &attributes) {
    return nullptr;
}

void litehtml_container::get_media_features(litehtml::media_features &media) {

}
