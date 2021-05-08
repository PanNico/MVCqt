#ifndef MVCQTMODEL_H
#define MVCQTMODEL_H

#include <MVCqt/MVCqtActor/mvcqtActor.h>

class MVCqtModel : public MVCqtActor
{
    Q_OBJECT

    public:
       MVCqtModel(QObject *parent = nullptr);
       ~MVCqtModel();

    public slots:
        void controller_channel_rx(QString cmd) override;

    private:
        void actorStart() override;
        void actorStop() override;

};

#endif // MVCQTMODEL_H
