//
// Created by Артем Белявский on 8/18/21.
//

#include "config_thread.h"
#include "../functions/aserco_api_functions.h"
#include "../functions/parse_config_functions.h"
#include "../data/data_box.h"


using namespace THREADS;
using namespace DATA;
using namespace FUNCTIONS;
using namespace TYPES;
using namespace std;

shared_ptr<ConfigThread> g_configurator_obj;
bool g_configurator_need_stoped = false;

void ConfiguratorRun(){
    while(true){
        if (g_configurator_need_stoped) {
            return;
        }

        Parse_RemoteConfig(make_shared<string>(""));
        //Get_RemoteConfig();//добавлено в полседующих обновлениях

        this_thread::sleep_for(chrono::minutes(1));
    }
}

ConfigThread::~ConfigThread() {
}

ConfigThread::ConfigThread() :
        _is_runing(false) {
}

shared_ptr<MyThread> ConfigThread::GetThread() {
    if (!g_configurator_obj) {
        g_configurator_obj.reset(new ConfigThread);
    }

    return g_configurator_obj;
}

bool ConfigThread::Run() {
    if (_is_runing == false) {
        _thread.reset(new thread(ConfiguratorRun));
        _is_runing = true;
        return true;
    } else {
        return false;
    }
}

void ConfigThread::Terminate() {
    g_configurator_need_stoped = true;

    if (_is_runing) {
        _thread->join();
        _thread.reset(nullptr);
        _is_runing = false;
    }

    g_configurator_need_stoped = false;
}

void ConfigThread::Check() {
    if (_is_runing) {
        if (_thread || !_thread->joinable()) {
            _thread.reset(new thread(ConfiguratorRun));
            g_data_box->log_box->Push(make_shared<string>("\"ConfigThread::Check\""),
                                      Log_Type::DEBUG);
        }
    }
}

