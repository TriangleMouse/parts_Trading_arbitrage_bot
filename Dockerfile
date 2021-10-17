FROM debian:stretch
LABEL tradebot.version="1.0.0"

RUN apt update
RUN apt -y install g++ make autoconf libssl-dev libboost-all-dev libcpprest-dev git libcrypto++-dev libcpprest gdbserver
RUN mkdir /tradebot
RUN git clone --depth=1 https://github.com/Tencent/rapidjson.git /rapidjson
RUN git clone --depth=1 https://github.com/zaphoyd/websocketpp.git /websocketpp
