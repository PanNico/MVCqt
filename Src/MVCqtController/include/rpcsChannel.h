#ifndef RPCSCHANNEL_H
#define RPCSCHANNEL_H

#include <MVCqt/MVCqtActor/mvcqtDebug.h>
#include <QMutex>
#include <QWaitCondition>

class RpcsChannel{
    public:
        RpcsChannel() :
            stop(false),
            received_rpc(false),
            rpc_string("")
        {
        #ifdef MVC_QT_DEBUG
            print_str("RpcsChannel created");
        #endif
        }

        ~RpcsChannel()
        {
        #ifdef MVC_QT_DEBUG
            print_str("RpcsChannel destructor");
        #endif
        }

        void writeRpc(std::string msg){
            if(stop) return;
            do{
            #ifdef MVC_QT_DEBUG
                print_str("RpcsChannel writeRpc");
            #endif

                variable_guard.lock();
                if(!received_rpc){
                    rpc_string=msg;
                    received_rpc=true;
                    variable_guard.unlock();
                    readable.wakeAll();
                    return;
                }
                variable_guard.unlock();
            #ifdef MVC_QT_DEBUG
                print_str("RpcsChannel: write sleeping wait...");
            #endif
                writeable.wait(&rpcs_mutex);
                stop_guard.lock();
                    if(stop){
                    #ifdef MVC_QT_DEBUG
                        print_str("RpcsChannel: ending write channel");
                    #endif
                        rpc_string="";
                        received_rpc=false;
                        stop_guard.unlock();                      
                    #ifdef MVC_QT_DEBUG
                        print_str("RpcsChannel: ended write channel");
                    #endif
                        return;
                    }
                stop_guard.unlock();
            }while(true);

        }

        std::string readRpc(){
            if(stop) return "";
            do{
            #ifdef MVC_QT_DEBUG
                print_str("RpcsChannel readRpc");
            #endif
                variable_guard.lock();
                if(received_rpc){
                    std::string toRet = rpc_string;
                    rpc_string="";
                    received_rpc=false;
                    variable_guard.unlock();
                    writeable.wakeAll();
                    return toRet;
                }
                variable_guard.unlock();
            #ifdef MVC_QT_DEBUG
                print_str("RpcsChannel: read sleeping wait...");
            #endif
                readable.wait(&rpcs_mutex);
                stop_guard.lock();
                    if(stop){
                    #ifdef MVC_QT_DEBUG
                        print_str("RpcsChannel: ending read channel");
                    #endif
                        rpc_string="";
                        received_rpc=false;
                        stop_guard.unlock();
                    #ifdef MVC_QT_DEBUG
                        print_str("RpcsChannel: ended read channel");
                    #endif
                        return "";
                    }
                stop_guard.unlock();

            }
            while(true);

        }

        void close_channel(){
        #ifdef MVC_QT_DEBUG
            print_str("RpcsChannel: called close_channel()");
        #endif
            stop_guard.lock();
            stop=true;
            readable.wakeAll();
            writeable.wakeAll();
            stop_guard.unlock();
        }

    private:
        bool stop;
        bool received_rpc=false;
        std::string rpc_string="";
        QMutex rpcs_mutex;
        QMutex variable_guard;
        QMutex stop_guard;
        QWaitCondition readable;
        QWaitCondition writeable;


};

#endif // RPCSCHANNEL_H
