#ifndef SEYCHELLES_LIBEDIT_H_
#define SEYCHELLES_LIBEDIT_H_

#include <histedit.h>

#include <string>
#include <map>

namespace Edit {

    class EditLine;
    class History;

    extern std::map< ::EditLine*, EditLine*> editLineMap;

    class EditLine {
    public:
        enum EditStyle {
            Emacs,
            Vi
        };

        typedef std::string(*PromptF)(EditLine&);
    public:
        EditLine(std::string argv0, FILE* input = stdin, FILE* output = stdout,
                FILE* error = stderr);

        ~EditLine(); 

        ::EditLine* operator&();

        const ::EditLine* operator&() const;

        void setPrompt(PromptF);

        void setEditStyle(EditStyle e);

        void setHistory(History& h);

        EditLine::PromptF promptCallback();

        std::string gets();

    private:
        ::EditLine* el;
        EditLine::PromptF mPromptCallback;
    };

    class History {
    public:
        History(size_t size = 1000);
        ~History(); 

        ::History* operator&(); 

        const ::History* operator&() const; 

        void add(const std::string&);
    private:
        ::History* hist;
        ::HistEvent ev;
    };
}

#endif /* SEYCHELLES_LIBEDIT_H_ */
