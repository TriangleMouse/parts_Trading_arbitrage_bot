cmake_minimum_required(VERSION 3.17)
project(tradebot)

set(CMAKE_CXX_STANDARD 17)

# BOOST PACKAGE

set(Boost_USE_MULTITHREADED      ON) # Default ON
set(Boost_USE_STATIC_LIBS        ON) # Default OFF
set(Boost_USE_DEBUG_RUNTIME     OFF) # Default ON
set(Boost_USE_DEBUG_PYTHON      OFF) # Default OFF
set(Boost_USE_STLPORT           OFF) # Default OFF
find_package(Boost REQUIRED COMPONENTS
        atomic
        chrono
        date_time
       exception
      filesystem
      program_options
      random
      regex
      system
      serialization
        thread
      )
IF (!Boost_FOUND)
    MESSAGE("*** ERROR *** Boost package not found")
    RETURN()
ENDIF ()
include_directories(${Boost_INCLUDE_DIRS})
MESSAGE("Boost_INCLUDE_DIRS:\t" ${Boost_INCLUDE_DIRS})

# Open SSL Package
set(OpenSSL_INCLUDE /usr/local/opt/openssl/include)
set(OpenSSL_LIBRARIES
        /usr/local/opt/openssl/lib/libcrypto.dylib
        /usr/local/opt/openssl/lib/libssl.dylib
        )
include_directories(${OpenSSL_INCLUDE})


# Microsoft RESTful API Package
 set(CppREST_INCLUDE /usr/local/opt/cpprestsdk/include)
 set(CppREST_LIBRARIES /usr/local/opt/cpprestsdk/lib/libcpprest.dylib)
 include_directories(${CppREST_INCLUDE})

# Parse Json
 set(RapidJSON_INCLUDE /usr/local/opt/rapidjson/include)
 include_directories(${RapidJSON_INCLUDE})

# Compile and link
# Build the core library and executable
#set(SOURCE_FILES main.cpp)
set(LINK_LIBRARIES
        #${Boost_LIBRARIES}
        ${OpenSSL_LIBRARIES}
        ${CppREST_LIBRARIES}
        )

set(SOURCE_FILES src/main.cpp src/helpers/math.cpp
        src/data/types/double.cpp
        src/helpers/hmac_sha256.hpp
        src/helpers/non_copyable.h
        src/functions/binance_api_functions.cpp
        src/functions/binance_parse_functions.cpp
        src/threads/http_client.h
        src/helpers/locker.h
        src/data/types/symbol_status.cpp
        src/data/types/symbol_sub_status.h
        src/data/types/symbol_name.cpp
        src/threads/orderbook_thread.cpp
        src/threads/my_thread.h
        src/data/data_box.h
        src/data/log_creator_msg_queue.cpp
        src/data/types/log_type.cpp
        src/data/types/symbol_information.cpp
        src/data/types/symbol_information.h
        src/data/types/market_type.cpp
        src/data/types/market_type.h
        src/data/types/market_item.h
        src/data/local_config.h
        src/data/stock_market.cpp
        src/data/stock_market.h
        src/data/stock_market_info.cpp
        src/data/stock_market_info.h
        src/data/market.cpp
        src/data/market.h
        src/data/order_links.cpp
        src/data/order_links.h
        src/data/types/order.cpp
        src/data/types/order.h
        src/data/types/trade_type.cpp
        src/data/types/trade_type.h
        src/data/types/order_type.cpp
        src/data/types/order_type.h
        src/functions/parse_config_functions.cpp
        src/functions/parse_config_functions.h
        src/threads/config_thread.cpp src/threads/config_thread.h src/functions/aserco_api_functions.cpp src/functions/aserco_api_functions.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})