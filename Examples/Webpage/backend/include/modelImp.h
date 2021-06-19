#ifndef MODELIMP_H
#define MODELIMP_H

#include <MVCqt/mvcqt.h>

class WebPageModel : public MVCqtModel
{
    public:
        WebPageModel();
        void run() override;

        void printHello(){
            query_ui_fields("get_form_infos", {"#contact_name", "#contact_email", "#contact_message"});
        }

};

#endif // MODELIMP_H
