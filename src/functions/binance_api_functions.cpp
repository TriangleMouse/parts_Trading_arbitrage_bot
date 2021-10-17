//
// Created by Артем Белявский on 8/11/21.
//

#include "../helpers/hmac_sha256.hpp"
#include "binance_api_functions.h"
#include "binance_parse_functions.h"

using namespace DATA;
using namespace TYPES;
using namespace THREADS;
//using namespace HELPERS;

using namespace std;
using namespace web;
using namespace http;
using namespace client;
using namespace utility;
using namespace concurrency;
using namespace chrono;


bool FUNCTIONS::Active_Binance_Symbols(){
    cout<<"1"<<endl;
    uri_builder http_builder(U("/api/v3/exchangeInfo"));
    http_request http_req;
    http_req.set_method(methods::GET);
    http_req.set_request_uri(http_builder.to_string());

    shared_ptr<string> req_msg;
    try {
        auto req_result = g_binance_public_client->request(http_req).get();
        auto status_code = req_result.status_code();
        if (status_code == 200) {
            req_msg = make_shared<string>(req_result.extract_string().get());
            cout<<req_msg<<endl;
        } else {
            auto err_msg = make_shared<string>(
                    string("\"Error REST-request (Active_Binance_Symbols) for Binance\",\"status_code\":")
                    + to_string(status_code));
            g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
        }
    } catch (const std::exception &e) {
        auto err_msg = make_shared<string>(
                string("\"Error REST-request (Active_Binance_Symbols) for Binance\",\"err_msg\":\"")
                + e.what() + "\"");
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
    } catch (...) {
        auto err_msg = make_shared<string>(
                string("\"Error REST-request (Active_Binance_Symbols) for Binance (undefined catch)\""));
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
    }

    if (Parse_Active_BinanceSymbols(req_msg) == g_data_box->market_info->GetBinanceSymbolNames().size()) {
        return true;
    } else {
        string msg = req_msg ? *req_msg : string("\"NULL\"");
        auto err_msg = make_shared<string>(
                string("\"Error Active_Binance_Symbols symbols number uncorrected \",\"need_number\":")
                + to_string(g_data_box->market_info->GetBinanceSymbolNames().size())
                + string(",\"data\":") + msg);
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
        return false;
    }



}

bool FUNCTIONS::Active_Binance_Balance() {
    uri_builder http_builder(U("/api/v3/account"));
    http_request http_req;
    http_req.headers().add(U("X-MBX-APIKEY"), U(g_data_box->market_config->binance_key.c_str()));
    string params = "recvWindow=60000";
    params.append(string("&timestamp=")+to_string(duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count()));
    HMAC_SHA256 hmac_sha256(g_data_box->market_config->binance_secret, params);
    params.append(string("&signature=")+string(hmac_sha256.hex_digest().c_str()));
    http_builder.append_query(U(params.c_str()));
    http_req.set_method(methods::GET);
    http_req.set_request_uri(http_builder.to_string());

    shared_ptr<string> req_msg;
    try {
        auto req_result = g_binance_secret_client->request(http_req).get();
        auto status_code = req_result.status_code();
        if (status_code == 200) {
            req_msg = make_shared<string>(req_result.extract_string().get());
        } else {
            auto err_msg = make_shared<string>(
                    string("\"Error REST-request (Active_Binance_Balance) for Binance\",\"status_code\":")
                    + to_string(status_code));
            g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
        }
    } catch (const std::exception &e) {
        auto err_msg = make_shared<string>(
                string("\"Error REST-request (Active_Binance_Balance) for Binance\",\"err_msg\":\"")
                + e.what() + "\"");
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
    } catch (...) {
        auto err_msg = make_shared<string>(
                string("\"Error REST-request (Active_Binance_Balance) for Binance (undefined catch)\""));
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
    }
    //cout <<params<< endl;
    //cout <<*req_msg<< endl;

    if (Parse_Active_BinanceBalance(req_msg)) {
        return true;
    } else {
        string msg = req_msg ? *req_msg : string("\"NULL\"");
        auto err_msg = make_shared<string>(
                string("\"Error Active_Binance_Balance parse fail\",\"data\":") + msg);
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_PARSE);
        //this_thread::sleep_for(chrono::seconds(1));
        return false;
    }

}

bool FUNCTIONS::Binance_Best_Price_Symbol(const std::string &symbol){
    uri_builder http_builder(U("/api/v3/ticker/bookTicker"));
    http_request http_req;
    http_req.set_method(methods::GET);
    string params="symbol=";
    params.append(symbol);
    http_builder.append_query(U(params.c_str()));
    http_req.set_request_uri(http_builder.to_string());

    shared_ptr<string> req_msg;
    try {
        auto req_result = g_binance_public_client->request(http_req).get();
        auto status_code = req_result.status_code();
        if (status_code == 200) {
            req_msg = make_shared<string>(req_result.extract_string().get());
        } else {
            auto err_msg = make_shared<string>(
                    string("\"Error REST-request (Binance_Best_Price_Symbol) for Binance\",\"status_code\":")
                    + to_string(status_code));
            g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
        }
    } catch (const std::exception &e) {
        auto err_msg = make_shared<string>(
                string("\"Error REST-request (Binance_Best_Price_Symbol) for Binance\",\"err_msg\":\"")
                + e.what() + "\"");
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
    } catch (...) {
        auto err_msg = make_shared<string>(
                string("\"Error REST-request (Binance_Best_Price_Symbol) for Binance (undefined catch)\""));
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
    }
    if (Parse_Binance_Best_Price_Symbol(req_msg,symbol)) {
        return true;
    } else {
        string msg = req_msg ? *req_msg : string("\"NULL\"");
        auto err_msg = make_shared<string>(
                string("\"Error Binance_Best_Price_Symbol symbols number uncorrected \",\"need_number\":")
                + to_string(g_data_box->market_info->GetBinanceSymbolNames().size())
                + string(",\"data\":") + msg);
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_BINANCE);
        return false;
    }

}