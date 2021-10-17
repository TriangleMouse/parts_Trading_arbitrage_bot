#include "data/data_box.h"
#include "threads/config_thread.h"
#include "threads/orderbook_thread.h"
#include "threads/http_client.h"
#include "functions/parse_config_functions.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <csignal>
#include <list>
#include <unistd.h>

using namespace DATA;
//using namespace TYPES;
using namespace THREADS;
using namespace FUNCTIONS;
using namespace std;

DataBox* DATA::g_data_box;
web::http::client::http_client* THREADS::g_aserco_client;
web::http::client::http_client* THREADS::g_moscowExchange_secret_client;
web::http::client::http_client* THREADS::g_moscowExchange_public_client;
web::http::client::http_client* THREADS::g_binance_secret_client;
web::http::client::http_client* THREADS::g_binance_public_client;

auto configurator = ConfigThread::GetThread();
auto orderbook_thread = OrderBook_Thread::GetThread();
auto loger = LogSender_Thread::GetThread();//Реализация Вырезана

list<shared_ptr<MyThread>> threads;


void stop_handler(int) {
    g_data_box->log_box->Push(make_shared<string>("\"Main STOP. Tickets destroyed success\""),Log_Type::DEBUG);
    g_data_box->log_box->Push(make_shared<string>("\"Main EXIT. Wait...\""), Log_Type::DEBUG);
    exit(0);
}

void destroy_handler(int s) {
    //g_data_box->log_box->Push(make_shared<string>("\"Main STOP. Wait...\""), Log_Type::DEBUG);

    g_data_box->log_box->Push(make_shared<string>("\"Wait... Tickets destroyed \""), Log_Type::DEBUG);
    configurator->Terminate();
    orderbook_thread->Terminate();
    g_data_box->log_box->Push(make_shared<string>("\"Main STOP. success\""), Log_Type::DEBUG);
    this_thread::sleep_for(chrono::seconds(1));
    loger->Terminate();

    if (s == SIGINT) {
        exit(0);
    }
}




int main() {
    signal(SIGINT, destroy_handler);
    signal(SIGUSR1, destroy_handler);

    signal(SIGTERM, stop_handler);
    signal(SIGKILL, stop_handler);
    g_data_box = new DataBox;
    g_data_box->binance_market.reset(new StockMarket);
    g_data_box->moscow_market.reset(new StockMarket);
    g_data_box->market_info.reset(new StockMarketInfo);
    g_data_box->market_config.reset(new LocalConfig);
    g_data_box->log_box.reset(new LogCreator_Queue);

    cout << "Main RUN" << endl;

    if (!Parse_Local_ConfigFile()) {
        cout << "Main ./config.json failed" << endl;
        return 1;
    }

    cout << "Main parsed local CONFIG" << endl;


    if (!(Parse_RemoteConfig(make_shared<string>("")))) {
        cout << "Main aserco REST config failed" << endl;
        return 1;
    }

    cout << "Main parsed CONFIG from server" << endl;

    //Запускаем потоки
    if (configurator->Run() && loger->Run() && ) {
        //проверяем получены ли первоначальные настройки
        //Реализация Вырезана
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    g_data_box->log_box->Push(make_shared<string>("\"Main START\""), Log_Type::DEBUG);


    threads.push_back(loger);
    threads.push_back(orderbook_thread);
    //Реализация верезана(другие потоки)


    while (true) {
        this_thread::sleep_for(chrono::seconds(60));
       // for (auto it : threads) {
            //			it->Check();
       // }
    }
    return 0;
}
