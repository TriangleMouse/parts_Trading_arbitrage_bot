//
// Created by Артем Белявский on 8/12/21.
//

#include "../helpers/math.h"
#include "orderbook_thread.h"
#include "http_client.h"
#include "../data/data_box.h"
#include "../functions/binance_api_functions.h"
#include "../functions/binance_parse_functions.h"
#include "cpprest/http_client.h"
#include "cpprest/details/http_helpers.h"
#include "cpprest/http_msg.h"
#include "iostream"
#include "cmath"
#include <string>
#include <list>
#include <memory>

using namespace DATA;
using namespace TYPES;
using namespace THREADS;
using namespace FUNCTIONS;

using namespace web;
using namespace http;
using namespace client;
using namespace utility;
using namespace concurrency;

using namespace std;

shared_ptr<OrderBook_Thread> g_booker_obj;
bool g_booker_need_stoped = false;

//Order Book Бинанса
void BinanceOrderBookRun(){
    *g_data_box->time = time(nullptr);
    Active_Binance_Symbols(); //получаем информацию о символах

  while (true) {
        if (g_booker_need_stoped) {
            return;
        }

        auto symbol_names = g_data_box->market_info->GetBinanceSymbolNames();
        for (auto symbol : symbol_names) {
            uri_builder http_builder(U("/api/v3/depth"));
            http_request http_req;
            http_req.set_method(methods::GET);
            http_builder.append_query(U("symbol"), U(symbol.c_str()));
            http_builder.append_query(U("limit"), U("5000"));
            http_req.set_request_uri(http_builder.to_string());

            shared_ptr<string> req_msg;
            try {
                auto req_result = g_binance_public_client->request(http_req).get();
                auto status_code = req_result.status_code();
                if (status_code == 200) {
                    auto data = req_result.extract_json().get().serialize();
                    req_msg = make_shared<string>(data.begin(), data.end());
                } else {
                    auto err_msg =make_shared<string>(string("\"Error REST-request (BinanceOrderBookRun) for Binance\",\"status_code\":")+ to_string(status_code));
                    g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
                    continue;
                }
            } catch (const std::exception &e) {
                auto err_msg = make_shared<string>(string("\"Error REST-request (BinanceOrderBookRun) for Binance\",\"err_msg\":\"")+ e.what() + "\"");
                g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
                continue;
            } catch (...) {
                auto err_msg =
                        make_shared<string>(
                                string(
                                        "\"Error REST-request (BinanceOrderBookRun) for Binance (undefined catch)\""));
                g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
                continue;
            }

            list<MarketItem> ask;
            list<MarketItem> bid;
            if (Parse_BinanceMarketTickets(ask, bid, req_msg)) {
                auto market = g_data_box->binance_market->FindMarket(symbol);
                if (market) {
                    market->UpdateAskItem(ask);
                    market->UpdateBidItem(bid);
                }
            } else {
                auto err_msg = make_shared<string>(string("\"Error parse (BinanceOrderBookRun)\""));
                g_data_box->log_box->Push(err_msg, Log_Type::ERR_PARSE);
            }
        }
        this_thread::sleep_for(chrono::seconds(1));//добавить переменную времени
    }
}



OrderBook_Thread::OrderBook_Thread() :
        _is_runing(false) {
}

OrderBook_Thread::~OrderBook_Thread() {
    Terminate();
    g_data_box->log_box->Push(make_shared<string>("\"~OrderBook_Thread\""), Log_Type::DEBUG);
}

shared_ptr<MyThread> OrderBook_Thread::GetThread() {
    if (!g_booker_obj) {
        g_booker_obj.reset(new OrderBook_Thread);
    }
    return g_booker_obj;
}

bool OrderBook_Thread::Run() {
    if (_is_runing == false) {
        if (g_data_box->market_config->binance_enable) {
            _binance_thread.reset(new thread(BinanceOrderBookRun));
        }
        _is_runing = true;
        return true;
    } else {
        return false;
    }
}

void OrderBook_Thread::Terminate() {
    g_booker_need_stoped = true;

    if (_is_runing) {
        if (g_data_box->market_config->binance_enable) {
            _binance_thread->join();
        }
        _binance_thread.reset(nullptr);
        _is_runing = false;
    }

    g_booker_need_stoped = false;
}

void OrderBook_Thread::Check() {
    if (_is_runing) {
        if (_binance_thread || !_binance_thread->joinable()) {
            _binance_thread.reset(new thread(BinanceOrderBookRun));
            g_data_box->log_box->Push(make_shared<string>("\"OrderBook_Thread::Check (Binance)\""), Log_Type::DEBUG);
        }
    }
}

