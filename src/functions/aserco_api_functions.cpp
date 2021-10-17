//
// Created by Артем Белявский on 8/18/21.
//

#include "aserco_api_functions.h"

#include "parse_config_functions.h"
#include "../data/data_box.h"
#include "../threads/http_client.h"
#include <iostream>

using namespace FUNCTIONS;
using namespace DATA;
using namespace THREADS;
using namespace TYPES;
using namespace std;

using namespace web;
using namespace http;
using namespace client;
using namespace utility;
using namespace concurrency;

bool FUNCTIONS::Get_RemoteConfig(){

    http_request http_req;
    http_req.headers().add(U("token"), U(g_data_box->market_config->aserco_key.c_str()));
    uri_builder http_builder(U(""));//
    http_req.set_method(methods::GET);
    http_req.set_request_uri(http_builder.to_string());

    shared_ptr<string> req_msg;
    try {
        auto http_res = g_aserco_client->request(http_req).get();
        auto status_code = http_res.status_code();
        if (status_code == 200) {
            req_msg = make_shared<string>(http_res.extract_string().get());
        } else {
            auto err_msg = make_shared<string>(
                    string("\"Error REST-request (Get_RemoteConfig) for Aserco\",\"status_code\":")
                    + to_string(status_code));
            g_data_box->log_box->Push(err_msg, Log_Type::ERR_ASERCO);

        }
    } catch (const std::exception &e) {
        auto err_msg = make_shared<string>(
                string("\"Error REST-request (Get_RemoteConfig) for Aserco\",\"err_msg\":\"") + e.what()
                + "\"");
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_ASERCO);
    } catch (...) {
        auto err_msg = make_shared<string>(
                string("\"Error REST-request (Get_RemoteConfig) for Aserco (undefined catch)\""));
        g_data_box->log_box->Push(err_msg, Log_Type::ERR_ASERCO);
    }

    return Parse_RemoteConfig(req_msg);
}

