#ifndef MVCQTVIEW_H
#define MVCQTVIEW_H

#include <MVCqt/MVCqtActor/mvcqtActor.h>

class MVCqtView : public MVCqtActor
{
    Q_OBJECT

    public:
        explicit MVCqtView(QObject *parent = nullptr);
        ~MVCqtView();

    public slots:
       void model_channel_rx(const QString cmd);

    private:
       void actorStart() override;
       void actorStop() override;
       bool cmds_controller_channel(const QString cmd) override; // must return true if the comand has been recognized else false

    signals:
       void model_channel_tx(const QString cmd);

};

#endif // MVCQTVIEW_H
