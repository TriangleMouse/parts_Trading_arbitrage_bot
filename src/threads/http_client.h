//
// Created by Артем Белявский on 8/11/21.
//

#ifndef TRADEBOT_HTTP_CLIENT_H
#define TRADEBOT_HTTP_CLIENT_H

#include "cpprest/http_client.h"
#include <ctime>

namespace THREADS {
  extern web::http::client::http_client* g_aserco_client; //изменить название
    extern web::http::client::http_client* g_moscowExchange_secret_client;
    extern web::http::client::http_client* g_moscowExchange_public_client;
    extern web::http::client::http_client* g_binance_secret_client;
    extern web::http::client::http_client* g_binance_public_client;
}
#endif //TRADEBOT_HTTP_CLIENT_H
