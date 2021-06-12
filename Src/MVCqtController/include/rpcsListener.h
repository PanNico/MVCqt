#ifndef RPCSLISTENER_H
#define RPCSLISTENER_H

#include "rpcsChannel.h"
#include <unordered_map>
#include <MVCqt/MVCqtActor/mvcqtDebug.h>
#include <QMutex>
#include <memory>

template <class CustomModel>
class RpcsListener{

    public:
        typedef void (CustomModel::*ModelMethod)();
        RpcsListener(RpcsChannel &_rpcs_channel, std::shared_ptr<CustomModel> _model, std::unordered_map<std::string,ModelMethod>& _names_to_methods) :
            rpcs_channel(_rpcs_channel),
            model(_model),
            names_to_methods(_names_to_methods),
            stop(true)
        {
        #ifdef MVC_QT_DEBUG
            print_str("RpcsListener constructor");
        #endif
        }

        ~RpcsListener()
        {
        #ifdef MVC_QT_DEBUG
            print_str("RpcsListener destructor");
        #endif
        }

        void stopListener()
        {
        #ifdef MVC_QT_DEBUG
            print_str("RpcsListener stopListener");
        #endif
            stopMutex.lock();
            stop=true;
            stopMutex.unlock();

        }

        bool isStopped()
        {
            bool toRet;
            stopMutex.lock();
            toRet=stop;
            stopMutex.unlock();
            return toRet;
        }

        void operator()()
        {
            stop=false;
        #ifdef MVC_QT_DEBUG
            print_str("RpcsListener started.");
        #endif
            while(!isStopped()){

                std::string cmd=rpcs_channel.readRpc();

        #ifdef MVC_QT_DEBUG
            std::ostringstream ss;
            ss << "RpcsListener received rpc " << cmd;
            print_str(ss);
        #endif
                auto iter=names_to_methods.find(cmd);

                if(iter != names_to_methods.end()){
                    CustomModel& mod_ref=*model;
                    ModelMethod metod=iter->second;

                #ifdef MVC_QT_DEBUG
                    print_str("RpcsListener running rpc...");
                #endif
                    (mod_ref.*metod)();
                #ifdef MVC_QT_DEBUG
                    print_str("RpcsListener rpc executed!");
                #endif
                }
                else{
                #ifdef MVC_QT_DEBUG
                    print_str("RpcsListener warning: rpc not found");
                    print_str("RpcsListener registered rpcs:");

                    for(auto ptr=names_to_methods.begin(); ptr != names_to_methods.end(); ptr++)
                        print_str(ptr->first);
                #endif
                }

            }

        #ifdef MVC_QT_DEBUG
            print_str("RpcsListener stopped.");
        #endif
        }
    private:
        RpcsChannel &rpcs_channel;
        std::shared_ptr<CustomModel> model;
        std::unordered_map<std::string,ModelMethod>& names_to_methods;
        bool stop;
        QMutex stopMutex;
};

#endif // RPCSLISTENER_H
