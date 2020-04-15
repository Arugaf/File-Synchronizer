#include "p2p_client.h"

p2p_client::p2p_client() {

}

p2p_client::~p2p_client() {

}

int p2p_client::wait_for_connection() {
    return 1;
}

int p2p_client::process_income_connection() {
    return 1;
}

int p2p_client::ping_connection() {
    return 1;
}

int p2p_client::close_connection() {
    return 1;
}