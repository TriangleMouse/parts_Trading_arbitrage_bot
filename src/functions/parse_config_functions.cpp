//
// Created by Артем Белявский on 8/16/21.
//

#include "parse_config_functions.h"
#include "../data/data_box.h"
#include "../threads/http_client.h"
#include <rapidjson/document.h>

#include "../helpers/math.h"

#include "iostream"
#include <string>
#include <unistd.h>
#include <limits.h>

using namespace FUNCTIONS;
using namespace DATA;
using namespace TYPES;
using namespace THREADS;
using namespace rapidjson;
using namespace std;

bool FUNCTIONS::Parse_Local_ConfigFile() {
    char work_directory[PATH_MAX]; // rename variable
    ifstream config_json_file(string(getcwd(work_directory, PATH_MAX)) + "/config.json");
    if(!config_json_file.is_open()){
        cout << "Parse_Local_ConfigFile config.json undefined" << endl;
        return false;
    }
    string json;
    getline(config_json_file, json, (char) config_json_file.eof());
    Document json_document;
    json_document.Parse(json.c_str());

   web::http::client::http_client_config aserco_http_conf;
    aserco_http_conf.set_validate_certificates(false);

    if (!json_document.IsObject()) {
        auto msg = make_shared<string>("Invalid Parse_Local_ConfigFile");
        g_data_box->log_box->Push(msg, DATA::TYPES::Log_Type::ERR_MODEL);
        cout << "Parse_Local_ConfigFile config.json not constitute JSON" << endl;
        return false;
    }

    if (json_document.HasMember("aserco_host") && json_document["aserco_host"].IsString()
        && json_document.HasMember("moscow_host") && json_document["moscow_host"].IsString()
        && json_document.HasMember("binance_host") && json_document["binance_host"].IsString()) {
        g_data_box->market_config->aserco_host = json_document["aserco_host"].GetString();
        g_data_box->market_config->moscow_host = json_document["moscow_host"].GetString();
        g_data_box->market_config->binance_host = json_document["binance_host"].GetString();
    } else {
        auto msg = make_shared<string>("Invalid Parse_Local_ConfigFile");
        g_data_box->log_box->Push(msg, DATA::TYPES::Log_Type::ERR_MODEL);
        cout << "Parse_Local_ConfigFile config.json host not found" << endl;
        return false;
    }


    THREADS::g_aserco_client = new web::http::client::http_client(
            U(g_data_box->market_config->aserco_host.c_str()), aserco_http_conf);
    THREADS::g_moscowExchange_public_client = new web::http::client::http_client(
            U(g_data_box->market_config->moscow_host.c_str()));
    THREADS::g_binance_secret_client = new web::http::client::http_client(
            U(g_data_box->market_config->moscow_host.c_str()));
    THREADS::g_binance_secret_client = new web::http::client::http_client(
            U(g_data_box->market_config->binance_host.c_str()));
    THREADS::g_binance_public_client = new web::http::client::http_client(
            U(g_data_box->market_config->binance_host.c_str()));

    if (json_document.HasMember("aserco_token") && json_document["aserco_token"].IsString()
        && json_document.HasMember("moscow_token") && json_document["moscow_token"].IsString()
        && json_document.HasMember("binance_key") && json_document["binance_key"].IsString()
        && json_document.HasMember("binance_secret") && json_document["binance_secret"].IsString()
        && json_document.HasMember("aserco_bot_user_id") && json_document["aserco_bot_user_id"].IsInt()) {
        g_data_box->market_config->aserco_key = U(json_document["aserco_token"].GetString());
        g_data_box->market_config->moscow_key = U(json_document["moscow_token"].GetString());
        g_data_box->market_config->binance_key = U(json_document["binance_key"].GetString());
        g_data_box->market_config->binance_secret = U(json_document["binance_secret"].GetString());
        g_data_box->market_config->aserco_bot_user_id = json_document["aserco_bot_user_id"].GetInt();
    } else {
        auto msg = make_shared<string>("Invalid Parse_Local_ConfigFile");
        g_data_box->log_box->Push(msg, DATA::TYPES::Log_Type::ERR_MODEL);
        cout << "Parse_Local_ConfigFile config.json param not found" << endl;
        return false;
    }

    return true;
}




bool FUNCTIONS::Parse_RemoteConfig(shared_ptr<string> msg) {
    /////////////////////// Когда появится сайт удалить
    char work_directory[PATH_MAX]; // rename variable
    ifstream config_json_file(string(getcwd(work_directory, PATH_MAX)) + "/config_site.json");
    if(!config_json_file.is_open()){
        cout << "Parse_Local_ConfigFile config.json undefined" << endl;
        return false;
    }
    string json;
    getline(config_json_file, json, (char) config_json_file.eof());
    msg=make_shared<string>(json);



    ///////////////////////

    if (!msg) {
        auto err_msg = make_shared<string>("Invalid Parse_RemoteConfig");
        g_data_box->log_box->Push(err_msg, DATA::TYPES::Log_Type::ERR_MODEL);

        return false;
    }

    Document doc;
    doc.Parse(msg->c_str());

    if(!(doc.IsObject() && doc["bots"].IsArray()))
    {
        auto msg = make_shared<string>("Invalid Parse_RemoteConfig");
        g_data_box->log_box->Push(msg, DATA::TYPES::Log_Type::ERR_MODEL);

        return false;
    }

    for(auto& setting : doc["bots"].GetArray()){
        if(g_data_box->market_config->aserco_bot_user_id == setting["user_id"].GetInt64()
           && setting.HasMember("starting_volume") && setting["starting_volume"].IsDouble()
           && setting.HasMember("disregarded_offer_vol") && setting["disregarded_offer_vol"].IsDouble()
           && setting.HasMember("to_hedge_vol") && setting["to_hedge_vol"].IsDouble()
           && setting.HasMember("pairs") && setting["pairs"].IsArray()
        ){

            g_data_box->market_config->starting_volume=setting["starting_volume"].GetDouble();
            g_data_box->market_config->disregarded_offer_vol=setting["disregarded_offer_vol"].GetDouble();
            g_data_box->market_config->to_hedge_vol=setting["to_hedge_vol"].GetDouble();

            if(setting.HasMember("time_upd_orderbook") && setting["time_upd_orderbook"].IsInt()>0){
                g_data_box->market_config->time_upd_orderbook = setting["time_upd_orderbook"].GetInt();

            }
            if(setting.HasMember("time_check_arbitrage") && setting["time_check_arbitrage"].IsInt()>0){
                g_data_box->market_config->time_check_arbitrage = setting["time_check_arbitrage"].GetInt();

            }
            if(setting.HasMember("time_upd_balance") && setting["time_upd_balance"].IsInt()>0){
                g_data_box->market_config->time_upd_balance = setting["time_upd_balance"].GetInt();

            }

            if(setting["time_death_task"].GetInt() > 14){
                g_data_box->market_config->death_task_timer = setting["time_death_task"].GetInt();

            }
            if(setting["time_waiting_ticket_event"].GetInt() > 14){
                g_data_box->market_config->waiting_ticket_event = setting["time_waiting_ticket_event"].GetInt();

            }

            for(auto& pair_setting : setting["pairs"].GetArray()){
                auto pair_item = g_data_box->market_info->FindSymbolInfo(pair_setting["binance_pair"].GetString());

                if (pair_item) {

                    pair_item->min_spread(pair_setting["min_spread"].GetDouble());
                    pair_item->binance_disregarded_bid_vol(pair_setting["binance_disregarded_bid_vol"].GetDouble());
                    pair_item->binance_disregarded_ask_vol(pair_setting["binance_disregarded_ask_vol"].GetDouble());


                    cout<<HELPERS::DoubleToString(pair_item->min_spread())<<endl;
                    cout<<HELPERS::DoubleToString(pair_item->binance_disregarded_bid_vol())<<endl;
                    cout<<HELPERS::DoubleToString(pair_item->binance_disregarded_ask_vol())<<endl;
                    cout<<pair_item->moscow_name()<<endl;
                    cout<<pair_item->binance_name()<<endl;
                    continue;
                }

                auto new_symbol_item = make_shared<SymbolInfo>();
                new_symbol_item->binance_name(pair_setting["binance_pair"].GetString());
                new_symbol_item->flagship_store(Market_Type::BINANCE);
                new_symbol_item->moscow_name(pair_setting["moscow_pair"].GetString());
                new_symbol_item->market_type(Market_Type::MOSCOW_EXCHANGE);

                new_symbol_item->min_spread(pair_setting["min_spread"].GetDouble());
                new_symbol_item->binance_disregarded_bid_vol(pair_setting["binance_disregarded_bid_vol"].GetDouble());
                new_symbol_item->binance_disregarded_ask_vol(pair_setting["binance_disregarded_ask_vol"].GetDouble());

                g_data_box->market_info->PushSymbolInfo(new_symbol_item);

                auto new_status_item = make_shared<SymbolStatus>();
                new_status_item->name(new_symbol_item->name());
                g_data_box->market_info->PushSymbolStatus(new_status_item);

                new_symbol_item = g_data_box->market_info->FindSymbolInfo(
                        new_symbol_item->binance_name());

                if (new_symbol_item) {
                    g_data_box->binance_market->CreateMarket(new_symbol_item);
                    g_data_box->binance_market->CreadOrdersBox(new_symbol_item);
                    g_data_box->market_config->binance_enable = true;
                    g_data_box->market_config->moscow_enable = true;
                    g_data_box->moscow_market->CreateMarket(new_symbol_item);
                    g_data_box->moscow_market->CreadOrdersBox(new_symbol_item);

                }

            }


        }
        else {
            auto msg = make_shared<string>("Invalid Parse_Active_Config");
            g_data_box->log_box->Push(msg, DATA::TYPES::Log_Type::ERR_MODEL);
            return false;
        }
    }

    return true;
}



