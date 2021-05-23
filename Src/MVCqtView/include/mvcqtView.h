/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#ifndef MVCQTVIEW_H
#define MVCQTVIEW_H

#include <MVCqt/MVCqtActor/mvcqtActor.h>
#include <QWebEngineView>
#include <QPointer>

class MVCqtView : public MVCqtActor
{
    Q_OBJECT

    public:
        explicit MVCqtView(const int _width, const int _height, QObject *parent = nullptr);
        ~MVCqtView();

    public slots:
       void model_channel_rx(const QString cmd);

    protected:
       QPointer<QWebEngineView> html_window;

    private:
       const QString html_dir;
       const int width;
       const int height;

       void actorStart() override;
       void actorStop() override;
       bool cmds_controller_channel(const QString cmd) override; // must return true if the comand has been recognized else false

    private slots:
       void urlChanged(const QUrl &url);
       void loadStarted();

    signals:
       void model_channel_tx(const QString cmd);

};

#endif // MVCQTVIEW_H
