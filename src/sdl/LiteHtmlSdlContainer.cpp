#include <SDL_ttf.h>
#include <iostream>
#include "LiteHtmlSdlContainer.h"

using namespace litehtml;

class LiteHtmlSdlContainer : public document_container {
private:
    std::string monoTtfFile;
    ILogger *log;

public:
    INJECT(LiteHtmlSdlContainer(ILogger *log, IApplicationConfig *config)) : log(log) {
        this->monoTtfFile = config->getResourcePath("fonts") + "FreeMono.ttf";
    }

    virtual ~LiteHtmlSdlContainer() {

    }

    virtual uint_ptr create_font(const tchar_t* faceName, int size, int weight, font_style italic, unsigned int decoration, font_metrics* fm) override;
    virtual void delete_font(uint_ptr hFont);
    virtual int text_width(const tchar_t* text, uint_ptr hFont) override;
    virtual void draw_text(uint_ptr hdc, const tchar_t* text, uint_ptr hFont, web_color color, const position& pos) override;
    virtual int pt_to_px(int pt) override;
    virtual int get_default_font_size() override;
    virtual const tchar_t* get_default_font_name() override;
    virtual void draw_list_marker(uint_ptr hdc, const list_marker& marker) override;
    virtual void load_image(const tchar_t* src, const tchar_t* baseurl, bool redraw_on_ready) override;
    virtual void get_image_size(const tchar_t* src, const tchar_t* baseurl, size& sz) override;
    virtual void draw_background(uint_ptr hdc, const background_paint& bg) override;
    virtual void draw_borders(uint_ptr hdc, const css_borders& borders, const position& draw_pos, bool root) override;
    virtual void set_caption(const tchar_t* caption) override;
    virtual void set_base_url(const tchar_t* base_url) override;
    virtual void link(document* doc, element::ptr el) override;
    virtual void on_anchor_click(const tchar_t* url, element::ptr el) override;
    virtual void set_cursor(const tchar_t* cursor) override;
    virtual void transform_text(tstring& text, text_transform tt) override;
    virtual void import_css(tstring& text, const tstring& url, tstring& baseurl) override;
    virtual void set_clip(const position& pos, bool valid_x, bool valid_y) override;
    virtual void del_clip() override;
    virtual void get_client_rect(position& client) override;
    virtual element* create_element(const tchar_t* tag_name, const string_map& attributes) override;
    virtual void get_media_features(media_features& media) override;
};


fruit::Component<fruit::Required<ILogger, IApplicationConfig>, document_container> getLiteHtmlSdlContainer() {
    return fruit::createComponent().bind<document_container, LiteHtmlSdlContainer>();
}


uint_ptr LiteHtmlSdlContainer::create_font(const tchar_t *faceName, int size, int weight,
                                                   font_style italic, unsigned int decoration,
                                                   font_metrics *fm) {

    std::cout << "[create_font] faceName: " << faceName
        << ", size: " << size
        << ", weight: " << weight
        << ", italic: " << italic
        << ", decoration: " << decoration << std::endl;

    string_vector fonts;
    split_string(faceName, fonts, _t(","));

    //std::string fnt_name = fonts.empty() ? "sans-serif" : fonts[0];
    const char* fnt_name = this->monoTtfFile.c_str();

    TTF_Font* font = TTF_OpenFont(fnt_name, size);

    //If there was an error in loading the font
    if(font == nullptr)
    {
        std::cout << "[create_font] can't load ttf: " << fnt_name << std::endl;
        return nullptr;
    }

    int ttfStyle = TTF_STYLE_NORMAL;
    if(italic == fontStyleItalic) {
        ttfStyle = ttfStyle | TTF_STYLE_ITALIC;
    }

    if((decoration & font_decoration_linethrough) != 0) {
        ttfStyle = ttfStyle | TTF_STYLE_STRIKETHROUGH;
    }

    if((decoration & font_decoration_underline) != 0) {
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
        fm->draw_spaces = italic == fontStyleItalic || decoration;

        std::cout << "[create_font] ascent: " << fm->ascent
            << ", descent: " << fm->descent
            << ", height: " << fm->height
            << ", x_height: " << fm->x_height
            << ", draw_spaces: " << fm->draw_spaces  << std::endl;
    }

    return (uint_ptr) font;
}

void LiteHtmlSdlContainer::delete_font(uint_ptr hFont) {
    TTF_Font* font = (TTF_Font*)hFont;

    std::cout << "[delete_font] font: " << (font ? "not null" : "null") << std::endl;
    if(font)
    {
        TTF_CloseFont( font );
    }
}

int LiteHtmlSdlContainer::text_width(const tchar_t *text, uint_ptr hFont) {

    TTF_Font* font = (TTF_Font*)hFont;
    if(!font)
    {
        std::cout << "[text_width](" << text << ") font: null" << std::endl;
        return 0;
    }

    int iWidth = 0, iHeight = 0;
    TTF_SizeText(font, _t(text), &iWidth, &iHeight);
    std::cout << "[text_width](" << text << ") width: " << iWidth << std::endl;
    return iWidth;
}

void LiteHtmlSdlContainer::draw_text(uint_ptr hdc, const tchar_t *text, uint_ptr hFont,
                                   web_color color, const position &pos) {

}

int LiteHtmlSdlContainer::pt_to_px(int pt) {
    return (int) round(pt * 125.0 / 72.0);
}

int LiteHtmlSdlContainer::get_default_font_size() {
    return this->pt_to_px(10);
}

const tchar_t *LiteHtmlSdlContainer::get_default_font_name() {
    return _t("sans-serif");
}

void LiteHtmlSdlContainer::draw_list_marker(uint_ptr hdc, const list_marker &marker) {

}

void LiteHtmlSdlContainer::load_image(const tchar_t *src, const tchar_t *baseurl,
                                    bool redraw_on_ready) {

}

void LiteHtmlSdlContainer::get_image_size(const tchar_t *src, const tchar_t *baseurl,
                                        size &sz) {

}

void LiteHtmlSdlContainer::draw_background(uint_ptr hdc, const background_paint &bg) {

}

void LiteHtmlSdlContainer::draw_borders(uint_ptr hdc, const css_borders &borders,
                                      const position &draw_pos, bool root) {

}

void LiteHtmlSdlContainer::set_caption(const tchar_t *caption) {

}

void LiteHtmlSdlContainer::set_base_url(const tchar_t *base_url) {

}

void LiteHtmlSdlContainer::link(document *doc, element::ptr el) {

}

void LiteHtmlSdlContainer::on_anchor_click(const tchar_t *url, element::ptr el) {

}

void LiteHtmlSdlContainer::set_cursor(const tchar_t *cursor) {

}

void LiteHtmlSdlContainer::transform_text(tstring &text, text_transform tt) {

}

void LiteHtmlSdlContainer::import_css(tstring &text, const tstring &url, tstring &baseurl) {

}

void LiteHtmlSdlContainer::set_clip(const position &pos, bool valid_x, bool valid_y) {

}

void LiteHtmlSdlContainer::del_clip() {

}

void LiteHtmlSdlContainer::get_client_rect(position &client) {

}

element *LiteHtmlSdlContainer::create_element(const tchar_t *tag_name,
                                                      const string_map &attributes) {
    return nullptr;
}

void LiteHtmlSdlContainer::get_media_features(media_features &media) {

}
