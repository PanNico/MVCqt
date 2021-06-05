#ifndef RPCSCHANNEL_H
#define RPCSCHANNEL_H

#include <QMutex>
#include <QWaitCondition>

class RpcsChannel{
    public:
        RpcsChannel() :
            stop(false),
            received_rpc(false),
            rpc_string("")
            {}

        void writeRpc(std::string msg){
            do{
                variable_guard.lock();
                if(!received_rpc){
                    rpc_string=msg;
                    received_rpc=true;
                    variable_guard.unlock();
                    readable.wakeAll();
                    return;
                }
                variable_guard.unlock();
                writeable.wait(&rpcs_mutex);
                stop_guard.lock();
                    if(stop){
                        rpc_string="";
                        received_rpc=false;
                        stop_guard.unlock();
                        return;
                    }
                stop_guard.unlock();
            }while(true);


        }

        std::string readRpc(){
            do{
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
                readable.wait(&rpcs_mutex);
                stop_guard.lock();
                    if(stop){
                        rpc_string="";
                        received_rpc=false;
                        stop_guard.unlock();
                        return "";
                    }
                stop_guard.unlock();

            }
            while(true);

        }

        void close_channel(){
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
