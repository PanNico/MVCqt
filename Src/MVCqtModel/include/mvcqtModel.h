#ifndef MVCQTMODEL_H
#define MVCQTMODEL_H

#include <MVCqt/MVCqtActor/mvcqtActor.h>

class MVCqtModel : public MVCqtActor
{
    Q_OBJECT

    public:
       MVCqtModel(QObject *parent = nullptr);
       ~MVCqtModel();


    private:
       void actorStart() override;
       void actorStop() override;
       bool cmds_controller_channel(const QString cmd) override; // must return true if the comand has been recognized else false



};

#endif // MVCQTMODEL_H
