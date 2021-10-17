//
// Created by Артем Белявский on 8/11/21.
//

#include "binance_parse_functions.h"
#include "../data/types/market_type.h"
#include "iostream"
#include <cmath>
#include <string>

unsigned FUNCTIONS::Parse_Active_BinanceSymbols(shared_ptr<string> msg){
    unsigned result = 0;
    if (!msg || msg->size() == 0) {
        auto err_msg = make_shared<string>("Invalid Parse_Active_BinanceSymbols");
        g_data_box->log_box->Push(err_msg, DATA::TYPES::Log_Type::ERR_MODEL);

        return result;
    }

    Document doc;
    doc.Parse(msg->c_str());
    for (auto symbol : g_data_box->market_info->GetBinanceSymbolNames()) {
        for (auto& it : doc["symbols"].GetArray()) {
            if (it.HasMember("symbol") && it["symbol"].IsString() && string(it["symbol"].GetString()) == symbol
                && it.HasMember("filters")) {
                Double min_price,min_amount,max_price,min_total;
                for (auto& filter_val : it["filters"].GetArray()) {
                    if(string(filter_val["filterType"].GetString())=="PRICE_FILTER" && filter_val.HasMember("minPrice") && filter_val["minPrice"].IsString()  && filter_val.HasMember("maxPrice") && filter_val["maxPrice"].IsString()){
                        min_price = atof(filter_val["minPrice"].GetString());
                        max_price = atof(filter_val["maxPrice"].GetString());
                    }
                    else if(string(filter_val["filterType"].GetString())=="LOT_SIZE" && filter_val.HasMember("minQty") && filter_val["minQty"].IsString()){
                        min_amount =atof(filter_val["minQty"].GetString());
                    }
                    else if(string(filter_val["filterType"].GetString())=="MIN_NOTIONAL" && filter_val.HasMember("minNotional") && filter_val["minNotional"].IsString()){
                        min_total =atof(filter_val["minNotional"].GetString());
                    }
                }
                string baseAsset =it["baseAsset"].IsString() ? it["baseAsset"].GetString() : "";
                string quoteAsset =it["quoteAsset"].IsString() ? it["quoteAsset"].GetString() : "";
                auto symbol_info = g_data_box->market_info->FindSymbolInfo(symbol);
                if (symbol_info && symbol_info->flagship_store() != Market_Type::BINANCE) {
                    continue;
                }
                auto status = g_data_box->market_info->FindSymbolStatus(symbol);

                if (min_price && max_price && min_amount && status) {
                    if (min_amount > symbol_info->export_min_amount()) {
                        symbol_info->export_min_amount(min_amount);
                    }
                    if (min_price > symbol_info->min_price()) {
                        symbol_info->min_price(min_price);
                    }
                    if (max_price < symbol_info->max_price()) {
                        symbol_info->max_price(max_price);
                    }
                    symbol_info->binance_base_cur(baseAsset);
                    symbol_info->binance_quote_cur(quoteAsset);
                    symbol_info->binance_min_total(min_total);
                    status->binance_sub_status(true);
                    ++result;
                }
            }
        }
    }
    return result;
}

bool FUNCTIONS::Parse_BinanceMarketTickets(list<MarketItem>& ask_result, list<MarketItem>& bid_result,shared_ptr<string> msg) {
    ask_result.clear();
    bid_result.clear();

    if (!msg || msg->size() == 0) {
        auto err_msg = make_shared<string>("Invalid Parse_BinanceMarketTickets");
        g_data_box->log_box->Push(err_msg, DATA::TYPES::Log_Type::ERR_MODEL);

        return false;
    }

    Document doc;
    doc.Parse(msg->c_str());
    if (doc.IsObject()) {
        if (doc.HasMember("asks")) {
            auto& ask = doc["asks"];
            if (ask.IsArray()) {
                for (auto& it : ask.GetArray()) {
                    if (it.IsArray() && it.GetArray().Size() >= 2) {
                        auto item = it.GetArray();
                        Double price;
                        if (item[0].IsString()) {
                            price = atof(it[0].GetString());
                        }

                        Double size;
                        if (item[1].IsString()) {
                            size = atof(item[1].GetString());
                        }

                        if (price && size) {
                            ask_result.push_back( { price, size });
                            //g_data_box->log_box->Push(make_shared<string>("\"asks price:"+HELPERS::DoubleToString(price)+"  size:"+HELPERS::DoubleToString(size)), Log_Type::DEBUG);
                        }
                    }
                }
            }
        }

        if (doc.HasMember("bids")) {
            auto& bid = doc["bids"];
            if (bid.IsArray()) {
                for (auto& it : bid.GetArray()) {
                    if (it.IsArray() && it.GetArray().Size() >= 2) {
                        auto item = it.GetArray();
                        Double price;
                        if (item[0].IsString()) {
                            price = atof(it[0].GetString());
                        }

                        Double size;
                        if (item[1].IsString()) {
                            size = atof(item[1].GetString());
                        }

                        if (price && size) {
                            bid_result.push_back( { price, size });
                            //g_data_box->log_box->Push(make_shared<string>("\"bids price:"+HELPERS::DoubleToString(price)+"  size:"+HELPERS::DoubleToString(size)), Log_Type::DEBUG);
                        }
                    }
                }
            }
        }
    }

    return (ask_result.size() > 0 || bid_result.size() > 0);
}

bool FUNCTIONS::Parse_Active_BinanceBalance(shared_ptr<string> msg) {
    if (!msg || msg->size() == 0) {
        auto msg = make_shared<string>("Invalid Parse_Active_BinanceBalance");
        g_data_box->log_box->Push(msg, DATA::TYPES::Log_Type::ERR_MODEL);

        return false;
    }

    Document doc;
    doc.Parse(msg->c_str());

    if (!doc["balances"].IsArray()) {
        auto msg = make_shared<string>("Invalid Parse_Active_BinanceBalance");
        g_data_box->log_box->Push(msg, DATA::TYPES::Log_Type::ERR_MODEL);
        return false;
    }

    bool result = true;
    double balance_moderator = g_data_box->market_config->balance_moderator;


    for (auto& it : doc["balances"].GetArray()) {
        if (it.HasMember("asset") && it.HasMember("free")) {
            string currency = it["asset"].GetString();
            Double balance = atof(it["free"].GetString());
            for (auto symbol : g_data_box->market_info->GetBinanceSymbolNames()) {
                auto symbol_info = g_data_box->market_info->FindSymbolInfo(symbol);

                struct tm *u;
                char *f;
                const time_t timer = time(NULL);
                u = localtime(&timer);
                f = HELPERS::settime(u);

                if (symbol_info && balance) {
                    if (symbol_info->binance_base_cur() == currency) {
                        symbol_info->bid_limit(balance * balance_moderator);
                    } else if (symbol_info->binance_quote_cur() == currency) {
                        symbol_info->ask_limit(balance * balance_moderator);
                    }
                }
            }
        } else {
            result = false;
        }
    }
    return result;
}


bool FUNCTIONS::Parse_Binance_Best_Price_Symbol(std::shared_ptr <std::string> msg, const std::string &symbol){
    if (!msg || msg->size() == 0) {
        auto msg = make_shared<string>("Invalid Parse_Binance_Best_Price_Symbol");
        g_data_box->log_box->Push(msg, DATA::TYPES::Log_Type::ERR_MODEL);
        return false;
    }

    Document doc;
    doc.Parse(msg->c_str());

    auto  symbol_info = g_data_box->market_info->FindSymbolInfo(symbol);
    if(symbol_info){
        double bidPrice,askPrice;
        if(doc.HasMember("bidPrice") && doc["bidPrice"].IsString()  && doc.HasMember("askPrice") && doc["askPrice"].IsString()){
            bidPrice = atof(doc["bidPrice"].GetString());
            askPrice = atof(doc["askPrice"].GetString());
        }

        if(bidPrice && askPrice){
            symbol_info->binance_ask_price(askPrice);
            symbol_info->binance_bid_price(bidPrice);
            return true;
        }
    }

    return false;
}



list<OrderReportItem> FUNCTIONS::Parse_Active_BinanceTrade(Task_Type task_type, shared_ptr<string> msg) {
    list<OrderReportItem> result;
    if (!msg || msg->size() == 0) {
        auto msg = make_shared<string>("Invalid Parse_Active_BinanceTrade");
        g_data_box->log_box->Push(msg, DATA::TYPES::Log_Type::ERR_MODEL);

        return result;
    }

    Document doc;
    doc.Parse(msg->c_str());
    if (doc.IsObject() && doc.HasMember("orderId") && doc["orderId"].IsInt64()
        && doc.HasMember("fills") && doc["fills"].IsArray()) {
        long long group_id = doc["orderId"].GetInt64();
        for (auto& it : doc["fills"].GetArray()) {
            if (it.IsObject() && it.HasMember("price") && it["price"].IsString()
                && it.HasMember("qty") && it["qty"].IsString() && it.HasMember("commission")
                && it["commission"].IsString() && it.HasMember("tradeId") && it["tradeId"].IsInt64()) {
                double price = atof(it["price"].GetString());
                double size = atof(it["qty"].GetString());
                double fee = atof(it["commission"].GetString());
                string order_id = to_string(it["tradeId"].GetInt64());
                if (!isnan(price) && !isnan(size) && !isnan(fee)) {
                    OrderReportItem this_report;
                    this_report.type=doc["side"].GetString() == string("BUY") ? Trade_Type::BUY : Trade_Type::SELL;
                    this_report.price = price;
                    this_report.size = size;
                    this_report.fee = fee;
                    this_report.groupe_id = std::to_string(group_id);
                    this_report.close_id = order_id;
                    result.push_back(this_report);
                }
            }
        }
    }

    return result;
}
