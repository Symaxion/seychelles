#include "libedit.h"
#include "safe_exit.h"

#include <iostream>

namespace Edit {

    EditLine* editLineObject(::EditLine* e) {
        EditLine* e1;
        el_get(e, EL_CLIENTDATA, &e1);
        return e1;
    }

    char* editLinePromptCallback(::EditLine* e) {
        EditLine* e1 = editLineObject(e);
        return const_cast<char*>(e1->promptCallback()(*e1).c_str());
    }

    unsigned char controlC(::EditLine* el, int ch) {
        el_reset(el);
        std::cout << std::endl;
        return CC_REDISPLAY;
    }

    //// EditLine //// 

    EditLine::EditLine(std::string argv0, FILE* input, FILE* output,
            FILE* error) :
        el(el_init(argv0.c_str(), input, output, error)),
        mPromptCallback(0) {
        el_set(el, EL_EDITOR, "emacs");
        el_set(el, EL_SIGNAL, 1);
        el_set(el, EL_CLIENTDATA, this);
        el_set(el, EL_SETTY, "-d", "intr=^@", NULL);
        el_set(el, EL_SETTY, "-d", "eof=^@", NULL);
        el_set(el, EL_ADDFN, "cust-control-c", "", controlC);
        el_set(el, EL_BIND, "^C", "cust-control-c", NULL);
        el_set(el, EL_BIND, "^D", "ed-end-of-file", NULL);
    }

    EditLine::~EditLine() {
        el_end(el);
    }

    ::EditLine* EditLine::operator&() {
        return el;
    }

    const ::EditLine* EditLine::operator&() const {
        return el;
    }

    void EditLine::setPrompt(PromptF f) {
        mPromptCallback = f;
        el_set(el, EL_PROMPT, editLinePromptCallback);
    }

    void EditLine::setHistory(History& h) {
        el_set(el, EL_HIST, history, &h);
    }

    EditLine::PromptF EditLine::promptCallback() {
        return mPromptCallback;
    }

    void EditLine::setEditStyle(EditLine::EditStyle e) {
        switch(e) {
        case Emacs:
            el_set(el, EL_EDITOR, "emacs");

        case Vi:
            el_set(el, EL_EDITOR, "vi");
        }
    }

    std::string EditLine::gets() {
        int count;
        const char* c = el_gets(el, &count);
        if(c == 0) {
            safe_exit(0);
        }
        std::string s = c;
        return s.substr(0, s.size() - 1);
    }

    //// History ////

    History::History(size_t size) : hist(history_init()) {
        history(hist, &ev, H_SETSIZE, size);
    }
    History::~History() {
        history_end(hist);
    }

    ::History* History::operator&() {
        return hist;
    }

    const ::History* History::operator&() const {
        return hist;
    }

    void History::add(const std::string& s) {
        history(hist, &ev, H_ENTER, s.c_str());
    }

}
