#ifndef MODELIMP_H
#define MODELIMP_H

#include <MVCqt/mvcqt.h>

class WebPageModel : public MVCqtModel
{
    public:
        WebPageModel();
        void run() override;

        void printHello(){
           QVector<QString> res=query_ui_fields("get_form_infos", {"#contact_name", "#contact_email", "#contact_message"});
           for(auto str : res) print_str(str);
        }

};

#endif // MODELIMP_H
