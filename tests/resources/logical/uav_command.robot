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
Library        icmp
Library        utils
Resource       iperf.robot


*** Variables ***
${BASE_IP}    10.0.10.1
${UAV1_IP}    10.0.10.2
${UAV2_IP}    10.0.12.2
${UAV3_IP}    10.0.23.2

*** Keywords ***
Simple ICMP Test
    [Documentation]                     Simple ICMP Ping Test
    [Arguments]                         ${uav_ip}  ${count}  ${repetitions}
    multiple icmp ping                  ${uav_ip}  ${count}  ${repetitions}

UDP Test
    [Documentation]                     Simple UDP iperf Test
    [Arguments]                         ${client_ip}  ${port}         ${interval}      ${test_time}
    ...                                 ${bitrate}    ${json_output}  ${logfile_name}  ${repetitions}
    Start iPerf UDP Server              ${port}       ${logfile_name}
    Run UDP Test                        ${client_ip}  ${BASE_IP}      ${port}          ${interval}
    ...                                 ${test_time}  ${bitrate}      ${json_output}   ${logfile_name}  ${repetitions}

UDP Simultaneous Test
    [Documentation]                     UDP Simultaneous Clients transmitting
    [Arguments]                         ${num_uavs}      ${interval}      ${test_time}   ${bitrate} 
    ...                                 ${json_output}   ${logfile_name}  ${repetitions}
    Start Multiple iPerf UDP Server     ${num_uavs}     ${logfile_name}

    Run Keyword If  ${num_uavs} == 2 
          ...   Run Multiple UDP Test               ${num_uavs}     ${UAV1_IP}       ${UAV1_IP}       None           
                ...                                 ${BASE_IP}      ${interval}      ${test_time}     ${bitrate}      
                ...                                 ${json_output}  ${logfile_name}  ${repetitions}
    ...   ELSE
          ...   Run Multiple UDP Test               ${num_uavs}     ${UAV1_IP}      ${UAV2_IP}       ${UAV3_IP}           
                ...                                 ${BASE_IP}      ${interval}     ${test_time}     ${bitrate}    
                ...                                 ${json_output}  ${logfile_name}  ${repetitions}
