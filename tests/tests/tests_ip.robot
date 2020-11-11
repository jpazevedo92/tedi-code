#/*******************************************************************************
#**                                                                            **
#**  PROJECT   : UAV Command Forward                                           **
#**                                                                            **
#**  AUTHORS   : João Pedro Azevedo          					               **
#**                                                                            **
#*******************************************************************************/

*** Settings ***
Documentation    Automated Test Suite for IP Routing Method
Resource         uav_command.robot      

Default Tags     UAV  IP
Suite Setup		 Clean Log Files

*** Test Cases ***
T1 - ICMP Ping - Base --> UAV1
	[Documentation]	Get the max, min and avg values of icmp ping 
	Simple ICMP Test    ${UAV1_IP}  5   10

T2 - ICMP Ping - Base --> UAV2
	[Documentation]	Get the max, min and avg values of icmp ping 
	Simple ICMP Test    ${UAV2_IP}  5   10

T3 - ICMP Ping - Base --> UAV3
	[Documentation]	Get the max, min and avg values of icmp ping
	Simple ICMP Test    ${UAV3_IP}  5   10

T4 - Iperf3 UDP test with 10Mb/s bitrate- UAV1 --> Base
	[Documentation]	Get the status from Iperf3 test
	UDP Test  ${UAV1_IP}  5001  1  30  10m  yes  T4  10

T5 - Iperf3 UDP test with 10Mb/s bitrate- UAV2 --> Base
	[Documentation]	Get the status from Iperf3 test
	UDP Test  ${UAV2_IP}  5002  1  30  10m  yes  T5  10

T6 - Iperf3 UDP test with 10Mb/s bitrate- UAV3 --> Base
	[Documentation]	Get the status from Iperf3 test
	UDP Test  ${UAV3_IP}  5003  1  30  10m  yes  T6  10

T7 - Iperf3 UDP test with 100Mb/s bitrate- UAV1 --> Base
	[Documentation]	Get the status from Iperf3 test
	UDP Test  ${UAV1_IP}  5001  1  30  100m  yes  T7  10

T8 - Iperf3 UDP test with 100Mb/s bitrate- UAV2 --> Base
	[Documentation]	Get the status from Iperf3 test
	UDP Test  ${UAV2_IP}  5002  1  30  100m  yes  T8  10

T9 - Iperf3 UDP test with 100Mb/s bitrate- UAV3 --> Base
	[Documentation]	Get the status from Iperf3 test
	UDP Test  ${UAV3_IP}  5003  1  30  100m  yes  T9  10

T10 - Iperf3 UDP test with 10Mb/s bitrate- UAV1 & UAV2 --> Base
	[Documentation]	Get the status from Iperf3 test
	UDP Simultaneous Test  2  1  30  10m  yes  T10  10

T11 - Iperf3 UDP test with 100Mb/s bitrate- UAV1 & UAV2 --> Base
	[Documentation]	Get the status from Iperf3 test
	UDP Simultaneous Test  2  1  30  100m  yes  T11  10

T12 - Iperf3 UDP test with 10Mb/s bitrate- UAV1 & UAV2 & UAV3 --> Base
	[Documentation]	Get the status from Iperf3 test
	UDP Simultaneous Test  3  1  30  10m  yes  T12  10

T13 - Iperf3 UDP test with 100Mb/s bitrate- UAV1 & UAV2 & UAV3 --> Base
	[Documentation]	Get the status from Iperf3 test
	UDP Simultaneous Test  3  1  30  100m  yes  T13  10
	 