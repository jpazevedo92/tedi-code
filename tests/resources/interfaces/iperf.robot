#/*******************************************************************************
#**                                                                            **
#**  PROJECT   : UAV Command Forward                                           **
#**                                                                            **
#**  AUTHORS   : João Pedro Azevedo          					               **
#**                                                                            **
#**  REMARKS   :                                                               **
#*******************************************************************************/

*** Settings ***
Documentation  Resource file for UAV Command Forward Tests
Library     icmp
Library     iperf    

*** Variables ***

*** Keywords ***
Start iPerf UDP Server
    [Documentation]        Start iPerf udp test server and save log
    [Arguments]            ${port}  ${logfile_name}
    Start Udp Test Server  ${port}  ${logfile_name}

Start Multiple iPerf UDP Server
    [Documentation]        Start iPerf udp test server and save log
    [Arguments]            ${num_servers}  ${logfile_name}
    Start Multiple Udp Test Server  ${num_servers}  ${logfile_name}

Run UDP Test
    [Documentation]        Run UDP Test on client
    [Arguments]            ${client_ip}  ${base_ip}      ${port}          ${interval}   ${test_time}
    ...                    ${bitrate}    ${json_output}  ${logfile_name}  ${repetitions}
    Simple Udp Test        ${client_ip}  ${base_ip}  ${port}         ${interval}
    ...                    ${test_time}  ${bitrate}  ${json_output}  ${logfile_name}    ${repetitions}

Run Multiple UDP Test
    [Documentation]        Run Multiple UDP Test on client
    [Arguments]            ${num_clients}  ${client1_ip}   ${client2_ip}    ${client3_ip}           
    ...                    ${server_ip}    ${interval}      ${test_time}    ${bitrate}    
    ...                    ${json_output}  ${logfile_name}  ${repetitions}

    Multiple Udp Test      ${num_clients}  ${client1_ip}   ${client2_ip}    ${client3_ip}           
    ...                    ${server_ip}    ${interval}      ${test_time}    ${bitrate}           
    ...                    ${json_output}  ${logfile_name}  ${repetitions}      

Stop Multiple iPerf UDP Server
    [Documentation]        Stop iPerf udp test server and save log
    [Arguments]            ${num_servers}
    Stop Multiple Udp Test Server  ${num_servers} 

#Start multiple iPerf UDP Servers