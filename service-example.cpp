/*
 * @Author: https://github.com/haohaoalt
 * @Date: 2023-08-16 17:58:11
 * @LastEditors: haohaoalt haohaoalt@163.com
 * @LastEditTime: 2023-08-16 18:14:02
 * @FilePath: /someip_demo/service-example.cpp
 * @Description:
 * Copyright (c) 2023 by haohaoalt@163.com, All Rights Reserved.
 */
/*
 * @Author: https://github.com/haohaoalt
 * @Date: 2023-08-16 15:14:36
 * @LastEditors: haohaoalt haohaoalt@163.com
 * @LastEditTime: 2023-08-16 15:14:37
 * @FilePath: /someip_demo/service.cpp
 * @Description:
 * Copyright (c) 2023 by haohaoalt@163.com, All Rights Reserved.
 */
#include <iomanip>
#include <iostream>
#include <sstream>

#include <vsomeip/vsomeip.hpp>

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421
#define SAMPLE_EVENTGROUP_ID 0x001
#define SAMPLE_EVENT_ID 0x002

std::shared_ptr<vsomeip::application> app;

void on_message(const std::shared_ptr<vsomeip::message> &_request)
{

    std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload();
    vsomeip::length_t l = its_payload->get_length();

    // Get payload
    std::stringstream ss;
    for (vsomeip::length_t i = 0; i < l; i++)
    {
        ss << std::setw(2) << std::setfill('0') << std::hex
           << (int)*(its_payload->get_data() + i) << " ";
    }

    std::cout << "SERVICE: Received message with Client/Session ["
              << std::setw(4) << std::setfill('0') << std::hex << _request->get_client() << "/"
              << std::setw(4) << std::setfill('0') << std::hex << _request->get_session() << "] "
              << ss.str() << std::endl;

    // Send response
    std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request);
    its_payload = vsomeip::runtime::get()->create_payload();
    std::vector<vsomeip::byte_t> its_payload_data;
    for (int i = 9; i >= 0; i--)
    {
        its_payload_data.push_back(i % 256);
    }
    its_payload->set_data(its_payload_data);
    its_response->set_payload(its_payload);
    app->send(its_response);

    // Notify event
    const vsomeip::byte_t its_data[] = {0x10};
    its_payload = vsomeip::runtime::get()->create_payload();
    its_payload->set_data(its_data, sizeof(its_data));
    app->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_payload);
}

int main()
{

    app = vsomeip::runtime::get()->create_application("World");

    std::set<vsomeip::eventgroup_t> its_groups;
    its_groups.insert(SAMPLE_EVENTGROUP_ID);

    app->init();
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
    app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->offer_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_groups);
    app->start();
}